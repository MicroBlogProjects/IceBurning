#pragma once
#ifndef __CONSOLE_OUTPUT_H__
#define __CONSOLE_OUTPUT_H__

#include "Common.h"

#define MAXLINE 200

static void err_doit(int, int, const char *, va_list);
void err_ret(const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_exit(int error, const char *fmt, ...);
void err_dump(const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_quit(const char *fmt, ...);
static void err_doit(int errnoflag, int error, const char *fmt, va_list ap);


#endif // !__CONSOLE_OUTPUT_H__
