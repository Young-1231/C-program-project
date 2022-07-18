#ifndef _CHECK_POINT_H_
#define _CHECK_POINT_H_

#include"database.h"
#include"menu.h"


typedef void (*PolyPtr) (unsigned int);

//检验点操作总控制函数
void check_point(int* button);
//显示地图以外的功能栏
void point_screen(void);
//显示东湖地图
void show_map(void);
//显示标记
void draw_tag(Point* points, int n);
//判断检验点存在情况
int judge_check_point(Point* points, int n, Point* point);
//判断用户选择的检验点是否在水体中
int is_in_water(Point* point);
//根据屏幕坐标设定检验点
void pc_set_point(PolyPtr polyptrs[], Point* points, int n, Point* point, int* num_now, Point* dep_point);
//根据屏幕坐标删除检验点
void pc_delete_point(PolyPtr polyptrs[], Point* points, int n, Point* point, int* now_num);
//根据屏幕坐标删除出发点
void pc_delete_dep(Point* dep_point, Point* point);
//根据相对坐标设定检验点
void rc_set_point(Point* points, int n, Point* point_tmp, Point* dep_point, int index, int* num_now);
//鼠标在页面右侧检验点框的序号		返回-1代表未在检验点坐标框中点击
int get_point_index(void);
//将源检验点的数据复制到目标检验点
void point_cpy(Point* des, Point* src);
//将出发点和检验点数据清零
void clear_points(Point* dep_point, Point* points, int n);
//检验点数据清零
void clear_point(Point* point);
//显示检验点相对坐标
void show_point_rc(Point* points, int n);
//选择无人艇出发点
int set_departure_point(Point* dep_point, Point* point);
//显示无人艇出发起始点
void draw_departure_point(Point* point);
//更新多边形	1-增加模式 2-减少模式
void renew_poly(Point* points,PolyPtr polytrs[], int index,int mode);
//高级覆盖已有点
void new_cover_point(Point* points, int cover_index, int activated_index);
//覆盖已有点
void cover_point(Point point);
//申请菜单
void init_menu(MENUTYPE* main_menu, MENUTYPE* sub_menus[], int sub_menu_num);
//从文件中读取检验点的屏幕坐标
void read_check_pc(Point* check_points, int n);
//将检验点数据写入文件中
void save_point_data(Point* dep_point, Point* points, int n);
//从文件中读取检验点数据
void read_point_data(Point* dep_point, Point* points, int n);
//初始化函数指针
void init_func_ptrs(PolyPtr* poly_ptrs);
//从文件中读取检验点平面坐标 0-数据未存在 1-数据已存在
//int read_point_pc_data(Point* dep_point, Point* points, int n);
//检验相关检验点是否写入数据
int point_was_set(Point* point);
//将检验点屏幕坐标文件删除
void delete_hist_pc(void);
//从文件中读取出发点和检验点的屏幕坐标
int read_hist_pc(Point* dep_point, Point* points, int n);
//将出发点和检验点的屏幕坐标写入文件中
void save_point_pc(Point* dep_point, Point* points, int n);
//void save_point_pc(PC* pcs, int n);
//画检验点界面的菜单
void draw_point_menu(void);

void choosepoly(void);
void choosepoly1(unsigned int color);
void choosepoly2(unsigned int color);
void choosepoly3(unsigned int color);
void choosepoly4(unsigned int color);
void choosepoly5(unsigned int color);
void choosepoly6(unsigned int color);
void choosepoly7(unsigned int color);
void choosepoly8(unsigned int color);
void choosepoly9(unsigned int color);
void choosepoly10(unsigned int color);

//操作的宏
#define DEFAULT		    0
#define ADD			    1
#define ADD_DEP         5
#define DELETE		    2
//#define ADD_MENU      3
//#define DELETE_MENU     4
#define ADD_CHECK       6
#define DELETE_DEP      7
#define DELETE_CHECK    8	


//检验点总数
#define NUM_POINT       10          
#define WATER_COLOR		GREEN		//水体颜色
#define BELT_COLOR		CYAN		//出发点所在带状区域颜色
#define ACTIVATE_COLOR	YELLOW		//激活水体的颜色

#define SUCCESS		0
#define FAILURE		1

//#define 

#endif // !_CHECK_POINT_H
