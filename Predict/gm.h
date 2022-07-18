#ifndef _GM_H_
#define _GM_H_


#include"matrix.h"
#include"mat_com.h"
#include"database.h"

#define Predicted_Period 3

void gm_main(void);

//形成时间序列
//Matrix* get_time_series(Stacks* S);
//检验数据是否满足GM模型对级比的要求
int check_ratio(Matrix* x0);
//进行累加
void gm_predicted(Matrix* x0, int num, REAL* predicted_result);
Matrix* accmulate(Matrix* x0, Stacks* S);
Matrix* get_parameter(Matrix* x0, Matrix* x1, Stacks* S);
Matrix* predicted_sequence(Matrix* x0, Matrix* P, Stacks* S);
Matrix* random_series(Stacks* S, INTEGER num);
VOID linear_nomalization(Matrix* A);
VOID zscore_normalization(Matrix* A, REAL* g_mean, REAL* g_std);
REAL avg_relative_error(Matrix* x0, Matrix* x_predicted);
REAL get_predicted_result(REAL x0_1, Matrix* P, int k);
//删除上一轮的预测数据
void delete_predicted(void);
//对某一点进行预测
void point_predicted(Matrix* data_matrix, Indicator* indicators, int num);

void save_predicted(REAL(* predicted)[Predicted_Period], int row, int col);
void read_predicted(double* values, int index);
//将未来三天的水质类别写入文件中
void write_threeday_category(void);
//从文件中读取未来三天的水质类别
void read_threeday_category(int* cats, int index);

//REAL time_response_sequence(REAL x0_1, Matrix* P, int k);
#endif 