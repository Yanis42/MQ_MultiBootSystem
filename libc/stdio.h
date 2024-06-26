#ifndef _STDIO
#define _STDIO

#ifdef __cplusplus
extern "C" {
#endif

#include "ctype.h"
#include "dolphin/types.h"
#include "stdarg.h"
#include "stddef.h"

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define __ungetc_buffer_size 2

typedef unsigned long __file_handle;
typedef unsigned long fpos_t;
typedef unsigned short wchar_t;

enum __file_kinds {
    __closed_file,
    __disk_file,
    __console_file,
    __unavailable_file,
};

enum __file_orientation {
    /* 0x0 */ UNORIENTED,
    /* 0x1 */ CHAR_ORIENTED,
    /* 0x2 */ WIDE_ORIENTED,
};

typedef struct _file_modes {
    unsigned int open_mode : 2;
    unsigned int io_mode : 3;
    unsigned int buffer_mode : 2;
    unsigned int file_kind : 3;
    unsigned int file_orientation : 2;
    unsigned int binary_io : 1;
} file_modes;

enum __io_modes {
    __read = 1,
    __write = 2,
    __read_write = 3,
    __append = 4,
};

enum __io_states {
    __neutral,
    __writing,
    __reading,
    __rereading,
};

enum __io_results {
    __no_io_error,
    __io_error,
    __io_EOF,
};

typedef struct _file_states {
    unsigned int io_state : 3;
    unsigned int free_buffer : 1;
    unsigned char eof;
    unsigned char error;
} file_states;

typedef void (*__idle_proc)(void);
typedef int (*__pos_proc)(__file_handle file, fpos_t* position, int mode, __idle_proc idle_proc);
typedef int (*__io_proc)(__file_handle file, unsigned char* buff, size_t* count, __idle_proc idle_proc);
typedef int (*__close_proc)(__file_handle file);

typedef struct _FILE {
    /* 0x00 */ __file_handle handle;
    /* 0x04 */ file_modes file_mode;
    /* 0x08 */ file_states file_state;
    /* 0x0C */ unsigned char is_dynamically_allocated;
    /* 0x0D */ char char_buffer;
    /* 0x0E */ char char_buffer_overflow;
    /* 0x0F */ char ungetc_buffer[2];
    /* 0x12 */ wchar_t ungetc_wide_buffer[2];
    /* 0x18 */ unsigned long position;
    /* 0x1C */ unsigned char* buffer;
    /* 0x20 */ unsigned long buffer_size;
    /* 0x24 */ unsigned char* buffer_ptr;
    /* 0x28 */ unsigned long buffer_length;
    /* 0x2C */ unsigned long buffer_alignment;
    /* 0x30 */ unsigned long save_buffer_length;
    /* 0x34 */ unsigned long buffer_position;
    /* 0x38 */ __pos_proc position_fn;
    /* 0x3C */ __io_proc read_fn;
    /* 0x40 */ __io_proc write_fn;
    /* 0x44 */ __close_proc close_fn;
    /* 0x48 */ __idle_proc idle_fn;
    /* 0x4C */ struct _FILE* next_file;
} FILE;

typedef struct _files {
    FILE _stdin;
    FILE _stdout;
    FILE _stderr;
    FILE empty;
} files;

#define _IONBF 0
#define _IOLBF 1
#define _IOFBF 2

extern files __files;

#define stdin (&__files._stdin)
#define stdout (&__files._stdout)
#define stderr (&__files._stderr)

int __close_console(__file_handle file);
int __write_console(__file_handle file, unsigned char* buf, size_t* count, __idle_proc idle_fn);
int __read_console(__file_handle file, unsigned char* buf, size_t* count, __idle_proc idle_fn);
void __close_all(void);

int puts(const char* s);
int printf(const char*, ...);
size_t sprintf(char* s, const char* format, ...);
size_t vprintf(const char* format, va_list arg);
size_t vsprintf(char* s, const char* format, va_list arg);
size_t fread(const void*, size_t memb_size, size_t num_memb, FILE*);
size_t fwrite(const void* buffer, size_t memb_size, size_t num_memb, FILE* file);
int fseek(FILE* file, fpos_t offset, int mode);
size_t _fseek(FILE* file, fpos_t offset, int mode);
size_t ftell(FILE* file);
size_t __fwrite(const void*, size_t, size_t, FILE*);

#ifdef __cplusplus
};
#endif

#endif // _STDIO
