/*******************************************************************************
*     File Name :                        mat_com.h
*     Library/Module Name :              MatrixComputation
*     Author :                           黄飞扬
*     Create Date :                      2022/2/16
*     Abstract Description :             矩阵运算库公用头文件
*******************************************************************************/

#ifndef  __MAT_COM_H__
#define  __MAT_COM_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/*******************************************************************************
* Macro Define Section
*******************************************************************************/
#define _IN
#define _OUT
#define _IN_OUT
#define MAX(x,y) (x) > (y) ? (x) : (y)
#define MIN(x,y) (x) < (y) ? (x) : (y)

#define _CRT_SECURE_NO_WARNINGS
#define PI 3.1415926535897932
#define POSITIVE_INFINITY 999999999
#define NEGATIVE_INFINITY -999999999
#define _ERROR_NO_ERROR		                                        0X00000000   //无错误
#define _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY	                    0X00000001   //分配堆内存失败
#define _ERROR_SVD_EXCEED_MAX_ITERATIONS							0X00000002   //svd超过最大迭代次数
#define _ERROR_MATRIX_ROWS_OR_COLUMNS_NOT_EQUAL	                    0X00000003   //矩阵行数或列数不相等
#define _ERROR_MATRIX_MULTIPLICATION								0X00000004   //矩阵乘法错误(第一个矩阵的列数不等于第二个矩阵行数)
#define _ERROR_MATRIX_MUST_BE_SQUARE								0X00000005   //矩阵必须为方阵
#define _ERROR_MATRIX_NORM_TYPE_INVALID								0X00000006   //矩阵模类型无效
#define _ERROR_MATRIX_EQUATION_HAS_NO_SOLUTIONS						0X00000007   //矩阵方程无解
#define _ERROR_MATRIX_EQUATION_HAS_INFINITY_MANNY_SOLUTIONS	        0X00000008   //矩阵方程有无穷多解
#define _ERROR_QR_DECOMPOSITION_FAILED								0X00000009   //QR分解失败
#define _ERROR_CHOLESKY_DECOMPOSITION_FAILED						0X0000000a   //cholesky分解失败
#define _ERROR_IMPROVED_CHOLESKY_DECOMPOSITION_FAILED				0X0000000b   //improved cholesky分解失败
#define _ERROR_LU_DECOMPOSITION_FAILED								0X0000000c   //LU分解失败
#define _ERROR_CREATE_MATRIX_FAILED									0X0000000d   //创建矩阵失败
#define _ERROR_MATRIX_TRANSPOSE_FAILED								0X0000000e   //矩阵转置失败
#define _ERROR_CREATE_VECTOR_FAILED									0X0000000f   //创建向量失败
#define _ERROR_VECTOR_DIMENSION_NOT_EQUAL 							0X00000010   //向量维数不相同
#define _ERROR_VECTOR_NORM_TYPE_INVALID								0X00000011   //向量模类型无效
#define _ERROR_VECTOR_CROSS_FAILED									0X00000012   //向量叉乘失败
#define _ERROR_MATRIX_MUST_BE_SYMMETRIC								0x00000013	 //矩阵必须为对称阵
#define _ERROR_MATRIX_STACK_SHAPE_NOT_FIT							0x00000014   //矩阵堆叠形状不匹配
#define _ERROR_INPUT_PARAMETERS_ERROR								0X00010000   //输入参数错误

/*******************************************************************************
* Struct(Data Types) Define Section
*******************************************************************************/
typedef  unsigned int ERROR_ID;
typedef int INDEX;
typedef short FLAG;
typedef int INTEGER;
typedef double REAL;
typedef char* STRING;
typedef void VOID;

typedef  struct matrix
{
	INTEGER rows;
	INTEGER columns;
	REAL* p;
}Matrix;

typedef struct named_matrix
{
	Matrix* matrix;			//矩阵
	STRING* row_names;		//行名称
	STRING* col_names;		//列名称
}NamedMatrix;

typedef struct named_matrix_node
{
	NamedMatrix* ptr;
	struct named_matrix_node* next;
}NamedMatrixNode;

typedef struct matrix_node
{
	Matrix* ptr;
	struct matrix_node* next;
} MatrixNode;

typedef struct matrix_element_node
{
	REAL* ptr;
	struct matrix_element_node* next;
} MatrixElementNode;

typedef struct stacks
{
	MatrixNode* matrixNode;
	NamedMatrixNode* namedmatrixNode;
	MatrixElementNode* matrixElementNode;
	// ...
	// 添加其他对象的指针
} Stacks;

/*******************************************************************************
* Prototype Declare Section
*******************************************************************************/
/**********************************************************************************************
Function: init_stack
Description: 初始化栈
Input: 无
Output: 无
Input_Output: 栈指针
Return: 无
Author: 黄飞扬
***********************************************************************************************/
VOID init_stack(_IN_OUT Stacks* S);

/**********************************************************************************************
Function: free_stack
Description: 释放栈
Input: 栈指针
Output: 无
Input_Output: 无
Return: 无
Author: 黄飞扬
***********************************************************************************************/
VOID free_stack(_IN Stacks* S);

#endif