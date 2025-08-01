#!/usr/bin/env python
"""
Command line tool for managing the changelogs.

The 'current' directory contains log files that contain the changes for each branch.
These will be collected into a release at release time.

The 'releases' directory contains the log files that have been collected for each
release.

Usage:

    ./cli.py full-changelog
        - Displays the current logs, followed by the historic logs.
          Includes the 'header.md' file at the start, and the 'footer.md' file
          at the end.

    ./cli.py edit [<name>]
        - Edits the current log (for the current branch if no name given),
          creating a file if necessary.

    ./cli.py current [<version>]
        - Displays the current log, with a specific version if supplied

    ./cli.py collate <version>
        - Collects the content of the current version and writes it into the
          specified version file.
"""

import argparse
import datetime
import os
import re
import subprocess
import sys

import changelog
import editor


this_dir = os.path.dirname(__file__)
releases_dir = os.path.join(this_dir, 'releases')
current_dir = os.path.join(this_dir, 'current')


def locate_released_logs():
    """
    Return the version numbers and filenames of the logs.

    @return: dict keyed by the tuple of the version number, with the value the filename.
    """
    mdfiles = [fn for fn in os.listdir(releases_dir) if fn.endswith('.md')]
    versions = {}
    for fn in mdfiles:
        try:
            # Trim the .md
            numstring = fn[:-3]
            version = tuple(int(n) for n in numstring.split('.'))
            versions[version] = os.path.join(releases_dir, fn)
        except ValueError:
            # Any file that isn't a version number is just ignored
            pass

    return versions


def released_logs():
    """
    Collect all the released logs togther.

    @return: List of ChangelogFile objects, in descending order.
    """
    versions = locate_released_logs()
    logs = []
    for version, fn in sorted(versions.items(), reverse=True):
        clf = changelog.ChangelogFile(fn)
        logs.append(clf)

    return logs


def locate_current_logs():
    """
    Locate the filenames of all the log files for the current version.

    @return: list of filenames
    """
    mdfiles = []
    if os.path.isdir(current_dir):
        mdfiles = [fn for fn in os.listdir(current_dir) if fn.endswith('.md')]
    mdfiles = sorted(mdfiles)
    if 'master.md' in mdfiles:
        # Move the master entry to the front
        mdfiles.remove('master.md')
        mdfiles.insert(0, 'master.md')
    return [os.path.join(current_dir, fn) for fn in mdfiles]


def current_log(version='[UNRELEASED]', base_changelog=None):
    """
    Collect the current log.

    @return: A ChangelogCollection object containing the collected entries.
    """
    logfiles = locate_current_logs()
    clc = changelog.ChangelogCollection()
    if base_changelog:
        clc.append(base_changelog)

    clc.version = version
    for fn in logfiles:
        clc.append(fn)

    return clc


def todays_date():
    """
    The date, in log format.
    """
    return datetime.date.today().strftime('%d %h %Y')


def get_header():
    """
    Return the content in the header file.
    """
    fn = os.path.join(this_dir, 'header.md')
    if os.path.isfile(fn):
        with open(fn, 'r') as fh:
            return fh.read()
    return ''


def get_footer():
    """
    Return the content in the footer file.
    """
    fn = os.path.join(this_dir, 'footer.md')
    if os.path.isfile(fn):
        with open(fn, 'r') as fh:
            return fh.read()
    return ''


class Git(object):

    @classmethod
    def run(cls, args):
        cmd = ['git']
        cmd.extend(args)
        return subprocess.check_call(cmd)

    @classmethod
    def capture(cls, args):
        cmd = ['git']
        cmd.extend(args)
        return subprocess.check_output(cmd)

    @classmethod
    def branch_name(cls):
        """
        Get the name of the current branch.
        """
        branch = cls.capture(['branch', '--show-current']).strip()
        if not branch:
            # If we're in the middle of a rebase or otherwise behind the main branch,
            # the above branch will be empty.
            text = cls.capture(['rev-parse', 'HEAD']).strip()
            if text.startswith('HEAD '):
                text = text[6:]
                if '~' in text:
                    (text, count) = text.split('~')
            else:
                # We don't recognise the branch.
                return None

        if not isinstance(branch, str):
            # Convert from (probably) bytes to a regular unicode string
            branch = branch.decode('utf-8')
        return branch

    @classmethod
    def add_file(cls, fn):
        """
        Add a given file to git.
        """
        return cls.run(['add', '--', fn])

    @classmethod
    def remove_file(cls, fn, force=False):
        """
        Remove a given file from git.
        """
        cmd = ['rm']
        if force:
            cmd.append('--force')
        cmd.append('--')
        cmd.append(fn)
        return cls.run(cmd)


class Command(object):
    title_re = re.compile(r'([^A-Z])([A-Z])')

    def __init__(self):
        pass

    @property
    def name(self):
        name = self.__class__.__name__
        if name.startswith('Command'):
            name = name[7:]
        name = self.title_re.sub(r'\1-\2', name).lower()
        return name

    def setup_parser(self, parser):
        raise NotImplementedError()

    def execute(self, args):
        raise NotImplementedError()


class CommandFullChangelog(Command):

    def setup_parser(self, parser):
        pass

    def execute(self, args):
        header = get_header()
        if header:
            print(header)
            print("")

        # Show the current, unreleased version
        clc = current_log()
        if clc.changes():
            # Only show the current log if there's something present.
            lines = clc.md(all_groups=False)
            for line in lines:
                print(line)
            print("")

        # Show the released logs
        for clf in released_logs():
            lines = clf.md(all_groups=False)
            for line in lines:
                print(line)
            print("")

        footer = get_footer()
        if footer:
            print(footer)
            print("")


class CommandCollate(Command):

    def setup_parser(self, parser):
        parser.add_argument('version',
                            help="Specify the version number to apply the the collated log")

    def execute(self, args):
        release_file = os.path.join(releases_dir, '{}.md'.format(args.version))
        base_changelog = None
        if os.path.isfile(release_file):
            # If the file already exists we should use it as the basis for
            # the current log.
            base_changelog = release_file

        clc = current_log(base_changelog=base_changelog)
        date = todays_date()
        clc.version = '{} ({})'.format(args.version, date)

        # Create the collated log
        lines = clc.md(all_groups=False)
        with open(release_file, 'w') as fh:
            for line in lines:
                fh.write('{}\n'.format(line))

        # Remove the files that built it
        for clf in clc.logs:
            if clf.filename != release_file:
                Git.remove_file(clf.filename, force=True)

        # Add the new collated log
        Git.add_file(release_file)


class CommandCurrent(Command):

    def setup_parser(self, parser):
        parser.add_argument('version',
                            default=None,
                            nargs='?',
                            help="Specify the version number of the current version")

    def execute(self, args):
        # Show the current, unreleased version
        clc = current_log()
        if args.version:
            date = todays_date()
            clc.version = '{} ({})'.format(args.version, date)
        if clc.changes:
            # Only show the current log if there's something present.
            lines = clc.md(all_groups=False)
            for line in lines:
                print(line)
            print("")


class CommandEdit(Command):

    def setup_parser(self, parser):
        parser.add_argument('--no-edit',
                            action='store_true',
                            help="Disable the editing; just ensure that the record exists")
        parser.add_argument('name',
                            default=None,
                            nargs='?',
                            help="Name of the new changelog entry to create")

    def execute(self, args):
        branch = Git.branch_name() or 'change'
        fn = os.path.join(current_dir, "{}.md".format(branch))

        # If the file doesn't exist, create a template
        if not os.path.isfile(fn):
            if not os.path.isdir(current_dir):
                os.makedirs(current_dir)

            clf = changelog.ChangelogFile()

            # Create an empty entry for each group, so that there's an obvious
            # pattern to continue
            for group in clf.groups.values():
                group.append('')

            with open(fn, 'w') as fh:
                fh.write('\n'.join(clf.md()))

        if not args.no_edit:
            edit = editor.HostEditor()
            status = edit.edit_inplace(fn)
            if status == 0:
                Git.add_file(fn)
        else:
            # Just print the filename
            print(fn)


class CommandStatisticsTable(Command):

    def setup_parser(self, parser):
        parser.add_argument('--output',
                            default=None,
                            nargs='?',
                            help="Filename to write output to (defaults to stdout)")
        parser.add_argument('--current',
                            action='store_true',
                            help="Include the current change log in the table")

    def execute(self, args):
        all_logfiles = locate_released_logs()

        ordered_releases = sorted(all_logfiles.keys())
        headings = ['Release']
        headings.extend(['{}.{:02d}'.format(key[0], key[1]) for key in ordered_releases])

        # Accumulate the counts for each change type
        all_changelogs = dict((key, changelog.ChangelogFile(filename)) for key, filename in all_logfiles.items())

        if args.current:
            clc = current_log()
            headings.append(clc.version)
            ordered_releases.append(clc.version)
            all_changelogs[clc.version] = clc

        rows = []
        for group in changelog.default_groups:
            row = [group]
            for release in ordered_releases:
                cl = all_changelogs[release]
                row.append(len(cl[group]))
            rows.append(row)

        # Add the totals row
        row = ["TOTAL"]
        for release in ordered_releases:
            cl = all_changelogs[release]
            row.append(cl.changes())
        rows.append(row)

        # FIXME: We should be able to replace this with CSV output with an option.

        output = []
        # FIXME: Add an option for omitting the style?
        output.extend(["<style>",
                       "<!-- "
                       "table.pyrostats { border: 1px solid black; border-collapse: collapse; }",
                       "table.pyrostats tr { border: 1px solid black; }",
                       "table.pyrostats th { border: 1px solid black; text-align: left; padding: 0.125em 0.25em; }",
                       "table.pyrostats td { border: 1px solid black; text-align: right; padding: 0.125em 0.25em; }",
                       "table.pyrostats .datanone { color: gray; }",
                       "-->"
                       "</style>",
                      ])
        output.append('<table class="pyrostats">')
        output.append('  <tr>')
        output.extend(['    <th>{}</th>'.format(heading) for heading in headings])
        output.append('  </tr>')
        for row in rows:
            output.append('  <tr class="datarow">')
            output.append('    <th>{}</th>'.format(row[0]))
            output.extend(['    <td class="{}">{}</td>'.format("datanone" if value is 0 else "",
                                                               value) for value in row[1:]])
            output.append('  </tr>')
        output.append('</table>')

        if args.output:
            with open(args.output, 'w') as fh:
                fh.write("\n".join(output))
        else:
            sys.stdout.write("\n".join(output))


available_commands = (
        CommandFullChangelog,
        CommandEdit,
        CommandCurrent,
        CommandCollate,
        CommandStatisticsTable,
    )


def main():
    parser = argparse.ArgumentParser()

    subparsers = parser.add_subparsers(help='Commands',
                                       dest='cmd')

    dispatch = {}
    for command_class in available_commands:
        command = command_class()

        sp = subparsers.add_parser(command.name)
        command.setup_parser(sp)
        dispatch[command.name] = command

    options = parser.parse_args()

    if options.cmd in dispatch:
        command = dispatch[options.cmd]

        command.execute(options)
    else:
        print("Unrecognised command %s" % (options.cmd,))
        sys.exit(1)


if __name__ == '__main__':
    main()
