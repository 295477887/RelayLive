#pragma once

class CRtpClient;
namespace HttpWsServer
{
    struct pss_http_ws_live;
    enum MediaType;

    struct LIVE_BUFF {
        char *pBuff;
        int   nLen;
    };

    class CLiveWorker
    {
    public:
        CLiveWorker(string strCode, int rtpPort, pss_http_ws_live *pss);
        ~CLiveWorker();
        /** ֪ͨ���Ž��̲��� */
        bool RealPlayAsync(int rtpPort);
        /** ���ųɹ��ص� */
        void RealPlaySuccess();
        /** ֪ͨ���Ž��̹ر� */
        void StopAsync();
        /** ffmpeg������߳� */
        bool Play();
        /** ffmpeg��ȡ���� */
        int ReadInput(uint8_t *buf, int buf_size);

        /** ����UDP�˿ڼ��� */
        void StartListen();

		/** �ͻ���ȫ���Ͽ�����ʱ������ʵ�� */
		void Clear2Stop();
        bool m_bStop;          //< ���붨ʱ���ص�����Ϊtrue��close��ʱ���ص������ٶ���
        bool m_bOver;          //< ��ʱ����Ϊtrue���ͻ���ȫ���Ͽ�����ʱ����������

        /** ����˻�ȡ��Ƶ���� */
        LIVE_BUFF GetFlvVideo(uint32_t *tail);
        void NextWork(pss_http_ws_live* pss);

        /** ��ȡ�ͻ�����Ϣ */
        string GetClientInfo();

        /**
         * ��Դ��������Ƶ���ݣ����߳����� 
         * ���¼̳���IlibLiveCb�ķ�����rtp�������ڵ�loop�̵߳���
         * �������������������졢��������http���ڵ�loop�̵߳���
         */
        void push_flv_frame(char* pBuff, int nLen);
        void stop();
    private:
        void cull_lagging_clients(MediaType type);


    private:
        string                m_strCode;     // ����ý����
        CRtpClient            *m_pRtp;
        char                  *m_pRtpBuff;
        int                   m_nRtpBuffLen;
        int                   m_nRtpLen;
        int                   m_nRtpRead;

        /**
         * lws_ring�������λ�������ֻ��һ���߳�д�룬һ���̶߳�ȡ
         */
        struct lws_ring       *m_pRing;
        pss_http_ws_live      *m_pPssList;


        int                   m_nType;          //< 0:liveֱ����1:record��ʷ��Ƶ
        int                   m_nPort;          //< rtp���ն˿�

        uv_timer_t            m_uvTimerPlayTimeOut; //< ���ų�ʱû�еõ���Ӧ
    };

    /** ipc ��ʼ�� */
    void ipc_init();

    /** ֱ�� */
    CLiveWorker* CreatLiveWorker(string strCode, pss_http_ws_live *pss);

    /** �㲥 */

    /** ��ȡ������Ϣ������json */
    string GetClientsInfo();
};