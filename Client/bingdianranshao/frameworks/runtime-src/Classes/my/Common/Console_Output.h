#pragma once
#ifndef __CONSOLE_OUTPUT_H__
#define __CONSOLE_OUTPUT_H__

#include "Common_Head.h"

#define console_msg CCLOG

#define MAXERRBUFSIZE 2000

void err_ret(const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_exit(int error, const char *fmt, ...);
void err_dump(const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_quit(const char *fmt, ...);
void err_doit(int errnoflag, int error, const char *fmt, va_list ap);

#endif // !__CONSOLE_OUTPUT_H__
