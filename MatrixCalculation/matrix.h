/*******************************************************************************
*     File Name :                        matrix.h
*     Library/Module Name :              MatrixComputation
*     Author :                           黄飞扬
*     Create Date :                      2022/2/16
*     Abstract Description :             矩阵运算库头文件
*******************************************************************************/
#ifndef _MATRIX_H_
#define _MATRIX_H_

/*******************************************************************************
* Include File Section
*******************************************************************************/
#include "mat_com.h"

/*******************************************************************************
* Prototype Declare Section
*******************************************************************************/
VOID print_matrix(Matrix* a, STRING string);

//打印具名矩阵
VOID print_named_matrix(NamedMatrix* a, STRING string);

/**********************************************************************************************
Function: creat_matrix
Description: 创建矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
Author: 黄飞扬
***********************************************************************************************/
Matrix* creat_matrix(_IN INTEGER rows, _IN INTEGER columns, _OUT ERROR_ID* errorID, _OUT Stacks* S);

/**********************************************************************************************
Function: creat_multiple_matrices
Description: 创建多个矩阵
Input: 矩阵行数rows，列数columns，个数count
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
Author: 黄飞扬
***********************************************************************************************/
Matrix* creat_multiple_matrices(_IN INTEGER rows, _IN INTEGER columns, _IN INTEGER count, _OUT ERROR_ID* errorID, _OUT Stacks* S);

/**********************************************************************************************
Function: creat_named_matrix
Description: 创建具名矩阵
Input: 矩阵行数rows，列数columns, 列名称colnames, 行名称rownames
Output: 错误号指针errorID，(栈指针S)
Input_Output: 无
Return: 矩阵指针
Author: 黄飞扬
***********************************************************************************************/

NamedMatrix* create_named_matrix(_IN INTEGER rows, _IN INTEGER columns, _OUT ERROR_ID* errorID, _OUT Stacks* S, _IN STRING rownames[], _IN STRING colnames[]);

/**********************************************************************************************
Function: creat_zero_matrix
Description: 创建零矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
Author: 黄飞扬
***********************************************************************************************/
Matrix* creat_zero_matrix(_IN INTEGER rows, _IN INTEGER columns, _OUT ERROR_ID* errorID, _OUT Stacks* S);


/**********************************************************************************************
Function: creat_eye_matrix
Description: 创建单位矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
Author: 黄飞扬
***********************************************************************************************/
Matrix* creat_eye_matrix(_IN INTEGER n, _OUT ERROR_ID* errorID, _OUT Stacks* S);


/**********************************************************************************************
Function: matrix_add
Description: 矩阵A + 矩阵B = 矩阵C
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
Author: 黄飞扬
***********************************************************************************************/
ERROR_ID matrix_add(_IN Matrix* A, _IN Matrix* B, _OUT Matrix* C);

/**********************************************************************************************
Function: matrix_subtraction
Description: 矩阵A - 矩阵B = 矩阵C
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
Author: Marc Pony(marc_pony@163.com)
***********************************************************************************************/
ERROR_ID matrix_subtraction(_IN Matrix* A, _IN Matrix* B, _OUT Matrix* C);


/**********************************************************************************************
Function: matrix_multiplication
Description: 矩阵乘法C = A * B
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
Author: 黄飞扬
***********************************************************************************************/
ERROR_ID matrix_multiplication(_IN Matrix* A, _IN Matrix* B, _OUT Matrix* C);


/**********************************************************************************************
Function: matrix_inverse
Description: 矩阵求逆
Input: 矩阵A
Output: 矩阵A的逆矩阵
Input_Output: 无
Return: 错误号
Author: 黄飞扬
***********************************************************************************************/
ERROR_ID matrix_inverse(_IN Matrix* A, _OUT Matrix* invA);


/**********************************************************************************************
Function: matrix_transpose
Description: 矩阵转置
Input: 矩阵A
Output: 矩阵A的转置
Input_Output: 无
Return: 错误号
Author: 黄飞扬
***********************************************************************************************/
ERROR_ID matrix_transpose(_IN Matrix* A, _OUT Matrix* transposeA);


/**********************************************************************************************
Function: matrix_trace
Description: 矩阵的迹
Input: 矩阵A
Output: 矩阵A的迹
Input_Output: 无
Return: 错误号
Author: 黄飞扬
***********************************************************************************************/
ERROR_ID matrix_trace(_IN Matrix* A, _OUT REAL* trace);


/**********************************************************************************************
Function: lup_decomposition
Description: n行n列矩阵LUP分解PA = L * U
Input: n行n列矩阵A
Output: n行n列下三角矩阵L，n行n列上三角矩阵U，n行n列置换矩阵P
Input_Output: 无
Return: 错误号
Author: 黄飞扬
参考：https://zhuanlan.zhihu.com/p/842106
***********************************************************************************************/
ERROR_ID lup_decomposition(_IN Matrix* A, _OUT Matrix* L, _OUT Matrix* U, _OUT Matrix* P);


/**********************************************************************************************
Function: solve_matrix_equation_by_lup_decomposition
Description: LUP分解解矩阵方程AX=B,其中A为n行n列矩阵，B为n行m列矩阵，X为n行m列待求矩阵(写到矩阵B)
Input: n行n列矩阵A
Output: 无
Input_Output: n行m列矩阵B(即n行m列待求矩阵X)
Return: 错误号
Author: 黄飞扬
***********************************************************************************************/
ERROR_ID solve_matrix_equation_by_lup_decomposition(_IN Matrix* A, _IN_OUT Matrix* B);

ERROR_ID matrix_scalar_product(_IN_OUT Matrix* A, _IN REAL n);
int matrix_size(_IN Matrix* a);
REAL matrix_norm2(_IN Matrix* a);
ERROR_ID convert_to_eye_matrix(_IN_OUT Matrix* A);
INTEGER matrix_find_maxelem(_IN Matrix* A);
int matrix_is_symmetic(_IN Matrix* A);
ERROR_ID classic_jacobi_method(_IN_OUT Matrix* A, _IN_OUT Matrix* egi_vector);
ERROR_ID matrix_copy(_IN_OUT Matrix* des, _IN_OUT Matrix* src);
VOID matrix_sort(_IN_OUT Matrix* P, _IN_OUT Matrix* D, _IN INTEGER mode);
//交换矩阵中的行或列	1-行 2-列
VOID matrix_swap(_IN INTEGER i, _IN INTEGER j, _IN_OUT Matrix* A, int mode);
//交换具名矩阵中的行或列 1-行 2-列
VOID namedmatrix_swap(_IN INTEGER i, _IN INTEGER j, _IN_OUT NamedMatrix* A, int mode);
//pca中对特征值矩阵和特征向量矩阵进行排序
VOID pca_matrix_sort(_IN_OUT NamedMatrix* D, _IN_OUT Matrix* P);
//对二维矩阵进行切片操作 i:j
Matrix* matrix_slice(Matrix* A, INTEGER i, INTEGER j, INTEGER dim, ERROR_ID* errorID, Stacks* S);
//矩阵按轴向取最大值
void matrix_axis_max(Matrix* a, Matrix* max, int axis);
//矩阵按轴向求和
void matrix_axis_sum(Matrix* a, Matrix* sum, int axis);
//矩阵求和
REAL matrix_sum(Matrix* a);
//矩阵自然指数运算
void matrix_exp(Matrix* a, Matrix* a_exp);
//偏置
void bias_add(Matrix* a, Matrix* bias);
//原地加法a = a + b
void local_add(Matrix* a, Matrix* b);
//ReLu
void relu(Matrix* pdata);
//求矩阵轴向上最大值索引
void matrix_argmax(Matrix* a, Matrix* max_index, int axis);
#endif