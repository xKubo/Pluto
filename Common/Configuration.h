#pragma once

namespace Pluto
{
	using StringView = std::string_view;

	struct CConfigurationView
	{

	private:
		struct CImpl;
		CImpl *m_pImpl;
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
		
	private:
		struct CImpl;
		std::unique_ptr<CImpl> m_pImpl;
	};

	CConfiguration LoadFromFile(StringView FilePath);
	CConfiguration LoadFromString(StringView);
	CConfigurationView GetByPath(StringView Path, CConfigurationView c);
	StringView GetVal(StringView Path, CConfigurationView& c);
}