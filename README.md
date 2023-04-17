# Simple log library
A simple logging library implemented in C++98 supporting Linux, MacOS and Windows operating systems. 

## Supported functionalities
1. Log to stderr
2. Log to file
3. Works under Linux, MacOS and Windows operating systems
4. Predefined function like macros for logging with levels (DEBUG, TRACE, WARNING, etc.)

## Output
Call of LOG_D function with string parameter
```cpp
LOG_D("Some debug log output text");
```

will result into output like this
```
17.04.2023 12:17:49 tests.cpp:37 D: Some debug log output text
```

## Usage
Easy to include it in any of your C++ projects because it contains only one class and it's written using C++98 standard. 

1. Add [SimpleLog.cpp](https://github.com/huckor/SimpleLog/blob/main/src/SimpleLog.cpp) and [SimpleLog.h](https://github.com/huckor/SimpleLog/blob/main/src/SimpleLog.h) into your project.

2. Logging class is considered as global object used as singleton so you need to first create it. In your main.cpp file define SimpleLog global object and in your main function create it's instance.

3. Now you can log using predefined macros inside [SimpleLog.h](https://github.com/huckor/SimpleLog/blob/main/src/SimpleLog.h). Anywhere where you include [SimpleLog.h](https://github.com/huckor/SimpleLog/blob/main/src/SimpleLog.h) file you will be able to use it.

### Example with log to stderr
```cpp
#include "SimpleLog.h"

SimpleLog *__LOG;

int main(int argc, const char * argv[]) {
    __LOG = new SimpleLog();
    __LOG->Create(LOG_TO_STDERR);
    LOG_T("Some trace log output text");
    LOG_D("Some debug log output text");
    LOG_I("Some info log output text");
    LOG_W("Some warning log output text");
    LOG_E("Some error log output text");
    LOG_F("Some fatal log output text");
    delete __LOG;
    return 0;
}
```

### Example with log to file
```cpp
#include "SimpleLog.h"

SimpleLog *__LOG;

int main(int argc, const char * argv[]) {
    __LOG = new SimpleLog();
    __LOG->Create("mylog.txt");
    LOG_T("Some trace log output text");
    LOG_D("Some debug log output text");
    LOG_I("Some info log output text");
    LOG_W("Some warning log output text");
    LOG_E("Some error log output text");
    LOG_F("Some fatal log output text");
    delete __LOG;
    return 0;
}
```

## How to contribute
There is a Visual Studio Code project inside .vscode folder which supports C++ intellisense and debugging.
Feel free to fix any issue you find or add new features if you like to. Follow instructions from [GitHub Contributing](https://gist.github.com/MarcDiethelm/7303312) to know how to contribute.


## In case you like this project
Much appreciate any of given :star: