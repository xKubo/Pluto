#pragma once

#include "../include/Intf.h"
#include <unordered_map>

namespace Pluto
{
	struct CCoreImpl : ICore
	{

	private:
		virtual IMemoryResource& GetMemoryResource() = 0;
		virtual ILogger& GetLogger() = 0;

		virtual int RegisterModule(IModule&) = 0;
		virtual void UnregisterModule(int Cookie) = 0;

		unordered_map<int, 

	};
}

