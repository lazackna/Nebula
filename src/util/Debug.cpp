//
// Created by User on 12/7/2023.
//
#include <iostream>
#include "Debug.hpp"

namespace nebula
{

	void Debug::log(const std::string& message)
	{
		log(message, LogSeverity::Message);
	}

	void Debug::log(const std::stringstream& message)
	{
		log(message, LogSeverity::Message);
	}

	void Debug::logInfo(const std::string& message)
	{
		log(message, LogSeverity::Info);
	}

	void Debug::logInfo(const std::stringstream& message)
	{
		log(message, LogSeverity::Info);
	}

	void Debug::logWarning(const std::string& message)
	{
		log(message, LogSeverity::Warning);
	}

	void Debug::logWarning(const std::stringstream& message)
	{
		log(message, LogSeverity::Warning);
	}

	void Debug::logError(const std::string& message)
	{
		log(message, LogSeverity::Error);
	}

	void Debug::logError(const std::stringstream& message)
	{
		log(message, LogSeverity::Error);
	}

	void Debug::logFatal(const std::string& message)
	{
		log(message, LogSeverity::Fatal);
	}

	void Debug::logFatal(const std::stringstream& message)
	{
		log(message, LogSeverity::Fatal);
	}

    void Debug::log(const std::string& message, LogSeverity severity)
    {
        switch (severity)
        {
            case Debug::LogSeverity::Message: std::cout << "[MESSAGE]: "; break;
            case Debug::LogSeverity::Info: std::cout << "[INFO]   : "; break;
            case Debug::LogSeverity::Warning: std::cout << "[WARNING]: "; break;
            case Debug::LogSeverity::Error: std::cout << "[ERROR]  : "; break;
            case Debug::LogSeverity::Fatal: std::cout << "[FATAL]  : "; break;
        }

        std::cout << message << "\n";
    }

    void Debug::log(const std::stringstream& message, LogSeverity severity)
    {
        log(message.str(), severity);
    }
} // namespace pico2d