#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <stdio.h>
#include <map>

#define LOG_TO_STDERR   "stderr"

#define LOG_TRACE       0x01
#define LOG_DEBUG       0x02
#define LOG_INFO        0x04
#define LOG_WARNING     0x08
#define LOG_ERROR       0x10
#define LOG_FATAL       0x20
#define LOG_ALL         0xFF

#define LOG_T(Message) __LOG->Write(LOG_TRACE, Message, std::string(__FILE__), __LINE__)
#define LOG_D(Message) __LOG->Write(LOG_DEBUG, Message, std::string(__FILE__), __LINE__)
#define LOG_I(Message) __LOG->Write(LOG_INFO, Message, std::string(__FILE__), __LINE__)
#define LOG_W(Message) __LOG->Write(LOG_WARNING, Message, std::string(__FILE__), __LINE__)
#define LOG_E(Message) __LOG->Write(LOG_ERROR, Message, std::string(__FILE__), __LINE__)
#define LOG_F(Message) __LOG->Write(LOG_FATAL, Message, std::string(__FILE__), __LINE__)

class SimpleLog
{
public:
    SimpleLog();
    ~SimpleLog();
    bool Create(const std::string &FileName);
    void Write(const unsigned char &LogLevel, const std::string &Text, const std::string &CppFile, const int &CppLine);
    void SetLogLevel(const unsigned char &LogLevel);
private:
    FILE *_LogFile;
    unsigned char _LogLevel;
    std::map<unsigned int, std::string> _LogLevelStr;

    void GetFormattedHeader(const std::string &Path, const int &Line, std::string *Out);
};

extern SimpleLog *__LOG;

#endif /* LOGFILE_H_ */
