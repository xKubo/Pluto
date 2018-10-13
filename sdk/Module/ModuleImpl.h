#pragma once

#include <memory>

#include "../../include/Intf.h"

namespace Pluto
{
	struct IModuleImpl
	{
		virtual ~IModuleImpl() {}
	};

	using PModuleImpl = std::unique_ptr<IModuleImpl>;

	PModuleImpl InitModuleImpl(ICore& c);


}
