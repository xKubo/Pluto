// OpenCV.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "../../sdk/Module/ModuleImpl.h"
	
namespace Pluto
{


	struct CModuleImpl : IModuleImpl
	{

	};

	PModuleImpl InitModuleImpl(ICore& c)
	{
		return nullptr;
	}
}



