// sever.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "common.h"
#include "DeviceMgr.h"
#include "SipInstance.h"
#include "MiniDump.h"
#include "uvIpc.h"
#include "utilc_api.h"
#include "stdio.h"

uv_ipc_handle_t* h = NULL;

static string strfind(char* src, char* begin, char* end){
    char *p1, *p2;
    p1 = strstr(src, begin);
    if(!p1) return "";
    p1 += strlen(begin);
    p2 = strstr(p1, end);
    if(p2) return string(p1, p2-p1);
    else return string(p1);
}

void on_ipc_recv(uv_ipc_handle_t* h, void* user, char* name, char* msg, char* data, int len)
{
    if (!strcmp(msg,"live_play")) {
        // ssid=123&rtpip=1.1.1.1&rtpport=50000
        data[len] = 0;
        string ssid = strfind(data, "ssid=", "&");
        string ip = strfind(data, "rtpip=", "&");
        string port = strfind(data, "rtpport=", "&");

        bool bplay = SipInstance::RealPlay(ssid, ip, stoi(port));
        if(bplay) {
            stringstream ss;
            ss << "ssid=" << port << "&ret=0&error=success";
            string str = ss.str();
            uv_ipc_send(h, "liveDest", "live_play_answer", (char*)str.c_str(), str.size());
        } else {
            stringstream ss;
            ss << "ssid=" << port << "&ret=-1&error=sip play failed";
            string str = ss.str();
            uv_ipc_send(h, "liveDest", "live_play_answer", (char*)str.c_str(), str.size());
        }
    } else if(!strcmp(msg,"stop_play")) {
        string ssid(data, len);

        SipInstance::StopPlay(ssid);
    } else if(!strcmp(msg,"close")) {
        //�ر��������ڽ��еĲ���
        SipInstance::StopPlayAll();
    }
}

int main()
{
    /** Dump���� */
    CMiniDump dump("sipServer.dmp");

    /** ���̼�ͨ�� */
    int ret = uv_ipc_client(&h, "relay_live", NULL, "liveSrc", on_ipc_recv, NULL);
    if(ret < 0) {
        printf("ipc server err: %s\n", uv_ipc_strerr(ret));
    }

    /** ������־�ļ� */
    char path[MAX_PATH];
    sprintf_s(path, MAX_PATH, ".\\log\\sipServer.txt");
    Log::open(Log::Print::both, Log::Level::debug, path);

    /** ���������ļ� */
    if (!Settings::loadFromProfile(".\\config.txt"))
    {
        Log::error("�����ļ�����");
        return -1;
    }
    Log::debug("Settings::loadFromProfile ok");


    /** ��ʼ���豸ģ�� */
    if (!DeviceMgr::Init())
    {
        Log::error("DeviceManagerInstance init failed");
        return -1;
    }
    Log::debug("DeviceMgr::Init ok");

    /** ��ʼ��SIP������ */
    if (!SipInstance::Init())
    {
        Log::error("SipInstance init failed");
        return -1;
    }
    Log::debug("SipInstance::Init ok");
    
    sleep(INFINITE);
    return 0;
}