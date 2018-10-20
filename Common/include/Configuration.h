#pragma once

namespace Pluto
{
	using StringView = std::string_view;

	struct CConfigurationView;

	struct CConfiguration
	{
		CConfiguration() = default;

		CConfiguration(const CConfiguration& c) = delete;
		CConfiguration& operator=(const CConfiguration& c) = delete;

		CConfiguration(CConfiguration&& c) = default;
		CConfiguration& operator=(CConfiguration&& c) = default;

		virtual ~CConfiguration() {}

		operator CConfigurationView();
		
	private:
		struct CImpl;
		//std::unique_ptr<CImpl> m_pImpl = nullptr;
	};

	struct CConfigurationView
	{
		struct CImpl;

	private:
		CImpl *m_pImpl;
	};

	CConfiguration LoadFromFile(StringView FilePath);
	CConfiguration LoadFromString(StringView);
	CConfigurationView GetByPath(StringView Path, CConfigurationView c);
	StringView GetVal(StringView Path, CConfigurationView& c);
}