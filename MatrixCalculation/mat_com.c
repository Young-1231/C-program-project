/*******************************************************************************
*     File Name :                        mat_com.c
*     Library/Module Name :              MatrixComputation
*     Author :                           黄飞扬
*     Create Date :                      2022/2/16
*     Abstract Description :            矩阵运算库公用源文件
*******************************************************************************/

/*******************************************************************************
* Include File Section
*******************************************************************************/
//#include "common.h"
#include "mat_com.h"

/*******************************************************************************
* Function Define Section
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
VOID init_stack(_IN_OUT Stacks* S)
{
	if (S == NULL)
	{
		return;
	}

	memset(S, 0, sizeof(Stacks));
}


/**********************************************************************************************
Function: free_stack
Description: 释放栈
Input: 栈指针
Output: 无
Input_Output: 无
Return: 无
Author: 黄飞扬
***********************************************************************************************/
VOID free_stack(_IN Stacks* S)
{
	MatrixNode* matrixNode = NULL;
	NamedMatrixNode* namedmatrixNode = NULL;
	MatrixElementNode* matrixElementNode = NULL;

	if (S == NULL)
	{
		return;
	}

	while (S->matrixNode != NULL)
	{
		matrixNode = S->matrixNode;
		S->matrixNode = matrixNode->next;

		free(matrixNode->ptr);
		matrixNode->ptr = NULL;
		free(matrixNode);
		matrixNode = NULL;
	}

	while (S->namedmatrixNode != NULL)
	{
		namedmatrixNode = S->namedmatrixNode;
		S->namedmatrixNode = namedmatrixNode->next;

		free(namedmatrixNode->ptr);
		namedmatrixNode->ptr = NULL;
		free(namedmatrixNode);
		namedmatrixNode = NULL;
	}

	while (S->matrixElementNode != NULL)
	{
		matrixElementNode = S->matrixElementNode;
		S->matrixElementNode = matrixElementNode->next;

		free(matrixElementNode->ptr);
		matrixElementNode->ptr = NULL;
		free(matrixElementNode);
		matrixElementNode = NULL;
	}
	// ...
	// 
	// 释放其他指针
}
