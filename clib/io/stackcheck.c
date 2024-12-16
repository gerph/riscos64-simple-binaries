#include <stdlib.h>
#include <stdint.h>
#include "kernel.h"
#include "swis_os.h"

#define attribute_relro __attribute__ ((section (".data.rel.ro")))

uintptr_t __stack_chk_guard attribute_relro = 0xFF88211445fe2211ll;

void __attribute__ ((__noreturn__))
     __stack_chk_fail(void)
{
    os_write0("Stack smash detected");
    os_newline();
    os_newline();

    _kernel_backtrace();

    _Exit(1);
}


#include <stdarg.h>
#include <stdio.h>

int __attribute__ ((__optimize__ ("-fno-stack-protector")))
    __printf_chk (int flag, const char *format, ...)
{
  va_list ap;
  int wrote;

  va_start(ap, format);
  wrote = vprintf(format, ap);
  va_end(ap);

  return wrote;
}

int __attribute__ ((__optimize__ ("-fno-stack-protector")))
    __snprintf_chk (char *s, size_t maxlen, int flag, size_t slen, const char *format, ...)
{
  va_list ap;
  int wrote;

  va_start(ap, format);
  wrote = vsnprintf(s, slen, format, ap);
  va_end(ap);

  return wrote;
}

int __attribute__ ((__optimize__ ("-fno-stack-protector")))
    __fprintf_chk (FILE *fh, int flag, const char *format, ...)
{
  va_list ap;
  int wrote;

  va_start(ap, format);
  wrote = vfprintf(fh, format, ap);
  va_end(ap);

  return wrote;
}

int __attribute__ ((__optimize__ ("-fno-stack-protector")))
    __vfprintf_chk (FILE *fh, int flag, const char *format, va_list ap)
{
  int wrote;

  wrote = vfprintf(fh, format, ap);

  return wrote;
}

int __attribute__ ((__optimize__ ("-fno-stack-protector")))
    __vprintf_chk(int flag, const char *format, va_list ap)
{
  int wrote;

  wrote = vprintf(format, ap);

  return wrote;
}

int __attribute__ ((__optimize__ ("-fno-stack-protector")))
    __vsnprintf_chk (char *s, size_t maxlen, int flag, size_t slen, const char *format, va_list ap)
{
  int wrote;

  wrote = vsnprintf(s, slen, format, ap);

  return wrote;
}
