#include "SimpleLog.h"
#ifndef WIN32
#include <cstdio>
#include <cstring>
#else
#include <windows.h>
#include <winbase.h>
#include <time.h>
#endif
#include <ctime>

#define LOG_EVERYTHING 0xFFFF

SimpleLog::SimpleLog() {
    _LogLevel = LOG_EVERYTHING;
    _LogFile = NULL;
}

SimpleLog::~SimpleLog() {
    if (_LogFile != NULL && _LogFile != stderr) {
        fclose(_LogFile);
    }
}

bool SimpleLog::Create(std::string FileName) {
    if (FileName.compare("stderr") == 0) {
        _LogFile = stderr;
        return true;
    }
    if ((_LogFile = fopen(FileName.c_str(), "at")) == NULL) {
        return false;
    }
    return true;
}

void SimpleLog::Write(unsigned int LogLevel, std::string Text, std::string CppFile, int CppLine) { 
    if (_LogLevel & LogLevel) {
        fprintf(_LogFile, "%s (%s) - %s\n", GetDateTime().c_str(), GetFileAndLine(CppFile, CppLine).c_str(), Text.c_str());
        fflush(_LogFile);
    }
}

void SimpleLog::SetLogLevel(unsigned int LogLevel) {
    _LogLevel = LogLevel;
}

std::string SimpleLog::GetFileAndLine(std::string Path, int Line) {
    std::string Result;
    size_t Found = Path.find_last_of("/\\");
    if (Found != std::string::npos) {
        Path = Path.substr(Found + 1);
        Path += ":" + IntToStr(Line);
    }
    return Path;
}

std::string SimpleLog::IntToStr(int Number) {
    char Buffer[15];
    sprintf(Buffer, "%i", Number);
    return std::string(Buffer);
}

std::string SimpleLog::GetDateTime() {
    char Result[50];
#ifndef WIN32
    struct tm tm_time;
    time_t tm;
    time(&tm);
    memcpy(&tm_time, localtime(&tm), sizeof(tm_time));
    snprintf(Result, 50, "[%02i.%02i.%02i %02i:%02i:%02i]", tm_time.tm_mday, tm_time.tm_mon + 1,
            tm_time.tm_year + 1900, tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
#else
    SYSTEMTIME SysTime;
    GetLocalTime(&SysTime);
    _snprintf(Result, 50, "[%02i.%02i.%02i %02i:%02i:%02i]", SysTime.wDay, SysTime.wMonth, 
              SysTime.wYear, SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
#endif
    return std::string(Result);
}