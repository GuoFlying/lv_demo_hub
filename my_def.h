/*
 * @Author: Flying
 * @Date: 2022-02-25 22:43:33
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-10 15:39:31
 * @Description: 通用定义
 */
#pragma once

//基础坐标大小（内部APP坐标、布局按改比例进行）
#define MY_BASE_W_MAX 1024
#define MY_BASE_H_MAX 600

//实际UI 大小（对ubuntu、windows有效，linuxarm是获取fb大小进行实际放大或缩小）
#if 0   
    #define MY_REALITE_W_MAX 480
    #define MY_REALITE_H_MAX 480
#else
    #define MY_REALITE_W_MAX 1024
    #define MY_REALITE_H_MAX 600
#endif

#define MY_VERSION "1.2.0"

#ifdef F_WINDOWS
#define MY_RESOURCE_PATH "./resource/"
#define MY_RESOURCE_PATH_EX "S:./resource/"
#endif

#ifdef F_UBUNTU
#define MY_RESOURCE_PATH "./resource/"
#define MY_RESOURCE_PATH_EX "S./resource/"
#endif

#ifdef F_LINUXARM
#define MY_RESOURCE_PATH "./resource/"
#define MY_RESOURCE_PATH_EX "S./resource/"
#endif

#define MY_PNG_PATH        MY_RESOURCE_PATH_EX "img/"
#define MY_LOTTIE_PATH     MY_RESOURCE_PATH "lottie/"
#define MY_FONT_NAME       MY_RESOURCE_PATH "font/SourceHanSansCN-Regular.ttf"
#define MY_ICON_FONT_NAME  MY_RESOURCE_PATH "font/flying_iconfont.ttf"

//linuxarm other 
#define MY_DOUBLE_FB        1 /*LINUXARM 是否开启双buffer （处理屏幕撕裂）*/
