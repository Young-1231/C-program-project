#ifndef	_DATA_H_
#define	_DATA_H_

#include"database.h"

typedef	struct Node
{
	WaterData	waterdata;
	struct Node* next;
}*Data;

typedef struct CSV_Node
{
	Indicator indicator;
	struct CSV_Node* next;
}*CSV_Data;


#define MAX_CSV_LINE	49
#define Precision		8

//将当前水质数据保存到文件中
void write_data(WaterData* waterdata_head, int num);

//void write_data(Data head);
void read_data(Data head);
//Data new_data(void);
//void add_data(Data head, Data new_data);
//在链表中寻找寻找相应时间段内的数据	0-寻找失败		非零值-寻找成功且为相应区间内的结点个数
//int find_data(Time* upper_limit, Time* lower_limit, Data head,Data target);
//Data generate_data(int num, Point* points);
int check_data(WaterData* waterdata, Time* lower_limit, Time* upper_limit, int num_limit);
//将此次水质数据写到文件中
void write_now_data(WaterData* waterdata, int num);

char* remove_quoted(char* str);
char* get_field(char* line, int num);
void write_to_struct(Indicator* indicator, int index, char* str);
//CSV_Data batch_read_csv_data(int num);
//CSV_Data random_read_csv_data(int num);
//CSV_Data read_csv_data(void);
//void read_csv_line(int line, CSV_Data csv_data);
void random_index(int* index, int num, int min, int max);
//void free_csv_data(Data head);
//从csv文件中随机读取指定行数的记录
void random_read_csv_data(int num, Indicator* indicators);
void read_csv_line(int line, Indicator* indicator);

//生成随机浮点数
void rand_doubles(double* rand_results, int num, double min, double max);
//生成随机数据
void rand_data(Indicator* indicators, int num);
//生成随机数据
void rand_indicators(double* rand_results, int num, double* mins, double* max);
//获取位置信息和水质数据和时间信息 组成综合水质数据
void generate_data(Indicator* indicators, Point* points, WaterData* waterdata_head, int num);
/*
//将标志数据生成标志设为0
void reset_index(void);
//将标志数据生成标志设为1
void set_index(void);

void one_index(void);//将标志数据生成标志设为1 1-已经生成 0-未生成

int set_index(void);
*/

#endif // _DATA_H_
