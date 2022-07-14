/*
 * @Author: Flying
 * @Date: 2022-02-25 22:54:00
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-11 22:54:00
 * @Description: file content
 */

#include <Windows.h>
#include <process.h>
#include "base_main.h"
#define IDI_LVGL 101
static volatile int run_time_flag = 0;
void WINAPI run_time_flag_thread(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
    run_time_flag++;
}

#if _MSC_VER >= 1200
// Disable compilation warnings.
#pragma warning(push)
// nonstandard extension used : bit field types other than int
#pragma warning(disable : 4214)
// 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable : 4244)
#endif

#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "my_drivers/win32drv/win32drv.h"

#if _MSC_VER >= 1200
// Restore compilation warnings.
#pragma warning(pop)
#endif

#include <stdio.h>

#pragma comment(lib, "Winmm.lib")
int main()
{
    system("chcp 65001 && cls");
    lv_init();
    DWORD_PTR dwUser = NULL;
    timeSetEvent(1, 1, (LPTIMECALLBACK)run_time_flag_thread, dwUser, TIME_PERIODIC);

    my_app_init(0, NULL);

    if (!lv_win32_init(
            GetModuleHandleW(NULL),
            SW_SHOW,
            MY_UI_W_MAX,
            MY_UI_H_MAX,
            LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCE(IDI_LVGL))))
    {
        return -1;
    }

    lv_win32_add_all_input_devices_to_group(NULL);

    my_app_main(NULL, NULL);
    return 0;
}
