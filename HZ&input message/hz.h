#ifndef __HZ_H__
#define __HZ_H__

void puthz(int x, int y, char* s, int flag, int part, int color);
void center_puthz(int x1, int y1, int x2, int y2, char* s, int flag, int part, int color);	//居中显示汉字
void drawtext(int x, int y, char* s, int fontsize, int partChinese, int partEnglish, int color);//x,y,s(ANSI),字体大小，中文输出间隔，英文输出间隔，颜色
void drawchar(int x, int y, char c, int col);
void vertical_puthz(int x1, int y1, int x2, int y2, char* s, int flag, int color);

#endif

