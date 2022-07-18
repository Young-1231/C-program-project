#ifndef _COORD_H_
#define _COORD_H_
#include"database.h"
#include"matrix.h"


#define Anchor1_Pc_X     20
#define Anchor1_Pc_Y     50
#define Anchor1_Gc_Lon   34.12
#define Anchor1_Gc_Lat   114.56

#define Anchor2_Pc_X     500
#define Anchor2_Pc_Y     500
#define Anchor2_Gc_Lon   34.55
#define Anchor2_Gc_Lat   114.86

#define PI      3.141592653589793


//相对坐标到屏幕坐标的转换
void rc_to_pc(Point* point, Point* datum_point);
//屏幕坐标到相对坐标的转换
void pc_to_rc(Point* point, Point* datum_point);
//向量的L2范数
double norm(double x, double y);
//屏幕坐标到经纬度的转换
void pc_to_gc(Point* point);


#endif // !_COORD_H_
