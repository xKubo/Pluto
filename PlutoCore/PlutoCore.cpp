// PlutoCore.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "../include/Intf.h"
#include <boost/dll/alias.hpp>
#include <functional>

namespace Pluto
{

	struct CCoreImpl;

	std::unique_ptr<CCoreImpl> g_pCore;

	ICore& InitCore(ILogger&l, IMemoryResource& mr)
	{
		g_pCore = std::make_unique<CCoreImpl>(l, mr);
	}

	void UninitCore()
	{
		g_pCore.reset();
	}

	BOOST_DLL_AUTO_ALIAS(InitCore)
	BOOST_DLL_AUTO_ALIAS(UninitCore)
}
