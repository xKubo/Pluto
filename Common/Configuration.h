#pragma once

#include "String.h"

namespace Pluto
{

	struct CImpl;

	struct CConfigurationView
	{
		CConfigurationView(const CImpl& Impl) :
			m_Impl(Impl)
		{

		}

		const CImpl& impl()
		{
			return m_Impl;
		}
	private:
		const CImpl &m_Impl;
	};

	struct CConfiguration
	{
		CConfiguration();

		CConfiguration(const CConfiguration& c) = delete;
		CConfiguration& operator=(const CConfiguration& c) = delete;

		CConfiguration(CConfiguration&& c) = default;
		CConfiguration& operator=(CConfiguration&& c) = default;

		virtual ~CConfiguration();

		operator CConfigurationView();
		
		CImpl& impl()
		{
			return *m_pImpl;
		}
	private:
		
		std::unique_ptr<CImpl> m_pImpl;
	};

	CConfiguration LoadFromFile(StringView FilePath);
	CConfiguration LoadFromString(StringView);
	CConfigurationView GetByPath(StringView Path, CConfigurationView c);
	std::string GetStringVal(StringView Path, CConfigurationView c);

	inline int GetIntVal(StringView Path, CConfigurationView c)
	{
		return std::stoi(GetStringVal(Path, c));
	}

	template <typename T>
	inline T GetVal(StringView Path, CConfigurationView c);

	template <>
	inline int GetVal<int>(StringView Path, CConfigurationView c)
	{
		return GetIntVal(Path, c);
	}

	template <>
	inline std::string GetVal<std::string>(StringView Path, CConfigurationView c)
	{
		return GetStringVal(Path, c);
	}

}