#pragma once

#include "../include/Intf.h"
#include <unordered_map>
#include <map>

namespace Pluto::Core
{

	struct CModule
	{

	private:
		//Pluto::IModule
	};

	struct CPlugin
	{
		CPlugin(PPlugin pPlugin) : m_pPlugin(move(pPlugin))
		{

		}

	private:
		PPlugin m_pPlugin;
	};

	struct CPlutoImpl : IPluto, ICore
	{
		CPlutoImpl(ILogger& l, IMemoryResource &mr) :
			m_Logger(l),
			m_MemoryResource(mr)
		{

		}

		virtual ICore& GetCore() override
		{
			return *this;
		}

		virtual PGraph CreateGraph() override
		{
			throw EError{ "Not implemented" };
		}

		virtual PGraph LoadGraph(CConfigurationView cfg) override
		{
			throw EError{ "Not implemented" };
		}

		virtual IMemoryResource& GetMemoryResource()
		{
			return m_MemoryResource;
		}

		virtual ILogger& GetLogger()
		{
			return m_Logger;
		}

		virtual int RegisterModule(IModule& m) override
		{
			//m_Modules.insert()
			return 42;
		}

		virtual void UnregisterModule(int Cookie) override
		{
			//m_Modules.erase(Cookie);
		}

		ILogger& m_Logger;
		IMemoryResource& m_MemoryResource;
		
		std::map<std::string, Pluto::PPlugin> m_Plugins;
		std::map<std::string, Pluto::SPMedia> m_Media;
		std::map<std::string, CModule> m_Modules;
	};
}

