#include <sys/stat.h>
#include <sys/types.h>

#if 1 /* they might get called by assert (if DEBUG is defined, or NDEBUG is not defined)? */
  int _isatty(int file) {(void)file; return -1;}
  int _fstat(int file, struct stat *st) {(void)file; (void)st; return -1;}
  int _write(int file, char *ptr, int len) {(void)file; (void)ptr; (void)len; return -1;}
  caddr_t _sbrk(int incr) {(void)incr; return (caddr_t)-1;}
  int _getpid(void) {return -1;}
  int _kill(int pid, int sig) {(void)pid; (void)sig; return -1;}
  void _exit(int status) {
    (void)status;
    for (;;) {
      __asm volatile ("bkpt 0");
    }
  }
  int _close(int file) {(void)file; return -1;}
  int _lseek(int file, int offset, int whence) {(void)file; (void)offset; (void)whence; return -1;}
  int _read(int file, char *ptr, int len) {(void)file; (void)ptr; (void)len; return -1;}
#endif

void __assert_func(const char *_file, int _line, const char *_func, const char *_expr) {
  (void)_file;
  (void)_line;
  (void)_func;
  (void)_expr;
  volatile int loop = 1;
  __asm volatile ("bkpt 0");
  do { ; } while( loop );
}
