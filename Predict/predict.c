#include"common.h"
#include"predict.h"
#include"gm.h"

/*void show_data(double * data[24]);
    center_puthz(224,72+136*i,328,106+136*i,"酸碱度",24,24,WHITE);
    center_puthz(328,72+136*i,432,106+136*i,"溶解氧",24,24,WHITE);
    center_puthz(432,72+136*i,536,106+136*i,"铜离子",24,24,WHITE);
    center_puthz(536,72+136*i,640,106+136*i,"磷酸根",24,24,WHITE);

    center_puthz(224,140+136*i,328,174+136*i,"高锰酸钾",24,24,WHITE);
    center_puthz(328,140+136*i,432,174+136*i,"氨氮",24,24,WHITE);
    center_puthz(432,140+136*i,536,174+136*i,"总磷",24,24,WHITE);
    center_puthz(536,140+136*i,640,174+136*i,"总氮",24,24,WHITE);
void show_data(double *data[24])
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<4;j++)
        {

        }
    }
}*/

void show_data(double* data)
{
    int i, j;
    char a[10];
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 4; j++)
        {
            sprintf(a, "%.2lf", data[i * 4 + j]);
            my_outtextxy(254 + 104 * j, 108 + 68 * i, a, 1, 0, 2);
        }
    }
}

void predict(int* button)
{
    my_clr_mouse();
    predict_page();
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if (mouse_press(530, 0, 590, 39) == left_click_no)
        {
            MouseS = 1;
            continue;
        }
        else if (mouse_press(530, 0, 590, 39) == left_click_yes)
        {
            my_bar(530, 0, 590, 39, 1, DARKGRAY);
            center_puthz(530, 0, 590, 40, "返回", 24, 25, WHITE);
            delay(100);
            my_bar(530, 0, 590, 39, 1, LIGHTBLUE);
            center_puthz(530, 0, 590, 40, "返回", 24, 25, WHITE);
            *button = 8;
            return;
        }
        else
        {
            MouseS = 0;
        }
    }
}

void predict_page(void)
{
    int i;
    int num;
    char a[10];
    int day[3];
    double data[25];
    FILE* fp = NULL;
    if ((fp = fopen("../database/areanum/areanum.txt", "rt")) == NULL)
    {
        printf("fopen(areanum.txt)failed");
        delay(1000);
        exit(1);
    }
    //读取上级菜单所选择的索引值
    fscanf(fp, "%d", &num);
    fclose(fp);

    sprintf(a, "%d", num);
    my_bar(0, 0, 640, 480, 1, CYAN);
    my_bar(0, 0, 640, 40, 1, LIGHTBLUE);
    //write_threeday_predicted();
    center_puthz(0, 0, 240, 40, "未来水质数据预测", 24, 28, WHITE);
    center_puthz(240, 0, 500, 40, "区域编号：", 24, 24, WHITE);
    setcolor(WHITE);
    my_outtextxy(430, 8, a, 1, 0, 2);
    center_puthz(530, 0, 590, 40, "返回", 24, 25, WHITE);
    setlinestyle(0, 0, 1);
    setcolor(YELLOW);
    line(0, 72, 640, 72);
    line(0, 208, 640, 208);
    line(0, 344, 640, 344);
    line(112, 40, 112, 480);
    line(224, 40, 224, 480);
    line(0, 40, 640, 40);
    line(639, 40, 639, 479);
    line(639, 479, 0, 479);
    line(0, 479, 0, 40);
    line(328, 72, 328, 480);
    line(432, 72, 432, 480);
    line(536, 72, 536, 480);
    for (i = 0; i < 11; i++)
    {
        line(224, 106 + 34 * i, 640, 106 + 34 * i);
    }
    center_puthz(0, 40, 112, 72, "预测时间", 24, 26, WHITE);
    center_puthz(0, 112, 112, 140, "未来", 24, 28, WHITE);
    center_puthz(0, 140, 112, 168, "一天", 24, 28, WHITE);
    center_puthz(0, 248, 112, 276, "未来", 24, 28, WHITE);
    center_puthz(0, 276, 112, 304, "两天", 24, 28, WHITE);
    center_puthz(0, 384, 112, 412, "未来", 24, 28, WHITE);
    center_puthz(0, 412, 112, 440, "三天", 24, 28, WHITE);
    center_puthz(112, 40, 224, 72, "水质类型", 24, 26, WHITE);
    center_puthz(224, 40, 640, 72, "水质变量", 24, 40, WHITE);
    read_threeday_category(day, num);
    for (i = 0; i < 3; i++)
    {
        chooseday(day[i], i);
    }
    //从文件中读取未来三天的水质类别
    //从文件中读取未来三天的水质数据
    read_predicted(data, num);
    show_data(data);
    /*
    if ((fp = fopen("../database/predict/data.txt", "rt")) == NULL)
    {
        printf("fopen(data.txt)failed");
        delay(1000);
        exit(1);
    }
    
    for (i = 0; i < 24; i++)
    {
        fscanf(fp, "%lf", data[i]);
    }
    
    fclose(fp);
    */
    //shoe_data(data);
    /*drawtext(148,120,"Ⅰ",48,48,48,WHITE);
    drawtext(148,256,"Ⅱ",48,48,48,WHITE);
    drawtext(148,392,"Ⅲ",48,48,48,WHITE);*/
    for (i = 0; i < 3; i++)
    {
        center_puthz(224, 72 + 136 * i, 328, 106 + 136 * i, "酸碱度", 24, 24, WHITE);
        center_puthz(328, 72 + 136 * i, 432, 106 + 136 * i, "溶解氧", 24, 24, WHITE);
        center_puthz(432, 72 + 136 * i, 536, 106 + 136 * i, "铜离子", 24, 24, WHITE);
        center_puthz(536, 72 + 136 * i, 640, 106 + 136 * i, "磷酸根", 24, 24, WHITE);

        center_puthz(224, 140 + 136 * i, 328, 174 + 136 * i, "高锰酸钾", 24, 24, WHITE);
        center_puthz(328, 140 + 136 * i, 432, 174 + 136 * i, "氨氮", 24, 24, WHITE);
        center_puthz(432, 140 + 136 * i, 536, 174 + 136 * i, "总磷", 24, 24, WHITE);
        center_puthz(536, 140 + 136 * i, 640, 174 + 136 * i, "总氮", 24, 24, WHITE);
    }
    /*center_puthz(224,208,328,242,"酸碱度",24,24,WHITE);
    center_puthz(328,208,432,242,"溶解氧",24,24,WHITE);
    center_puthz(432,208,536,242,"铜离子",24,24,WHITE);
    center_puthz(536,208,640,242,"磷酸根",24,24,WHITE);

    center_puthz(224,276,328,310,"高锰酸钾",24,24,WHITE);
    center_puthz(328,276,432,310,"氨氮",24,24,WHITE);
    center_puthz(432,276,536,310,"总磷",24,24,WHITE);
    center_puthz(536,276,640,310,"总氮",24,24,WHITE);*/
}

void chooseday(int day, int num)
{
    if (day == 1)
    {
        drawtext(148, 120 + 136 * num, "Ⅰ", 48, 48, 48, WHITE);
    }
    if (day == 2)
    {
        drawtext(148, 120 + 136 * num, "Ⅱ", 48, 48, 48, WHITE);
    }
    if (day == 3)
    {
        drawtext(148, 120 + 136 * num, "Ⅲ", 48, 48, 48, WHITE);
    }
    if (day == 4)
    {
        drawtext(148, 120 + 136 * num, "Ⅳ", 48, 48, 48, WHITE);
    }
    if (day == 5)
    {
        drawtext(148, 120 + 136 * num, "Ⅴ", 48, 48, 48, WHITE);
    }
}
