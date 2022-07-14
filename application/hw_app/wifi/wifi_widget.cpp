/*
 * @Author: Flying
 * @Date: 2022-06-22 22:29:08
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-11 22:29:14
 * @Description: 修改文件
 */
#ifdef F_LINUXARM

#include "wifi_widget.h"

wifi_widget::wifi_widget(lv_obj_t *parent)
    : hw_app_base(parent)
{
    this->loading = NULL;
    this->config = new wifi_config(this->open_cb, this->state_cb, this);

    this->timer = lv_timer_create(run, 100, this);

    this->wifi_list = new v_wifi_list(parent, wifi_widget::connect_ctr_cb, wifi_widget::disconnect_ctr_cb, this);

    this->show_loading();
}

wifi_widget::~wifi_widget()
{
    lv_timer_del(this->timer);
    this->timer = NULL;
    delete this->config;
    this->config = NULL;
}

void wifi_widget::show_loading()
{
    if (this->loading)
    {
        return;
    }
    this->loading = lv_rlottie_create_from_file(parent, 350 * MY_UI_W_ZOOM, 350 * MY_UI_H_ZOOM, MY_LOTTIE_PATH "loading.json");
    lv_obj_center(this->loading);
}

void wifi_widget::del_loading()
{
    if (!this->loading)
    {
        return;
    }
    lv_obj_del(this->loading);
    this->loading = NULL;
}

void wifi_widget::run(lv_timer_t *t)
{
    wifi_widget *_this = (wifi_widget *)t->user_data;
    _this->config->wifi_mastar_run();
}

void wifi_widget::open_cb(void *arg, void *req)
{
    LV_LOG_USER("");
    wifi_widget *_this = (wifi_widget *)arg;
    int is = (int)req;
    if (is)
    {
        LV_LOG_USER("wifo open success");
        _this->config->wifi_scan(_this->wifi_scan_cb, _this);
    }
    else
    {
        LV_LOG_USER("wifo open error");
    }
}

void wifi_widget::state_cb(void *arg, void *req)
{
    // LV_LOG_USER("");
    MI_WLAN_Status_sta_t *st = (MI_WLAN_Status_sta_t *)req;
    wifi_widget *_this = (wifi_widget *)arg;
    if (!st)
    {
        return;
    }
    if (WPA_COMPLETED == st->state)
    {
        // LV_LOG_USER("连接成功： [%s] [%s] [%d] [%d]\n", st->ssid, st->address, st->channel, st->RSSI);
        _this->del_loading();
        v_wifi_list_item item;
        item.ssid = (char *)st->ssid;
        _this->wifi_list->set_connect_item(item);
        _this->wifi_list->show();
    }
    else if (WPA_DISCONNECTED == st->state)
    {
        LV_LOG_USER("断开连接 [%s] [%s] [%d] [%d]\n", st->ssid, st->address, st->channel, st->RSSI);
        _this->del_loading();
        v_wifi_list_item item;
        item.ssid = "";
        _this->wifi_list->set_connect_item(item);
        _this->wifi_list->show();
    }
}

void wifi_widget::wifi_scan_cb(void *arg, void *req)
{
    LV_LOG_USER("");
    wifi_widget *_this = (wifi_widget *)arg;

    MI_WLAN_ScanResult_t *scanResult = (MI_WLAN_ScanResult_t *)req;
    if (!scanResult)
    {
        return;
    }

    LV_LOG_USER("Scan result:\n");
    if (scanResult->u8APNumber <= 0)
    {
        LV_LOG_USER("第一次可能会获取失败，再次获取试下\n");
        _this->config->wifi_scan(_this->wifi_scan_cb, _this);
        return;
    }

    //排序
    for (int i = 0; i < scanResult->u8APNumber - 1; i++)
    {
        for (int j = 0; j < scanResult->u8APNumber - i - 1; j++)
        {
            if (scanResult->stAPInfo[j].stQuality.signalSTR < scanResult->stAPInfo[j + 1].stQuality.signalSTR)
            {
                MI_WLAN_APInfo_t tmp;
                memcpy(&tmp, &scanResult->stAPInfo[j], sizeof(MI_WLAN_APInfo_t));
                memcpy(&scanResult->stAPInfo[j], &scanResult->stAPInfo[j + 1], sizeof(MI_WLAN_APInfo_t));
                memcpy(&scanResult->stAPInfo[j + 1], &tmp, sizeof(MI_WLAN_APInfo_t));
            }
        }
    }
    _this->wifi_list->clear();
    _this->del_loading();

    for (int i = 0; i < scanResult->u8APNumber; i++)
    {
        char *pSsid = (char *)scanResult->stAPInfo[i].au8SSId;
        if (pSsid && strcmp(pSsid, "\"\""))
        {
            // printf("SSID: %s\n", pSsid);
            // printf("MAC: %s\n", (char *)scanResult->stAPInfo[i].au8Mac);
            // printf("encrypt: %s\n", scanResult->stAPInfo[i].bEncryptKey ? "true" : "false");
            // printf("signalSTR: %d db\n", scanResult->stAPInfo[i].stQuality.signalSTR);
            // printf("frequency: %f GHz\n", scanResult->stAPInfo[i].fFrequency);
            // printf("bitrate: %f Mb/s\n", scanResult->stAPInfo[i].fBitRate);
            // printf("channel: %d\n", scanResult->stAPInfo[i].u8Channel);
            // printf("channel: %d\n", scanResult->stAPInfo[i].u16CellId);
            // printf("\n");
            LV_LOG_USER(" [%s] [%d] [%d] [%d]\n", pSsid, scanResult->stAPInfo[i].bEncryptKey, scanResult->stAPInfo[i].stQuality.signalSTR, scanResult->stAPInfo[i].eEncrypt);
            v_wifi_list_item item;
            item.ssid = pSsid;
            item.singnal = scanResult->stAPInfo[i].stQuality.signalSTR;
            _this->wifi_list->push_back_list(item);
        }
    }
    _this->wifi_list->show();
}

void wifi_widget::connect_ctr_cb(void *arg, const char *ssid, const char *pwd)
{
    wifi_widget *_this = (wifi_widget *)arg;
    _this->config->wifi_connect((char *)ssid, (char *)pwd);
    _this->show_loading();
    _this->wifi_list->clear();
    _this->config->wifi_scan(_this->wifi_scan_cb, _this);
}

void wifi_widget::disconnect_ctr_cb(void *arg)
{
    wifi_widget *_this = (wifi_widget *)arg;
    _this->config->wifi_disconnect(wifi_widget::disconnect_cb, _this);
    _this->show_loading();
    _this->wifi_list->clear();
    _this->config->wifi_scan(_this->wifi_scan_cb, _this);
}

void wifi_widget::disconnect_cb(void *arg, void *req)
{
    wifi_widget *_this = (wifi_widget *)arg;
    v_wifi_list_item item;
    item.ssid = "";
    _this->wifi_list->set_connect_item(item);
    _this->wifi_list->show();
}

#endif