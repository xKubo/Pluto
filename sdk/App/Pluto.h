#pragma once
#include "../../include/Intf.h"
#include "../../include/Logger.h"
#include <memory_resource>
#include <boost/dll.hpp>

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

		TLibrary m_Library;
		IPluto* m_pPluto = nullptr;
	};

}