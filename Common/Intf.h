#pragma once
#include <string>
#include <utility>
#include <memory_resource>

#include "Configuration.h"

namespace Pluto
{





	struct EError 
	{
		EError(String s) : m_Text(std::move(s))
		{

		}

		StringView Message() const
		{
			return m_Text;
		}

		virtual ~EError()
		{

		}
	private:
		String m_Text;
	};

	enum struct Level
	{
		Panic,
		Error,
		Warning,
		Info,
		Verbose,
	};

	struct ILogger
	{
		virtual void Log(Level l, StringView Module, StringView Msg) = 0;
	};

	using MediaType = StringView;

	struct IMedia
	{
		virtual CConfigurationView GetMediaInfo() = 0;
		virtual ~IMedia() {}
	};

	struct CPoint
	{
		int x, y;
	};
	struct CSize
	{
		int w, h;
	};

	struct CRect
	{
		CSize sz;
		CPoint pt;
	};

	using Color = int;

	enum Format
	{
		RGB24,
	};

	struct CImageBits
	{
		Format GetFormat() const;
		CSize Resolution() const;
	};

	struct ICanvas
	{
		virtual void DrawLine(Color c, CPoint p1, CPoint p2) = 0;
		virtual void DrawBits(Color c, CPoint p, const CImageBits& b) = 0;
		virtual void DrawBits(Color c, CRect r, const CImageBits& b) = 0;
		virtual void DrawEllipse(Color c, CRect Bounds) = 0;
	};

	struct IMediaDraw
	{
		virtual void Draw(ICanvas& c, const CRect &r) = 0;
	};

	struct IImage : IMedia
	{
		virtual StringView Data() = 0;		
	};

	struct TMediaArray
	{
		IMedia *pBegin;
		IMedia *pEnd;
	};

	struct IPlugin
	{
		virtual CConfigurationView StoreParams() = 0;
		virtual CConfigurationView GetPluginInfo() = 0;
		virtual TMediaArray Prepare(TMediaArray Inputs) = 0;
		virtual void Apply() = 0;
		virtual ~IPlugin() {}
	};

	using PPlugin = std::unique_ptr<IPlugin>;
	using SPPlugin = std::shared_ptr<IPlugin>;


	using PMedium = std::unique_ptr<IMedia>;
	using SPMedia = std::shared_ptr<IMedia>;

	struct IModule
	{
		virtual CConfigurationView GetInfo() = 0;
		virtual PPlugin CreatePlugin(StringView Name, CConfigurationView PluginInfo) = 0;
		virtual PMedium CreateMedium(StringView Name, CConfigurationView MediaInfo) = 0;
		virtual ~IModule() {}
	};

	using PModule = std::unique_ptr<IModule>;

	using PluginID = StringView;

	struct IGraph
	{
		virtual PluginID AddPlugin(IPlugin&) = 0;
		virtual void DelPlugin(PluginID PluginID) = 0;

		virtual void Connect(PluginID id1, int Pin1, PluginID id2, int Pin2) = 0;
		virtual void Disconnect(PluginID id1, int Pin) = 0;

		virtual CConfigurationView GetGraphConnections() = 0;

		virtual void Run() = 0;
		virtual void Save() = 0;

		virtual ~IGraph() {}
	};

	using PGraph = std::unique_ptr<IGraph>;

	struct ICore
	{
		virtual IMemoryResource& GetMemoryResource() = 0;
		virtual ILogger& GetLogger() = 0;

		virtual int RegisterModule(IModule&) = 0;
		virtual void UnregisterModule(int Cookie) = 0;
	};

	struct IPluto
	{
		virtual ICore& GetCore() = 0;
		virtual PGraph CreateGraph() = 0;
		virtual PGraph LoadGraph(CConfigurationView cfg) = 0;
	};

	struct IConfiguration;
	using SPConfiguration = std::shared_ptr<IConfiguration>;

	struct Configuration;


	IPluto& InitPluto(ILogger&l, IMemoryResource& r);
	void UninitPluto();

	void InitModule(ICore& c);
	void UninitModule();

}
