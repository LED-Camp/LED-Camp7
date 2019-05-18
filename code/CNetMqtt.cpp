/* --------------------------------------------------------------- */
/* ファイルインクルード */
/* --------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>    // sleep()
#include <string>
#include "MQTTClient.h"
#include "CNetMqtt.h"
#include "CommonDefine.h"

using namespace std;

string Payload;


/* --------------------------------------------------------------- */
/* メンバ関数定義 */
/* --------------------------------------------------------------- */


/* TODO: コンストラクタでの接続作業の引越し */
/* 接続処理に関してはinitConnect()で行なうものとする */
/* シングルトンでの実装 */
/* *************************************************************** */
/* 関数名: CNetMqtt */
/* 概要: コンストラクタ */
/* 引数: [in] pcszClientId : クライアントID */
/* 引数: [in] pcszDestAddr : ブローカアドレス */
/* 引数: [in] iPort : ポート番号 (default: 1883) */
/* 戻り値: なし */
/* 説明: クライアントの生成〜ブローカへの接続までを行なう */
/* *************************************************************** */
CNetMqtt::CNetMqtt()
#if 0
    const char* pcszClientId,   // クライアントID
    const char* pcszDestAddr,   // ブローカアドレス
    int iPort)                  // ポート番号
#endif /* 0 */
{
    /* 局所変数宣言 */
    //int iRet;          // 戻り値

    /* 初期設定 */
    m_enRole = ROLE_PLAYER;
    m_pClient = NULL;
    m_bConenct = false;
    m_szTopic[0] = '\0';

    m_iQueHead = 0;
    m_iQueTail = 0;
    m_szContent[0] = '\0';

#if 0
    /* クライアントの生成 */
    snprintf(m_szBrokerAddr, sizeof(m_szBrokerAddr) - 1, "%s:%d", pcszDestAddr, iPort);
    iRet = MQTTClient_create(
        &m_pClient,
        m_szBrokerAddr,
        pcszClientId,
        MQTTCLIENT_PERSISTENCE_NONE,
        NULL
    );
    /* クライアントの生成に失敗した場合、続行不能とみなす */
    if (MQTTCLIENT_SUCCESS != iRet) {
        m_pClient = NULL;
        return;
    }

    /* コールバックの設定 */
    iRet = MQTTClient_setCallbacks(
        m_pClient,
        this,
        CNetMqtt::voLostConnection,
        CNetMqtt::siArrived,
        CNetMqtt::voDelivered
    );

    /* コールバックの設定に失敗した場合、続行不能とみなす */
    if (MQTTCLIENT_SUCCESS != iRet) {
        MQTTClient_destroy(&m_pClient);
        m_pClient = NULL;
        return;
    }

    /* ブローカへの接続 */
    iRet = siConnectBroker();

    /* ブローカへの接続に失敗した場合、続行不能とみなす */
    if (MQTTCLIENT_SUCCESS != iRet) {
        MQTTClient_destroy(&m_pClient);
        m_pClient = NULL;
        return;
    }
    else {
        m_bConenct = true;
    }

    /* 発行メッセージの設定 */
    m_stPubMsg.qos = m_ciQos;
    m_stPubMsg.retained = 0;
#endif /* 0 */

    return;
}


/* *************************************************************** */
/* 関数名: ~CNetMqtt */
/* 概要: デストラクタ */
/* 引数: なし */
/* 戻り値: なし */
/* 説明: 通信の切断およびオブジェクトの後始末 */
/* *************************************************************** */
CNetMqtt::~CNetMqtt()
{
    /* ブローカに接続している場合は解除する */
    if (false != m_bConenct) {
        m_bConenct = false;
        (void)MQTTClient_disconnect(m_pClient, MQTT_TIMEOUT);
    }
    /* クライアントが残っている場合は解放する */
    if (NULL != m_pClient) {
        MQTTClient_destroy(&m_pClient);
        m_pClient = NULL;
    }

    return;
}



/* *************************************************************** */
/* 関数名: initConnect */
/* 概要: ブローカへの接続 */
/* 引数: [in] pcszClientId : クライアントID */
/* 引数: [in] pcszDestAddr : ブローカアドレス */
/* 引数: [in] iPort : ポート番号 (default: 1883) */
/* 戻り値: 処理成否 */
/* 説明: クライアントの生成〜ブローカへの接続までを行なう */
/* *************************************************************** */
int CNetMqtt::initConnect(
    const char* pcszClientId,   // クライアントID
    const char* pcszDestAddr,   // ブローカアドレス
    int iPort)                  // ポート番号
{
    /* 局所変数宣言 */
    int iRet;          // 戻り値


    /* クライアントの生成 */
    snprintf(m_szBrokerAddr, sizeof(m_szBrokerAddr) - 1, "%s:%d", pcszDestAddr, iPort);
    iRet = MQTTClient_create(
        &m_pClient,
        m_szBrokerAddr,
        pcszClientId,
        MQTTCLIENT_PERSISTENCE_NONE,
        NULL
    );
    /* クライアントの生成に失敗した場合、続行不能とみなす */
    if (MQTTCLIENT_SUCCESS != iRet) {
        m_pClient = NULL;
        return RET_FAILED;
    }

    /* コールバックの設定 */
    iRet = MQTTClient_setCallbacks(
        m_pClient,
        this,
        CNetMqtt::voLostConnection,
        CNetMqtt::siArrived,
        CNetMqtt::voDelivered
    );

    /* コールバックの設定に失敗した場合、続行不能とみなす */
    if (MQTTCLIENT_SUCCESS != iRet) {
        MQTTClient_destroy(&m_pClient);
        m_pClient = NULL;
        return RET_FAILED;
    }

    /* ブローカへの接続 */
    iRet = siConnectBroker();

    /* ブローカへの接続に失敗した場合、続行不能とみなす */
    if (MQTTCLIENT_SUCCESS != iRet) {
        MQTTClient_destroy(&m_pClient);
        m_pClient = NULL;
        return RET_FAILED;
    }
    else {
        m_bConenct = true;
    }

    /* 発行メッセージの設定 */
    m_stPubMsg.qos = MQTT_QOS;
    m_stPubMsg.retained = 0;


    return RET_SUCCESS;
}


/* *************************************************************** */
/* 関数名: getInstance */
/* 概要: インスタンスの取得 */
/* 引数: なし */
/* 戻り値: インスタンスの参照 */
/* 説明: 唯一のインスタンスの取得を行なう */
/* *************************************************************** */
CNetMqtt& CNetMqtt::getInstance(void)
{
    static CNetMqtt inst;
    return inst;
}

// エンキュー
int CNetMqtt::siEnqueueMessage(enMsgId_t enMsgId)
{
    /* これ以上キューイングできない場合 */
    if (NEXT_INDEX(m_iQueTail) == m_iQueHead) {
        return RET_FAILED;
    }
    m_enMsgIds[m_iQueTail] = enMsgId;

    /* インデックスの更新 */
    m_iQueTail = NEXT_INDEX(m_iQueTail);

    return RET_SUCCESS;
}


// デキュー
int CNetMqtt::dequeueMessage(enMsgId_t* penMsgId)
{
    /* 何もキューにないとき */
    if (m_iQueHead == m_iQueTail) {
        return RET_FAILED;
    }
    *penMsgId = m_enMsgIds[m_iQueHead];

    /* インデックスの更新 */
    m_iQueHead = NEXT_INDEX(m_iQueHead);

    return RET_SUCCESS;
}

/* *************************************************************** */
/* 関数名: siConnectBroker */
/* 概要: ブローカへの接続 */
/* 引数: なし */
/* 戻り値: 処理成否 */
/* 説明: クライアントの情報は事前に設定されているものとする */
/* *************************************************************** */
int CNetMqtt::siConnectBroker(void)
{
    /* 局所変数宣言 */
    int iRet;                                       // 戻り値
    MQTTClient_connectOptions staConnOpt            // 接続オプション
        = MQTTClient_connectOptions_initializer;
    
    /* 接続オプションの設定 */
    staConnOpt.keepAliveInterval = INTERV_KEEPALIVE;
    staConnOpt.cleansession      = 1;

    /* ブローカへの接続 */
    iRet = MQTTClient_connect(
        m_pClient,
        &staConnOpt
    );

    return iRet;
}

/* *************************************************************** */
/* 関数名: subscrTopic (API) */
/* 概要: トピックの購読 */
/* 引数: [in] pcszToic : トピック名 */
/* 戻り値: 処理成否 */
/* 説明: 引数で指定したトピック名のメッセージの購読を開始する */
/* *************************************************************** */
int CNetMqtt::subscrTopic(const char* pcszToic)
{
    /* 局所変数宣言 */
    int iRet;

    /* クライアントチェック */
    if (NULL == m_pClient) {
        return RET_INVLID_CLIENT;
    }

    /* 購読の手続き */
    iRet = MQTTClient_subscribe(
        m_pClient,
        pcszToic,
        MQTT_QOS
    );

    return (MQTTCLIENT_SUCCESS == iRet) ? RET_SUCCESS : RET_FAILED;
}


/* *************************************************************** */
/* 関数名: publishMessage (API) */
/* 概要: メッセージの発行 */
/* 引数: [in] enMsgId : メッセージID */
/* 引数: [in] pcszContent : メッセージの内容 */
/* 戻り値: 処理成否 */
/* 説明: メッセージの発行 */
/* *************************************************************** */
int CNetMqtt::publishMessage(
    enMsgId_t   enMsgId,
    const char* pcszContent)
{
    /* 局所変数宣言 */
    int   iRet;                                  // 戻り値
    char  szMessage[SIZE_MESSAGE];               // 発行メッセージ
    MQTTClient_deliveryToken  iDeliverToken;     // 配送トークン

#ifdef _DEBUG
    printf("[publishMessage] >> Enter\n");
#endif /* _DEBUG */

    /* クライアントチェック */
    if (NULL == m_pClient) {
        return RET_INVLID_CLIENT;
    }

    /* *** ペイロードの設定 *** */
    /* メッセージIDのみの場合 */
    if (NULL == pcszContent) {
#ifdef _DEBUG
        printf("[publishMessage] Only MessageID\n");
#endif /* _DEBUG */
        snprintf(szMessage, SIZE_MESSAGE - 1, "%c", (char)enMsgId);
    }
    /* コンテンツがある場合 */
    else {
#ifdef _DEBUG
        printf("[publishMessage] With Content\n");
#endif /* _DEBUG */
        snprintf(szMessage, SIZE_MESSAGE - 1, "%c%s", (char)enMsgId, pcszContent); 
    }
    m_stPubMsg.payload = (void*)szMessage;
    m_stPubMsg.payloadlen = strlen(szMessage);

#ifdef _DEBUG
    printf("[publishMessage]::\n");
    printf("\tClient: %p\n", m_pClient);
    printf("\tTopic: %s\n", m_szTopic);
    printf("\tMessageID: 0x%02x\n", *(char*)(m_stPubMsg.payload));
    if (1 < strlen(szMessage)) {
        printf("\tContent: %s\n", (char*)m_stPubMsg.payload + 1);
    }
#endif /* _DEBUG */

    /* メッセージの発行 */
    m_iDelivered = 0;
    iRet = MQTTClient_publishMessage(
        m_pClient,
        m_szTopic,
        &m_stPubMsg,
        &iDeliverToken
    );
    if (MQTTCLIENT_SUCCESS != iRet) {
        return RET_FAILED;
    }
    
    /* NOTE: タイムアウトがあったほうがいいかも */
    while(iDeliverToken != m_iDelivered);
#ifdef _DEBUG
    printf("[publishMessage] << Leave\n");
#endif /* _DEBUG */
    return RET_SUCCESS;
}

/* *************************************************************** */
/* 関数名: setTopic (API) */
/* 概要: トピック名の設定 */
/* 引数: [in] pcszToic : トピック名 */
/* 戻り値: 処理成否 */
/* 説明: トピック名の設定 */
/* *************************************************************** */
int CNetMqtt::setTopic(const char* pcszTopic)
{
    /* 局所変数宣言 */
    const int ciLenMem = ARRAY_SIZE(m_szTopic);
    const int ciLen    = strlen(pcszTopic);

    /* 正常系処理 */
    if (ciLenMem > ciLen) {
        strncpy(m_szTopic, pcszTopic, ciLen);
        return RET_SUCCESS;
    }
    /* 引数の文字列が長すぎる場合 */
    else {
        return RET_FAILED;
    }

}


/* *************************************************************** */
/* 関数名: getTopic (API) */
/* 概要: トピック名の取得 */
/* 引数: [out] pszTopic : トピック名 */
/* 引数: [in] iLenTopic : トピック名の配列長 */
/* 戻り値: 処理成否 */
/* 説明: トピック名の取得 */
/* *************************************************************** */
int CNetMqtt::getTopic(
    char* pszTopic,
    int   iLenTopic)
{
    /* 局所変数宣言 */
    const int ciLenMem = strlen(m_szTopic);

    if (ciLenMem < iLenTopic) {
        strncpy(pszTopic, m_szTopic, ciLenMem + 1);
        return RET_SUCCESS;
    }
    /* コピー先の配列が小さい場合 */
    else {
        return RET_FAILED;
    }
}


/* *************************************************************** */
/* 関数名: getContent (API) */
/* 概要: コンテンツの取得 */
/* 引数: [out] pszTopic : コンテンツ */
/* 引数: [in] iLenTopic : コンテンツの配列長（callee） */
/* 戻り値: 処理成否 */
/* 説明: トピック名の取得 */
/* *************************************************************** */
int CNetMqtt::getContent(
    char* pszContent,
    int   iLenContent)
{
    /* 局所変数宣言 */
    const int ciLenMem = strlen(m_szContent);

    if (ciLenMem < iLenContent) {
        strncpy(pszContent, m_szContent, ciLenMem + 1);
        return RET_SUCCESS;
    }
    /* コピー先の配列が小さい場合 */
    else {
        return RET_FAILED;
    }
}


/* *************************************************************** */
/* 関数名: voDelivered */
/* 概要: 非同期コールバック関数 */
/* 引数: [in] pvContext : コンテキスト (自オブジェクト) */
/* 引数: [in] iDeliverToken : 配送トークン */
/* 戻り値: 処理成否 */
/* 説明: メッセージの配送が完了した時に呼ばれる */
/* 配送完了メッセージの設定を行なう */
/* *************************************************************** */
void CNetMqtt::voDelivered(
    void* pvContext,
    MQTTClient_deliveryToken iDeliverToken)
{
    ((CNetMqtt*)pvContext)->m_iDelivered = iDeliverToken;
    return;
}


/* *************************************************************** */
/* 関数名: siArrived */
/* 概要: 非同期コールバック関数 */
/* 引数: [in] pvContext : コンテキスト (自オブジェクト) */
/* 引数: [in] pszTopic : トピック名 */
/* 引数: [in] iLenTopic : トピック名の文字列長 */
/* 引数: [in] pstMsg : 受け取ったメッセージ */
/* 戻り値: 処理成否 */
/* 説明: メッセージを受け取った時に呼ばれる */
/* メッセージの固有処理は外部関数に委譲する */
/* *************************************************************** */
int CNetMqtt::siArrived(
    void* pvContext,
    char* pszTopic,
    int iLenTopic,
    MQTTClient_message* pstMsg)
{
    /* 局所変数宣言 */
    int i;       // ループ変数
    int j;
    char*  pszPayload;  // ペイロードへのポインタ
    char   szContent[SIZE_CONTENT];
    enMsgId_t enMsgId;   // メッセージID
    int iRet = RET_TRUE;
    CNetMqtt* pOwn = (CNetMqtt*)pvContext;

#ifdef _DEBUG
        printf("[siArrived] >> Enter\n");
        printf("\tpayloadlen: %d\n", pstMsg->payloadlen);
        /* ペイロード長が1の場合 */
        if (1 == pstMsg->payloadlen) {
            printf("\tpayload: 0x%02x\n", *(char*)pstMsg->payload);
        }
        printf("Topic: %s\n", pszTopic);
        printf("m_Topic: %s\n", pOwn->m_szTopic);
#endif /* _DEBUG */

    pszPayload = (char*)pstMsg->payload;

    // 自身がPlayerでPlayerが発行したメッセージを受け取った場合
    // if ((ROLE_PLAYER & *pszPayload) == pOwn->m_enRole) {
    //     goto exit;
    // }
    // 自身がJudgeでJudgeが発行したメッセージを受け取った場合
    if ((ROLE_JUDGE & *pszPayload) == pOwn->m_enRole) {
        goto exit;
    }

    j = 0;
    for (i = 0; pstMsg->payloadlen >= i; ++i) {
        /* payloadが大きすぎる場合 */
        if (SIZE_CONTENT - 1 < i) {
            iRet = RET_FALSE;
            break;
        }

        /* メッセージIDの処理 */
        if (0 == i) {
            enMsgId = (enMsgId_t)*pszPayload;
        }
        /* メッセージID以外 */
        else {
            szContent[j++] = *pszPayload++;
        }
    }
    szContent[j] = '\0';

    /* コンテンツのコピー */
    if (SIZE_CONTENT >= j) {
        strncpy(pOwn->m_szContent, szContent, j + 1);
#ifdef _DEBUG
        printf("[siArrived] Copy Content: %s\n", pOwn->m_szContent);
#endif /* _DEBUG */
    }

    /* *** メッセージ固有処理 *** */
    /* NOTE: 関数ポインタにする？ */
    pOwn->siEnqueueMessage(enMsgId);
    pOwn->voProcUniqMessage(enMsgId, szContent);
    //ペイロードの更新
    Payload = szContent;


    


exit:
    /* メッセージメモリの解放 */
    MQTTClient_freeMessage(&pstMsg);
    MQTTClient_free(pszTopic);

#ifdef _DEBUG
        printf("[siArrived] << Leave\n");
#endif /* _DEBUG */

    return iRet;
}


/* *************************************************************** */
/* 関数名: voLostConnection */
/* 概要: 非同期コールバック関数 */
/* 引数: [in] pvContext : コンテキスト (自オブジェクト) */
/* 引数: [in] pszCause : 切断原因 (未使用) */
/* 戻り値: 処理成否 */
/* 説明: ブローカとの接続が切断した時に呼ばれる */
/* ブローカに再接続を試みる */
/* *************************************************************** */
void CNetMqtt::voLostConnection(
    void* pvContext,
    char* pszCause)
{
    /* 局所変数宣言 */
    int iCntRetry;
    int iRet;

    //((CNetMqtt*)pvContext)->m_bConenct = false;
#ifdef _DEBUG
        printf("[voLostConnection] >> Enter\n");
#endif /* _DEBUG */

    for (iCntRetry = 0; MAX_RETRY_CONN > iCntRetry; ++iCntRetry) {
#ifdef _DEBUG
        printf("[voLostConnection] Reconnectings... (%d/%d)\n", iCntRetry + 1, MAX_RETRY_CONN);
#endif /* _DEBUG */
        iRet = ((CNetMqtt*)pvContext)->siConnectBroker();
        if (RET_SUCCESS == iRet) {
            break;
        }
        sleep(1);
    }

#ifdef _DEBUG
        printf("[voLostConnection] << Leave\n");
#endif /* _DEBUG */

    return;
}


void CNetMqtt::voProcUniqMessage(
     enMsgId_t enMsgId,
     const char* pcszContent)
{
// {
//     switch(enMsgId) {
//         case PLAYER_HELLO:
//             printf("PLAYER_HELLO\n");
//             break;
//         case PLAYER_UPDATE:
//             printf("PLAYER_UPDATE\n");
//             break;
//         case PLAYER_START:
//             printf("PLAYER_START\n");
//             break;
//         case PLAYER_ABORT:
//             printf("PLAYER_ABORT\n");
//             break;
//         case PLAYER_BYE:
//             printf("PLAYER_BYE\n");
//             break;
//         case JUDGE_HELLO:
//             printf("JUDGE_HELLO\n");
//             break;
//         case JUDGE_BUSY:
//             printf("JUDGE_BUSY\n");
//             break;
//         case JUDGE_DEAL:
//             printf("JUDGE_DEAL\n");
//             break;
//         case JUDGE_ACK:
//             printf("JUDGE_ACK\n");
//             break;
//         case JUDGE_NACK:
//             printf("JUDGE_NACK\n");
//             break;
//         case JUDGE_OK:
//             printf("JUDGE_OK\n");
//             break;
//         case JUDGE_NG:
//             printf("JUDGE_NG\n");
//             break;
//         case JUDGE_TIMEOUT:
//             printf("JUDGE_TIMEOUT\n");
//             break;
//         case JUDGE_BYE:
//             printf("JUDGE_BYE\n");
//             break;
//         default:
//             printf("UNKNOWN MESSAGE ID!! (0x%02x)\n", enMsgId);
//             break;
//             /* ここには来ない */
//     } // switch

//    return;
}

/* ***** デバッグ用関数 ***** */
#ifdef _DEBUG
void CNetMqtt::dbgDisconnect(void)
{

    (void)MQTTClient_disconnect(m_pClient, MQTT_TIMEOUT);

    return;
}

void CNetMqtt::dbgSetRole(enRole_t enRole)
{
    m_enRole = enRole;
}
#endif /* _DEBUG */
