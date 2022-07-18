#include"common.h"
#include"coord.h"

//向量的L2范数
double norm(double x, double y)
{
	double length;
	x = pow(x, 2);
	y = pow(y, 2);
	length = sqrt(x + y);
	return length;
}

//屏幕坐标到相对坐标的转换
void pc_to_rc(Point* point, Point* datum_point)
{
	double ratio = 2.0 / 80.0;		//公里每像素
	point->rc.X = (point->pc.X - datum_point->pc.X) * ratio;
	point->rc.Y = (point->pc.Y - datum_point->pc.Y) * ratio;
}

//相对坐标到屏幕坐标的转换
void rc_to_pc(Point* point, Point* datum_point)
{
	double ratio = 80.0 / 2.0;				//像素每公里
	point->pc.X = datum_point->pc.X + ratio * (point->rc.X - datum_point->rc.X);
	point->pc.Y = datum_point->pc.Y + ratio * (point->rc.Y - datum_point->rc.Y);
}

//屏幕坐标到地理坐标的转换
void pc_to_gc(Point* point)
{
	point->gc.lon = asin((point->pc.X *( sin(Anchor2_Gc_Lon * PI / 180) - sin(Anchor1_Gc_Lon * PI / 180)) +
		(Anchor2_Pc_Y - Anchor1_Pc_Y) * sin(Anchor1_Gc_Lon * PI / 180)) / (Anchor2_Pc_Y - Anchor1_Pc_Y)) * 180 / PI;
	point->gc.lat = ((point->pc.X * (Anchor2_Gc_Lat - Anchor1_Gc_Lat) + (Anchor2_Pc_X - Anchor1_Pc_X) *(Anchor1_Gc_Lat)) / (Anchor2_Pc_X - Anchor1_Pc_X));
}
