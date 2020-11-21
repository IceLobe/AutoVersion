// AutoVersion.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <Windows.h>
#include <iostream>
#include <string>
#include <time.h>

#include "strTools.h"

#ifdef _DEBUG
#else
//不显示控制台窗口
#pragma comment(linker,"/subsystem:windows /entry:mainCRTStartup")
#endif

/// <summary>
/// 将日期设为版本号
/// </summary>
/// <param name="vData"></param>
/// <returns></returns>
int getDateToVersion(std::string& vData, std::string& version)
{
    time_t nowtime = time(NULL);
    struct tm p;
    localtime_s(&p, &nowtime);
    //p.tm_year的结果为 (当前年 - 1900)
    std::string year = std::to_string(p.tm_year);
    year = year.substr(1, 2);
    std::string month = std::to_string(p.tm_mon + 1);
    std::string day = std::to_string(p.tm_mday);
    vData = year + "," + month + "," + day + ",";
    version = year + "." + month + "." + day + ".";
    return 0;
}

/// <summary>
/// 变更资源文件内容
/// </summary>
/// <param name="res">资源文件内容</param>
/// <returns></returns>
int changeResFileContent(std::string& res)
{
    try
    {
        std::string vData, version;
        getDateToVersion(vData, version);
        char verStr[] = "FILEVERSION";
        //得到版本号的位置
        size_t verPos = res.find(verStr) + strlen(verStr) + 1;
        //原版本号
        std::string desVersion = res.substr(verPos);
        desVersion = desVersion.substr(0, desVersion.find("\r"));
        //获取最后一位版本号
        std::string appVersion = desVersion.substr(desVersion.length() - 1);
        if (-1 == desVersion.find(vData))
        {
            vData = vData + "0";
        }
        else
        {
            int appVer = atoi(appVersion.c_str()) + 1;
            vData = vData + std::to_string(appVer);
        }
        //循环替换有逗号的版本号
        while (-1 != (verPos = res.find(desVersion)))
        {
            res.replace(verPos, desVersion.length(), vData);
        }
        //获取新版本号的最后一位
        int pos = vData.find_last_of(",") + 1;
        version = version + vData.substr(pos, vData.length() - pos);
        while (-1 != (pos = desVersion.find(",")))
        {
            desVersion.replace(pos, 1, ".");
        }
        while (-1 != (verPos = res.find(desVersion)))
        {
            res.replace(verPos, desVersion.length(), version);
        }
        return 1;
    }
    catch (const std::exception&)
    {
        return 0;
    }
}

int main()
{
    std::string resFileName;
    WIN32_FIND_DATA p;
    HANDLE handle = FindFirstFileW(L"*.rc",&p);
    do
    {
        if (INVALID_HANDLE_VALUE != handle)
        {
            resFileName = strTools::ws2s(p.cFileName);
        }
        FILE* fp;
        fopen_s(&fp, resFileName.c_str(), "rb+");
        if (fp)
        {
            //获取文件大小
            fseek(fp, 0, SEEK_END);
            unsigned int reslen = ftell(fp) + 1;
            unsigned char* str = new unsigned char[reslen];
            memset(str, 0, reslen * sizeof(unsigned char));
            //读取文件内容
            fseek(fp, 0, SEEK_SET);
            fread((void*)str, 1, reslen, fp);
            //------------------------------------------
            std::string res = (char*)str;
            changeResFileContent(res);
            //重写文件内容
            fseek(fp, 0, SEEK_SET);
            fwrite(res.c_str(), 1, res.length(), fp);
            fclose(fp);
        }
    } while (FindNextFileW(handle, &p));
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
