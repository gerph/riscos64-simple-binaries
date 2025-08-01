"""
Managing launching an editor on a file.
"""

import os

##### Temporary directory creation in a context manager

import shutil
import tempfile

class TemporaryDirectory(object):
    """
    Create a temporary directory as a context handler.
    """

    def __init__(self, prefix='', suffix=''):
        self.prefix = prefix
        self.suffix = suffix
        self._dirname = None

    def __repr__(self):
        if self._dirname:
            return "TemporaryDirectory('%s')" % (self._dirname,)

        return "TemporaryDirectory(prefix=%r, suffix=%r)" % (self.prefix, self.suffix)

    def __del__(self):
        self.cleanup()

    def cleanup(self):
        if self._dirname:
            shutil.rmtree(self._dirname, ignore_errors=True)
            self._dirname = None

    @property
    def name(self):
        if not self._dirname:
            self._dirname = tempfile.mkdtemp(prefix=self.prefix, suffix=self.suffix)
        return self._dirname

    def __enter__(self):
        if self._dirname:
            raise RuntimeError('Cannot use a TemporaryDirectory whilst already in use')

        return self.name

    def __exit__(self, exctype, exc, tb):
        self.cleanup()


class HostEditor(object):
    """
    Class for managing the editing of a file.
    """

    @property
    def editor(self):
        editor = os.environ['EDITOR']
        if editor:
            return editor
        editor = os.environ['VISUAL']
        if editor:
            return editor
        raise RuntimeError("No editor configured - set EDITOR, or VISUAL")

    def _edit(self, content='', leafname=None):
        """
        Invoke an editor on content, returning the new content.
        """
        with TemporaryDirectory() as tempdir:
            tempfilename = os.path.join(tempdir, leafname)
            with open(tempfilename, 'w') as fh:
                if content:
                    fh.write(content)

            # FIXME: Escaping?
            command = self.editor + " " + tempfilename
            status = os.system(command)

            with open(tempfilename, 'r') as fh:
                text = fh.read()
            return (status, text)

    def edit(self, data=None, fn=None, leafname=None):
        """
        Edit the content, and then return the edited content.

        @return: tuple of (return code, content)
        """
        if leafname is None:
            if fn:
                leafname = os.path.basename(leafname)
            else:
                # We have to call the file something if they didn't give a name
                leafname = 'Text'

        if fn:
            with open(fn, 'r') as fh:
                data = fh.read()

        return self._edit(data, leafname=leafname)

    def edit_inplace(self, fn):
        """
        Edit the content in a file, and then update the file with the new content.

        The file content is only updated if the return code was 0.

        @return: return code
        """
        (dirname, leafname) = os.path.split(fn)
        (status, data) = self.edit(fn=fn, leafname=leafname)
        if status == 0:
            # FIXME: Should this be w+ with a truncate on the end?
            with open(fn, 'w') as fh:
                fh.write(data)
        return status
