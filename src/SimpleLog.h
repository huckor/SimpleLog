#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <stdio.h>

#define DEBUG            0x00000001
#define INFO             0x00000002
#define WARNING          0x00000004

#define LOG(Level, Message) __LOG->Write(Level, Message, std::string(__FILE__), __LINE__)

class SimpleLog
{
public:
    SimpleLog();
    ~SimpleLog();
    bool Create(std::string FileName);
    void Write(unsigned int LogLevel, std::string Text, std::string CppFile, int CppLine);
    void SetLogLevel(unsigned int LogLevel);
private:
    FILE *_LogFile;
    unsigned long _LogLevel;

    std::string GetFileAndLine(std::string Path, int Line);
    std::string IntToStr(int Number);
    std::string GetDateTime();
};

extern SimpleLog *__LOG;

#endif /* LOGFILE_H_ */
