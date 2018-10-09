// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "../include/Intf.h"
#include <boost/dll/alias.hpp>
#include <functional>


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


/*

int Get42()
{
	return 42;
}

BOOST_DLL_ALIAS(
	Get42, // <-- this function is exported with...
	Get42Name                               // <-- ...this alias name
)*/


struct CPlugin
{

};

struct CModuleImpl
{
	void RegisterPlugin()
	{

	}


};

namespace Pluto
{
	struct IModuleImpl
	{
		virtual ~IModuleImpl() {}
	};

	using PModuleImpl = std::unique_ptr<IModuleImpl>;

	std::function<PModuleImpl(ICore&)> FCreateModule;

	PModuleImpl pImpl;

	void InitModule(ICore& c)
	{
		pImpl = FCreateModule(c);
	}

	void UninitModule()
	{
		pImpl.reset();
	}

	BOOST_DLL_AUTO_ALIAS(InitModule)
	BOOST_DLL_AUTO_ALIAS(UninitModule)
}
