#pragma once

#include "../include/Intf.h"

namespace Pluto
{
	struct CCore : ICore
	{
		virtual StringView GetLastErrorString() = 0;
		virtual IAllocator& GetAllocator() = 0;
		virtual ILogger& GetLogger() = 0;
		virtual int RegisterModule(IModule&) = 0;
		virtual void UnregisterFactory(int Cookie) = 0;

		virtual void Connect() = 0;
		virtual void Disconnect() = 0;

	};
}

