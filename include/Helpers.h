#pragma once

#include "Intf.h"
#include <string>
#include <sstream>

namespace Pluto
{
	namespace detail
	{


		inline void ArgsToOSS(std::ostringstream& oss)
		{
			
		}

		template <typename A ,typename ... Args>
		inline void ArgsToOSS(std::ostringstream& oss, const A& a, const Args&... args...)
		{
			oss << a;
			ArgsToOSS(oss, args...);
		}


		template <typename ... Args>
		inline std::string ArgsToString(const Args&... args...)
		{
			std::ostringstream oss;
			detail::ArgsToOSS(oss, args...);
			return oss.str();
		}

	}


	struct CLogger
	{
		CLogger(ILogger&l, StringView Module) :
			m_Logger(l)
		{

		}

		template <typename ... Args>
		void LogI(const Args&... a...)
		{
			m_Logger.Log(Level::Info, m_Module, detail::ArgsToString(a...));
		}
	private:
		std::string m_Module;
		ILogger& m_Logger;
	};
}
