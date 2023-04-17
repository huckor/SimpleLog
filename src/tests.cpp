#include <iostream>
#include <ostream>
#include <fstream>
#include <cstdio>
#include "SimpleLog.h"

SimpleLog *__LOG;

int main(int argc, const char * argv[]) {
    short TestNo = 0;
#ifndef WIN32
    const std::string Passed = "\x1b[32m PASSED \x1b[0m";
    const std::string Failed = "\x1b[31m !!!FAILED!!! \x1b[0m";
#else
    const std::string Passed = " PASSED ";
    const std::string Failed = " !!!FAILED!!! ";
#endif
    const std::string LogFile = "log.txt";
    std::fstream File;
    std::string Tmp, FileContent;

    __LOG = new SimpleLog();
    
    std::cout << "*********************************************************" << std::endl;
    std::cout << "Test " << ++TestNo << ": Open stderr as log channel" << std::endl;
    std::cout << "*********************************************************" << std::endl;
    if(__LOG->Create(LOG_TO_STDERR)) {
        std::cout << "Test " << TestNo << " - " << Passed << std::endl;
    } else {
        std::cout << "Test " << TestNo << " - " << Failed << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "*********************************************************" << std::endl;
    std::cout << "Test " << ++TestNo << ": Log 'SOME TEXT' to stderr log channel"  << std::endl;
    std::cout << "*********************************************************" << std::endl;
    LOG_D("SOME TEXT");
    std::cout << "Test " << TestNo << " - if you can see 'SOME TEXT' in your console then this test " << Passed << std::endl;
	std::cout << std::endl;

    delete __LOG;


    __LOG = new SimpleLog();

    std::cout << "*********************************************************" << std::endl;
    std::cout << "Test " << ++TestNo << ": Open " << LogFile << " file as log channel"  << std::endl;
    std::cout << "*********************************************************" << std::endl;
    if(__LOG->Create(LogFile)) {
        if (FILE *File = fopen(LogFile.c_str(), "r")) {
            fclose(File);
            std::cout << "Test " << TestNo << " - " << Passed << std::endl;
        } else {
            std::cout << "Test " << TestNo << " - " << Failed << std::endl;
        }
    } else {
        std::cout << "Test " << TestNo << " - " << Failed << std::endl;
    }
	std::cout << std::endl;

    std::cout << "*********************************************************" << std::endl;
    std::cout << "Test " << ++TestNo << ": Log 'SOME TEXT' into " << LogFile << " log channel"  << std::endl;
    std::cout << "*********************************************************" << std::endl;
    LOG_D("SOME TEXT");
    File.open(LogFile, std::ios::in);
    while(getline(File, Tmp)){
        FileContent += Tmp;
    }
    if (FileContent.find("SOME TEXT") != std::string::npos) {
        std::cout << "Test " << TestNo << " - " << Passed << std::endl;   
    } else {
        std::cout << "Test " << TestNo << " - " << Failed << std::endl;
    }
    File.close();
    File.open(LogFile, std::ios::out);
    File.close();
    FileContent.clear();
	std::cout << std::endl;

    std::cout << "*********************************************************" << std::endl;
    std::cout << "Test " << ++TestNo << ": Usage of ALL log level"  << std::endl;
    std::cout << "*********************************************************" << std::endl;
    __LOG->SetLogLevel(LOG_ALL);
    LOG_D("DEBUG TEXT");
    LOG_I("INFO TEXT");
    File.open(LogFile, std::ios::in);
    while(getline(File, Tmp)){
        FileContent += Tmp;
    }
    if (FileContent.find("DEBUG TEXT") != std::string::npos
            && FileContent.find("INFO TEXT") != std::string::npos) {
        std::cout << "Test " << TestNo << " - " << Passed << std::endl;   
    } else {
        std::cout << "Test " << TestNo << " - " << Failed << std::endl;
    }
    File.close();
    File.open(LogFile, std::ios::out);
    File.close();
    FileContent.clear();
	std::cout << std::endl;

    std::cout << "*********************************************************" << std::endl;
    std::cout << "Test " << ++TestNo << ": Usage of DEBUG log level"  << std::endl;
    std::cout << "*********************************************************" << std::endl;
    __LOG->SetLogLevel(LOG_DEBUG);
    LOG_D("DEBUG TEXT");
    LOG_I("INFO TEXT");
    File.open(LogFile, std::ios::in);
    while(getline(File, Tmp)){
        FileContent += Tmp;
    }
    if (FileContent.find("DEBUG TEXT") != std::string::npos
            && FileContent.find("INFO TEXT") == std::string::npos) {
        std::cout << "Test " << TestNo << " - " << Passed << std::endl;   
    } else {
        std::cout << "Test " << TestNo << " - " << Failed << std::endl;
    }
    File.close();
    File.open(LogFile, std::ios::out);
    File.close();
    FileContent.clear();
	std::cout << std::endl;
    
    remove(LogFile.c_str());
    delete __LOG;

    return 0;
}
