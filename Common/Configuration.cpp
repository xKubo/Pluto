#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "Configuration.h"

namespace Pluto
{

	using CTree = boost::property_tree::ptree;
	using namespace boost::property_tree;
	using namespace std;


	struct CImpl
	{
		CTree m_Tree;
	};

	const CTree& GetTree(CConfigurationView cv)
	{
		return cv.impl().m_Tree;
	}

	CTree& GetTree(CConfiguration& c)
	{
		return c.impl().m_Tree;
	}

	CConfiguration::CConfiguration()
	{
		m_pImpl = std::make_unique<CImpl>();
	}

	CConfiguration::~CConfiguration()
	{

	}

	CConfiguration::operator CConfigurationView()
	{
		return {*m_pImpl};
	}


	CConfiguration LoadFromFile(StringView FilePath) 
	{
		CConfiguration c;
		json_parser::read_json(std::string{ FilePath }, GetTree(c));
		return c;
	}
	CConfiguration LoadFromString(StringView JSON)
	{
		CConfiguration c;
		istringstream iss(std::string{JSON});
		json_parser::read_json(iss, GetTree(c));
		return c;
	}

	CConfigurationView GetByPath(StringView Path, CConfigurationView c)
	{
		return { c.impl() };
	}

	std::string GetStringVal(StringView Path, CConfigurationView c)
	{
		std::string p{ Path };
		return GetTree(c).get<std::string>(p);
	}

}
