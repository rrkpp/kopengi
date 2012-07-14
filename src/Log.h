/*
* 	Log.h - Regan Russell
* 
* 	Contains enumerations, constant values and functions
* 	used for engine logging and console output.
*/

enum LogType {
	LOG_TYPE_DEFAULT,
	LOG_TYPE_WARNING,
	LOG_TYPE_ERROR,
	LOG_TYPE_SCRIPT
};

#ifdef _WIN32
	const std::string LOG_COLOR_DEFAULT = "\033[0m";
	const std::string LOG_COLOR_BLACK = "\033[30m";
	const std::string LOG_COLOR_RED = "\033[31m";
	const std::string LOG_COLOR_GREEN = "\033[32m";
	const std::string LOG_COLOR_YELLOW = "\033[33m";
	const std::string LOG_COLOR_BLUE = "\033[34m";
	const std::string LOG_COLOR_MAGENTA = "\033[35m";
	const std::string LOG_COLOR_CYAN = "\033[36m";
	const std::string LOG_COLOR_GRAY = "\033[37m";

#else
	const std::string LOG_COLOR_DEFAULT = "\e[0m";
	const std::string LOG_COLOR_BLACK = "\e[30m";
	const std::string LOG_COLOR_RED = "\e[31m";
	const std::string LOG_COLOR_GREEN = "\e[32m";
	const std::string LOG_COLOR_YELLOW = "\e[33m";
	const std::string LOG_COLOR_BLUE = "\e[34m";
	const std::string LOG_COLOR_MAGENTA = "\e[35m";
	const std::string LOG_COLOR_CYAN = "\e[36m";
	const std::string LOG_COLOR_GRAY = "\e[37m";
#endif

void log(LogType type, std::string msg);
