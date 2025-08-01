"""
Very basic markdown parser.
"""

import sys
import textwrap


class MDBlock(object):

    def __init__(self, mdf, content, level):
        self.mdf = mdf
        self.content = content
        self.level = level

    def __repr__(self):
        content = self.content
        if len(content) > 80:
            content = "{} + <{} chars>".format(content[:40], len(content) - 40)
        return "<{}(level={}, content={})>".format(self.__class__.__name__,
                                                   self.level,
                                                   content)

    def write(self, text):
        sys.stdout.write(text)

    def writeln(self, text):
        sys.stdout.write(text + "\n")

    def writewrapped(self, text, indent=''):
        textwrap.wrap(text, initial_indent='', subsequent_indent=indent)

    def render(self):
        indent = ' ' * self.level
        self.writewrapped(self.content, indent=indent)
        self.writeln("")


class MDBlockText(MDBlock):
    pass


class MDBlockHeading(MDBlock):
    underline_levels = {
            1: '=',
            2: '-',
            3: "'",
        }

    def render(self):
        underline = self.underline_levels[self.level] * len(self.content)
        self.writeln(self.content)
        self.writeln(underline)


class MDBlockBreak(MDBlock):

    def render(self):
        count = 2 if self.level > 1 else 1
        self.write('\n' * count)


class MDBlockBullet(MDBlock):

    def render(self):
        indent = ' ' * self.level * 4
        self.write(indent)
        self.write('* ')
        indent += '  '
        self.writewrapped(self.content, indent=indent)
        self.writeln("")


class MDFile(object):
    """
    Very basic markdown file parser.

    Block level elements are the only ones recognised:
        # <name>
            - heading

        <text>
            - plain text, may be indented

        * <text>
        - <text>
            - bulleted text, with indents of 4 characters per level.

        <blank>
            - paragraph break.
    """
    mdbreak = MDBlockBreak
    mdbullet = MDBlockBullet
    mdheading = MDBlockHeading
    mdtext = MDBlockText

    def __init__(self, filename=None):
        self.blocks = []
        if filename:
            self.read(filename)

    def __repr__(self):
        return "<{}({} block(s))>".format(self.__class__.__name__,
                                          len(self.blocks))

    def __iter__(self):
        for block in self.blocks:
            yield block

    def read(self, filename):
        self.filename = filename
        last_block = None
        with open(filename, 'r') as fh:
            for line in fh:
                line = line.rstrip()

                # Work out what the indent is (and strip it)
                lenwas = len(line)
                line = line.lstrip(' ')
                indent = ' ' * (lenwas - len(line))

                block = None

                if line == '':
                    # Break
                    if last_block:
                        if isinstance(last_block, MDBlockBreak):
                            last_block.level += 1
                        else:
                            block = self.mdbreak(self, '', 1)

                elif indent == '' and line and line[0] == '#':
                    # Deal specially with headings
                    lenwas = len(line)
                    line = line.lstrip('#')
                    level = lenwas - len(line)

                    line = line.lstrip()
                    block = self.mdheading(self, line, level)

                else:
                    if line[0:2] in ('* ', '- ', '*', '-'):
                        block = self.mdbullet(self, line[2:], len(indent) / 4)
                    else:
                        block = self.mdtext(self, line, len(indent))

                if block:
                    self.blocks.append(block)
                    last_block = block
