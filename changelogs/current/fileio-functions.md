### Security
- 

### Added
- stdio: `open_memstream` is now implemented (a POSIX function).
- stdio: The magic `:tt` filename is now supported to reopen the console handles.
- stdio: `fopen` now supports appending to files with the `a` mode.
- clib: Commands now support redirection when supplied on the command line.
- backtrace: Fix for hex conversion of 0 values not being aligned.

### Changed
- clib: The error handler now reports a backtrace when it is called.
- time: Reading lines or characters from `stdin` now freezes the `clock()`.
- backtrace: Checks for address range of parameters, to identify corrupt stacks.

### Fixed
- stdio: Fix for `freopen` on stdin, stdout, or stderr causing a backtrace.

### Removed
- 
