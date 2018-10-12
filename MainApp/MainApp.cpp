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
		cout << Module << ":" << Msg << endl;
	}
};


using namespace std;
int main(int argc, char* argv[])
{
	try
	{
		CAppLogger l;
		CPluto p(l, *std::pmr::new_delete_resource());
		p.LoadPlugins();
		auto g = p.LoadGraph("");
		g.Run();
	}
	catch (const std::exception& e)
	{
		cout << "Err : " << e.what() << endl;
	}

}
