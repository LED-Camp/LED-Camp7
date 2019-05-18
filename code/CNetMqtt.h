#ifndef __C_NET_MQTT_H__

/* *** 2重イングルード禁止 *** */
#define __C_NET_MQTT_H__

/* *** ファイルインクルード *** */
#include "CommonDefine.h"
#include "/usr/local/include/MQTTClient.h"  // MQTTClient_deliveryToken, MQTTClient_message etc.
//#include "CSingleton.h"

/* *** 定数定義 *** */
#define SIZE_ADDR    (255)                  // アドレス名の最大長
#define SIZE_CONTENT (31)                   // コンテンツの最大長
#define SIZE_TOPIC   SIZE_CONTENT           // トピック名の最大長
#define SIZE_MESSAGE (SIZE_CONTENT + 1)     // ペイロード最大長
#define MQTT_TIMEOUT (10000)                // タイムアウト時間 [ms]
#define MQTT_QOS     (1)                    // QOS

#define MAX_RETRY_CONN    (10)              // 接続試行回数
#define INTERV_KEEPALIVE  (20)              // キープアライブ間隔 [sec]

#define RET_INVLID_CLIENT (-11)             // 戻り値: クライアント無効

#define SIZE_QUEUE  (10)                    // キューのサイズ

/* *** 共通定義 *** */

/* *** 型定義 *** */


/* *** マクロ関数 *** */
#define NEXT_INDEX(x)   (((x) + 1) % SIZE_QUEUE)
/* #define _DEBUG */
class CNetMqtt {
    /* Variables */
 public:
 private:
    bool          m_bConenct;                   // 接続状態
    char          m_szTopic[SIZE_TOPIC];        // トピック名
    char          m_szBrokerAddr[SIZE_ADDR];    // 接続先アドレス
    //const int     m_ciQos = MQTT_QOS;           // QOS
    MQTTClient    m_pClient;                    // クライアント
    enRole_t      m_enRole;                     // 役割
    enMsgId_t     m_enMsgIds[SIZE_QUEUE];
    int           m_iQueHead;
    int           m_iQueTail;
    char          m_szContent[SIZE_CONTENT];    // コンテンツ


    MQTTClient_message                  m_stPubMsg      // 発行メッセージ
        = MQTTClient_message_initializer;
    volatile MQTTClient_deliveryToken   m_iDelivered;   // 配送完了トークン
    /* Functions */
 public:

    // dead code
    /* CNetMqtt(const char* pcszClientId, const char* pszDestAddr, int iPort = 1883); */
    /* ~CNetMqtt(); */


    /* *** APIs *** */

    /* インスタンスの取得 */
    static CNetMqtt& getInstance(void);

    /* 接続の初期設定 */
    int initConnect(const char* pcszClientId, const char* pszDestAddr, int iPort = 1883);

    /* トピックの設定 */
    int setTopic(const char* pcszTopic);
    /* トピックの取得 */
    int getTopic(char* pszTopic, const int iLenTopic);

    /* トピックの購読開始 */
    int subscrTopic(const char* pcszToic);

    /* トピックの購読解除 */
    /* TODO: 実装 */

    /* メッセージの発行 */
    int publishMessage(enMsgId_t enMsgId, const char* pcszMsg = NULL);

    int dequeueMessage(enMsgId_t* penMsgId);

    /* コンテンツの取得 */
    int getContent(char* pszContent, int iLenContent);
    CNetMqtt();
    ~CNetMqtt();


#ifdef _DEBUG
    void dbgDisconnect(void);
    void dbgSetRole(enRole_t);
#endif /* _DEBUG */
 private:
    int siConnectBroker(void);
    /* *** コールバック関数 *** */
    static void voDelivered(void* pvContext, MQTTClient_deliveryToken iMsg);
    static int  siArrived(void* pvContext, char* pszTopic, int iLenTopic, MQTTClient_message* pstMsg);
    static void voLostConnection(void* pvContext, char* pszCause);

    //void connectBroker(void);
    void voProcUniqMessage(enMsgId_t enMsgId, const char* pcszContent);

    int siEnqueueMessage(enMsgId_t enMsgId);


};


#endif /* __C_NET_MQTT_H__ */
