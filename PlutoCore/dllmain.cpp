// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"



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


