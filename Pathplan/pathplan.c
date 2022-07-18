/*******************************************************************************
*     File Name :                        pathplan.c
*     Library/Module Name :              PathPlanning
*     Author :                           黄飞扬
*     Create Date :                      2022/3/26
*     Abstract Description :             路径规划源文件
*******************************************************************************/
#include"common.h"
#include"pathplan.h"

//贪心算法路径规划
void greedy_main(Point* checkpoints)
{
	Point locations[NUM_POINT + 1];									//出发点和检验点数组
	PC pcs[NUM_POINT + 1];
	double Node[NUM_POINT + 1][NUM_POINT + 1];						//距离矩阵
	int travled[NUM_POINT + 1] = { 0 };								//标志数组
	double min_distance;
	int traveled_record[NUM_POINT + 1];
	int cur_node;
	int dep_node;
	double pre_distance;
	double cur_distance;
	int index;
	int tmpi, tmpj;
	int i, j, k;
	double total_distance = 0;

	read_point_pc(pcs, NUM_POINT + 1);
	//delete_hist_pc();			//删除历史检验点屏幕坐标

	for (i = 0; i < NUM_POINT + 1; i++)
	{
		locations[i].pc.X = pcs[i].X;
		locations[i].pc.Y = pcs[i].Y;
		//printf("Point %d : (%.2lf, %.2lf)\n", i + 1,locations[i].pc.X, locations[i].pc.Y);
	}

	//delay(1000);
	init_node(locations, NUM_POINT + 1, Node);
	//出发点必为首点
	traveled_record[0] = 0;
	for (i = 1; i <= NUM_POINT; i++)
	{
		traveled_record[i] = -1;
	}
	travled[0] = 1;

	cur_node = 0;

	for (i = 1; i < NUM_POINT + 1; i++)
	{
		min_distance = 10000000;
		index = -1;
		for (j = 0; j < NUM_POINT + 1; j++)
		{
			if (travled[j])
				continue;
			if (j == cur_node)
				continue;
			if (Node[cur_node][j] < min_distance)
			{
				min_distance = Node[cur_node][j];
				index = j;
			}
		}

		if (index != -1)
		{
			cur_node = index;
			travled[index] = 1;
			traveled_record[i] = index;
			total_distance += min_distance;
		}
		else	//未能找到局部最优点
		{
			printf("Fail to give a good solution!");
			exit(1);
		}
	}

	total_distance += Node[traveled_record[NUM_POINT]][traveled_record[0]];
	//便于调试
	//printf("total_distance = %.2lf\n", cal_distance(traveled_record, Node, NUM_POINT + 1));

	
	for (i = 1; i < NUM_POINT + 1; i++)
	{
		for (j = 1; j < NUM_POINT + 1; j++)
		{
			if (i == j)
				continue;
			pre_distance = cal_distance(traveled_record, Node, NUM_POINT + 1);
			swap_record(traveled_record, i, j);
			cur_distance = cal_distance(traveled_record, Node, NUM_POINT + 1);
			if (pre_distance <= cur_distance)
				swap_record(traveled_record, i, j);
		}
	}
	//printf("total_distance = %.2lf\n", cal_distance(traveled_record, Node, NUM_POINT + 1));
	
	
	for (i = 1; i < NUM_POINT + 1; i++)
	{
		for (j = 1; j < NUM_POINT + 1; j++)
		{
			for (k = 1; k < NUM_POINT + 1; k++)
			{
				if (i == j || i == k || j == k)
					continue;
				pre_distance = cal_distance(traveled_record, Node, NUM_POINT + 1);
				tmpi = traveled_record[i];
				tmpj = traveled_record[j];
				traveled_record[i] = traveled_record[k];
				traveled_record[j] = tmpi;
				traveled_record[k] = tmpj;
				cur_distance = cal_distance(traveled_record, Node, NUM_POINT + 1);
				if (pre_distance <= cur_distance)
				{
					traveled_record[k] = traveled_record[i];
					traveled_record[i] = tmpi;
					traveled_record[j] = tmpj;
				}
				pre_distance = cal_distance(traveled_record, Node, NUM_POINT + 1);
				tmpi = traveled_record[i];
				tmpj = traveled_record[j];
				traveled_record[j] = traveled_record[k];
				traveled_record[i] = tmpj;
				traveled_record[k] = tmpi;
				cur_distance = cal_distance(traveled_record, Node, NUM_POINT + 1);
				if (pre_distance <= cur_distance)
				{
					traveled_record[k] = traveled_record[j];
					traveled_record[i] = tmpi;
					traveled_record[j] = tmpj;
				}
			}
		}
	}
	
	//printf("total_distance = %.2lf\n", cal_distance(traveled_record, Node, NUM_POINT + 1));
	//printf("Successfully!");
	//或是直接传结构数组
	//save_path_pc()
	for (i = 0; i < NUM_POINT + 1; i++)
	{
		checkpoints[i].pc.X = locations[traveled_record[i]].pc.X;
		checkpoints[i].pc.Y = locations[traveled_record[i]].pc.Y;
		//printf("Point %d: (%.2lf, %.2lf)\n", checkpoints[i].pc.X, checkpoints[i].pc.Y);
	}
	
	//delay(1000);
}

void read_point_pc(PC* pcs, int n)
{
	FILE* fp = NULL;
	if ((fp = fopen("../database/point/point.dat", "rb")) == NULL)   //文件打开失败
	{
		fprintf(stderr, "fopen()failed");
		delay(1000);
		exit(1);
	}
	fread(pcs, sizeof(PC), n, fp);
	fclose(fp);
}

void read_path_pc(Point* points, int num)
{
	FILE* fp = NULL;
	int i;
	PC pcs[20];
	if ((fp = fopen("../database/path/path.dat", "rb")) == NULL)	//文件打开失败
	{
		fprintf(stderr, "fopen()failed");
		delay(1000);
		exit(1);
	}
	fread(pcs, sizeof(PC), num, fp);
	for (i = 0; i < num; i++)
	{
		points[i].pc.X = pcs[i].X;
		points[i].pc.Y = pcs[i].Y;
	}
	fclose(fp);
}

void save_path_pc(Point* points, int num)
{
	FILE* fp = NULL;
	int i;
	PC pcs[20];
	if ((fp = fopen("../database/path/path.dat", "wb")) == NULL)	//文件打开失败
	{
		fprintf(stderr, "fopen()failed.");
		delay(1000);
		exit(1);
	}
	for (i = 0; i < num; i++)
	{
		pcs[i].X = points[i].pc.X;
		pcs[i].Y = points[i].pc.Y;
	}

	fwrite(pcs, sizeof(PC), num, fp);
	fclose(fp);
}

void init_node(Point* locations, int num, double(* node)[NUM_POINT + 1])
{
	int i, j;
	for (i = 0; i < num; i++)
	{
		for (j = 0; j < num; j++)
		{
			if (i == j)
				node[i][j] = 0;		//同一点之间距离记作0
			else
			{
				node[i][j] = sqrt(pow((locations[i].pc.X - locations[j].pc.X), 2) +
					pow((locations[i].pc.Y - locations[j].pc.Y), 2));
			}
		}
	}
	/*
	for(i = 0;i < num;i++)
	{
		for(j = 0;j < num;j++)
		{
			printf("node[%d][%d] = %.2lf\t", i,j,node[i][j]);
		}
		putchar('\n');
	}*/
}

void swap_record(int* record, int i, int j)
{
	int tmp;
	tmp = record[i];
	record[i] = record[j];
	record[j] = tmp;
}

void swap_point_pc(Point* points, int* record, int num)
{
	int i;
	//Point tmp_points[20];
	Point* tmp_points = NULL;

	if ((tmp_points = (Point*)malloc(num * sizeof(Point))) == NULL)
	{
		printf("No enought memory.\n");
		delay(1000);
		exit(1);
	}

	for (i = 0; i < num; i++)
	{
		tmp_points[i].pc.X = points[record[i]].pc.X;
		tmp_points[i].pc.Y = points[record[i]].pc.Y;
	}

	for (i = 0; i < num; i++)
	{
		points[i].pc.X = tmp_points[i].pc.X;
		points[i].pc.Y = tmp_points[i].pc.Y;
	}
	free(tmp_points);
}

double cal_distance(int* record, double(* Node)[NUM_POINT+1], int num)
{
	int i;
	double total_distance = 0;

	for (i = 0; i < num; i++)
	{
		total_distance += Node[record[i]][record[i + 1]];
	}
	total_distance += Node[record[NUM_POINT]][record[0]];

	return total_distance;
}
