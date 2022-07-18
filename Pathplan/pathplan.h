#ifndef _PATHPLAN_H_
#define _PATHPLAN_H_

#include"point.h"

void greedy_main(Point* checkpoints);
void init_node(Point* locations, int num, double(* node)[NUM_POINT + 1]);
void swap_record(int* record, int i, int j);
void swap_point_pc(Point* points, int* record, int num);
double cal_distance(int* record, double(* Node)[NUM_POINT+1], int num);
void save_path_pc(Point* points, int num);	//将路径规划后的检验点顺序写入文件中
void read_point_pc(PC* pcs, int n);			//读取路径规划后的检验点
void read_path_pc(Point* points, int num);

#endif // !_PATHPLAN_H_
