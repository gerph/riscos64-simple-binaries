#!/usr/bin/python
"""
Decode the ChangeLog files.

The ChangeLog format is a Markdown file using the format:

    ## <version number>

    ### <group>
    - <change>
"""

import md


default_groups = [
        'Security',
        'Added',
        'Changed',
        'Fixed',
        'Removed'
    ]


class ChangelogBase(object):
    version = None
    mdf = None

    def __init__(self):
        self.groups = dict((group, []) for group in default_groups)

    def changes(self):
        """
        Count the number of changes in the changelog
        """
        return sum(len(values) for values in self.groups.values())

    def __repr__(self):
        return "<{}({} groups, {} change(s))>".format(self.__class__.__name__,
                                                      len(self.groups),
                                                      self.changes())

    def __getitem__(self, index):
        return self.groups.get(index, [])

    def md(self, all_groups=True):
        """
        Return the markdown representation of the structured elements.
        """

        # Make a list of the groups, starting with the default ones
        groups = default_groups[:]
        for group in sorted(self.groups):
            if group not in groups:
                groups.append(group)

        lines = []
        if self.version:
            lines.append('## {}'.format(self.version))
            lines.append('')

        for group in groups:
            values = self.groups[group]
            if len(values) or all_groups:
                lines.append('### {}'.format(group))
                for value in values:
                    lines.append('- {}'.format(value))
                lines.append('')

        return lines


class ChangelogFile(ChangelogBase):
    """
    Comprises the content of a single changelog file.
    """
    version = None

    def __init__(self, fn=None):
        super(ChangelogFile, self).__init__()
        self.filename = fn
        self.mdf = md.MDFile(fn)

        # Parse information out of the file, assuming that it's correctly formed.
        in_group = None
        for block in self.mdf:
            if isinstance(block, md.MDBlockHeading):
                if block.level == 2:
                    # The main version number
                    self.version = block.content
                elif block.level == 3:
                    # A grouping
                    group = block.content
                    if group not in self.groups:
                        # FIXME: Issue warning that the group isn't known?
                        self.groups[group] = []
                    in_group = self.groups[group]
                else:
                    raise RuntimeError("MDHeading with level {} not supported".format(block.level))

            elif isinstance(block, md.MDBlockBullet):
                if block.level == 0:
                    if block.content:
                        # Only add the content if the item isn't empty.
                        in_group.append(block.content)
                else:
                    raise RuntimeError("MDBullet with level {} not supported".format(block.level))

            elif isinstance(block, md.MDBlockBreak):
                # Nothing to do for the line breaks; they're ignorable.
                pass

            else:
                raise RuntimeError("{} object not understood (content={})".format(block.__class__.__name__,
                                                                                  block.content))


class ChangelogCollection(ChangelogBase):
    """
    Collects a number of changelog files into a single file.
    """

    def __init__(self):
        super(ChangelogCollection, self).__init__()
        self.logs = []

    def append(self, fn):
        clf = ChangelogFile(fn)
        self.logs.append(clf)
        for (group, values) in clf.groups.items():
            if group not in self.groups:
                self.groups[group] = []
            self.groups[group].extend(values)
