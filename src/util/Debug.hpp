//
// Created by david on 14/11/2023.
//

#ifndef PICO2D_DEBUG_HPP
#define PICO2D_DEBUG_HPP
#include <memory>
#include <sstream>

namespace nebula
{

	class Debug
	{
    public:
        enum class LogSeverity
        {
            Message,
            Info,
            Warning,
            Error,
            Fatal
        };

        /**
         * Used to log a message with a severity.
         * @param message The message to print.
         * @param severity The severity level of the message.
         */
        static void log(const std::string& message, LogSeverity severity);
        static void log(const std::stringstream& message, LogSeverity severity);

		/**
		 * Log with a @see Gluon::Service::LoggingService::LoggingSeverity::Message severity.
		 * @param message The message to print.
		 */
		static void log(const std::string& message);
		static void log(const std::stringstream& message);

		/**
		 * Log with a @see Gluon::Service::LoggingService::LoggingSeverity::Info severity.
		 * @param message The message to print.
		 */
		static void logInfo(const std::string& message);
		static void logInfo(const std::stringstream& message);

		/**
		 * Log with a @see Gluon::Service::LoggingService::LoggingSeverity::Warning severity.
		 * @param message The message to print.
		 */
		static void logWarning(const std::string& message);
		static void logWarning(const std::stringstream& message);

		/**
		 * Log with a @see Gluon::Service::LoggingService::LoggingSeverity::Error severity.
		 * @param message The message to print.
		 */
		static void logError(const std::string& message);
		static void logError(const std::stringstream& message);

		/**
		 * Log with a @see Gluon::Service::LoggingService::LoggingSeverity::Fatal severity.
		 * @param message The message to print.
		 */
		static void logFatal(const std::string& message);
		static void logFatal(const std::stringstream& message);

	};

} // namespace pico2d

#endif // PICO2D_DEBUG_HPP