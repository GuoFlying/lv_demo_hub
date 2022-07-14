/*
 * @Author: Flying
 * @Date: 2021-11-08 17:48:53
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-08 21:18:28
 * @Description: font 管理
 */
#include "c_font.h"
#include <iostream>
using namespace std;

#define C_FONT_DEF 0
#define C_ICON_FONT_DEF 1

map<int, lv_ft_info_t *> c_font::c_icon_map;
map<int, lv_ft_info_t *> c_font::c_map;

c_font::c_font()
{
}

c_font::~c_font()
{
}

#define UNI_SUR_HIGH_START 0xD800
#define UNI_SUR_HIGH_END 0xDBFF
#define UNI_SUR_LOW_START 0xDC00
#define UNI_SUR_LOW_END 0xDFFF
#define UNI_REPLACEMENT_CHAR 0x0000FFFD
static int UTF16ToUTF8(unsigned char *utf8, unsigned char *utf16)
{
    unsigned short *source = (unsigned short *)utf16;
    unsigned char *target = utf8;
    int result;
    int halfShift = 10;
    unsigned long halfBase = 0x0010000UL;
    unsigned long halfMask = 0x3FFUL;
    unsigned char firstByteMark[7] = {0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC};

    while (*source)
    {
        unsigned long ch;
        unsigned short bytesToWrite = 0;
        unsigned long byteMask = 0xBF;
        unsigned long byteMark = 0x80;
        unsigned short *oldSource = source; /* In case we have to back up because of target overflow. */

        ch = *source++;
        /* If we have a surrogate pair, convert to UTF32 first. */
        if ((ch >= UNI_SUR_HIGH_START) && (ch <= UNI_SUR_HIGH_END))
        {
            /* If the 16 bits following the high surrogate are in the source buffer... */
            if (*source)
            {
                unsigned short ch2 = *source;
                /* If it's a low surrogate, convert to UTF32. */
                if ((ch2 >= UNI_SUR_LOW_START) && (ch2 <= UNI_SUR_LOW_END))
                {
                    ch = ((ch - UNI_SUR_HIGH_START) << halfShift) + (ch2 - UNI_SUR_LOW_START) + halfBase;
                    ++source;
                }
            }
            else
            {             /* We don't have the 16 bits following the high surrogate. */
                --source; /* return to the high surrogate */
                result = 0;
                break;
            }
        }
        /* Figure out how many bytes the result will require */
        if (ch < (unsigned long)0x80)
        {
            bytesToWrite = 1;
        }
        else if (ch < (unsigned long)0x800)
        {
            bytesToWrite = 2;
        }
        else if (ch < (unsigned long)0x10000)
        {
            bytesToWrite = 3;
        }
        else if (ch < (unsigned long)0x110000)
        {
            bytesToWrite = 4;
        }
        else
        {
            bytesToWrite = 3;
            ch = UNI_REPLACEMENT_CHAR;
        }

        target += bytesToWrite;

        switch (bytesToWrite)
        { /* note: everything falls through. */
        case 4:
            *--target = (unsigned char)((ch | byteMark) & byteMask);
            ch >>= 6;
        case 3:
            *--target = (unsigned char)((ch | byteMark) & byteMask);
            ch >>= 6;
        case 2:
            *--target = (unsigned char)((ch | byteMark) & byteMask);
            ch >>= 6;
        case 1:
            *--target = (unsigned char)(ch | firstByteMark[bytesToWrite]);
        }
        target += bytesToWrite;
    }
    *target = 0;
    if (utf8[0] == 0xe2 && utf8[1] == 0x80 && utf8[2] == 0x99 && strlen((const char *)utf8) == 3)
    {
        target = utf8;
        *target = 0x27;
        *(target + 1) = 0;
    }
    return 0;
}

/**
 * @description: u16转utf8字符串
 * @param {unsigned short} val
 * @return {*}
 */
string c_font::get_utf8(unsigned short val)
{
    unsigned char utf16[4] = {0};
    unsigned char utf8[10] = {0};

    utf16[0] = val & 0xFF;
    utf16[1] = (val & 0xFF00) >> 8;
    UTF16ToUTF8(utf8, utf16);
    return string((char *)utf8);
}

/**
 * @description:
 * @param {int} type
 * @param {int} size
 * @return {*}
 */
lv_font_t *c_font::get_font_by_name(int type, int size)
{
    map<int, lv_ft_info_t *> *map_tmp = &c_font::c_map;
    string fontname = MY_FONT_NAME;
    uint16_t style = FT_FONT_STYLE_NORMAL;

    if (type == C_ICON_FONT_DEF)
    {
        map_tmp = &c_font::c_icon_map;
        fontname = MY_ICON_FONT_NAME;
    }
    else
    {
        // LV_LOG_WARN("没找到 %s 字库，已使用默认字库", name.data());
    }

    if (!map_tmp)
    {
        return NULL;
    }

    lv_ft_info_t *ft = NULL;
    if (map_tmp->count(size) > 0)
    {
        ft = map_tmp->at(size);
        if (ft && ft->font)
        {
            return ft->font;
        }

        if (ft)
        {
            free(ft);
        }
    }

    ft = (lv_ft_info_t *)malloc(sizeof(lv_ft_info_t));
    if (!ft)
    {
        return NULL;
    }
    memset(ft, 0, sizeof(lv_ft_info_t));

    ft->name = fontname.data();
    ft->weight = size;
    ft->style = style;
    bool is = lv_ft_font_init(ft);
    if (is == false)
    {
        LV_LOG_ERROR("%s  %d", fontname.data(), size);
        return NULL;
    }

    map_tmp->insert({size, ft});
    return ft->font;
}

/**
 * @description:
 * @param {int} size
 * @return {*}
 */
lv_font_t *c_font::get_icon_font(int size)
{
    return c_font::get_font_by_name(C_ICON_FONT_DEF, size);
}

/**
 * @description:
 * @param {int} size
 * @return {*}
 */
lv_font_t *c_font::get_font(int size)
{
    return c_font::get_font_by_name(C_FONT_DEF, size);
}
