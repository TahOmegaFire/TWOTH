//Log class
#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <string>

class Log
{
public:

    Log();
    ~Log();

    std::ofstream logFile;
    void WriteToLog(std::string message);
};

#endif // LOG_H
