#pragma once
namespace HttpWsServer
{
class CLiveWorker;
class CRtpClient
{
public:
    CRtpClient(CLiveWorker *live, uv_loop_t *uv, int rtpPort);
    ~CRtpClient(void);

    /** uv��ȡudp���ݻص� */
    void RtpRecv(char* pBuff, long nLen);
    /** uv��ȡ��ʱ�ص� */
    void TimeOut();

    /** ��ʼ���� */
    void StartListen();

    /** ��ȡһ��rtp�� */
    int GetPacket(char** buf, int *buf_len);

    /** �رս��� */
    void Stop();
private:

private:
    uv_loop_t             *m_uvLoop;
    uv_udp_t              m_uvRtpSocket;      // rtp����
    uv_timer_t            m_uvTimeOver;       // ���ճ�ʱ��ʱ��
    int                   m_nPort;            // rtp���ն˿�
    struct lws_ring       *m_pRtpRing;        // ���rtp��
    uint32_t              m_nTail;            // ��һ�����ݵ�λ��
    CLiveWorker *m_pLive;
};
}

