#include "common.h"
#include "point.h"
#include "coord.h"
#include "menu.h"
#include "receive.h"

void check_point(int* button)
{
    int mode = ADD_DEP;     //操作模式初始化为增加检验点模式
    int num_now = 0;        //检验点计数
    char s[20];             //存储输出字符串
    static Point points[10];       //检验点以结构数组形式存储
    Point dep_point;        //无人艇出发点  
    Point point_tmp;        //临时检验点
    PolyPtr poly_ptrs[10];  //函数指针
    int i;
    int index;          //鼠标在右侧检验点相对坐标操作的序号
    int hist_flag = 0;  //检验点是否设置指标

    cleardevice();
    my_bar(0, 30, 470, 480, 1, GREEN);
    clrmous(MouseX, MouseY);
    point_screen();
    /*setcolor(BELT_COLOR);
    setlinestyle(SOLID_LINE, 0, 3);
    setfillstyle(1, WATER_COLOR);
    line(600,0,600,470);*/
    //将函数指针指向函数
    init_func_ptrs(poly_ptrs);
    show_map();

    clear_point(&point_tmp);
    clear_points(&dep_point, points, NUM_POINT);
    //hist_flag = read_point_pc_data(&dep_point, points, NUM_POINT);
    //hist_flag = read_hist_pc(&dep_point, points, NUM_POINT);
    if (hist_flag == 1)
    {
        draw_tag(points, NUM_POINT);        //显示检验点
        while (1)
        {
            ;
        }
    }
    else
    {
        //检验点未设置
        while (1)
        {
            newmouse(&MouseX, &MouseY, &press);

            if (mouse_press(10, 0, 60, 24) == left_click_no) //在增加栏中未点击
            {
                MouseS = 1;
                continue;
            }
            else if (mouse_press(10, 0, 60, 24) == left_click_yes) //在增加栏中点击
            {
                MouseS = 0;
                newmouse(&MouseX, &MouseY, &press);
                clrmous(MouseX, MouseY);
                my_bar(10, 0, 60, 28, 1, DARKGRAY);
                //getimage(10, 28, 60, 68, buffer_curse);
                center_puthz(10, 0, 60, 28, "增加", 24, 24, WHITE);
                delay(100);
                my_bar(10, 0, 60, 28, 1, CYAN);
                center_puthz(10, 0, 60, 28, "增加", 24, 24, WHITE);

                if (dep_point.pc.X <= 1e-2 && dep_point.pc.Y <= 1e-2)    //出发点未设置
                {
                    pop_up_window("请先设置出发点");
                    //my_bar(350, 0, 600, 28, 1, CYAN);
                    //center_puthz(350, 0, 600, 28, "请先设置出发点", 16, 16, WHITE);
                    mode = ADD_DEP;
                }
                else if (mode == ADD_DEP || mode == DELETE_DEP)          //出发点已经设置,但是并未确认
                {
                    pop_up_window("请确认出发点");
                    //my_bar(350, 0, 600, 28, 1, CYAN);
                    //center_puthz(350, 0, 600, 28, "请确认出发点", 16, 16, WHITE);
                }
                else
                    mode = ADD_CHECK;
                delay(100);
                continue;
            }
            else if (mouse_press(105, 0, 155, 24) == left_click_no) //鼠标在删除栏中未点击
            {
                MouseS = 1;
                continue;
            }
            else if (mouse_press(105, 0, 155, 24) == left_click_yes) //鼠标在删除栏中点击
            {
                MouseS = 0;
                newmouse(&MouseX, &MouseY, &press);
                clrmous(MouseX, MouseY);
                my_bar(105, 0, 155, 28, 1, DARKGRAY);
                center_puthz(105, 0, 155, 28, "删除", 24, 24, WHITE);
                delay(100);
                my_bar(105, 0, 155, 28, 1, CYAN);
                center_puthz(105, 0, 155, 28, "删除", 24, 24, WHITE);

                if (dep_point.pc.X <= 1e-2 && dep_point.pc.Y <= 1e-2)                   //出发点未设置
                {
                    pop_up_window("请在边缘带设置出发点");
                    //my_bar(350, 0, 600, 28, 1, CYAN);
                    //center_puthz(350, 0, 600, 28, "请在边缘带设置出发点", 16, 16, WHITE);
                }
                else if (dep_point.pc.X >= 1e-2 && dep_point.pc.Y >= 1e-2 && mode != ADD_CHECK)              //出发点已经设置
                {
                    mode = DELETE_DEP;
                }
                else
                    mode = DELETE_CHECK;
                delay(100);
                continue;
            }
            else if (mouse_press(200, 0, 250, 24) == left_click_no) //鼠标在确认栏中未点击
            {
                MouseS = 1;
                continue;
            }
            else if (mouse_press(200, 0, 250, 24) == left_click_yes) //鼠标在确认栏中点击
            {
                MouseS = 0;
                clrmous(MouseX, MouseY);
                my_bar(350, 0, 600, 28, 1, CYAN);
                my_bar(200, 0, 250, 28, 1, DARKGRAY);
                center_puthz(200, 0, 250, 28, "确认", 24, 24, WHITE);
                delay(100);
                my_bar(200, 0, 250, 28, 1, CYAN);
                center_puthz(200, 0, 250, 28, "确认", 24, 24, WHITE);
                switch (mode)
                {
                case DELETE_DEP:
                case ADD_DEP:
                    if (dep_point.pc.X <= 1e-2 && dep_point.pc.Y <= 1e-2)   //出发点未设置
                    {
                        pop_up_window("请先设置出发点");
                        //my_bar(350, 0, 600, 28, 1, CYAN);
                        //center_puthz(350, 0, 600, 28, "请先设置出发点", 16, 16, WHITE);
                    }
                    else
                    {
                        pop_delay_window("出发点确认成功");
                        //my_bar(350, 0, 600, 28, 1, CYAN);
                        //center_puthz(350, 0, 600, 28, "出发点确认成功", 16, 16, WHITE);
                        mode = ADD_CHECK;
                        (*poly_ptrs[0])(YELLOW);
                        delay(100);
                    }
                    break;
                case DELETE_CHECK:
                case ADD_CHECK:
                    if (num_now != 10)
                    {
                        sprintf(s, "还缺");
                        // center_puthz(280, 0, 600, 28, s, 16, 16, WHITE);
                        puthz(350, 7, s, 16, 16, WHITE);
                        sprintf(s, "%d", 10 - num_now);
                        setcolor(RED);
                        my_outtextxy(386, 7, s, SMALL_FONT, HORIZ_DIR, 5);
                        sprintf(s, "个检验点");
                        puthz(400, 7, s, 16, 16, WHITE);
                    }
                    else if (num_now == 10)
                    {
                        //将检验点位置坐标保存到文件中去
                        /*
                        printf("(%.2lf, %.2lf)\n", dep_point.pc.X, dep_point.pc.Y);
                        for(i = 0;i < NUM_POINT;i++)
                        {
                            printf("(%.2lf, %.2lf)\n", points[i].pc.X, points[i].pc.Y);
                        }
                        */
                        /*
                        pcs[0].X = dep_point.pc.X;    pcs[0].Y = dep_point.pc.Y;
                        for(i = 1;i < NUM_POINT + 1;i++)
                        {
                            pcs[i].X = points[i - 1].pc.X;
                            pcs[i].Y = points[i - 1].pc.Y;
                        }
                        */
                        save_point_pc(&dep_point, points, NUM_POINT);
                        my_bar(330, 37, 450, 67, 1, BLUE);
                        center_puthz(350, 40, 430, 64, "路径规划", 24, 24, WHITE);
                        while (1)
                        {
                            newmouse(&MouseX, &MouseY, &press);
                            if (mouse_press(330, 37, 450, 67) == left_click_yes)
                            {
                                *button = 5;
                                return;
                            }
                            else {
                                MouseS = 1;
                            }
                        }
                    }
                    break;
                }
                continue;
            }
            else if (mouse_press(0, 30, 470, 480) == left_click_no) //鼠标在地图栏中未点击
            {
                MouseS = 0;
                continue;
            }
            else if (mouse_press(0, 30, 470, 480) == left_click_yes) //鼠标在地图栏中点击
            {
                switch (mode)
                {
                case ADD_DEP:
                    clrmous(MouseX, MouseY);
                    set_departure_point(&dep_point, &point_tmp);
                    newmouse(&MouseX, &MouseY, &press);
                    delay(100);
                    break;
                case DELETE_DEP:
                    clrmous(MouseX, MouseY);
                    pc_delete_dep(&dep_point, &point_tmp);
                    newmouse(&MouseX, &MouseY, &press);
                    break;
                case ADD_CHECK:
                    clrmous(MouseX, MouseY);
                    pc_set_point(poly_ptrs, points, 10, &point_tmp, &num_now, &dep_point);
                    // draw_tag();
                    newmouse(&MouseX, &MouseY, &press);
                    delay(100);
                    break;
                case DELETE_CHECK:
                    clrmous(MouseX, MouseY);
                    pc_delete_point(poly_ptrs, points, 10, &point_tmp, &num_now);
                    newmouse(&MouseX, &MouseY, &press);
                    delay(100);
                    break;
                }
                continue;
            }
            /*
            else if ((index = get_point_index()) != -1)
            {
                if (mode == ADD_CHECK || mode == DELETE_CHECK)
                {
                    rc_set_point(points, NUM_POINT, &point_tmp, &dep_point, index, &num_now);
                }
                else
                    MouseS = 0;
                continue;
            }
            */
            else if (mouse_press(610, 0, 638, 28) == left_click_no) //鼠标在框 退出 中未点击
            {
                MouseS = 1;
                continue;
            }
            else if (mouse_press(610, 0, 638, 28) == left_click_yes) //鼠标在框 退出 中点击
            {
                MouseS = 2;
                my_bar(610, 0, 638, 28, 1, BLUE);
                *button = 0;
                break;
            }
            else
            {
                MouseS = 0;
                continue;
            }
        }
    }
}

/*void draw_tag(void)
{
    setviewport(0, 28, 470, 478, 1);
    my_bar(MouseX, MouseY - 10 - 28 - 2, MouseX + 2 , MouseY - 28 - 2, 1, BLUE);
    setcolor(RED);
    circle(MouseX + 1, MouseY - 12 - 28 - 2, 3);
    setfillstyle(1, RED);
    floodfill(MouseX +1, MouseY - 11 -28 - 2, RED);

    setviewport(0, 0, 639, 479, 0);
}
*/
/*
void save_point_pc(Point* points, int n)
{
    int i;
    FILE* fp = NULL;
    if((fp = fopen("../database/point/point.dat", "wb")) == NULL) //文件打开失败
    {
        printf("fuck");
        delay(1000);
        exit(1);
    }
    for(i = 0;i < n;i++)
    {
        fwrite(&points[i].pc, sizeof(PC), 1, fp);
    }
    fclose(fp);
}
*/
/*
void save_point_pc(PC* pcs, int n)
{
    FILE* fp = NULL;
    if((fp = fopen("../database/point/point.dat", "wb")) == NULL) //文件打开失败
    {
        printf("fopen()failed");
        delay(1000);
        exit(1);
    }
    fwrite(pcs, sizeof(PC), n, fp);
    fclose(fp);
}
*/

//将出发点和检验点数据清零
void clear_points(Point* dep_point, Point* points, int n)
{
    int i;
    clear_point(dep_point);
    for (i = 0; i < n; i++)
    {
        clear_point(&points[i]);
    }
}

//初始化函数指针
void init_func_ptrs(PolyPtr* poly_ptrs)
{
    poly_ptrs[0] = choosepoly1; poly_ptrs[1] = choosepoly2; poly_ptrs[2] = choosepoly3; poly_ptrs[3] = choosepoly4; poly_ptrs[4] = choosepoly5;
    poly_ptrs[5] = choosepoly6; poly_ptrs[6] = choosepoly7; poly_ptrs[7] = choosepoly8; poly_ptrs[8] = choosepoly9; poly_ptrs[9] = choosepoly10;
}

//保存出发点和检验点的屏幕坐标信息
void save_point_pc(Point* dep_point, Point* points, int n)
{
    FILE* fp = NULL;
    int i;
    PC pcs[11];
    if ((fp = fopen("../database/point/point.dat", "wb")) == NULL)    //文件打开失败
    {
        fprintf(stderr, "fopen()failed");
        delay(1000);
        exit(1);
    }
    pcs[0].X = dep_point->pc.X; pcs[0].Y = dep_point->pc.Y;
    for (i = 1; i < n + 1; i++)
    {
        pcs[i].X = points[i - 1].pc.X;
        pcs[i].Y = points[i - 1].pc.Y;
    }
    //坐标输出
        /*
        for (i = 0; i < n + 1; i++)
        {
            printf("(%.2lf, %.2lf)\n", pcs[i].X, pcs[i].Y);
        }
        */
    fwrite(pcs, sizeof(PC), n + 1, fp);
    fclose(fp);
}

/*
void save_point_data(Point* dep_point, Point* points, int n)
{
    FILE* fp = NULL;
    int i;
    if ((fp = fopen("../database/point/point.dat", "wb")) == NULL)   //文件打开失败
    {
        fprintf(stderr, "fopen()failed.");
        delay(1000);
        exit(1);
    }
    fwrite(dep_point, sizeof(Point), 1, fp);
    for (i = 0; i < n; i++)
    {
        fwrite(&points[i], sizeof(Point), 1, fp);
    }
    fclose(fp);
}
*/
void read_point_data(Point* dep_point, Point* points, int n)
{
    FILE* fp = NULL;
    int i;
    if ((fp = fopen("../database/point/point.dat", "rb")) == NULL)  //文件打开失败
    {
        fprintf(stderr, "fopen()failed.");
        delay(1000);
        exit(1);
    }
    fread(dep_point, sizeof(Point), 1, fp);
    for (i = 0; i < n; i++)
    {
        fread(&points[i], sizeof(Point), 1, fp);
    }
    fclose(fp);
}

/*
void save_point_pc_data(Point* dep_point, Point* points, int n)
{
    FILE* fp = NULL;
    int i;
    if ((fp = fopen("../database/point/pc.dat", "wb")) == NULL)  //文件打开失败
    {
        fprintf(stderr, "fopen()failed.");
        delay(1000);
        exit(1);
    }

    fwrite(&dep_point->pc, sizeof(PC), 1, fp);

    for (i = 0; i < n; i++)
    {
        fwrite(&points[i].pc, sizeof(PC), 1, fp);
    }
    fclose(fp);
}
*/

//将检验点屏幕坐标文件删除
void delete_hist_pc(void)
{
    FILE* fp = NULL;
    if ((fp = fopen("../database/point/point.dat", "wb")) == NULL)    //文件打开失败
    {
        fprintf(stderr, "fopen()failed.");
        delay(1000);
        exit(1);
    }

    fclose(fp);
}

//从文件中读取检验点的屏幕坐标
void read_check_pc(Point* check_points, int n)
{
    Point tmp_point;
    int sub_status;

    sub_status = read_hist_pc(&tmp_point, check_points, n);

}

//从文件中读取出发点和检验点的屏幕坐标
int read_hist_pc(Point* dep_point, Point* points, int n)
{
    FILE* fp = NULL;
    static PC pcs[11];
    int i;

    if ((fp = fopen("../database/point/point.dat", "rb")) == NULL)
    {
        //fprintf(stderr, "fopen()failed");
        delay(1000);
        return 0;
    }
    /*
    if (feof(fp) != 0)
    {
        return 0;
    }
    */
    //fwrite(pcs, sizeof(PC), n + 1, fp);
    fread(pcs, sizeof(PC), n + 1, fp);
    dep_point->pc.X = pcs[0].X; dep_point->pc.Y = pcs[0].Y;
    for (i = 0; i < n; i++)
    {
        points[i].pc.X = pcs[i + 1].X;
        points[i].pc.Y = pcs[i + 1].Y;
    }
    return 1;
}
/*
int read_point_pc_data(Point* dep_point, Point* points, int n)
{
    FILE* fp = NULL;
    //FILE* fp2 = NULL;
    int i;
    //char ch;

    if ((fp = fopen("../database/point/pc.dat", "rb")) == NULL)   //文件打开失败
    {
        fprintf(stderr, "fopen()failed");
        delay(1000);
        return 0;
    }
    /*
    ch = fgetc(fp);
    if (ch == EOF)
        return 0;

    if (feof(fp) == 1)
        return 0;

    fread(&dep_point->pc, sizeof(PC), 1, fp);
    for (i = 0; i < n; i++)
    {
        fread(&points[i].pc, sizeof(PC), 1, fp);
    }
    fclose(fp);
    /*
    //将文件内容清空
    fp2 = fopen("../database/point/pc.dat", "wb");
    fclose(fp2);

    return 1;
}
*/
//检验相关检验点是否写入数据 0-未写入 1-已写入
int point_was_set(Point* point)
{
    if (point->pc.X != 0 && point->pc.Y != 0)
    {
        return 1;
    }
    return 0;
}

void draw_tag(Point* points, int n)
{
    int i;
    int X;
    int Y;
    for (i = 0; i < n; i++)
    {
        if ((fabs(points[i].pc.X) >= 1e-1) && (fabs(points[i].pc.Y) >= 1e-1)) //判断当前检验点是否已写入数据
        {

            X = (int)points[i].pc.X;
            Y = (int)points[i].pc.Y;
            my_bar(X, Y - 4 - 1, X + 2, Y - 1, 1, BLUE);
            setcolor(RED);
            circle(X + 1, Y - 7 - 1, 3);
            setfillstyle(1, RED);
            floodfill(X + 1, Y - 7 - 1, RED);
            //draw_departure_point(&points[i]);
        }
    }
    show_point_rc(points, n);
}


//更新多边形 1-增加模式 2-删除模式
void renew_poly(Point* points, PolyPtr polytrs[], int index, int mode)
{
    int i;
    int activated_index;
    for (i = 0; i < NUM_POINT; i++)
    {
        if (points[i].pc.X <= 1e-2 || points[i].pc.Y <= 1e-2)
        {
            break;
        }
    }
    activated_index = i;    //找出第一个未被设置的检验点,并将其序号设置为激活序号            
    if (mode == 2)
    {
        for (i = 0; i < NUM_POINT; i++)
        {
            (*polytrs[i])(GREEN);            //删除模式消除所有多边形
        }
    }
    /*
    for (i = 0; i < NUM_POINT; i++)
    {
        (*polytrs[i])(GREEN);
    }
    */
    else if (mode == 1)
        (*polytrs[index])(GREEN);               //消除现有多边形

    //if(num_now < 9)
    //    (*polytrs[num_now + 1])(YELLOW);    //显示下个多边形
    if (activated_index < 10)
        (*polytrs[activated_index])(YELLOW);    //显示下个多边形
}

//修改,将Point参数修改为主菜单和子菜单
void point_screen(void)
{
    int i;
    char num_string[4];
    int poly_1[] = { 428,455,442,455,435,436,428,455 };
    int poly_2[] = { 428,455,442,455,435,474,428,455 };
    //MENUTYPE* main_menu;
    //MENUTYPE* sub_menus[2];


    my_rectangle(0, 0, 612, 29, 2, CYAN, DARKGRAY);
    my_bar(0, 0, 640, 30, 1, CYAN); //上方功能栏

    //创建主菜单和子菜单
    //init_menu(main_menu, sub_menus, 2);
    draw_point_menu();

    my_rectangle(0, 27, 463, 479, 3, CYAN, DARKGRAY); //地图栏
    my_bar(464, 30, 640, 480, 1, DARKGRAY);           //检验点栏
    my_bar(350, 0, 600, 28, 1, CYAN);
    center_puthz(350, 0, 600, 28, "请在边缘带中设置无人艇出发点", 16, 16, WHITE);
    setcolor(CYAN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(464, 478, 640, 478);
    line(639, 28, 639, 480);

    for (i = 0; i < 10; i++)
    {
        //检验点相对坐标框
        my_bar(465, 40 + 45 * i, 637, 40 + 30 + 45 * i, 1, CYAN);
        puthz(465, 40 + 5 + 45 * i, "点", 24, 24, WHITE);
        setcolor(WHITE);
        my_outtextxy(512, 40 + 2 + 45 * i, "X", SMALL_FONT, HORIZ_DIR, 8);
        my_bar(528, 40 + 4 + 45 * i, 571, 40 + 26 + 45 * i, 1, WHITE); //X坐标框
        my_outtextxy(575, 40 + 2 + 45 * i, "Y", SMALL_FONT, HORIZ_DIR, 8);
        my_bar(592, 40 + 4 + 45 * i, 634, 40 + 26 + 45 * i, 1, WHITE); //Y坐标框
        setcolor(WHITE);
        itoa(i + 1, num_string, 10);
        my_outtextxy(493, 40 + 5 + 45 * i, num_string, SMALL_FONT, HORIZ_DIR, 7);
        setcolor(CYAN);
        setlinestyle(DASHED_LINE, 0, 1);
        if (i < 9)
        {
            line(464, 40 + 30 + 7 + 45 * i, 640, 40 + 30 + 7 + 45 * i);
        }
    }

    //比例尺
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 3);
    line(20, 460, 100, 460);
    setlinestyle(SOLID_LINE, 0, 1);
    line(20, 460, 20, 455);
    line(100, 460, 100, 455);
    my_outtextxy(40, 438, "2", SMALL_FONT, HORIZ_DIR, 6);
    puthz(50, 440, "公里", 16, 16, BLACK);

    //指南针
    setcolor(LIGHTGRAY);
    circle(435, 455, 15);
    setcolor(RED);
    setfillstyle(1, RED);
    fillpoly(4, poly_1);
    setcolor(BLACK);
    setfillstyle(1, BLACK);
    fillpoly(4, poly_2);

    //退出框
    setcolor(WHITE);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(610, 3, 630, 23);
    line(610, 23, 630, 3);
}

//输出检验点的相对坐标信息
void show_point_rc(Point* points, int n)
{
    int i;
    char str[10]; //临时字符串
    int length;
    for (i = 0; i < n; i++)
    {
        my_bar(528, 40 + 4 + 45 * i, 571, 40 + 26 + 45 * i, 1, WHITE); //X坐标框
        my_bar(592, 40 + 4 + 45 * i, 634, 40 + 26 + 45 * i, 1, WHITE); //Y坐标框

        if ((fabs(points[i].pc.X) >= 1e-2) && (fabs(points[i].pc.Y) >= 1e-2))   //当前点已设置
        {
            //sprintf(str,"%lf",points[i].)

            setcolor(BLACK);
            settextstyle(SMALL_FONT, HORIZ_DIR, 5);
            sprintf(str, "%3.2f", points[i].rc.X);
            outtextxy(533, 40 + 6 + 45 * i, str);
            sprintf(str, "%3.2f", points[i].rc.Y);
            outtextxy(594, 40 + 6 + 45 * i, str);
        }
    }
}
/*********************************************
DESCRIPTION：判断当前检验点在检验点数组中存在情况
INPUT:points,n,point
RETURN:0-不存在 1~n-存在且返回序号
***********************************************/
int judge_check_point(Point* points, int n, Point* point)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if ((fabs(point->pc.X - points[i].pc.X) <= 4) &&
            ((points[i].pc.Y - point->pc.Y) < 12) &&
            ((points[i].pc.Y - point->pc.Y) > -2))
        {
            return i + 1;
        }
    }

    return 0;
}

/*********************************************
DESCRIPTION：判断出发点存在情况
INPUT:points,n,point
RETURN:0-不存在 1-存在
***********************************************/
int judge_dep_point(Point* dep_point, Point* point)
{
    if ((fabs(dep_point->pc.X - point->pc.X) <= 5) &&
        ((dep_point->pc.Y - point->pc.Y) < 15) &&
        ((dep_point->pc.Y - point->pc.Y) > -2))
        return 1;

    return 0;
}

/*********************************************
DESCRIPTION：判断当前检验点是否在水体中
INPUT:point
RETURN:0-不在 1-在绿色水体中 2-在激活水体中
***********************************************/
int is_in_water(Point* point)
{
    int x = (int)point->pc.X;
    int y = (int)point->pc.Y;
    int color = getpixel(x, y);
    // printf("%d", color);
    if (color == WATER_COLOR)
        return 1;
    else if (color == ACTIVATE_COLOR)
        return 2;
    else
        return 0;
}

/*********************************************
DESCRIPTION：判断当前出发点是否在边缘带中
INPUT:point
RETURN:0-不在 1-在
***********************************************/
int is_in_belt(Point* point)
{
    int x = (int)point->pc.X;
    int y = (int)point->pc.Y;
    int color = getpixel(x, y);
    // printf("%d", color);
    if (color == BELT_COLOR)
        return 1;
    else
        return 0;
}

//根据屏幕坐标设定检验点
void pc_set_point(PolyPtr polyptrs[], Point* points, int n, Point* point, int* num_now, Point* dep_point)
{
    int index;
    point->pc.X = MouseX;
    point->pc.Y = MouseY;

    if ((*num_now) == 10) // 10个检验点已全部设置
    {
        pop_up_window("检验点已全部设置");
        return;
    }

    if (judge_check_point(points, n, point)) //当前点已经被设置
    {
        pop_up_window("当前点已被设置");
        clear_point(point);
    }
    else
    {
        for (index = 0; index < n; index++)
        {
            if (points[index].pc.X <= 1e-2 && points[index].pc.Y <= 1e-2)
            {
                break;
            }
        }
        if (is_in_water(point) == 2)    //当前点未被设置并且在待选水体中
        {
            my_bar(350, 0, 600, 28, 1, CYAN);
            pc_to_rc(point, dep_point);
            point_cpy(&points[index], point);
            //center_puthz(350, 0, 600, 28, "设置成功", 16, 16, WHITE);
            //pop_up_window("设置成功");
            pop_delay_window("设置成功");
            newmouse(&MouseX, &MouseY, &press);
            delay(100);
            my_clr_mouse();
            renew_poly(points, polyptrs, index, 1);
            draw_tag(points, 10);
            //newmouse(&MouseX, &MouseY, &press);
            ++(*num_now);
        }
        else if (is_in_water(point) == 1)//当前点不在待选水体中
        {
            pop_up_window("当前点不在待选水体中");
            //my_bar(350, 0, 600, 28, 1, CYAN);
            //center_puthz(350, 0, 600, 28, "当前点不在水体中", 16, 16, WHITE);
            clear_point(point);
        }
        else                            //当前点不在水体中
        {
            pop_up_window("当前点不在水体中");
            clear_point(point);
        }
    }
}

//选择无人艇出发点
/*********************************************
DESCRIPTION：选择无人艇出发点
INPUT: point
RETURN:无
***********************************************/
int set_departure_point(Point* dep_point, Point* point)
{
    point->pc.X = MouseX;
    point->pc.Y = MouseY;

    if ((dep_point->pc.X > 1e-2) && (dep_point->pc.Y > 1e-2))
    {
        pop_up_window("出发点已设置");
        //my_bar(350, 0, 600, 28, 1, CYAN);
        //center_puthz(350, 0, 600, 28, "出发点已设置", 16, 16, WHITE);
        return;
    }

    if (is_in_belt(point) && MouseX < 450 && MouseY > 30)  //当前点在边缘带中
    {
        point_cpy(dep_point, point);
        //my_bar(350, 0, 600, 28, 1, CYAN);
        //center_puthz(350, 0, 600, 28, "出发点设置成功", 16, 16, WHITE);
        pop_delay_window("出发点设置成功");
        pop_delay_window("请确认出发点");
        dep_point->rc.X = 0;    dep_point->rc.Y = 0;    //将出发点作为坐标系的原点(基准点)
        draw_departure_point(dep_point);
    }
    else                    //当前点不在边缘带中
    {
        pop_up_window("当前点不在边缘带中");
        //my_bar(350, 0, 600, 28, 1, CYAN);
        //center_puthz(350, 0, 600, 28, "当前点不在边缘带中", 16, 16, WHITE);
        clear_point(point);
    }
}

//根据屏幕坐标删除检验点
void pc_delete_point(PolyPtr polyptrs[], Point* points, int n, Point* point, int* now_num)
{
    int index; //待删除点的序号
    point->pc.X = MouseX;
    point->pc.Y = MouseY;
    if ((*now_num) == 0) // 10个检验点都未设置
    {
        pop_up_window("尚未开始设置检验点");
        //my_bar(350, 0, 600, 28, 1, CYAN);
        //center_puthz(350, 0, 600, 28, "尚未开始设置检验点", 16, 16, WHITE);
        return;
    }
    if (index = judge_check_point(points, n, point)) //当前点已设置检验点
    {
        pop_delay_window("删除成功");
        //my_bar(350, 0, 600, 28, 1, CYAN);
        //center_puthz(350, 0, 600, 28, "删除成功", 16, 16, WHITE);

        cover_point(points[index - 1]);
        clear_point(point);
        clear_point(&points[index - 1]);
        delay(50);
        renew_poly(points, polyptrs, index - 1, 2);
        draw_tag(points, n);
        --(*now_num);
        delay(100);
    }
    else //当前点未设置检验点
    {
        pop_up_window("当前点未设置检验点");
        //my_bar(350, 0, 600, 28, 1, CYAN);
        //center_puthz(350, 0, 600, 28, "当前点未设置检验点", 16, 16, WHITE);
        clear_point(point);
    }
}

//根据屏幕坐标删除出发点
void pc_delete_dep(Point* dep_point, Point* point)
{
    int index;
    if ((fabs(dep_point->pc.X) < 1e-2) && (fabs(dep_point->pc.Y) < 1e-2))    //出发点未设置
    {
        pop_up_window("尚未开始设置出发点");
        //my_bar(350, 0, 600, 28, 1, CYAN);
        //center_puthz(350, 0, 600, 28, "尚未开始设置出发点", 16, 16, WHITE);
        return;
    }
    if (index = judge_check_point(dep_point, 1, point))      //当前点已设置出发点
    {
        pop_up_window("删除成功");
        //my_bar(350, 0, 600, 28, 1, CYAN);
        //center_puthz(350, 0, 600, 28, "删除成功", 16, 16, WHITE);
        cover_point(*dep_point);
        cover_point(*dep_point);
        clear_point(point);
        clear_point(dep_point);
        delay(100);
    }
    else    //当前点未设置出发点
    {
        pop_up_window("当前点未设置出发点");
        //my_bar(350, 0, 600, 28, 1, CYAN);
        //center_puthz(350, 0, 600, 28, "当前点未设置出发点", 16, 16, WHITE);
        clear_point(point);
    }
}

//根据相对位置来确定检验点
void rc_set_point(Point* points, int n, Point* point_tmp, Point* datum_point, int index, int* num_now)
{
    char s[10];     //临时存储的字符串
    double coord;    //用来存储字符串转换生成的数
    unsigned char color = 0;    //接受检验点的颜色
    int sub_index = index % 10; int main_index = (index - sub_index) / 10;
    int i;

    my_bar(528 + 64 * sub_index, 40 + 4 + 45 * main_index, 571 + 62 * sub_index, 40 + 26 + 45 * main_index, 1, WHITE);
    my_input_message(s, 528 + 64 * sub_index, 40 + 4 + 45 * main_index, 571 + 62 * sub_index, 40 + 26 + 45 * main_index, 5, WHITE, 8);

    while (s[i] != '\0')
    {
        if ((s[i] < '0' || s[i] > '9') && s[i] != '.')
        {
            pop_up_window("请输入数字");
            //my_bar(350, 0, 600, 28, 1, CYAN);
            //center_puthz(350, 0, 600, 28, "请输入数字", 16, 16, WHITE);
            my_bar(528 + 64 * sub_index, 40 + 4 + 45 * main_index, 571 + 62 * sub_index, 40 + 26 + 45 * main_index, 1, WHITE);
            return;
        }
    }
    coord = atof(s);

    if (coord < -20 || coord > 20)
    {
        pop_up_window("请输入正常范围内坐标");
        //my_bar(350, 0, 600, 28, 1, CYAN);
        //center_puthz(350, 0, 600, 28, "请输入正常范围内坐标", 16, 16, WHITE);
        my_bar(528 + 64 * sub_index, 40 + 4 + 45 * main_index, 571 + 62 * sub_index, 40 + 26 + 45 * main_index, 1, WHITE);
        return;
    }

    if (fabs(points[main_index].rc.X) >= 1e-2 && fabs(points->rc.Y) >= 1e-2)     //此点之前已经被设置
    {
        cover_point(points[main_index]);
        delay(100);
        if (sub_index == 0)      //输入的是X相对坐标值
        {
            points[main_index].rc.X = 0;
            points[main_index].pc.X = 0;
            point_tmp->rc.Y = points[main_index].rc.Y;
            point_tmp->rc.X = coord;
            rc_to_pc(point_tmp, datum_point);
        }
        else
        {
            points[main_index].rc.Y = 0;
            points[main_index].pc.Y = 0;
            point_tmp->rc.X = points[main_index].rc.X;
            point_tmp->rc.Y = coord;
            rc_to_pc(point_tmp, datum_point);
        }
        if (fabs(coord) >= 1e-2)
            color = getpixel(point_tmp->pc.X, point_tmp->pc.Y);
        if (judge_check_point(points, n, point_tmp))
        {
            pop_up_window("当前点已经被设置");
            //my_bar(350, 0, 600, 28, 1, CYAN);
            //center_puthz(350, 0, 600, 28, "当前点已经被设置", 16, 16, WHITE);
            my_bar(528 + 64 * sub_index, 40 + 4 + 45 * main_index, 571 + 62 * sub_index, 40 + 26 + 45 * main_index, 1, WHITE);
        }
        else if (color != ACTIVATE_COLOR)
        {
            pop_up_window("当前点不在待选水体中");
            my_bar(528 + 64 * sub_index, 40 + 4 + 45 * main_index, 571 + 62 * sub_index, 40 + 26 + 45 * main_index, 1, WHITE);
        }
        else if (color != WATER_COLOR)
        {
            pop_up_window("当前点不在水体中");
            //my_bar(350, 0, 600, 28, 1, CYAN);
            //center_puthz(350, 0, 600, 28, "当前点不在水体中", 16, 16, WHITE);
            my_bar(528 + 64 * sub_index, 40 + 4 + 45 * main_index, 571 + 62 * sub_index, 40 + 26 + 45 * main_index, 1, WHITE);
        }
        else                        //检验点在水体中
        {
            point_cpy(&points[main_index], point_tmp);
            //my_bar(350, 0, 600, 28, 1, CYAN);
            //center_puthz(350, 0, 600, 28, "检验点设置成功", 16, 16, WHITE);
            pop_delay_window("检验点设置成功");
            ++(*num_now);
            draw_tag(points, n);
        }
    }
    else if (fabs(points[main_index].rc.X) <= 1e-2 && fabs(points[main_index].rc.Y) <= 1e-2)
    {
        if (fabs(coord) >= 1e-2)
        {
            if (sub_index == 0)      //输入的是X相对坐标值
                points[main_index].rc.X = coord;    //将输入的X坐标值写入相应的检验点中
            else                    //输入的是Y相对坐标值
                points[main_index].rc.Y = coord;    //将输入的Y坐标值写入相应的检验点中
        }
    }
    else if (fabs(points[main_index].rc.X) <= 1e-2 && fabs(points[main_index].rc.Y >= 1e-2))
    {
        if (sub_index == 0)
        {
            point_tmp->rc.X = coord;
            point_tmp->rc.Y = points[main_index].rc.Y;
            rc_to_pc(point_tmp, datum_point);
            if (fabs(coord) >= 1e-2)
                color = getpixel(point_tmp->pc.X, point_tmp->pc.Y);
            if (judge_check_point(points, n, point_tmp))
            {
                pop_up_window("当前点已经被设置");
                //my_bar(350, 0, 600, 28, 1, CYAN);
                //center_puthz(350, 0, 600, 28, "当前点已经被设置", 16, 16, WHITE);
                my_bar(528 + 64 * sub_index, 40 + 4 + 45 * main_index, 571 + 62 * sub_index, 40 + 26 + 45 * main_index, 1, WHITE);
            }
            else if (color != ACTIVATE_COLOR)
            {
                pop_up_window("当前点不在待选水体中");
                points[main_index].rc.X = 0;
                points[main_index].pc.X = 0;
                my_bar(528 + 64 * sub_index, 40 + 4 + 45 * main_index, 571 + 62 * sub_index, 40 + 26 + 45 * main_index, 1, WHITE);
            }
            else if (color != WATER_COLOR || point_tmp->pc.X >= 480 && point_tmp->pc.Y >= 480)
            {
                //my_bar(350, 0, 600, 28, 1, CYAN);
                //center_puthz(350, 0, 600, 28, "当前点不在水体中", 16, 16, WHITE);
                pop_up_window("当前点不在水体中");
                points[main_index].rc.X = 0;
                points[main_index].pc.X = 0;
                my_bar(528 + 64 * sub_index, 40 + 4 + 45 * main_index, 571 + 62 * sub_index, 40 + 26 + 45 * main_index, 1, WHITE);
            }
            else
            {
                point_cpy(&points[main_index], point_tmp);
                pop_delay_window("检验点设置成功");
                //my_bar(350, 0, 600, 28, 1, CYAN);
                //center_puthz(350, 0, 600, 28, "检验点设置成功", 16, 16, WHITE);
                ++(*num_now);
                draw_tag(points, n);
            }
        }
        else
            points[main_index].rc.Y = coord;
    }
    else
    {
        if (sub_index == 0)
        {
            points[main_index].rc.X = coord;
        }
        else
        {
            point_tmp->rc.Y = coord;
            point_tmp->rc.X = points[main_index].rc.X;
            rc_to_pc(point_tmp, datum_point);
            if (fabs(coord) >= 1e-2)
                color = getpixel(point_tmp->pc.X, point_tmp->pc.Y);
            if (judge_check_point(points, n, point_tmp))
            {
                pop_up_window("当前点已经被设置");
                //my_bar(350, 0, 600, 28, 1, CYAN);
                //center_puthz(350, 0, 600, 28, "当前点已经被设置", 16, 16, WHITE);
                my_bar(528 + 64 * sub_index, 40 + 4 + 45 * main_index, 571 + 62 * sub_index, 40 + 26 + 45 * main_index, 1, WHITE);
            }
            else if (color != ACTIVATE_COLOR)
            {
                pop_up_window("当前点不在待选水体中");
                points[main_index].rc.X = 0;
                points[main_index].pc.Y = 0;
                my_bar(528 + 64 * sub_index, 40 + 4 + 45 * main_index, 571 + 62 * sub_index, 40 + 26 + 45 * main_index, 1, WHITE);
            }
            else if (color != WATER_COLOR || point_tmp->pc.X >= 480 || point_tmp->pc.Y >= 480)
            {
                //my_bar(350, 0, 600, 28, 1, CYAN);
                //center_puthz(350, 0, 600, 28, "当前点不在水体中", 16, 16, WHITE);
                pop_up_window("当前点不在水体中");
                points[main_index].rc.Y = 0;
                points[main_index].pc.Y = 0;
                my_bar(528 + 64 * sub_index, 40 + 4 + 45 * main_index, 571 + 62 * sub_index, 40 + 26 + 45 * main_index, 1, WHITE);
            }
            else
            {
                point_cpy(&points[main_index], point_tmp);
                pop_delay_window("检验点设置成功");
                //my_bar(350, 0, 600, 28, 1, CYAN);
                //center_puthz(350, 0, 600, 28, "检验点设置成功", 16, 16, WHITE);
                ++(*num_now);
                draw_tag(points, n);
            }
        }
    }

    clear_point(point_tmp);
}

//鼠标在页面右侧检验点框的序号		返回-1代表未在检验点坐标框中点击
int get_point_index(void)
{
    int i;
    for (i = 0; i < NUM_POINT; i++)
    {
        if (mouse_press(533, 40 + 4 + 45 * i, 573, 40 + 26 + 45 * i) == left_click_yes)
            return (i * 10 + 0);
        else if (mouse_press(594, 40 + 4 + 45 * i, 633, 40 + 26 + 45 * i) == left_click_yes)
            return (i * 10 + 1);
    }

    return -1;
}

//将源检验点的数据复制到目标检验点
void point_cpy(Point* des, Point* src)
{
    des->pc.X = src->pc.X;
    des->pc.Y = src->pc.Y;
    des->rc.Y = src->rc.Y;
    des->rc.X = src->rc.X;
}

//将检验点数据清零
void clear_point(Point* point)
{
    point->pc.X = 0;
    point->pc.Y = 0;
    point->rc.X = 0;
    point->rc.Y = 0;
}


//显示无人艇出发点
void draw_departure_point(Point* point)
{
    int X = (int)point->pc.X;
    int Y = (int)point->pc.Y;
    setcolor(RED);
    arc(X - 7, Y, 0, 60, 7);
    arc(X + 7, Y, 120, 180, 7);
    circle(X, Y - 14, 8);
    setfillstyle(1, RED);
    floodfill(X, Y - 3, RED);
    floodfill(X, Y - 14, RED);
    setcolor(WHITE);
    circle(X, Y - 14, 4);
    setfillstyle(1, WHITE);
    floodfill(X, Y - 14, WHITE);
}

//高级覆盖已有点
void new_cover_point(Point* points, int cover_index, int activated_index)
{
    int X = points[cover_index].pc.X;
    int Y = points[cover_index].pc.Y;
    if (cover_index == activated_index)      //待删除点在被激活水体中
    {
        my_bar(X - 10, Y - 25, X + 10, Y + 1, 1, ACTIVATE_COLOR);
    }
    else                                     //待删除点在未被激活水体中
    {
        my_bar(X - 10, Y - 25, X + 10, Y + 1, 1, WATER_COLOR);
    }
}

void cover_point(Point point)
{
    int X = point.pc.X;
    int Y = point.pc.Y;
    my_bar(X - 8, Y - 8, X + 8, Y + 1, 1, WATER_COLOR);
}

//画检验点界面的菜单
void draw_point_menu(void)
{
    Menu menu;
    int i;
    char name[3][10] = { "增加", "删除", "确认" };
    menu.color = CYAN;
    menu.num = 3;
    menu.fontcolor = WHITE;
    menu.fontsize = 24;
    menu.fontspace = 24;
    //menu.name = name;
    for (i = 0; i < 3; i++)
    {
        menu.name[i] = name[i];
    }
    menu.y1 = 0;
    menu.y2 = 28;
    menu.margin = 10;
    menu.x1 = 0;
    menu.x2 = 260;
    menu_draw(menu);
}

/*
//申请该界面所需要菜单
void init_menu(MENUTYPE* main_menu, MENUTYPE* sub_menus[], int sub_menu_num)
{
    int i;
    int coord[4];
    int itemcoord[4 * 3];
    char** itemname;
    int itemnum;
    unsigned char color;
    char ch_size;

    itemname[0] = "增加"; itemname[1] = "删除"; itemname[2] = "确认";
    //创建主菜单
    coord[0] = 10;  coord[1] = 0; coord[2] = 240;    coord[3] = 28;
    for (i = 0; i < 3; i++)
    {
        itemcoord[4 * i] = 10 + 90 * i;
        itemcoord[4 * i + 1] = 0;
        itemcoord[4 * i + 2] = 60 + 90 * i;
        itemcoord[4 * i + 3] = 28;
    }
    itemnum = 3;
    color = CYAN;
    ch_size = 24;
    main_menu = create_menu(coord, itemcoord, itemname, ch_size, color, itemnum);

    display_main_menu(main_menu);

    for (i = 0; i < sub_menu_num; i++)
    {
        color = GREEN;
        coord[0] = 10 + 90 * i;
        coord[1] = 28;
        coord[2] = 10 + 90 + 90 * i;
        coord[3] = 28 + 32 * 2;
        itemname[0] = "出发点";    itemname[1] = "检验点";
        itemcoord[0] = 10 + 90 * i; itemcoord[1] = 28;  itemcoord[2] = 10 + 90 + 90 * i;    itemcoord[3] = 28 + 32 * 1;
        itemcoord[4] = 10 + 90 * i; itemcoord[1] = 28 + 32 * 1;  itemcoord[2] = 10 + 90 + 90 * i;    itemcoord[3] = 28 + 32 * 2;
        itemnum = 2;
        ch_size = 24;
        sub_menus[i] = create_menu(coord, itemcoord, itemname, ch_size, color, itemnum);
    }
    free_menu(main_menu);
    for (i = 0; i < sub_menu_num; i++)
    {
        free_menu(sub_menus[i]);
    }
}
*/
