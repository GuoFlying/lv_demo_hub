/*
 * @Author: Flying
 * @Date: 2022-06-26 20:34:36
 * @LastEditors: Flying
 * @LastEditTime: 2022-06-26 22:42:07
 * @Description: 修改文件
 */
#pragma once
#ifdef F_LINUXARM

#include "../common/hw_app_base.h"
#include <string>
#include "mi_common_datatype.h"
#include "mi_wlan.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <list>

typedef void (*wifi_cb_t)(void *arg, void *req);

typedef enum
{
    WIFI_CMD_SCAN,
    WIFI_CMD_CONNECT,
    WIFI_CMD_DISCONNECT,
} WIFI_CMD_E;

typedef struct _get_cmd_node_t
{
    WIFI_CMD_E cmd;
    void *arg;
    wifi_cb_t cb;
} get_cmd_node_t;

typedef struct _cb_cmd_node_t
{
    wifi_cb_t cb;
    void *arg;
    void *req;
    bool is_free;
} cb_cmd_node_t;

class wifi_config
{
private:
    WLAN_HANDLE hWlan;
    std::list<get_cmd_node_t> get_cmd_list;
    std::list<cb_cmd_node_t> cb_cmd_list;
    pthread_mutex_t mutex;
    pthread_t p_init_id;
    bool is_open; // 1 打开，0未打开
    bool is_exit;
    void *arg;

    wifi_cb_t open_cb;
    wifi_cb_t state_cb;
    static void *wifi_init_pthread_init(void *pdata);
    void wifi_state_run();
    void wifi_add_cb_list(wifi_cb_t cb, void *arg, void *req, bool is_free = false);

public:
    //会创建一个wifi配置线程。处理wifi阻塞的动作
    wifi_config(wifi_cb_t open_cb, wifi_cb_t state_cb, void *arg);
    ~wifi_config();
    void wifi_scan(wifi_cb_t cb, void *arg);
    void wifi_connect(char *ssid, char *pwd);
    void wifi_disconnect(wifi_cb_t cb, void *arg);
    void wifi_mastar_run();
};
#endif
