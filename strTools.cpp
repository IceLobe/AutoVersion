#include "strTools.h"

strTools::strTools()
{
}

strTools::~strTools()
{
}

std::wstring strTools::s2ws(std::string str)
{
	try
	{
		std::wstring result;
		//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
		int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
		TCHAR* buffer = new TCHAR[len + 1];
		//多字节编码转换成宽字节编码  
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
		//添加字符串结尾  
		buffer[len] = '\0';
		//删除缓冲区并返回值  
		result.append(buffer);
		delete[] buffer;
		if (result.size() == 0)
		{
			std::exception("字符串转换失败：strTools::s2ws");
		}
		return result;
	}
	catch (const std::exception&)
	{
		return L"";
	}
}

std::string strTools::ws2s(std::wstring wstr)
{
	try
	{
		std::string result;
		//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
		int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
		char* buffer = new char[len + 1];
		//宽字节编码转换成多字节编码  
		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
		buffer[len] = '\0';
		//删除缓冲区并返回值  
		result.append(buffer);
		delete[] buffer;
		if (result.size() == 0)
		{
			std::exception("字符串转换失败：strTools::ws2s");
		}
		return result;
	}
	catch (const std::exception& e)
	{
		return e.what();
	}
}

