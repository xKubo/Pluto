#pragma once

#include "Intf.h"
#include <string>
#include <sstream>

namespace Pluto
{
	namespace detail
	{
		template <typename ... Args>
		inline std::string ArgsToString(const Args&... args...)
		{
			std::ostringstream oss;
			detail::ArgsToString(oss, args...);
		}


		template <typename A ,typename ... Args>
		inline void ArgsToString(std::ostringstream& oss, const A& a, const Args&... args...)
		{
			oss << a;
			ArgsToString(oss, args...);
		}

		inline void ArgsToString(std::ostringstream& oss)
		{
			
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
			m_Logger.Log(Level::Info, m_Module, detail::ArgsToString(a));
		}
	private:
		std::string m_Module;
		ILogger& m_Logger;
	};
}
