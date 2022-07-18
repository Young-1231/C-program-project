#ifndef _DATABASE_H_
#define _DATABASE_H_

typedef struct
{
	char username[10];
	char password[10];
}USER;		//用户信息

typedef struct
{
	double X;
	double Y;
}RC;		//相对坐标(相对于出发点)

typedef struct
{
	double X;
	double Y;

}PC;		//屏幕坐标

typedef struct 
{
	double lon;	
	double lat;	
}GC;		//经纬度

typedef struct
{
	RC rc;
	PC pc;
	GC gc;
}Point;

typedef struct
{
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
}Time;

typedef struct
{
	int			category;		//水质类别
	double		temperature;	//水温
	double		ph;				//pH值
	double		oxygen;			//溶解氧
	double		cu;				//铜离子
	double		zn;				//磷酸根
	double		kmno4;			//高锰酸钾
	double		nh4;			//氨氮
	double		totalP;			//总磷
	double		totalN;			//总氮
}Indicator;

typedef struct
{
	Time		time;		//时间
	char		index;		//路径点序号
	Indicator	idctor;		//各项水质指标数据
	GC			gc;			//经纬度
}WaterData;	

#endif // !_DATABASE_H
