#ifdef F_LINUXARM

#include "wifi_config.h"

#include <iostream>
using namespace std;
#include <string>

wifi_config::wifi_config(wifi_cb_t open_cb, wifi_cb_t state_cb, void *arg)
{
    printf("%s %d <<<<<<<<<<<<\n", __func__, __LINE__);

    this->hWlan = -1;
    this->open_cb = open_cb;
    this->state_cb = state_cb;
    this->is_open = false;
    this->is_exit = false;
    this->arg = arg;

    this->get_cmd_list.clear();
    this->cb_cmd_list.clear();

    pthread_mutex_init(&this->mutex, NULL);

    // MI 中wifi 操作是阻塞的，所以开单独个线程来避免阻塞主线程
    pthread_create(&this->p_init_id, NULL, wifi_init_pthread_init, this);
    if (!this->p_init_id)
    {
        printf("Error: create check wifi  thread failed\n");
        return;
    }

    printf("%s %d >>>>>>>>>>>>>>\n", __func__, __LINE__);
    return;
}

wifi_config::~wifi_config()
{
    this->is_exit = true;
    pthread_join(this->p_init_id, NULL);

    for (auto item : this->cb_cmd_list)
    {
        if (item.is_free)
        {
            free(item.req);
        }
    }

    MI_WLAN_OpenParams_t stOpenParam = {E_MI_WLAN_NETWORKTYPE_INFRA};
    MI_WLAN_Close(&stOpenParam);
    MI_WLAN_DeInit();
}

void *wifi_config::wifi_init_pthread_init(void *pdata)
{
    printf("%s %d <<<<<<<<<<<<\n", __func__, __LINE__);
    wifi_config *_this = (wifi_config *)pdata;
    int checkCnt = 40;
    int isWlanInsmode = 0;

    MI_WLAN_InitParams_t stParm = {"/config/wifi/wlan.json"};
    MI_WLAN_OpenParams_t stOpenParam = {E_MI_WLAN_NETWORKTYPE_INFRA};

    if (MI_WLAN_Init(&stParm) || MI_WLAN_Open(&stOpenParam))
    {
        printf("Error: open wifi failed\n");
        _this->is_open = false;
        _this->wifi_add_cb_list(_this->open_cb, _this->arg, (void *)(_this->is_open));
        return NULL;
    }
    else
    {
        _this->is_open = true;
        _this->wifi_add_cb_list(_this->open_cb, _this->arg, (void *)(_this->is_open));
    }

    while (!_this->is_exit)
    {
        _this->wifi_state_run();

        pthread_mutex_lock(&_this->mutex);
        bool is = _this->get_cmd_list.empty();
        pthread_mutex_unlock(&_this->mutex);

        if (is)
        {
            usleep(200 * 1000);
            continue;
        }

        pthread_mutex_lock(&_this->mutex);
        get_cmd_node_t val = _this->get_cmd_list.front();
        _this->get_cmd_list.pop_front();
        pthread_mutex_unlock(&_this->mutex);

        MI_WLAN_ScanResult_t *scanResult;
        MI_WLAN_ConnectParam_t *pstConnParam;
        switch (val.cmd)
        {
        case WIFI_CMD_SCAN:
            scanResult = (MI_WLAN_ScanResult_t *)malloc(sizeof(MI_WLAN_ScanResult_t));
            MI_WLAN_Scan(NULL, scanResult);
            _this->wifi_add_cb_list(val.cb, val.arg, scanResult, true);
            break;
        case WIFI_CMD_CONNECT:
            pstConnParam = (MI_WLAN_ConnectParam_t *)val.arg;
            if (pstConnParam)
            {
                MI_WLAN_Connect(&_this->hWlan, pstConnParam);
                free(pstConnParam);
            }
            break;
        case WIFI_CMD_DISCONNECT:
            if (_this->hWlan > 0)
            {
                MI_WLAN_Disconnect(_this->hWlan);
                _this->hWlan = -1;
            }
            _this->wifi_add_cb_list(val.cb, val.arg, NULL);
            break;
        default:

            break;
        }

        usleep(50 * 1000);
    }

    printf("%s %d >>>>>>>>>>>>>>\n", __func__, __LINE__);
    return NULL;
}

void wifi_config::wifi_state_run()
{
    static MI_WLAN_Status_sta_t stStaStatus_old;
    MI_WLAN_Status_t stStatus;
    if (this->hWlan < 0)
    {
        return;
    }
    MI_WLAN_GetStatus(this->hWlan, &stStatus);
    if (0 == memcmp(&stStaStatus_old, &stStatus.stStaStatus, sizeof(MI_WLAN_Status_sta_t)))
    {
        return;
    }

    MI_WLAN_Status_sta_t *st = (MI_WLAN_Status_sta_t *)malloc(sizeof(MI_WLAN_Status_sta_t));
    memcpy(st, &stStatus, sizeof(MI_WLAN_Status_sta_t));
    memcpy(&stStaStatus_old, &stStatus, sizeof(MI_WLAN_Status_sta_t));

    this->wifi_add_cb_list(this->state_cb, this->arg, (void *)st, true);
}

//添加应答节点
void wifi_config::wifi_add_cb_list(wifi_cb_t cb, void *arg, void *req, bool is_free)
{
    cb_cmd_node_t val;
    val.arg = arg;
    val.cb = cb;
    val.req = (void *)req;
    val.is_free = is_free;

    pthread_mutex_lock(&this->mutex);
    this->cb_cmd_list.push_back(val);
    pthread_mutex_unlock(&this->mutex);
}

//主线程调用，搜索完成后通过全局list通知主线程
void wifi_config::wifi_scan(wifi_cb_t cb, void *arg)
{
    LV_LOG_USER("");

    get_cmd_node_t val;
    val.arg = arg;
    val.cmd = WIFI_CMD_SCAN;
    val.cb = cb;

    pthread_mutex_lock(&this->mutex);
    this->get_cmd_list.push_back(val);
    pthread_mutex_unlock(&this->mutex);
}

void wifi_config::wifi_connect(char *ssid, char *pwd)
{
    LV_LOG_USER("");
    if (!ssid || !pwd)
    {
        return;
    }
    MI_WLAN_ConnectParam_t *pstConnParam = (MI_WLAN_ConnectParam_t *)malloc(sizeof(MI_WLAN_ConnectParam_t));
    memset(pstConnParam, 0, sizeof(MI_WLAN_ConnectParam_t));
    pstConnParam->eSecurity = E_MI_WLAN_SECURITY_WPA;
    pstConnParam->OverTimeMs = 5 * 1000;

    strcpy((char *)pstConnParam->au8SSId, ssid);
    strcpy((char *)pstConnParam->au8Password, pwd);

    get_cmd_node_t val;
    val.arg = (void *)pstConnParam;
    val.cmd = WIFI_CMD_CONNECT;
    val.cb = NULL;

    pthread_mutex_lock(&this->mutex);
    this->get_cmd_list.push_back(val);
    pthread_mutex_unlock(&this->mutex);
}

void wifi_config::wifi_disconnect(wifi_cb_t cb, void *arg)
{
    LV_LOG_USER("");

    get_cmd_node_t val;
    val.arg = (void *)arg;
    val.cmd = WIFI_CMD_DISCONNECT;
    val.cb = cb;

    pthread_mutex_lock(&this->mutex);
    this->get_cmd_list.push_back(val);
    pthread_mutex_unlock(&this->mutex);
}

void wifi_config::wifi_mastar_run()
{
    pthread_mutex_lock(&this->mutex);
    bool is = this->cb_cmd_list.empty();
    pthread_mutex_unlock(&this->mutex);

    if (is)
    {
        return;
    }
    pthread_mutex_lock(&this->mutex);
    cb_cmd_node_t val = this->cb_cmd_list.front();
    this->cb_cmd_list.pop_front();
    pthread_mutex_unlock(&this->mutex);

    if (val.cb)
    {
        val.cb(val.arg, val.req);
    }

    if (val.is_free)
    {
        free(val.req);
    }
}
#endif
