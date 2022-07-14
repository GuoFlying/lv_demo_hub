/*
 * @Author: Flying
 * @Date: 2022-05-02 16:31:33
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 16:32:01
 * @Description: 新建文件
 */
#include "../app.h"

/**
 * Scrolling with Right To Left base direction
 */
int app_scroll_5(lv_obj_t *parent)
{
    lv_obj_t *obj = lv_obj_create(parent);
    lv_obj_set_style_base_dir(obj, LV_BASE_DIR_RTL, 0);
    lv_obj_set_size(obj, 200, 100);
    lv_obj_center(obj);

    lv_obj_t *label = lv_label_create(obj);
    lv_label_set_text(label,
                      "میکروکُنترولر (به انگلیسی: Microcontroller) گونه‌ای ریزپردازنده است که دارای حافظهٔ دسترسی تصادفی (RAM) و حافظهٔ فقط‌خواندنی (ROM)، تایمر، پورت‌های ورودی و خروجی (I/O) و درگاه ترتیبی (Serial Port پورت سریال)، درون خود تراشه است، و می‌تواند به تنهایی ابزارهای دیگر را کنترل کند. به عبارت دیگر یک میکروکنترلر، مدار مجتمع کوچکی است که از یک CPU کوچک و اجزای دیگری مانند تایمر، درگاه‌های ورودی و خروجی آنالوگ و دیجیتال و حافظه تشکیل شده‌است.");
    lv_obj_set_width(label, 400);
    lv_obj_set_style_text_font(label, &lv_font_dejavu_16_persian_hebrew, 0);
    return 0;
}
