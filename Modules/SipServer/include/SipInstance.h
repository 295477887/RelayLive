#pragma once

#ifdef SIP_EXPORTS
#define SIP_API __declspec(dllexport)
#else
#define SIP_API
#endif


class SIP_API SipInstance
{
public:
    SipInstance(void);
    ~SipInstance(void);

    static bool Init();

    static void Cleanup();

    static bool rtsp_play(string devCode, string rtpIP, int rtpPort);

    /**
     * ����һ��ʵʱ����
     * @param[in] strDev �豸����
     * @return true:�ɹ� false:ʧ��
     */
    static bool RealPlay(string strDev, string rtpIP, int rtpPort);

    /**
     * �ر�һ��ʵʱ����
     * @param[in] rtpPort �ö˿���Ϊid
     * @return true:�ɹ� false:ʧ��
     */
    static bool StopPlay(string rtpPort);

    /**
     * �ر����в���
     */
    static bool StopPlayAll();

    /**
     * ����һ����ʷ��Ƶ����
     * @param[in] strDev �豸����
     * @param startTime ��ʼʱ��
     * @param endTime ����ʱ��
     * @param session �Ựsession
     * @return true:�ɹ� false:ʧ��
     */
    static bool RecordPlay(string strDev, string startTime, string endTime);

    /**
     * ��̨����
     * @param strDev[in] �豸����
     * @param nInOut[in]     ��ͷ�Ŵ���С 0:ֹͣ 1:��С 2:�Ŵ�
     * @param nUpDown[in]    ��ͷ�������� 0:ֹͣ 1:���� 2:����
     * @param nLeftRight[in] ��ͷ�������� 0:ֹͣ 1:���� 2:����
     */
    static bool DeviceControl(string strDev,
        int nInOut = 0, int nUpDown = 0, int nLeftRight = 0);

private:
    static void* m_pHandle;
};

