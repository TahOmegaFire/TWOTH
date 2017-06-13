#include "headers/Log.h"

Log::Log()
{
    logFile.open("logFile.log");
    if(!logFile.is_open())
        std::cout << "Could not create log file!\n";
}

Log::~Log()
{
    logFile.close();
}

void Log::WriteToLog(std::string message)
{
    logFile << message << std::endl;
}
