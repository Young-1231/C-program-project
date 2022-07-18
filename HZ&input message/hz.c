#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hz.h"

void puthz(int x, int y, char *s, int flag, int part, int color)
{
    FILE *hzk_p = NULL;                                                      //瀹氫箟姹夊瓧搴撴枃浠舵寚閽??
    unsigned char quma, weima;                                               //瀹氫箟姹夊瓧鐨勫尯鐮佸拰浣嶇爜
    unsigned long offset;                                                    //瀹氫箟姹夊瓧鍦ㄥ瓧搴撲腑鐨勫亸绉婚噺
    unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01}; //鍔熻兘鏁扮粍锛岀敤浜庢樉绀烘眽瀛楃偣闃典腑鐨勪寒鐐??
    int i, j, pos;

    switch (flag) //涓嶅悓鐨刦lag瀵瑰簲涓嶅悓鐨勬眽瀛楀簱锛屽疄鐜颁簡姹夊瓧鐨勫ぇ灏忓彲鏍规嵁闇€瑕佹敼鍙??
    {
    case 16:
    {
        char mat[32]; // 16*16鐨勬眽瀛楅渶瑕??32涓瓧鑺傜殑鏁扮粍鏉ュ瓨鍌??
        int y0 = y;
        int x0 = x;
        hzk_p = fopen("../HZK/HZ16", "rb"); //浣跨敤鐩稿璺緞
                                            // hzk_p = fopen("../HZK/HZ16", "rb");
        if (hzk_p == NULL)
        {
            settextjustify(LEFT_TEXT, TOP_TEXT);     //宸﹂儴瀵归綈锛岄《閮ㄥ榻??
            settextstyle(GOTHIC_FONT, HORIZ_DIR, 1); //榛戜綋绗斿垝杈撳嚭锛屾按骞宠緭鍑猴紝24*24鐐归樀
            outtextxy(10, 10, "Can't open hzk16 file!Press any key to quit...");
            getch();
            exit(1);
        }
        while (*s != NULL)
        {
            while (x < 640 - flag && (*s != NULL))
            {
                y = y0;
                quma = s[0] - 0xa0;                             //姹傚嚭鍖虹爜
                weima = s[1] - 0xa0;                            //姹傚嚭浣嶇爜
                offset = (94 * (quma - 1) + (weima - 1)) * 32L; //姹傚嚭瑕佹樉绀虹殑姹夊瓧鍦ㄥ瓧搴撴枃浠朵腑鐨勫亸绉??
                fseek(hzk_p, offset, SEEK_SET);                 //閲嶅畾浣嶆枃浠舵寚閽??
                fread(mat, 32, 1, hzk_p);                       //璇诲嚭璇ユ眽瀛楃殑鍏蜂綋鐐归樀鏁版嵁,1涓鸿璇诲叆鐨勯」鏁??

                for (i = 0; i < 16; i++)
                {
                    pos = 2 * i;             // 16*16鐭╅樀涓湁姣忎竴琛屾湁涓ゅ瀛楄妭
                    for (j = 0; j < 16; j++) //涓€琛屼竴琛屽湴鎵弿锛屽皢浣嶄笂涓轰簡1鐨勭偣鏄剧ず鍑烘潵
                    {
                        if ((mask[j % 8] & mat[pos + j / 8]) != NULL) // j%8鍙兘鍦??0鈥??8涔嬮棿寰幆锛宩/8鍦??0锛??1涔嬮棿寰幆
                        {
                            putpixel(x + j, y, color);
                        }
                    }
                    y++;
                }
                /*====================================================
                    浠ヤ笂鏄竴涓眽瀛楁樉绀哄畬
                ====================================================*/
                x += part; //缁檟 涓€涓亸绉婚噺part
                s += 2;    //姹夊瓧閲屽瓨鏀剧殑鏄唴鐮侊紝2涓瓧鑺傦紝鎵€浠ヨ鍔??2
            }
            x = x0;
            y0 += flag + 10; //涓€琛屾眽瀛楁樉绀哄畬鍚??,閲嶆柊浠庡乏渚у紑濮嬭緭鍑烘眽瀛楋紝缁檡涓€涓亸绉婚噺
        }

        break;
    }

    case 24:
    {
        char mat[72]; // 24*24鐭╅樀瑕??72涓瓧鑺傛潵瀛樺偍
        int y0 = y;
        int x0 = x;
        hzk_p = fopen("../HZK/Hzk24k", "rb");
        // hzk_p = fopen("../HZK/Hzk24k", "rb");
        if (hzk_p == NULL)
        {
            settextjustify(LEFT_TEXT, TOP_TEXT);     //宸﹂儴瀵归綈锛岄《閮ㄥ榻??
            settextstyle(GOTHIC_FONT, HORIZ_DIR, 3); //榛戜綋绗斿垝杈撳嚭锛屾按骞宠緭鍑猴紝24*24鐐归樀
            outtextxy(10, 10, "Can't open hzk24 file!Press any key to quit...");
            getch();
            exit(1);
        }
        while (*s != NULL)
        {
            while (x < 640 - flag && (*s != NULL))
            {
                y = y0;
                quma = s[0] - 0xa0;  //姹傚嚭鍖虹爜
                weima = s[1] - 0xa0; //姹傚嚭浣嶇爜
                offset = (94 * (quma - 1) + (weima - 1)) * 72L;
                fseek(hzk_p, offset, SEEK_SET);
                fread(mat, 72, 1, hzk_p);
                for (i = 0; i < 24; i++)
                {
                    pos = 3 * i;             //鐭╅樀涓瘡涓€琛屾湁涓変釜瀛楄妭
                    for (j = 0; j < 24; j++) // 姣忎竴琛屾湁24浣??
                    {
                        if ((mask[j % 8] & mat[pos + j / 8]) != NULL)
                            putpixel(x + j, y, color);
                    }
                    y++;
                }
                x += part;
                s += 2;
            }
            x = x0;
            y0 += flag + 10;
        }
        break;
    }

    case 32:
    {
        char mat[128]; // 32*32鐨勬眽瀛楅渶瑕??128涓瓧鑺傜殑鏁扮粍鏉ュ瓨鍌??
        int y0 = y;
        int x0 = x;
        hzk_p = fopen("../HZK/HZK32S", "rb");
        // hzk_p = fopen("../HZK/HZK32S", "rb");
        if (hzk_p == NULL)
        {
            settextjustify(LEFT_TEXT, TOP_TEXT);     //宸﹂儴瀵归綈锛岄《閮ㄥ榻??
            settextstyle(GOTHIC_FONT, HORIZ_DIR, 3); //榛戜綋绗斿垝杈撳嚭锛屾按骞宠緭鍑猴紝24*24鐐归樀
            outtextxy(10, 10, "Can't open hzk32 file!Press any key to quit...");
            getch();
            exit(1);
        }
        while (*s != NULL)
        {
            while (x < 640 - flag && (*s != NULL))
            {
                y = y0;
                quma = s[0] - 0xa0;  //姹傚嚭鍖虹爜
                weima = s[1] - 0xa0; //姹傚嚭浣嶇爜
                offset = (94 * (quma - 1) + (weima - 1)) * 128L;
                fseek(hzk_p, offset, SEEK_SET);
                fread(mat, 128, 1, hzk_p);
                for (i = 0; i < 32; i++)
                {
                    pos = 4 * i; // 32*32鐭╅樀涓湁姣忎竴琛屾湁涓ゅ瀛楄妭
                    for (j = 0; j < 32; j++)
                    {
                        if ((mask[j % 8] & mat[pos + j / 8]) != NULL)
                        {
                            putpixel(x + j, y, color);
                        }
                    }
                    y++;
                }
                //浠ヤ笂鏄竴涓眽瀛楁樉绀哄畬
                x += part; //缁檟 涓€涓亸绉婚噺part
                s += 2;    //姹夊瓧閲屽瓨鏀剧殑鏄唴鐮侊紝2涓瓧鑺傦紝鎵€浠ヨ鍔??2
            }
            x = x0;
            y0 += flag + 10; //涓€琛屾眽瀛楁樉绀哄畬鍚庯紝缁檡涓€涓亸绉婚噺
        }
        break;
    }

    case 48:
    {
        char mat[288]; // 48*48鐨勬眽瀛楅渶瑕??288涓瓧鑺傜殑鏁扮粍鏉ュ瓨鍌??
        int y0 = y;
        int x0 = x;
        // hzk_p = fopen("C:\\boat\\HZK\\Hzk48k","rb");
        hzk_p = fopen("../HZK/Hzk48k", "rb");
        if (hzk_p == NULL)
        {
            settextjustify(LEFT_TEXT, TOP_TEXT);     //宸﹂儴瀵归綈锛岄《閮ㄥ榻??
            settextstyle(GOTHIC_FONT, HORIZ_DIR, 3); //榛戜綋绗斿垝杈撳嚭锛屾按骞宠緭鍑猴紝24*24鐐归樀
            outtextxy(10, 10, "Can't open hzk48 file!Press any key to quit...");
            getch();
            exit(1);
        }
        while (*s != NULL)
        {
            while (x < 640 - flag && (*s != NULL))
            {
                y = y0;
                quma = s[0] - 0xa0;                              //姹傚嚭鍖虹爜
                weima = s[1] - 0xa0;                             //姹傚嚭浣嶇爜
                offset = (94 * (quma - 1) + (weima - 1)) * 288L; //姹傚嚭瑕佹樉绀虹殑姹夊瓧鍦ㄥ瓧搴撴枃浠朵腑鐨勫亸绉??
                fseek(hzk_p, offset, SEEK_SET);                  //閲嶅畾浣嶆枃浠舵寚閽??
                fread(mat, 288, 1, hzk_p);                       //璇诲嚭璇ユ眽瀛楃殑鍏蜂綋鐐归樀鏁版嵁,1涓鸿璇诲叆鐨勯」鏁??

                for (i = 0; i < 48; i++)
                {
                    pos = 6 * i;
                    for (j = 0; j < 48; j++) //涓€琛屼竴琛屽湴鎵弿锛屽皢浣嶄笂涓轰簡1鐨勭偣鏄剧ず鍑烘潵
                    {
                        if ((mask[j % 8] & mat[pos + j / 8]) != NULL) // j%8鍙兘鍦??0鈥??8涔嬮棿寰幆锛宩/8鍦??0锛??1涔嬮棿寰幆
                        {
                            putpixel(x + j, y, color);
                        }
                    }
                    y++;
                }
                //浠ヤ笂鏄竴涓眽瀛楁樉绀哄畬
                x += part; //缁檟 涓€涓亸绉婚噺part
                s += 2;    //姹夊瓧閲屽瓨鏀剧殑鏄唴鐮侊紝2涓瓧鑺傦紝鎵€浠ヨ鍔??2
            }
            x = x0;
            y0 += flag + 10; //涓€琛屾眽瀛楁樉绀哄畬鍚庯紝缁檡涓€涓亸绉婚噺
        }
        break;
    }

    default:
        break;
    }

    fclose(hzk_p);
}

void vertical_puthz(int x1, int y1, int x2, int y2, char *s, int flag, int color)
{
    char stmp[5];
    int i;
    int font_num = strlen(s) / 2; //获取汉字个数
    int space = (y2 - y1) / font_num;
    for (i = 0; i < font_num; i++)
    {
        stmp[0] = s[2 * i];
        stmp[1] = s[2 * i + 1];
        stmp[2] = '\0';
        center_puthz(x1, y1 + space * i, x2, y1 + space * (i + 1), stmp, flag, flag, color);
    }
}

void center_puthz(int x1, int y1, int x2, int y2, char *s, int flag, int part, int color)
{
    int x, y;
    int length = strlen(s) * part / 2;
    x = x1 + (x2 - x1 - length) / 2;
    y = y1 + (y2 - y1 - flag) / 2;
    puthz(x, y, s, flag, part, color);
}

void drawtext(int x, int y, char *s, int fontsize, int partChinese, int partEnglish, int color) // x,y,s(ANSI),字体大小，中文输出间隔，英文输出间隔，颜色
{
    FILE *hzk_p = NULL;                                                      //定义汉字库文件指针
    unsigned char quma, weima;                                               //定义汉字的区码和位码
    unsigned long offset;                                                    //定义汉字在字库中的偏移量
    unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01}; //功能数组，用于显示汉字点阵中的亮点
    int i, j, pos, y0 = y;
    int orgcolor = getcolor();

    char mat[288];
    char eng[2] = "E";
    char fn[30];
    long fsize = fontsize * fontsize / 8L;
    // sprintf(fn, "C:\\boat\\HZK\\HZ%d", fontsize);			//根据不同字体来动态读取
    switch (fontsize)
    {
    case 16:
        sprintf(fn, "../HZK/HZ16");
        break;
    case 24:
        sprintf(fn, "../HZK/Hzk24k");
        break;
    case 32:
        sprintf(fn, "../HZK/HZK32S");
        break;
    case 48:
        sprintf(fn, "../HZK/Hzk48k");
        break;
    }
    hzk_p = fopen(fn, "rb"); //使用相对路径
    if (hzk_p == NULL)
        exit(-1);
    setcolor(color);
    while (*s != NULL)
    {
        while (x < 640 && (*s != NULL))
        {
            y = y0;
            if (s[0] < 0)
            {
                quma = s[0] - 0xa0;                                //求出区码
                weima = s[1] - 0xa0;                               //求出位码
                offset = (94L * (quma - 1) + (weima - 1)) * fsize; //求出要显示的汉字在字库文件中的偏移
                fseek(hzk_p, offset, SEEK_SET);                    //重定位文件指针
                fread(mat, fsize, 1, hzk_p);                       //读出该汉字的具体点阵数据,1为要读入的项数
                for (i = 0; i < fontsize; i++)
                {
                    pos = fontsize / 8 * i;
                    for (j = 0; j < fontsize; j++) //一行一行地扫描，将位上为了1的点显示出来
                    {
                        if ((mask[j & 7] & mat[pos + (j >> 3)])) // j%8只能在0—8之间循环，j/8在0，1之间循环
                            putpixel(x + j, y, color);
                    }
                    y++;
                }
                s += 2;
                x += partChinese; //偏移汉字的距离
            }
            else
            {
                eng[0] = s[0];
                outtextxy(x, y, eng);
                s += 1;
                x += partEnglish; //偏移英字的距离
            }
        }
    }
    fclose(hzk_p);
    setcolor(orgcolor);
}
void drawchar(int x, int y, char c, int col)
{
    char st[3];
    if (c != '\"')
    {
        st[0] = c;
        st[1] = '\0';
    }
    else
    {
        st[0] = '\"';
        st[1] = '\0';
    }
    setcolor(col);
    outtextxy(x, y, st);
}
