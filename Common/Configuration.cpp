#include <boost/property_tree/ptree.hpp>
#include "Configuration.h"

namespace Pluto
{
	CConfiguration::CConfiguration()
	{

	}


	CConfiguration::~CConfiguration()
	{

	}

	CConfiguration::operator CConfigurationView()
	{
		return {};
	}

	struct CConfiguration::CImpl
	{
		
	};
	CConfiguration LoadFromFile(StringView FilePath) 
	{
		return {};
	}
	CConfiguration LoadFromString(StringView)
	{
		return {};
	}

	CConfigurationView GetByPath(StringView Path, CConfigurationView c)
	{
		return {};
	}

	StringView GetVal(StringView Path, CConfigurationView& c)
	{
		return {};
	}
}
