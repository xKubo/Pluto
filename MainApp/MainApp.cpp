// MainApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <boost/dll/import.hpp>
#include <boost/filesystem.hpp>
#include <iostream>

// Where should I store interface header
// 

using FGet42 = int ();

using namespace std;
int main(int argc, char* argv[])
{
	try
	{
		namespace fi = boost::filesystem;
		fi::path p = argv[0];
		cout << p << endl;
		auto plugin = boost::dll::import_alias<FGet42>(          // type of imported symbol is located between `<` and `>`
			p.parent_path() / "PlutoCore",                     // path to the library and library name
			"Get42Name",                                       // name of the symbol to import
			boost::dll::load_mode::append_decorations              // makes `libmy_plugin_sum.so` or `my_plugin_sum.dll` from `my_plugin_sum`
			);
		cout << plugin() << endl;
	}
	catch (const std::exception& e)
	{
		cout << "Err : " << e.what() << endl;
	}

}
