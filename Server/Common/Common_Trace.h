#pragma once

#ifndef __COMMON_TRACE_H__
#define __COMMON_TRACE_H__

#include "Common.h"
#include "Console_Output.h"

#include <fcntl.h>

#define TRACE_WARN(fmt, ...) Warn_Log(fmt, ##__VA_ARGS__)
#define TRACE_ERROR(fmt, ...) Error_Log(fmt, ##__VA_ARGS__)

#define Warn_Log(fmt, args...) PrintWarnLog(__FILE__, __LINE__, __FUNCTION__, fmt, ##args)
#define Error_Log(fmt, args...) PrintErrorLog(__FILE__, __LINE__, __FUNCTION__, fmt, ##args)

#define PrintWarnLog(file_name, line_no, func, fmt, args...)                \
        do {                                                                \
            int fd = NS_LG::OpenLogFile(&NS_LG::warn_log_path);             \
            if (fd < 0)                                                     \
            {                                                               \
                err_quit("PrintWarnLog Error...Maybe sudo?");               \
                break;                                                      \
            }                                                               \
            NS_LG::PrintLog(fd, file_name, line_no, func, fmt, ##args);     \
        } while(0)
#define PrintErrorLog(file_name, line_no, func, fmt, args...)               \
        do {                                                                \
            int fd = NS_LG::OpenLogFile(&NS_LG::error_log_path);            \
            if (fd < 0)                                                     \
            {                                                               \
                err_quit("PrintErrorLog Error...Maybe sudo?");              \
                break;                                                      \
            }                                                               \
            NS_LG::PrintLog(fd, file_name, line_no, func, fmt, ##args);     \
        } while(0)

NS_LG_BEGIN

#define PATH_MAX 100
#define LOG_BUF_MAX 200

const std::string warn_log_path = "/data/log/mygame/warn/";
const std::string error_log_path = "/data/log/mygame/error/";

std::string* GetFileName(const struct tm* tm = NULL);
int OpenLogFile(const std::string* path, const std::string* filename = NULL);
void PrintLog(int fd, const char* file_name, int line_no, const char* func, const char* fmt, ...);

NS_LG_END


#endif // !__COMMON_TRACE_H__
