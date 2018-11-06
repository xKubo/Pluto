#pragma once

#include <memory_resource>
#include <boost/dll.hpp>

#include "../../Common/Intf.h"
#include "../../Common/Logger.h"

namespace Pluto
{

	struct CGraph
	{
		CGraph(PGraph pGraph) : m_pGraph(move(pGraph))
		{

		}

		void Run()
		{
			m_pGraph->Run();
		}

	private:
		PGraph m_pGraph;
	};

	struct CPluto : CLogger
	{
		using TLibrary = boost::dll::shared_library;

		CPluto(ILogger& l, IMemoryResource& mr) :
			CLogger(l, "Pluto")
		{
			m_pDefaultResource = &mr;
			std::string LibName = "PlutoCore";
			LogI("Loading library: ", LibName);
			m_Library.load(LibName, boost::dll::load_mode::append_decorations);
			std::string AliasName = "InitPluto";
			LogI("Getting alias : ", AliasName);
			auto fInitPluto = m_Library.get_alias<decltype(Pluto::InitPluto)>(AliasName);
			m_pPluto = &fInitPluto(l, mr);
		}


		ICore& GetCore()
		{
			return m_pPluto->GetCore();
		}

		CGraph LoadGraph(CConfigurationView j)
		{
			return m_pPluto->LoadGraph(j);
		}

		~CPluto()
		{
			LogI("Uniniting Pluto");
			auto fUninitPluto = m_Library.get_alias<decltype(Pluto::UninitPluto)>("UninitPluto");
			fUninitPluto();
		}

	private:
		friend IMemoryResource& GetDefaultMemoryResource();
		TLibrary m_Library;
		inline static IMemoryResource* m_pDefaultResource = nullptr;
		IPluto* m_pPluto = nullptr;
	};

	IMemoryResource& GetDefaultMemoryResource()
	{
		return *CPluto::m_pDefaultResource;
	}

}