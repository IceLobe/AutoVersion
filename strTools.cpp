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
		//��ȡ��������С��������ռ䣬��������С���ַ�����  
		int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
		TCHAR* buffer = new TCHAR[len + 1];
		//���ֽڱ���ת���ɿ��ֽڱ���  
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
		//����ַ�����β  
		buffer[len] = '\0';
		//ɾ��������������ֵ  
		result.append(buffer);
		delete[] buffer;
		if (result.size() == 0)
		{
			std::exception("�ַ���ת��ʧ�ܣ�strTools::s2ws");
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
		//��ȡ��������С��������ռ䣬��������С�°��ֽڼ����  
		int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
		char* buffer = new char[len + 1];
		//���ֽڱ���ת���ɶ��ֽڱ���  
		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
		buffer[len] = '\0';
		//ɾ��������������ֵ  
		result.append(buffer);
		delete[] buffer;
		if (result.size() == 0)
		{
			std::exception("�ַ���ת��ʧ�ܣ�strTools::ws2s");
		}
		return result;
	}
	catch (const std::exception& e)
	{
		return e.what();
	}
}

