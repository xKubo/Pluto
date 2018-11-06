#pragma once

#include <memory_resource>
#include <string_view>

namespace Pluto
{
	using IMemoryResource = std::pmr::memory_resource;

	IMemoryResource& GetDefaultMemoryResource();
	using StringView = std::string_view;

	struct String
	{
		String()
		{

		}

		String(const char* pData) : String(StringView{ pData })
		{

		}

		String(StringView sv)
		{
			InitFrom(sv);
		}

		String(const String& rhs)
		{
			InitFrom(rhs);
		}

		String& operator=(const String&& rhs)
		{
			Cleanup();
			InitFrom(rhs);
			return *this;
		}

		String(String && rhs) :
			m_View(rhs.m_View)
		{
			rhs.m_View = {};
		}


		String& operator=(String&& rhs)
		{
			std::swap(m_View, rhs.m_View);
			return *this;
		}

		~String()
		{
			Cleanup();
		}

		operator StringView() const
		{
			return m_View;
		}
	private:

		void InitFrom(StringView sv)
		{
			if (!sv.empty())
			{
				char* pData = static_cast<char*>(GetDefaultMemoryResource().allocate(sv.size()));
				memcpy(pData, sv.data(), sv.size());
				m_View = { pData, sv.size() };
			}
			else
				m_View = {};
		}

		void Cleanup()
		{
			if (!m_View.empty())
				GetDefaultMemoryResource().deallocate((void*)m_View.data(), m_View.size());

		}

		StringView m_View;
	};


}
