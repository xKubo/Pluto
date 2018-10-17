#pragma once

namespace Pluto
{
	struct CConfiguration
	{
		CConfiguration() = default;

		CConfiguration(const CConfiguration& c) = delete;
		CConfiguration& operator=(const CConfiguration& c) = delete;

		CConfiguration(CConfiguration&& c) = default;
		CConfiguration& operator=(CConfiguration&& c) = default;

		virtual ~CConfiguration() {}

		
	private:
		struct CImpl;
		std::unique_ptr<CImpl> m_pImpl = nullptr;
	};

	struct CConfigurationView
	{
		struct CImpl;

	private:
		CImpl *m_pImpl;
	};
}