#pragma once
#include <string>

namespace Pluto
{


	using IMemoryResource = std::pmr::memory_resource;

	IMemoryResource& GetDefaultMemoryResource();

	using StringView = std::string_view;

	struct String
	{
		String(StringView sv)
		{

		}
	private:

	};

	using JSONView = StringView;
	using JSONData = String;

	struct EError 
	{
		EError(String s) : m_Text(move(s))
		{

		}

		StringView Message() const
		{
			return m_Text;
		}

		virtual ~EError() = default;
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
		virtual JSONData GetMediaInfo() = 0;
		virtual void Draw(ICanvas& c, const CRect &r) = 0;
		virtual ~IMedia() {}
	};

	struct ICanvas
	{

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
		virtual JSONView StoreParams() = 0;
		virtual JSONView GetPluginInfo() = 0;
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
		virtual JSONView GetInfo() = 0;
		virtual PPlugin CreatePlugin(StringView Name, JSONView PluginInfo) = 0;
		virtual PMedium CreateMedium(StringView Name, JSONView MediaInfo) = 0;
	};

	using PluginID = StringView;

	struct IGraph
	{
		virtual PluginID AddPlugin(IPlugin&) = 0;
		virtual void DelPlugin(PluginID PluginID) = 0;

		virtual void Connect(PluginID id1, int Pin1, PluginID id2, int Pin2) = 0;
		virtual void Disconnect(PluginID id1, int Pin) = 0;

		virtual JSONView GetGraphConnections() = 0;

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
		virtual PGraph LoadGraph(JSONView cfg) = 0;
	};

	IPluto& InitPluto(ILogger&l, IMemoryResource& r);
	void UninitPluto();

	void InitModule(ICore& c);
	void UninitModule();

}
