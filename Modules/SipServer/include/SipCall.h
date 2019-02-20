#pragma once
#include "PublicDefine.h"

/**
 * һ��Invite�Ự����������
 */
class CSipCall
{
public:
    ~CSipCall(void);

    /**
     * ����һ��SIPͨ����������Ƶ����
     * @param strPlatformCode[in] ƽ̨����
     * @param strDevCode[in] �豸����
     * @param strIP[in] rtp���շ���IP
     * @param nPort[in] rtp���շ���˿�
     * @return �ɹ�true,ʧ��false
     */
    static bool CreatSipCall(string strDevCode, string strIP, int nPort);
    static bool CreatSipCall(string strDevCode, string strIP, int nPort, 
        string startTime, string endTime);

    /**
     * ����һ��SIPͨ������ɾ������
     * @param strRtpPort[in] rtp�˿ڣ���Ϊ�Ựid
     * @return �ɹ�true,ʧ��false
     */
    static bool StopSipCall(string strRtpPort);

    static bool StopSipCallAll();

    /**
     * ������Ƶ����
     */
    bool SendInvite();
    bool SendRecordInvite();

    /**
     * ������Ƶ����ɹ�
     */
    bool OnInviteOk(int nDID, char* szBody, int nLength);
    bool OnInviteFailed();
    bool WaiteInviteFinish();

    /**
     * ������Ƶ
     */
    bool SendBye();

    /**
     * ����Call-ID�ҵ�����
     */
    static CSipCall* FindByCallID(int nCID);

private:
    CSipCall();

public:
    static map<int,CSipCall*>     m_mapGlobalCall;  //< ���еĸ���ʵ������������key��callid���Ա���Ӧʱ�ҵ�
    static map<string,CSipCall*>  m_mapDeviceCall;  //< key��rtp�˿ڡ���Ϊ�˿ڲ��ظ���������ΪID
    static CriticalSection        m_csGlobalCall;

private:
    // �Ự��Ϣ
    int             m_nCallID;     //< invite����ʱ�õ���ID
    int             m_nDialogID;   //< �����ɹ����Դ�osip_event�еõ�
    int             m_nRtpPort;    //< rtp���ն˿ڣ�rtcp�˿ڼ�1
    string          m_strRtpIP;    //< rtp����IP
    // �豸��Ϣ
    string          m_strPlatformCode;  //< ƽ̨�ı���
    string          m_strDevCode;       //< �豸�ı���

    int             m_nInvite;     //< ����״̬��ǣ�����������Ϊ0���յ�����Ӧ����Ϊ1

    //��ʷ��Ƶ�㲥
    bool            m_bRecord;
    string          m_strBeginTime;
    string          m_strEndTime;
};

