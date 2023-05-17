# Simple log library
A simple logging library implemented in C++98 supporting Linux, MacOS and Windows operating systems. 

## Supported functionalities
1. Log to stderr
2. Log to file
3. Works under Linux, MacOS and Windows operating systems
4. Predefined function like macros for logging with levels (DEBUG, TRACE, WARNING, etc.)
5. Set log level

## Output
Call of LOG_D, LOG_W and LOG_T functions with string parameter
```cpp
LOG_D("Some debug log output text");
LOG_W("Some warning log output text");
LOG_T("Some trace log output text");
```

will result into output like this
```
17.04.2023 12:17:49 main.cpp:37 D: Some debug log output text
17.04.2023 12:17:49 main.cpp:37 W: Some warning log output text
17.04.2023 12:17:49 main.cpp:37 T: Some trace log output text
```

## Usage
1. Add [SimpleLog.cpp](https://github.com/huckor/SimpleLog/blob/main/src/SimpleLog.cpp) and [SimpleLog.h](https://github.com/huckor/SimpleLog/blob/main/src/SimpleLog.h) into your project.

2. Logging class is considered as global object used as singleton so you need to first create it. Define SimpleLog global object in your main.cpp file and create it's instance in main function. This object is extended in [SimpleLog.h](https://github.com/huckor/SimpleLog/blob/main/src/SimpleLog.h) file.
```cpp
#include "SimpleLog.h"

SimpleLog *__LOG;

int main(int argc, const char * argv[]) {
    __LOG = new SimpleLog();
    __LOG->Create(LOG_TO_STDERR);
    
    //At this point you can use simple log
    
    delete __LOG;
    return 0;
}
```

3. Now you can log using predefined macros inside [SimpleLog.h](https://github.com/huckor/SimpleLog/blob/main/src/SimpleLog.h) file anywhere you include it.

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

### Example of logging in different file than main.cpp
```cpp
#include "DifferentFile.h"
#include "SimpleLog.h"

void Foo() {
    LOG_T("Some trace log output from Foo");
}
```

### Example with log levels
```cpp
#include "SimpleLog.h"

SimpleLog *__LOG;

int main(int argc, const char * argv[]) {
    __LOG = new SimpleLog();
    __LOG->Create("mylog.txt");
    __LOG->SetLogLevel(LOG_DEBUG);
    LOG_D("Some debug log output text"); //Only this will be logged
    LOG_T("Some trace log output text"); //This will not go to log
    LOG_E("Some error log output text"); //This will not go to log
    delete __LOG;
    return 0;
}
```


## How to Contribute

Contributions are highly encouraged and appreciated! If you have any ideas, suggestions, or bug fixes, please feel free to contribute. Here's how you can get started:

1. Fork this repository to your GitHub account.
2. Make the desired changes or add new features to your forked repository.
3. Write test cases for your changes.
4. Submit a pull request, explaining the changes you have made and why they are beneficial.
5. I will review your pull request as soon as possible and provide feedback if needed.
6. Once your changes are approved, they will be merged into the main repository.
7. Congratulations! You have successfully contributed to this project.

## Code Style and Guidelines

To maintain code consistency and readability, please adhere to the following guidelines:

- Write clean and self-explanatory code.
- Use meaningful variable and function names.
- Follow the established coding style and formatting.
- Add comments where necessary to improve code understanding.

## Issues and Bug Reports

If you come across any issues or bugs while using this project, please report them using the GitHub issue tracker. Include a detailed description of the problem, steps to reproduce it, and any relevant information that might help in resolving the issue.

## Support

If you need any assistance or have questions regarding this project, feel free to reach out to me. I'll do my best to help you.

## Spread the Word

If you find this project helpful or interesting, consider giving it a star on GitHub. Also, sharing it with others who might benefit from it would be greatly appreciated.

Thank you for your interest in this project.