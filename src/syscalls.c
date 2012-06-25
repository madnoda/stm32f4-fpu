#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <reent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "syscalls_if.h"

_ssize_t _read_r(struct _reent *r, int file, void *ptr, size_t len)
{
  char c;
  int  i;
  unsigned char *p;

  p = (unsigned char*)ptr;
  for (i = 0; i < len; i++)
  {
	do{		
		c = getch();
	}while(c == false);
	
    *p++ = c;
	#ifdef ECHOBACK 
		putch(c);
	#endif
	
    if (c == '\r' && i <= (len - 2)) /* 0x0D */
    {
      *p = '\n';					 /* 0x0A */
	  #ifdef ECHOBACK 
		putch('\n');				 /* 0x0A */
	  #endif
      return i + 2;
    }
  }
  return i;
}

_ssize_t _write_r (
    struct _reent *r, 
    int file, 
    const void *ptr, 
    size_t len)
{
	int i;
	const unsigned char *p;
	
	p = (const unsigned char*) ptr;
	
	for (i = 0; i < len; i++) {
		if (*p == '\n' ) putch('\r');
		putch(*p++);
	}
	
	return len;
}

int _close_r(
    struct _reent *r, 
    int file)
{
	return 0;
}

_off_t _lseek_r(
    struct _reent *r, 
    int file, 
    _off_t ptr, 
    int dir)
{
	return (_off_t)0;	/*  Always indicate we are at file beginning.	*/
}


int _fstat_r(
    struct _reent *r, 
    int file, 
    struct stat *st)
{
	/*  Always set as character device.				*/
	st->st_mode = S_IFCHR;	
		/* assigned to strong type with implicit 	*/
		/* signed/unsigned conversion.  Required by 	*/
		/* newlib.					*/

	return 0;
}

#ifdef __GNUC__
int isatty(int file); /* avoid warning */
#endif
int isatty(int file)
{
	return 1;
}


void _exit(int n) {
label:  goto label; /* endless loop */
}

int _getpid(int file)
{
	return 1;
}

int _kill(int file)
{
	return 1;
}

extern char end[];
extern char _heap_end[];
static char *heap_ptr;
void * _sbrk_r(
    struct _reent *_s_r, 
    ptrdiff_t nbytes)
{
	char  *base;
	if (!heap_ptr) {
		heap_ptr = end;
	}
	base = heap_ptr;
	if (heap_ptr + nbytes > _heap_end)
	{
			errno = ENOMEM;
			return (caddr_t) -1;
	}
	heap_ptr += nbytes;
	return base;
}



void * _sbrk(ptrdiff_t incr)
{
  char  *base;
  if (!heap_ptr) heap_ptr = end;
  base = heap_ptr;
	if (heap_ptr + incr > _heap_end)
	{
			errno = ENOMEM;
			return (caddr_t) -1;
	}
  
  heap_ptr += incr;
  return base;
}

int _open(const char *path, int flags, ...)
{
  return 1;
}

int _close(int fd)
{
  return 0;
}

int _fstat(int fd, struct stat *st)
{
  st->st_mode = S_IFCHR;
  return 0;
}

int _isatty(int fd)
{
  return 1;
}


int _lseek(int fd, off_t pos, int whence)
{
  return 0;
}

int _read(int fd, char *buf, size_t cnt)
{
  *buf = getch();

  return 1;
}

int _write(int fd, const char *buf, size_t cnt)
{
  int i;

  for (i = 0; i < cnt; i++)
    putch(buf[i]);

  return cnt;
}

extern char *__exidx_start;
extern char *__exidx_end;

