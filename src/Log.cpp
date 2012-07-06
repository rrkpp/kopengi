/*
 * Log.cpp - Regan Russell
 *
 * Contains enumerations, constant values and functions
 * used for engine logging and console output.
 */

#include "kopengi.h"

void log(LogType type, std::string msg)
{
	std::ofstream logFile("log.txt", std::fstream::in | std::fstream::app);

	if (!logFile.is_open())
	{
		std::cout << LOG_COLOR_YELLOW << "[WARNING]: " << LOG_COLOR_DEFAULT << "Failed to open log.txt! Logs will not be saved!" << std::endl;
	}

	if (type == LOG_TYPE_DEFAULT)
	{
		std::cout << msg << std::endl;
		logFile << msg << std::endl;
	}
	else if (type == LOG_TYPE_WARNING)
	{
		std::cout << LOG_COLOR_YELLOW << "[WARNING]: " << LOG_COLOR_DEFAULT << msg << std::endl;
		logFile << "[WARNING]: " << msg << std::endl;
	}
	else if (type == LOG_TYPE_ERROR)
	{
		std::cout << LOG_COLOR_RED << "[ERROR]: " << LOG_COLOR_DEFAULT << msg << std::endl;
		logFile << "[ERROR]: " << msg << std::endl;
	}
	else if (type == LOG_TYPE_SCRIPT)
	{
		std::cout << LOG_COLOR_CYAN << "[SCRIPT]: " << LOG_COLOR_DEFAULT << msg << std::endl;
		logFile << "[SCRIPT]: " << msg << std::endl;
	}
	else if (type == LOG_TYPE_SUCCESS)
	{
		std::cout << LOG_COLOR_GREEN << "[SUCCESS]: " << LOG_COLOR_DEFAULT << msg << std::endl;
		logFile << "[SUCCESS]: " << msg << std::endl;
	}

	logFile.close();
}
