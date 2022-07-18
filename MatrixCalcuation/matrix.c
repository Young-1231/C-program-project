/*******************************************************************************
*     File Name :                        matrix.c
*     Library/Module Name :              MatrixComputation
*     Author :                           黄飞扬
*     Create Date :                      2022/2/16
*     Abstract Description :             矩阵运算库源文件
*******************************************************************************/

/*******************************************************************************
* Include File Section
*******************************************************************************/
#include "matrix.h"
/*******************************************************************************
* Function Define Section
*******************************************************************************/

VOID print_matrix(Matrix* a, STRING string)
{
	INDEX i, j;
	printf("matrix %s:", string);
	printf("\n");
	if (a == NULL)
		printf("Error!Matrix is NULL.");
	for (i = 0; i < a->rows; i++)
	{
		for (j = 0; j < a->columns; j++)
		{
			printf("%lf  ", a->p[i * a->columns + j]);
		}
		printf("\n");
	}

	printf("\n");
}

//打印具名矩阵
VOID print_named_matrix(NamedMatrix* a, STRING string)
{
	INDEX i, j;
	print_matrix(a->matrix, string);

	for (i = 0; i < a->matrix->rows; i++)
	{
		printf("%s\t", a->row_names[i]);
	}
	putchar('\n');
	for (j = 0; j < a->matrix->columns; j++)
	{
		printf("%s\t", a->col_names[j]);
	}
	putchar('\n');
}
/**********************************************************************************************
Function: creat_matrix
Description: 创建矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，(栈指针S)
Input_Output: 无
Return: 矩阵指针
Author: 黄飞扬
***********************************************************************************************/
Matrix* creat_matrix(_IN INTEGER rows, _IN INTEGER columns, _OUT ERROR_ID* errorID, _OUT Stacks* S)
{
	Matrix* matrix = NULL;
	MatrixNode* matrixNode = NULL;
	MatrixElementNode* matrixElementNode = NULL;

	if (errorID == NULL)
	{
		return NULL;
	}

	*errorID = _ERROR_NO_ERROR;
	if (rows <= 0 || columns <= 0 || S == NULL)
	{
		*errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return NULL;
	}

	matrix = (Matrix*)malloc(sizeof(Matrix));
	matrixNode = (MatrixNode*)malloc(sizeof(MatrixNode));
	matrixElementNode = (MatrixElementNode*)malloc(sizeof(MatrixElementNode));
	if (matrix == NULL || matrixNode == NULL || matrixElementNode == NULL)
	{
		free(matrix);
		matrix = NULL;
		free(matrixNode);
		matrixNode = NULL;
		free(matrixElementNode);
		matrixElementNode = NULL;

		*errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
		return NULL;
	}

	matrix->rows = rows;
	matrix->columns = columns;
	matrix->p = (REAL*)malloc(rows * columns * sizeof(REAL));  //确保matrix非空才能执行指针操作
	if (matrix->p == NULL)
	{
		free(matrix->p);
		matrix->p = NULL;
		free(matrix);
		matrix = NULL;
		free(matrixNode);
		matrixNode = NULL;
		free(matrixElementNode);
		matrixElementNode = NULL;

		*errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
		return NULL;
	}

	matrixNode->ptr = matrix;
	matrixNode->next = S->matrixNode;
	S->matrixNode = matrixNode;

	matrixElementNode->ptr = matrix->p;
	matrixElementNode->next = S->matrixElementNode;
	S->matrixElementNode = matrixElementNode;

	return matrix;
}

/**********************************************************************************************
Function: creat_named_matrix
Description: 创建具名矩阵
Input: 矩阵行数rows，列数columns, 列名称colnames, 行名称rownames
Output: 错误号指针errorID，(栈指针S)
Input_Output: 无
Return: 矩阵指针
Author: 黄飞扬
***********************************************************************************************/

NamedMatrix* create_named_matrix(_IN INTEGER rows, _IN INTEGER columns, _OUT ERROR_ID* errorID, _OUT Stacks* S, _IN STRING rownames[], _IN STRING colnames[])
{
	NamedMatrix* named_matrix = NULL;
	NamedMatrixNode* named_matrixNode = NULL;
	INDEX index;

	if (*errorID = NULL)
	{
		return NULL;
	}

	*errorID = _ERROR_NO_ERROR;
	if (rows <= 0 || columns <= 0 || S == NULL)
	{
		*errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return NULL;
	}

	named_matrix = (NamedMatrix*)malloc(sizeof(NamedMatrix));
	named_matrixNode = (NamedMatrixNode*)malloc(sizeof(NamedMatrixNode));
	named_matrix->matrix = creat_matrix(rows, columns, errorID, S);

	if (*errorID != _ERROR_NO_ERROR)
		return NULL;

	if (named_matrix == NULL || named_matrixNode == NULL)
	{
		free(named_matrix);
		named_matrix = NULL;
		free(named_matrixNode);
		named_matrixNode = NULL;

		*errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
		return NULL;
	}

	named_matrix->row_names = (STRING*)malloc(rows * sizeof(STRING));
	named_matrix->col_names = (STRING*)malloc(columns * sizeof(STRING));

	if (named_matrix->col_names == NULL || named_matrix->row_names == NULL)
	{
		free(named_matrix->col_names);
		named_matrix->col_names = NULL;
		free(named_matrix->row_names);
		named_matrix->row_names = NULL;
		free(named_matrix);
		named_matrix = NULL;

		*errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
		return NULL;
	}

	for (index = 0; index < columns; index++)
	{
		named_matrix->col_names[index] = colnames[index];
		//colnames[index] = NULL;
	}
	for (index = 0; index < rows; index++)
	{
		named_matrix->row_names[index] = rownames[index];
		//rownames[index] = NULL;
	}

	named_matrixNode->ptr = named_matrix;
	named_matrixNode->next = S->namedmatrixNode;
	S->namedmatrixNode = named_matrixNode;

	return named_matrix;
}

/**********************************************************************************************
Function: creat_multiple_matrices
Description: 创建多个矩阵
Input: 矩阵行数rows，列数columns，个数count
Output: 错误号指针errorID，(栈指针S)
Input_Output: 无
Return: 矩阵指针
Author: 黄飞扬
***********************************************************************************************/
Matrix* creat_multiple_matrices(_IN INTEGER rows, _IN INTEGER columns, _IN INTEGER count, _OUT ERROR_ID* errorID, _OUT Stacks* S)
{
	INDEX i;
	Matrix* matrix = NULL, * p = NULL;
	MatrixNode* matrixNode = NULL;

	if (errorID == NULL)
	{
		return NULL;
	}

	*errorID = _ERROR_NO_ERROR;
	if (rows <= 0 || columns <= 0 || count <= 0 || S == NULL)
	{
		*errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return NULL;
	}

	matrix = (Matrix*)malloc(count * sizeof(Matrix));
	matrixNode = (MatrixNode*)malloc(sizeof(MatrixNode));
	if (matrix == NULL || matrixNode == NULL)
	{
		free(matrix);
		matrix = NULL;
		free(matrixNode);
		matrixNode = NULL;

		*errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
		return NULL;
	}

	for (i = 0; i < count; i++)
	{
		p = creat_matrix(rows, columns, errorID, S);
		if (p == NULL)
		{
			free(matrix);
			matrix = NULL;
			free(matrixNode);
			matrixNode = NULL;

			*errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
			return NULL;
		}

		matrix[i] = *p;
	}

	matrixNode->ptr = matrix;
	matrixNode->next = S->matrixNode;
	S->matrixNode = matrixNode;

	return matrix;
}

/**********************************************************************************************
Function: creat_zero_matrix
Description: 创建零矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，(栈指针S)
Input_Output: 无
Return: 矩阵指针
Author: 黄飞扬
***********************************************************************************************/
Matrix* creat_zero_matrix(_IN INTEGER rows, _IN INTEGER columns, _OUT ERROR_ID* errorID, _OUT Stacks* S)
{
	Matrix* matrix = NULL;

	if (errorID == NULL)
	{
		return NULL;
	}

	*errorID = _ERROR_NO_ERROR;
	if (rows <= 0 || columns <= 0 || S == NULL)
	{
		*errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return NULL;
	}

	matrix = creat_matrix(rows, columns, errorID, S);
	if (*errorID == _ERROR_NO_ERROR)
	{
		memset(matrix->p, 0, rows * columns * sizeof(REAL));
	}

	return matrix;
}

/**********************************************************************************************
Function: creat_eye_matrix
Description: 创建单位矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，(栈指针S)
Input_Output: 无
Return: 矩阵指针
Author: 黄飞扬
***********************************************************************************************/
Matrix* creat_eye_matrix(_IN INTEGER n, _OUT ERROR_ID* errorID, _OUT Stacks* S)
{
	INDEX i;
	Matrix* matrix = NULL;

	if (errorID == NULL)
	{
		return NULL;
	}

	*errorID = _ERROR_NO_ERROR;
	if (n <= 0 || S == NULL)
	{
		*errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return NULL;
	}

	matrix = creat_matrix(n, n, errorID, S);
	if (*errorID == _ERROR_NO_ERROR)
	{
		memset(matrix->p, 0, n * n * sizeof(REAL));
		for (i = 0; i < n; i++)
		{
			matrix->p[i * n + i] = 1.0;
		}
	}

	return matrix;
}

/**********************************************************************************************
Function: matrix_add
Description: 矩阵A + 矩阵B = 矩阵C
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
Author: 黄飞扬
***********************************************************************************************/
ERROR_ID matrix_add(_IN Matrix* A, _IN Matrix* B, _OUT Matrix* C)
{
	INDEX i, j;
	INTEGER rows, columns;
	ERROR_ID errorID = _ERROR_NO_ERROR;

	if (A == NULL || B == NULL || C == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->rows != B->rows || A->rows != C->rows || B->rows != C->rows
		|| A->columns != B->columns || A->columns != C->columns || B->columns != C->columns)
	{
		errorID = _ERROR_MATRIX_ROWS_OR_COLUMNS_NOT_EQUAL;
		return errorID;
	}

	rows = A->rows;
	columns = A->columns;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			C->p[i * columns + j] = A->p[i * columns + j] + B->p[i * columns + j];
		}
	}
	return errorID;
}

/**********************************************************************************************
Function: matrix_stack
Description: 将二维矩阵沿某一轴堆叠
Input: 矩阵A,矩阵B,堆叠模式mode,栈指针S
Output: 矩阵C
Input_Output: 无
Return: 错误号
Author: 黄飞扬
***********************************************************************************************/
ERROR_ID matrix2d_stack(_IN Matrix* A, _IN Matrix* B, _IN INTEGER mode, _OUT Matrix* C, _IN Stacks* S)
{
	ERROR_ID errorID = _ERROR_NO_ERROR;
	INTEGER new_rows, new_cols;
	INDEX i, j;

	if (A == NULL || B == NULL || (mode != 0 && mode != 1))
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	//按行堆叠
	if (mode == 0)
	{
		if (A->columns != B->columns)
		{
			errorID = _ERROR_MATRIX_STACK_SHAPE_NOT_FIT;
			return errorID;
		}
		new_rows = A->rows + B->rows;
		new_cols = A->columns;
	}
	else
	{
		if (A->rows != B->rows)
		{
			errorID = _ERROR_MATRIX_STACK_SHAPE_NOT_FIT;
			return errorID;
		}
		new_cols = A->columns + B->columns;
		new_rows = A->rows;
	}

	C = creat_matrix(new_rows, new_cols, &errorID, S);
	if (errorID != _ERROR_NO_ERROR)
	{
		return errorID;
	}

	switch (mode)
	{
	case 0:	//按行堆叠
		for (i = 0; i < A->rows; i++)
		{
			for (j = 0; j < A->columns; j++)
			{
				C->p[i * A->columns + j] = A->p[i * A->columns + j];
			}
		}
		for (; i < C->rows; i++)
		{
			for (j = 0; j < B->columns; j++)
			{
				C->p[i * B->columns + j] = A->p[(i - A->rows) * B->columns + j];
			}
		}
		break;
	case 1:	//按列堆叠
		for (i = 0; i < A->columns; i++)
		{
			for (j = 0; j < A->rows; j++)
			{
				C->p[j * C->rows + i] = A->p[j * A->rows + i];
			}
		}
		for (; i < C->columns; i++)
		{
			for (j = 0; j < B->rows; j++)
			{
				C->p[j * C->rows + i] = B->p[j * B->rows + j - A->columns];
			}
		}
		break;
	}

	return errorID;
}

/**********************************************************************************************
Function: matrix_subtraction
Description: n * 矩阵A
Input:  矩阵A 数量n
Output: 矩阵A
Input_Output: A
Return: 错误号
Author: 黄飞扬
***********************************************************************************************/
ERROR_ID matrix_scalar_product(_IN_OUT Matrix* A, _IN REAL n)
{
	INDEX i;	int size = matrix_size(A);
	ERROR_ID errorID = _ERROR_NO_ERROR;
	if (A == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	for (i = 0; i < size; i++)
	{
		A->p[i] *= n;
	}

	return errorID;
}

/**********************************************************************************************
Function: matrix_subtraction
Description: 矩阵A - 矩阵B = 矩阵C
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
Author: 黄飞扬
***********************************************************************************************/
ERROR_ID matrix_subtraction(_IN Matrix* A, _IN Matrix* B, _OUT Matrix* C)
{
	INDEX i, j;
	INTEGER rows, columns;
	ERROR_ID errorID = _ERROR_NO_ERROR;

	if (A == NULL || B == NULL || C == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->rows != B->rows || A->rows != C->rows || B->rows != C->rows
		|| A->columns != B->columns || A->columns != C->columns || B->columns != C->columns)
	{
		errorID = _ERROR_MATRIX_ROWS_OR_COLUMNS_NOT_EQUAL;
		return errorID;
	}

	rows = A->rows;
	columns = A->columns;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			C->p[i * columns + j] = A->p[i * columns + j] - B->p[i * columns + j];
		}
	}
	return errorID;
}

/**********************************************************************************************
Function: matrix_multiplication
Description: 矩阵乘法C = A * B
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
Author: Marc Pony(marc_pony@163.com)
***********************************************************************************************/
ERROR_ID matrix_multiplication(_IN Matrix* A, _IN Matrix* B, _OUT Matrix* C)
{
	INDEX  i, j, k;
	REAL sum;
	ERROR_ID errorID = _ERROR_NO_ERROR;

	if (A == NULL || B == NULL || C == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->columns != B->rows || A->rows != C->rows || B->columns != C->columns)
	{
		errorID = _ERROR_MATRIX_MULTIPLICATION;
		return errorID;
	}

	for (i = 0; i < A->rows; i++)
	{
		for (j = 0; j < B->columns; j++)
		{
			sum = 0.0;
			for (k = 0; k < A->columns; k++)
			{
				sum += A->p[i * A->columns + k] * B->p[k * B->columns + j];
			}
			C->p[i * B->columns + j] = sum;
		}
	}
	return errorID;
}

/**********************************************************************************************
Function: matrix_inverse
Description: 矩阵求逆
Input: 矩阵A
Output: 矩阵A的逆矩阵
Input_Output: 无
Return: 错误号
Author: Marc Pony(marc_pony@163.com)
***********************************************************************************************/
ERROR_ID matrix_inverse(_IN Matrix* A, _OUT Matrix* invA)
{
	INDEX i;
	INTEGER n;
	Matrix* ATemp = NULL;
	ERROR_ID errorID = _ERROR_NO_ERROR;
	Stacks S;

	if (A == NULL || invA == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->rows != A->columns)
	{
		errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
		return errorID;
	}

	init_stack(&S);

	n = A->rows;
	ATemp = creat_matrix(n, n, &errorID, &S);
	if (errorID != _ERROR_NO_ERROR)
	{
		free_stack(&S);
		return errorID;
	}

	memcpy(ATemp->p, A->p, n * n * sizeof(REAL));
	memset(invA->p, 0, n * n * sizeof(REAL));
	for (i = 0; i < n; i++)
	{
		invA->p[i * n + i] = 1.0;
	}

	errorID = solve_matrix_equation_by_lup_decomposition(ATemp, invA);

	free_stack(&S);
	return errorID;
}

/**********************************************************************************************
Function: matrix_transpose
Description: 矩阵转置
Input: 矩阵A
Output: 矩阵A的转置
Input_Output: 无
Return: 错误号
Author: 黄飞扬
***********************************************************************************************/
ERROR_ID matrix_transpose(_IN Matrix* A, _OUT Matrix* transposeA)
{
	INDEX i, j;
	ERROR_ID errorID = _ERROR_NO_ERROR;

	if (A == NULL || transposeA == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->rows != transposeA->columns || A->columns != transposeA->rows)
	{
		errorID = _ERROR_MATRIX_TRANSPOSE_FAILED;
		return errorID;
	}

	for (i = 0; i < A->rows; i++)
	{
		for (j = 0; j < A->columns; j++)
		{
			transposeA->p[j * A->rows + i] = A->p[i * A->columns + j];
		}
	}
	return errorID;
}

/**********************************************************************************************
Function: matrix_trace
Description: 矩阵的迹
Input: 矩阵A
Output: 矩阵A的迹
Input_Output: 无
Return: 错误号
Author: 黄飞扬
***********************************************************************************************/
ERROR_ID matrix_trace(_IN Matrix* A, _OUT REAL* trace)
{
	INDEX i;
	ERROR_ID errorID = _ERROR_NO_ERROR;

	if (A == NULL || trace == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->rows != A->columns)
	{
		errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
		return errorID;
	}

	*trace = 0.0;
	for (i = 0; i < A->rows; i++)
	{
		*trace += A->p[i * A->columns + i];
	}
	return errorID;
}

/**********************************************************************************************
Function: lup_decomposition
Description: n行n列矩阵LUP分解PA = L * U
Input: n行n列矩阵A
Output: n行n列下三角矩阵L，n行n列上三角矩阵U，n行n列置换矩阵P
Input_Output: 无
Return: 错误号
Author: 黄飞扬
参考：https://zhuanlan.zhihu.com/p/84210687
***********************************************************************************************/

ERROR_ID lup_decomposition(_IN Matrix* A, _OUT Matrix* L, _OUT Matrix* U, _OUT Matrix* P)
{
	INDEX i, j, k, index, s, t;
	INTEGER n;
	REAL maxValue, temp;
	ERROR_ID errorID = _ERROR_NO_ERROR;

	if (A == NULL || L == NULL || U == NULL || P == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->rows != A->columns)
	{
		errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
		return errorID;
	}

	n = A->rows;
	memcpy(U->p, A->p, n * n * sizeof(REAL));
	memset(L->p, 0, n * n * sizeof(REAL));
	memset(P->p, 0, n * n * sizeof(REAL));
	for (i = 0; i < n; i++)
	{
		L->p[i * n + i] = 1.0;
		P->p[i * n + i] = 1.0;
	}

	for (j = 0; j < n - 1; j++)
	{
		//Select i(>= j) that maximizes | U(i, j) |
		index = -1;
		maxValue = 0.0;
		for (i = j; i < n; i++)
		{
			temp = fabs(U->p[i * n + j]);
			if (temp > maxValue)
			{
				maxValue = temp;
				index = i;
			}
		}

		if (index == -1)
		{
			continue;
		}

		//Interchange rows of U : U(j, j : n) < ->U(i, j : n)
		for (k = j; k < n; k++)
		{
			s = j * n + k;
			t = index * n + k;
			temp = U->p[s];
			U->p[s] = U->p[t];
			U->p[t] = temp;
		}

		//Interchange rows of L : L(j, 1 : j - 1) < ->L(i, 1 : j - 1)
		for (k = 0; k < j; k++)
		{
			s = j * n + k;
			t = index * n + k;
			temp = L->p[s];
			L->p[s] = L->p[t];
			L->p[t] = temp;
		}

		//Interchange rows of P : P(j, 1 : n) < ->P(i, 1 : n)
		for (k = 0; k < n; k++)
		{
			s = j * n + k;
			t = index * n + k;
			temp = P->p[s];
			P->p[s] = P->p[t];
			P->p[t] = temp;
		}

		for (i = j + 1; i < n; i++)
		{
			s = i * n + j;
			L->p[s] = U->p[s] / U->p[j * n + j];
			for (k = j; k < n; k++)
			{
				U->p[i * n + k] -= L->p[s] * U->p[j * n + k];
			}
		}
	}
	return errorID;
}

/**********************************************************************************************
Function: solve_matrix_equation_by_lup_decomposition
Description: LUP分解解矩阵方程AX=B,其中A为n行n列矩阵，B为n行m列矩阵，X为n行m列待求矩阵(写到矩阵B)
Input: n行n列矩阵A
Output: 无
Input_Output: n行m列矩阵B(即n行m列待求矩阵X)
Return: 错误号
Author: 黄飞扬
***********************************************************************************************/

ERROR_ID solve_matrix_equation_by_lup_decomposition(_IN Matrix* A, _IN_OUT Matrix* B)
{
	INDEX i, j, k, index, s, t;
	INTEGER n, m;
	REAL sum, maxValue, temp;
	Matrix* L = NULL, * U = NULL, * y = NULL;
	ERROR_ID errorID = _ERROR_NO_ERROR;
	Stacks S;

	if (A == NULL || B == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->rows != A->columns)
	{
		errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
		return errorID;
	}

	init_stack(&S);

	n = A->rows;
	m = B->columns;

	L = creat_matrix(n, n, &errorID, &S);
	if (errorID != _ERROR_NO_ERROR)
	{
		free_stack(&S);
		return errorID;
	}
	U = creat_matrix(n, n, &errorID, &S);
	if (errorID != _ERROR_NO_ERROR)
	{
		free_stack(&S);
		return errorID;
	}

	y = creat_matrix(n, m, &errorID, &S);
	if (errorID != _ERROR_NO_ERROR)
	{
		free_stack(&S);
		return errorID;
	}

	memcpy(U->p, A->p, n * n * sizeof(REAL));
	memset(L->p, 0, n * n * sizeof(REAL));
	for (i = 0; i < n; i++)
	{
		L->p[i * n + i] = 1.0;
	}

	for (j = 0; j < n - 1; j++)
	{
		//Select i(>= j) that maximizes | U(i, j) |
		index = -1;
		maxValue = 0.0;
		for (i = j; i < n; i++)
		{
			temp = fabs(U->p[i * n + j]);
			if (temp > maxValue)
			{
				maxValue = temp;
				index = i;
			}
		}

		if (index == -1)
		{
			continue;
		}

		//Interchange rows of U : U(j, j : n) < ->U(i, j : n)
		for (k = j; k < n; k++)
		{
			s = j * n + k;
			t = index * n + k;
			temp = U->p[s];
			U->p[s] = U->p[t];
			U->p[t] = temp;
		}

		//Interchange rows of L : L(j, 1 : j - 1) < ->L(i, 1 : j - 1)
		for (k = 0; k < j; k++)
		{
			s = j * n + k;
			t = index * n + k;
			temp = L->p[s];
			L->p[s] = L->p[t];
			L->p[t] = temp;
		}

		//Interchange rows of P : P(j, 1 : n) < ->P(i, 1 : n), C = P * B，等价于对B交换行
		for (k = 0; k < m; k++)
		{
			s = j * m + k;
			t = index * m + k;
			temp = B->p[s];
			B->p[s] = B->p[t];
			B->p[t] = temp;
		}

		for (i = j + 1; i < n; i++)
		{
			s = i * n + j;
			L->p[s] = U->p[s] / U->p[j * n + j];
			for (k = j; k < n; k++)
			{
				U->p[i * n + k] -= L->p[s] * U->p[j * n + k];
			}
		}
	}

	for (i = 0; i < n; i++)
	{
		if (fabs(U->p[i * n + i]) < 1.0e-20)
		{
			errorID = _ERROR_MATRIX_EQUATION_HAS_NO_SOLUTIONS;
			free_stack(&S);
			return errorID;
		}
	}

	//L * y = C
	for (j = 0; j < m; j++)
	{
		for (i = 0; i < n; i++)
		{
			sum = 0.0;
			for (k = 0; k < i; k++)
			{
				sum = sum + L->p[i * n + k] * y->p[k * m + j];
			}
			y->p[i * m + j] = B->p[i * m + j] - sum;
		}
	}

	//U * x = y
	for (j = 0; j < m; j++)
	{
		for (i = n - 1; i >= 0; i--)
		{
			sum = 0.0;
			for (k = i + 1; k < n; k++)
			{
				sum += U->p[i * n + k] * B->p[k * m + j];
			}
			B->p[i * m + j] = (y->p[i * m + j] - sum) / U->p[i * n + i];
		}
	}

	free_stack(&S);
	return errorID;
}

int matrix_size(_IN Matrix* A)
{
	int size = A->columns * A->rows;
	return size;
}

REAL matrix_norm2(_IN Matrix* A)
{
	REAL norm2_ans = 0.0;
	int matrix_num = matrix_size(A);
	INDEX i;

	for (i = 0; i < matrix_num; i++)
	{
		norm2_ans += (A->p[i]) * (A->p[i]);
	}
	norm2_ans = (REAL)sqrt(norm2_ans);

	return norm2_ans;
}

//Jacobi方法实现实对称矩阵的特征值分解
ERROR_ID classic_jacobi_method(_IN_OUT Matrix* A, _IN_OUT Matrix* egi_vector)
{
	ERROR_ID errorID = _ERROR_NO_ERROR;
	INTEGER itr_limit = 20;		//迭代次数
	INTEGER count = 0;
	INTEGER max_index;	int row_index, col_index;
	INTEGER Rows = A->rows; INTEGER Cols = A->columns;
	REAL theta;
	INTEGER sign;
	Stacks S_tmp;
	Matrix* G = NULL;
	Matrix* G_tran = NULL;
	Matrix* A_tmp = NULL;
	Matrix* egi_tmp = NULL;

	if (A == NULL && egi_vector == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	/*
	if (!matrix_is_symmetic(A))
	{
		errorID = _ERROR_MATRIX_MUST_BE_SYMMETRIC;
		return errorID;
	}
	*/
	init_stack(&S_tmp);
	G = creat_matrix(Rows, Rows, &errorID, &S_tmp);
	G_tran = creat_matrix(Rows, Rows, &errorID, &S_tmp);
	A_tmp = creat_matrix(Rows, Rows, &errorID, &S_tmp);
	egi_tmp = creat_matrix(Rows, Rows, &errorID, &S_tmp);

	//将特征值矩阵转换为单位阵
	convert_to_eye_matrix(egi_tmp);
	convert_to_eye_matrix(egi_vector);

	while (count <= itr_limit)
	{
		max_index = matrix_find_maxelem(A);
		row_index = max_index / Cols;
		col_index = max_index - row_index * Cols;

		//printf("max_index = %d\n", max_index);
		//printf("(%d, %d)\n", row_index, col_index);

		if (A->p[row_index * Cols + row_index] == A->p[col_index * Rows + col_index])
		{
			if (A->p[max_index] > 0)
				sign = 1;
			else
				sign = -1;
			theta = sign * PI / 4.0;
		}
		else
		{
			theta = atan(2.0 * A->p[max_index] / (A->p[row_index * Cols + row_index] - A->p[col_index * Cols + col_index])) / 2;
		}

		convert_to_eye_matrix(G);
		G->p[row_index * Cols + row_index] = cos(theta);
		G->p[row_index * Cols + col_index] = sin(theta);
		G->p[col_index * Cols + row_index] = (-1.0) * sin(theta);
		G->p[col_index * Cols + col_index] = cos(theta);

		matrix_transpose(G, G_tran);
		matrix_multiplication(G, A, A_tmp);
		matrix_multiplication(A_tmp, G_tran, A);

		//print_matrix(G, "G");
		//print_matrix(A, "A");
		matrix_copy(egi_tmp, egi_vector);
		matrix_multiplication(egi_tmp, G_tran, egi_vector);

		//print_matrix(egi_vector, "特征向量");
		count++;
	}
	//print_matrix(A, "特征值矩阵");
	free_stack(&S_tmp);
	errorID = _ERROR_NO_ERROR;
	return errorID;
}

//判断矩阵是否对称
int matrix_is_symmetic(_IN Matrix* A)
{
	INDEX i, j;
	int row = A->rows;	int col = A->columns;
	int flag = 1;

	if (row != col)
	{
		flag = 0;
		return flag;
	}

	for (i = 0; i < row; i++)
	{
		for (j = 0; j <= i; j++)
		{
			if (A->p[i * col + j] != A->p[j * col + i])
			{
				flag = 0;
				break;
			}
		}
	}

	return flag;
}

//pca中找出下三角矩阵中绝对值最大的索引
INTEGER matrix_find_maxelem(_IN Matrix* A)
{
	INTEGER max_index = 0;
	INTEGER size = matrix_size(A);
	INDEX i, j;
	REAL max = 0.0;

	for (i = 0; i < A->rows; i++)
	{
		for (j = 0; j < i; j++)
		{
			if (fabs(A->p[i * A->columns + j]) >= max)
			{
				max = fabs(A->p[i]);
				max_index = i * A->columns + j;
			}
		}
	}

	return max_index;
}

//将方阵转换为单位阵
ERROR_ID convert_to_eye_matrix(_IN_OUT Matrix* A)
{
	ERROR_ID errorID = _ERROR_NO_ERROR;
	INDEX i, j;	int row = A->rows; int col = A->columns;

	if (A == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->rows != A->columns)
	{
		errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
		return errorID;
	}

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < row; j++)
		{
			if (i == j)
				A->p[i * col + j] = 1;
			else
				A->p[i * col + j] = 0;
		}
	}

	return errorID;
}

ERROR_ID matrix_copy(_IN_OUT Matrix* des, _IN_OUT Matrix* src)
{
	ERROR_ID errorID = _ERROR_NO_ERROR;
	INDEX i;	int size = matrix_size(src);

	if (des == NULL && src == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if ((des->rows != src->rows) || (des->columns != src->columns))
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	for (i = 0; i < size; i++)
	{
		des->p[i] = src->p[i];
	}

	return errorID;
}

VOID matrix_sort(_IN_OUT Matrix* P, _IN_OUT Matrix* D, _IN INTEGER mode)
{
	INTEGER row = P->rows;
	INTEGER col = D->columns;
	INDEX i, j;

	switch (mode)
	{
	case 1:
		for (i = 0; i < col - 1; i++)
		{
			for (j = i; j < col; j++)
			{
				if (D->p[i * col + i] > D->p[j * col + j])
				{
					matrix_swap(i, j, D, 2);
					matrix_swap(i, j, P, 2);
				}
			}
		}
		break;
	case 2:
		for (i = 0; i < col - 1; i++)
		{
			for (j = i; j < col; j++)
			{
				if (D->p[i * col + i] < D->p[j * col + j])
				{
					matrix_swap(i, j, D, 2);
					matrix_swap(i, j, P, 2);
				}
			}
		}
	case 3:
		for (i = 0; i < col - 1; i++)
		{
			for (j = i; j < col; j++)
			{
				if (fabs(D->p[i * col + i]) > fabs(D->p[j * col + j]))
				{
					matrix_swap(i, j, D, 2);
					matrix_swap(i, j, P, 2);
				}
			}
		}
	case 4:
		for (i = 0; i < col - 1; i++)
		{
			for (j = i; j < col; j++)
			{
				if (fabs(D->p[i * col + i]) < fabs(D->p[j * col + j]))
				{
					matrix_swap(i, j, D, 2);
					matrix_swap(i, j, P, 2);
				}
			}
		}
	}
	//matrix_transpose(P, P_tran);
}

//pca中对特征值矩阵和特征向量矩阵进行排序
VOID pca_matrix_sort(_IN_OUT NamedMatrix* D, _IN_OUT Matrix* P)
{
	INTEGER row = P->rows;
	INDEX i, j;
	REAL tmp;
	STRING name_tmp = NULL;

	//按照特征值绝对值的大小来排序
	for (i = 0; i < row - 1; i++)
	{
		for (j = i; j < row; j++)
		{
			if (fabs(D->matrix->p[i * row + i]) < fabs(D->matrix->p[j * row + j]))
			{
				tmp = D->matrix->p[i * row + i];
				D->matrix->p[i * row + i] = D->matrix->p[j * row + j];
				D->matrix->p[j * row + j] = tmp;

				name_tmp = D->col_names[i];
				D->col_names[i] = D->col_names[j];
				D->col_names[j] = name_tmp;

				matrix_swap(i, j, P, 2);
			}
		}
	}
}

//交换矩阵中的行或列	1-行 2-列
VOID matrix_swap(_IN INTEGER i, _IN INTEGER j, _IN_OUT Matrix* A, int mode)
{
	INDEX b;
	REAL tmp;

	switch (mode)
	{
	case 1:
		for (b = 0; b < A->columns; b++)
		{
			tmp = A->p[i * A->columns + b];
			A->p[i * A->columns + b] = A->p[j * A->columns + b];
			A->p[j * A->columns + b] = tmp;
		}
		break;
	case 2:
		for (b = 0; b < A->rows; b++)
		{
			tmp = A->p[b * A->rows + i];
			A->p[b * A->rows + i] = A->p[b * A->rows + j];
			A->p[b * A->rows + j] = tmp;
		}
		break;
	}
}

//交换具名矩阵中的行或列 1-行 2-列
VOID namedmatrix_swap(_IN INTEGER i, _IN INTEGER j, _IN_OUT NamedMatrix* A, int mode)
{
	STRING name_tmp;

	matrix_swap(i, j, A->matrix, mode);

	switch (mode)
	{
	case 1:
		name_tmp = A->row_names[i];
		A->row_names[i] = A->row_names[j];
		A->row_names[j] = name_tmp;
		break;
	case 2:
		name_tmp = A->col_names[i];
		A->col_names[i] = A->col_names[j];
		A->col_names[j] = name_tmp;
		break;
	}
}

//对二维矩阵进行切片操作 i:j
Matrix* matrix_slice(Matrix* A, INTEGER i, INTEGER j, INTEGER dim, ERROR_ID* errorID, Stacks* S)
{
	INTEGER slice_length;
	Matrix* sliced_matrix = NULL;
	INDEX a, b;

	*errorID = _ERROR_NO_ERROR;
	if (i > j)
	{
		*errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return NULL;
	}
	slice_length = j - i + 1;
	switch (dim)
	{
	case 0:
		sliced_matrix = creat_matrix(slice_length, A->columns, errorID, S);
		if (*errorID != _ERROR_NO_ERROR)
			return NULL;
		for (a = 0; a < A->columns; a++)
		{
			for (b = 0; b < slice_length; b++)
			{
				sliced_matrix->p[b * A->columns + a] = A->p[(b + i) * A->columns + a];
			}
		}
		break;
	case 1:
		sliced_matrix = creat_matrix(A->rows, slice_length, errorID, S);
		if (*errorID != _ERROR_NO_ERROR)
			return NULL;
		for (a = 0; a < A->rows; a++)
		{
			for (b = 0; b < slice_length; b++)
			{
				sliced_matrix->p[a * slice_length + b] = A->p[a * A->columns + b + i];
			}
		}
		break;
	}

	return sliced_matrix;
}

//原地加法a = a + b
void local_add(Matrix* a, Matrix* b)
{
	Stacks S_tmp;
	Matrix* a_copy = NULL;
	ERROR_ID errorID;
	init_stack(&S_tmp);
	a_copy = creat_matrix(a->rows, a->columns, &errorID, &S_tmp);
	matrix_copy(a_copy, a);

	matrix_add(a_copy, b, a);
	free_stack(&S_tmp);
}

//偏置
void bias_add(Matrix* a, Matrix* bias)
{
	int i;
	int j;
	for (i = 0; i < a->rows; i++)
	{
		for (j = 0; j < a->columns; j++)
		{
			a->p[i * a->columns + j] += bias->p[j];
		}
	}
}

void matrix_exp(Matrix* a, Matrix* a_exp)
{
	int i;
	int j;
	for (i = 0; i < a->rows; i++)
	{
		for (j = 0; j < a->columns; j++)
		{
			a_exp->p[i * a->columns + j] = exp(a->p[i * a->columns + j]);
		}
	}
}

REAL matrix_sum(Matrix* a)
{
	int i;
	int j;
	REAL sum = 0;

	for (i = 0; i < a->rows; i++)
	{
		for (j = 0; j < a->columns; j++)
		{
			sum += a->p[i * a->columns + j];
		}
	}

	return sum;
}

//矩阵按轴向求和
void matrix_axis_sum(Matrix* a, Matrix* sum, int axis)
{
	int i, j;
	//将求和矩阵置零
	for (i = 0; i < sum->rows; i++)
	{
		for (j = 0; j < sum->columns; j++)
		{
			sum->p[i * sum->columns + j] = 0;
		}
	}
	switch (axis)
	{
	case 0:
		for (i = 0; i < a->columns; i++)
		{
			for (j = 0; j < a->rows; j++)
			{
				sum->p[i] += a->p[j * a->columns + i];
			}
		}
		break;
	case 1:
		for (i = 0; i < a->rows; i++)
		{
			for (j = 0; j < a->columns; j++)
			{
				sum->p[i] += a->p[i * a->columns + j];
			}
		}
		break;
	}
}

//矩阵按轴向取最大值
void matrix_axis_max(Matrix* a, Matrix* max, int axis)
{
	int i, j;
	double tmp_max;
	//将最大值矩阵置零
	for (i = 0; i < max->rows; i++)
	{
		for (j = 0; j < max->columns; j++)
		{
			max->p[i * max->columns + j] = 0;
		}
	}

	switch (axis)
	{
	case 0:
		for (i = 0; i < a->columns; i++)
		{
			tmp_max = -10000;
			for (j = 0; j < a->rows; j++)
			{
				if (tmp_max < a->p[j * a->columns + i])
					tmp_max = a->p[j * a->columns + i];
			}
			max->p[i] = tmp_max;
		}
		break;
	case 1:
		for (i = 0; i < a->rows; i++)
		{
			tmp_max = -10000;
			for (j = 0; j < a->columns; j++)
			{
				if (tmp_max < a->p[i * a->columns + j])
					tmp_max = a->p[i * a->columns + j];
			}
			max->p[i] = tmp_max;
		}
		break;
	}
}

void relu(Matrix* pdata)
{
	int i, j;
	for (i = 0; i < pdata->rows; i++)
	{
		for (j = 0; j < pdata->columns; j++)
		{
			pdata->p[i * pdata->columns + j] = pdata->p[i * pdata->columns + j] > 0 ? pdata->p[i * pdata->columns + j] : 0;
		}
	}
}

void matrix_argmax(Matrix* a, Matrix* max_index, int axis)
{
	int i;
	int j;
	int index;
	REAL max = -100000;

	switch (axis)
	{
	case 0:
		for (i = 0; i < a->columns; i++)
		{
			max = -100000;
			index = 0;
			for (j = 0; j < a->rows; j++)
			{
				if (max < a->p[j * a->columns + i])
				{
					max = a->p[j * a->columns + i];
					index = j;
				}
			}
			max_index->p[i] = index;
		}
		break;
	case 1:
		for (i = 0; i < a->rows; i++)
		{
			max = -100000;
			index = 0;
			for (j = 0; j < a->columns; j++)
			{
				if (max < a->p[i * a->columns + j])
				{
					max = a->p[i * a->columns + j];
					index = j;
				}
			}

			max_index->p[i] = index;
		}
		break;
	}
}
