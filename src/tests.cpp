#include <iostream>
#include <ostream>
#include <fstream>
#include <cstdio>
#include "SimpleLog.h"

SimpleLog *__LOG;

int main(int argc, const char * argv[]) {
    short TestNo = 0;

    std::cout << "*********************************************************" << std::endl;
    std::cout << "Test " << ++TestNo << ": Open stderr as log channel" << std::endl;
    std::cout << "*********************************************************" << std::endl;
    __LOG = new SimpleLog();
    if(__LOG->Create("stderr")) {
        std::cout << "Test " << TestNo << " - PASSED" << std::endl;
    } else {
        std::cout << "Test " << TestNo << " - !!!FAILED!!!" << std::endl;
    }
    delete __LOG;
    std::cout << std::endl;
    
    std::cout << "*********************************************************" << std::endl;
    std::cout << "Test " << ++TestNo << ": Log 'SOME TEXT' to stderr log channel"  << std::endl;
    std::cout << "*********************************************************" << std::endl;
    __LOG = new SimpleLog();
    if(__LOG->Create("stderr")) {
        LOG(DEBUG, "SOME TEXT");
        std::cout << "Test " << TestNo << " - if you can see 'SOME TEXT' in your console then this test PASSED" << std::endl;
    } else {
        std::cout << "Test " << TestNo << " - !!!FAILED!!!" << std::endl;
    }
    delete __LOG;
	std::cout << std::endl;

    std::cout << "*********************************************************" << std::endl;
    std::cout << "Test " << ++TestNo << ": Open log.txt file as log channel"  << std::endl;
    std::cout << "*********************************************************" << std::endl;
    __LOG = new SimpleLog();
    if(__LOG->Create("log.txt")) {
        if (FILE *File = fopen("log.txt", "r")) {
            fclose(File);
            std::cout << "Test " << TestNo << " - PASSED" << std::endl;
        } else {
            std::cout << "Test " << TestNo << " - !!!FAILED!!!" << std::endl;
        }
    } else {
        std::cout << "Test " << TestNo << " - !!!FAILED!!!" << std::endl;
    }
    delete __LOG;
	std::cout << std::endl;

    //Delete old log file
    remove("log.txt");

    std::cout << "*********************************************************" << std::endl;
    std::cout << "Test " << ++TestNo << ": Log 'SOME TEXT' to log.txt log channel"  << std::endl;
    std::cout << "*********************************************************" << std::endl;
    __LOG = new SimpleLog();
    if(__LOG->Create("log.txt")) {
        LOG(DEBUG, "SOME TEXT");
        std::fstream File;
        File.open("log.txt", std::ios::in);
        std::string tmp;
        getline(File, tmp);
        if (tmp.find("SOME TEXT") != std::string::npos) {
            std::cout << "Test " << TestNo << " - PASSED" << std::endl;   
        } else {
            std::cout << "Test " << TestNo << " - !!!FAILED!!!" << std::endl;
        }
    } else {
        std::cout << "Test " << TestNo << " - !!!FAILED!!!" << std::endl;
    }
    delete __LOG;
	std::cout << std::endl;

    //Delete old log file
    remove("log.txt");

    std::cout << "*********************************************************" << std::endl;
    std::cout << "Test " << ++TestNo << ": Usage of DEBUG log level"  << std::endl;
    std::cout << "*********************************************************" << std::endl;
    __LOG = new SimpleLog();
    if(__LOG->Create("log.txt")) {
        __LOG->SetLogLevel(DEBUG);
        LOG(DEBUG, "DEBUG TEXT");
        LOG(INFO, "INFO TEXT");
        std::fstream File;
        File.open("log.txt", std::ios::in);
        std::string tmp;
        getline(File, tmp);
        if (tmp.find("DEBUG TEXT") != std::string::npos
            && tmp.find("INFO TEXT") == std::string::npos) {
            std::cout << "Test " << TestNo << " - PASSED" << std::endl;   
        } else {
            std::cout << "Test " << TestNo << " - !!!FAILED!!!" << std::endl;
        }
    } else {
        std::cout << "Test " << TestNo << " - !!!FAILED!!!" << std::endl;
    }
    delete __LOG;
	std::cout << std::endl;
    
    return 0;
}
