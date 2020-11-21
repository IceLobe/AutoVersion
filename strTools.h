#pragma once
#include <string>
#include <Windows.h>

class strTools
{
public:
	strTools();
	~strTools();

	/// <summary>
	/// 将wstring转换成string
	/// </summary>
	/// <param name="str">string</param>
	/// <returns>wstring</returns>
	static std::wstring s2ws(std::string str);

	/// <summary>
	/// 将string转换成wstring
	/// </summary>
	/// <param name="str">string</param>
	/// <returns>wstring</returns>
	static std::string ws2s(std::wstring wstr);

	static std::wstring replace(std::wstring wstr, const wchar_t* ch, const wchar_t* desChar);
};

