#pragma once
#define FMT_HEADER_ONLY
#define FMT_CONSTEVAL
#include <memory>
#include <any>
#include "fmt/xchar.h"

//C++20 std::format style logger which combined log4cplus and fmtlib
//Check Format String Syntax:
//https://fmt.dev/latest/syntax.html
//https://en.cppreference.com/w/cpp/utility/format
//Example:
//SimplyLive::Logger logger(LR"(C:\logs\windowsTestLog.log)");
//logger.info("Elapsed time: {:.2f} seconds, {}", 1.23, "Hello logger");
//
//SimplyLive::Logger logger2;
//logger2.setPath(LR"(C:\logs\windowsTest2Log.log)");
//logger.info(L"Elapsed time: {:.2f} seconds, {}", 1.23, "Hello logger");

namespace SimplyLive
{
	class Logger
	{
	public:
		enum class Level
		{
			debug = 10000,
			info = 20000,
			warn = 30000,
			error = 40000,
			fatal = 50000,
		};

		struct LogConfig
		{
			Level    logLevelThreshold = Level::info;
			bool     asyncLog = true;
			uint32_t maxLogFileSizeMB = 20;
			uint32_t maxNumberOfRollingFile = 5;
			bool     addProcessName = false;
			bool     relativePath = true;
		};

		explicit Logger(std::wstring_view path, LogConfig* logConfig = nullptr);

		void setPath(std::wstring_view path, LogConfig* logConfig = nullptr);

		template <typename T, typename... Args>
		void debug(const T* fmt, Args&& ...args) { log(Level::debug, fmt::format(fmt, std::forward<Args>(args)...)); }

		void debug(const std::string_view fmt) const { log(Level::debug, fmt); }
		void debug(const std::wstring_view fmt) const { log(Level::debug, fmt); }

		template <typename T, typename... Args>
		void info(const T* fmt, Args&& ...args) { log(Level::info, fmt::format(fmt, std::forward<Args>(args)...)); }

		void info(const std::string_view fmt) const { log(Level::info, fmt); }
		void info(const std::wstring_view fmt) const { log(Level::info, fmt); }

		template <typename T, typename... Args>
		void warn(const T* fmt, Args&& ...args) { log(Level::warn, fmt::format(fmt, std::forward<Args>(args)...)); }

		void warn(const std::string_view fmt) const { log(Level::warn, fmt); }
		void warn(const std::wstring_view fmt) const { log(Level::warn, fmt); }

		template <typename T, typename... Args>
		void error(const T* fmt, Args&& ...args) { log(Level::error, fmt::format(fmt, std::forward<Args>(args)...)); }

		void error(const std::string_view fmt) const { log(Level::error, fmt); }
		void error(const std::wstring_view fmt) const { log(Level::error, fmt); }

		template <typename T, typename... Args>
		void fatal(const T* fmt, Args&& ...args) { log(Level::fatal, fmt::format(fmt, std::forward<Args>(args)...)); }

		void fatal(const std::string_view fmt) const { log(Level::fatal, fmt); }
		void fatal(const std::wstring_view fmt) const { log(Level::fatal, fmt); }

		Logger();
		~Logger();
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;

	private:
		std::any m_logger;

		void log(Level level, std::string_view log) const;
		void log(Level level, std::wstring_view log) const;
	};
}

using simplyLogger = std::shared_ptr<SimplyLive::Logger>;