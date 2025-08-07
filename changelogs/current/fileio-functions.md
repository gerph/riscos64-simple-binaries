### Security
- 

### Added
- stdio: `open_memstream` is now implemented (a POSIX function).
- stdio: The magic `:tt` filename is now supported to reopen the console handles.
- stdio: `fopen` now supports appending to files with the `a` mode.
- clib: Commands now support redirection when supplied on the command line.

### Changed
- clib: The error handler now reports a backtrace when it is called.

### Fixed
- stdio: Fix for `freopen` on stdin, stdout, or stderr causing a backtrace.

### Removed
- 
