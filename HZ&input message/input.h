#ifndef __INPUT_H__
#define __INPUT_H__

#define BACK		0x0e08
#define BACK_SPACE	0x0e08
#define DELETE		0x5300
#define TAB			0x0f09
#define SPACE		0x3920
#define ENTER		0x1c0d
#define LASTLINE	0x1a5b
#define NEXTLINE	0x1b5d
#define LEFT		0x4b00
#define RIGHT		0x4d00
#define FIRST		0x0231
#define SECOND		0x0332
#define THIRD		0x0433
#define FOURTH		0x0534
#define UP			0x4800
#define DOWN		0x5000

#define MAXPY 8      //最大拼音（西文）数量 

#define FAIL 0
#define SUCCESS 1



   
int hz_input(int x1, int y1, int x2, int y2, char* s, int len, int color, int color2, int size);
//汉字输入法
int input_method(int x, int y, char* str, int value, char* py);
//汉字输入法调入
char* itostr(int a, char* s);
//数字标号
void pyFrm(int x1, int y1, int x2, int y2);
//输入法小框
int xouttextxy(int x, int y, char* s, int color);
//字符输入法

#endif
