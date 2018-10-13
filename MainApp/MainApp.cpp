// MainApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <boost/dll/import.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <string_view>
#include <string>

#include "../sdk/App/Pluto.h"

// Where should I store interface header
// 
using namespace Pluto;

struct CAppLogger : Pluto::ILogger
{
	void Log(Level l, StringView Module, StringView Msg) override
	{
		using namespace std;
		cout << Module << ":" << Msg << endl;
	}
};

using Path = boost::filesystem::path;

Pluto::JSONView JSON = R"(
	graph : {
		plugins : 
		{
			{name: 'FileSource', params: {file : "../data/1.jpg"}, instance: 'Source'},
			{name: 'Threshold', params: {threshold: 128}, instance: 'Threshold'},
			{name: 'FileWriter', params: {file : "../data/1t.jpg"}, instance: 'Writer'},
		},
		connections : 
		{
			{from : {instance: 'Source', pin: 0}, to: {instance: 'Threshold', pin : 0 },
			{from : {instance: 'Threshold'}, to: {instance: 'Writer'},
		},
	}

)";

void StartCore(CPluto& p) try
{
	auto g = p.LoadGraph(JSON);
	g.Run();
}
catch (Pluto::EError& e)
{
	using namespace std::string_literals;
	throw std::runtime_error(std::string{e.Message()});
}

using namespace std;
int main(int argc, char* argv[])
{
	try
	{
		CAppLogger l;
		CPluto p(l, *std::pmr::new_delete_resource());
		StartCore(p);
	}
	catch (const std::exception& e)
	{
		cout << "Err : " << e.what() << endl;
	}

}
