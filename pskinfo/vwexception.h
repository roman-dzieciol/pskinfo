#pragma once

#include <stdarg.h>
#include <stdio.h>
#include <string>

class vwexception
{	
public:
	explicit vwexception(const wchar_t *fmt, ...)
	{	// construct from argument list
		va_list args;
		va_start(args, fmt);
		size_t chars = _vscwprintf(fmt, args);
		std::wstring buf(chars+1, '\0');
		int charsWritten = vswprintf_s(&buf.at(0), chars+1, fmt, args);
		if(charsWritten) 
		{
			m_errorMsg = std::move(buf);
		}
		else
		{
			m_errorMsg = L"Erroneous Exception";
		}
		va_end(args);
	}

	explicit vwexception(const std::wstring& _Message)
	{	// construct from message string
		vwexception(L"%S", _Message.c_str());
	}

	explicit vwexception(const wchar_t *_Message)
	{	// construct from message string
		vwexception(L"%S", _Message);
	}

	const wchar_t *what() const
	{
		return m_errorMsg.c_str();
	}

	vwexception& operator=(const vwexception& rhs)
	{
		if(this != &rhs)
		{
			m_errorMsg = std::move(rhs.m_errorMsg);
		}
		return *this; 
	}
	
private:
	std::wstring m_errorMsg;
};

