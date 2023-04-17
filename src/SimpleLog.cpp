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

SimpleLog::SimpleLog() {
    _LogLevel = LOG_ALL;
    _LogFile = NULL;
    _LogLevelStr[LOG_TRACE]     = "T";
    _LogLevelStr[LOG_DEBUG]     = "D";
    _LogLevelStr[LOG_INFO]      = "I";
    _LogLevelStr[LOG_WARNING]   = "W";
    _LogLevelStr[LOG_ERROR]     = "E";
    _LogLevelStr[LOG_FATAL]     = "F";
}

SimpleLog::~SimpleLog() {
    if (_LogFile != NULL 
            && _LogFile != stderr) 
    {
        fclose(_LogFile);
        _LogFile = NULL;
    }
}

bool SimpleLog::Create(const std::string &FileName) {
    if (FileName.compare(LOG_TO_STDERR) == 0) {
        _LogFile = stderr;
        return true;
    }
    if ((_LogFile = fopen(FileName.c_str(), "at")) == NULL) {
        return false;
    }
    return true;
}

void SimpleLog::Write(const unsigned char &LogLevel, const std::string &Text, const std::string &CppFile, const int &CppLine) { 
    std::string Header;
    GetFormattedHeader(CppFile, CppLine, &Header);
    if (_LogLevel & LogLevel) {
        fprintf(_LogFile, "%s %s: %s\n", Header.c_str(), _LogLevelStr[LogLevel].c_str(), Text.c_str());
        fflush(_LogFile);
    }
}

void SimpleLog::SetLogLevel(const unsigned char &LogLevel) {
    _LogLevel = LogLevel;
}

void SimpleLog::GetFormattedHeader(const std::string &Path, const int &Line, std::string *Out) {
    //Format date and time
    char DateTime[25] = {0x00};
#ifndef WIN32
    struct tm tm_time;
    time_t tm;
    time(&tm);
    memcpy(&tm_time, localtime(&tm), sizeof(tm_time));
    snprintf(DateTime, sizeof(DateTime), "%02i.%02i.%02i %02i:%02i:%02i", tm_time.tm_mday, tm_time.tm_mon + 1,
            tm_time.tm_year + 1900, tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
#else
    SYSTEMTIME SysTime;
    GetLocalTime(&SysTime);
    _snprintf(DateTime, sizeof(DateTime), "%02i.%02i.%02i %02i:%02i:%02i", SysTime.wDay, SysTime.wMonth, 
              SysTime.wYear, SysTime.wHour, SysTime.wMinute, SysTime.wSecond);
#endif
    //Format source code file and source code line
    char StrLine[15] = {0x00};
    snprintf(StrLine, sizeof(StrLine), "%i", Line);
    size_t Position = Path.find_last_of("/\\");
    if (Position != std::string::npos) {
        *Out = std::string(DateTime) + " " + Path.substr(Position + 1) + ":" + StrLine;
    } else {
        *Out = std::string(DateTime) + " " + Path + ":" + StrLine;
    }
}
