// PlutoCore.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "../Common/Intf.h"
#include <boost/dll/alias.hpp>
#include <functional>
#include "CoreImpl.h"

namespace Pluto
{

	struct Core::CPlutoImpl;

	std::unique_ptr<Core::CPlutoImpl> g_pCore;

	IMemoryResource& GetDefaultMemoryResource()
	{
		return g_pCore->GetMemoryResource();
	}

	IPluto& InitPluto(ILogger&l, IMemoryResource& mr)
	{
		g_pCore = std::make_unique<Core::CPlutoImpl>(l, mr);
		return *g_pCore;
	}

	void UninitPluto()
	{
		g_pCore.reset();
	}

	BOOST_DLL_AUTO_ALIAS(InitPluto)
	BOOST_DLL_AUTO_ALIAS(UninitPluto)
}
