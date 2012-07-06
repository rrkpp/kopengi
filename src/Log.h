/*
 * Log.h - Regan Russell
 *
 * Contains enumerations, constant values and functions
 * used for engine logging and console output.
 */

enum LogType {
	LOG_TYPE_DEFAULT,
	LOG_TYPE_WARNING,
	LOG_TYPE_ERROR,
	LOG_TYPE_SCRIPT,
	LOG_TYPE_SUCCESS
};

#ifdef _WIN32

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
