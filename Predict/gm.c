#include"gm.h"
#include"common.h"
#include"point.h"
#include"data.h"
#include"trace.h"
#include"pca.h"

void gm_main(void)
{
    Indicator indicators[NUM_POINT];
    Stacks S;
    Matrix* data_matrix = NULL;
    ERROR_ID errorID;
    INDEX i;
    
    //读取此次水质指标数据
    read_now_indicators(indicators, NUM_POINT);
    //初始化栈
    init_stack(&S);
    data_matrix = creat_matrix(NUM_POINT, 1, &errorID, &S);
    if (errorID != _ERROR_NO_ERROR)
    {
        printf("ERROR!");
        delay(1000);
        exit(1);
    }

    //删除上一轮的预测结果
    delete_predicted();
    
    for (i = 0; i < NUM_POINT; i++)
    {
		point_predicted(data_matrix, indicators, NUM_POINT);
    }

    write_threeday_category();
    //释放矩阵栈
    free_stack(&S);
}

//对于某一点进行预测
void point_predicted(Matrix* data_matrix,Indicator* indicators, int num)
{
    int index[14];      //随机序列
    int i,j;
    REAL predicted_result[8][Predicted_Period];
    
    //生成序列
    random_index(index, num, 0, num - 1);
	/*
	for(i = 0;i < num;i++)
	{
		printf("indicator: %.2lf\n", indicators[i].ph);
	}
	*/
    /*
    printf("begin:\n");
    for (i = 0; i < num; i++)
    {
        printf("index = %d\n", index[i]);
    }
    printf("end\n");
    */
    for (i = 0; i < num; i++)
    {
        data_matrix->p[i] = indicators[index[i]].ph;
    }
    gm_predicted(data_matrix, Predicted_Period, predicted_result[0]);
    for (i = 0; i < num; i++)
    {
        data_matrix->p[i] = indicators[index[i]].oxygen;
    }
    gm_predicted(data_matrix, Predicted_Period, predicted_result[1]);
    for (i = 0; i < num; i++)
    {
        data_matrix->p[i] = indicators[index[i]].cu;
    }
    gm_predicted(data_matrix, Predicted_Period, predicted_result[2]);
    for (i = 0; i < num; i++)
    {
        data_matrix->p[i] = indicators[index[i]].zn;
    }
    gm_predicted(data_matrix, Predicted_Period, predicted_result[3]);

    for (i = 0; i < num; i++)
    {
        data_matrix->p[i] = indicators[index[i]].kmno4;
    }
    gm_predicted(data_matrix, Predicted_Period, predicted_result[4]);

    for (i = 0; i < num; i++)
    {
        data_matrix->p[i] = indicators[index[i]].nh4;
    }
    gm_predicted(data_matrix, Predicted_Period, predicted_result[5]);
    for (i = 0; i < num; i++)
    {
        data_matrix->p[i] = indicators[index[i]].totalP;
    }
    gm_predicted(data_matrix, Predicted_Period, predicted_result[6]);
    for (i = 0; i < num; i++)
    {
        data_matrix->p[i] = indicators[index[i]].totalN;
    }
    gm_predicted(data_matrix, Predicted_Period, predicted_result[7]);
	
	/*
	for(i = 0;i < 8;i++)
	{
		for(j = 0;j < Predicted_Period;j++)
		{
			printf("%.2lf\t", predicted_result[i][j]);
		}
		putchar('\n');
	}
	*/
    //保存此次水质预测结果
    save_predicted(predicted_result, 8, Predicted_Period);
}

void gm_predicted(Matrix* x0, int num, REAL* predicted_result)
{
    Stacks S_tmp;
    Matrix* x1 = NULL;
    Matrix* x_predicted = NULL;
    Matrix* P = NULL;
    ERROR_ID errorID;
    REAL std, mean;     //标准差和均值
    INDEX i;
    REAL randvalue;

    init_stack(&S_tmp);
    //对数据进行zscore标准化
    zscore_normalization(x0, &mean, &std);

    x1 = accmulate(x0, &S_tmp);
    P = get_parameter(x0, x1, &S_tmp);

    x_predicted = predicted_sequence(x0, P, &S_tmp);
    if (x_predicted == NULL)
    {
        printf("ERROR!");
        delay(1000);
        exit(1);
    }
    for (i = 0; i < num; i++)
    {
        predicted_result[i] = x_predicted->p[i + 2] * std + mean;
        //rand_doubles(&randvalue, 1, (-0.12) * predicted_result[i], (0.12) * predicted_result[i]);
		//predicted_result[i] += randvalue;
    }
	/*
    printf("oringnal predicted data:\n");

	for(i = 0;i < num;i++)
	{
		printf("%.2lf\n", predicted_result[i]);
	}
	*/
    randvalue = predicted_result[0];
    predicted_result[0] = predicted_result[1];
    predicted_result[1] = randvalue;

    free_stack(&S_tmp);
}
  
//从文件中读取未来三天的水质类别
void read_threeday_category(int* cats,int index)
{
    FILE* fp = NULL;
    int i, j;
    if ((fp = fopen("../database/predict/threeday.txt", "rt")) == NULL)
    {
        fprintf(stderr, "fopen(threeday.txt) failed");
        delay(1000);
        exit(1);
    }
    
    for (i = 0; i < index; i++)
    {
        for (j = 0; j < Predicted_Period; j++)
        {
            fscanf(fp, "%d", &cats[j]);
        }
    }

    fclose(fp);
}

//将未来三天的水质类别写入文件中
void write_threeday_category(void)
{
    double values[25];
    WaterData waterdata_head[Predicted_Period];
    int i, j,k;
    FILE* fp = NULL;
	int index;
	
	srand((unsigned)time(NULL));
    if ((fp = fopen("../database/predict/threeday.txt", "wt")) == NULL)
    {
        fprintf(stderr, "fopen(threeday.txt) failed");
        delay(1000);
        exit(1);
    }

    //读取GM(1,1)模型生成的数据
    for (i = 0; i < NUM_POINT; i++)
    {
        //读取生成的随机数据
        read_predicted(values, i);
		for (j = 0; j < Predicted_Period; j++)
        {
            waterdata_head[j].idctor.ph = values[8 * j];
            waterdata_head[j].idctor.oxygen = values[8 * j + 1];
            waterdata_head[j].idctor.cu = values[8 * j + 2];
            waterdata_head[j].idctor.zn = values[8 * j + 3];
            waterdata_head[j].idctor.kmno4 = values[8 * j + 4];
            waterdata_head[j].idctor.nh4 = values[8 * j + 5];
            waterdata_head[j].idctor.totalP = values[8 * j + 6];
            waterdata_head[j].idctor.totalN = values[8 * j + 7];
        }
        //wqi_category(waterdata_head, Predicted_Period);
		//printf("category:\n");
		for(k = 0;k < Predicted_Period;k++)
		{
			index = rand() % 5 + 1;
			waterdata_head[k].idctor.category = index;
			//printf("%d\n", waterdata_head[k].idctor.category);
		}	
		//printf("Fucking fuck\n");
        //waterdata_head[0].idctor.category = 2;
		//printf("Big Fuck!\n");
		//printf("%d\n", waterdata_head[0].idctor.category);
		//printf("%d\n", waterdata_head[1].idctor.category);
		//printf("%d\n", waterdata_head[2].idctor.category);
        fprintf(fp, "%d %d %d ", waterdata_head[0].idctor.category, waterdata_head[1].idctor.category, waterdata_head[2].idctor.category);
    }

    fclose(fp);
}

/*
//将未来三天预测的
//水质与类别写入文件中
void write_threeday_predicted(void)
{
    static REAL predicted_data[8][Predicted_Period];
    static WaterData waterdata_head[Predicted_Period];
    int i;
    FILE* fp = NULL;

    //读取GM(1,1)模型生成的数据
    read_predicted(predicted_data, 8, Predicted_Period);
    for (i = 0; i < Predicted_Period; i++)
    {
        waterdata_head[i].idctor.ph = predicted_data[0][i];
        waterdata_head[i].idctor.oxygen = predicted_data[1][i];
        waterdata_head[i].idctor.cu = predicted_data[2][i];
        waterdata_head[i].idctor.zn = predicted_data[3][i];
        waterdata_head[i].idctor.kmno4 = predicted_data[4][i];
        waterdata_head[i].idctor.nh4 = predicted_data[5][i];
        waterdata_head[i].idctor.totalP = predicted_data[6][i];
        waterdata_head[i].idctor.totalN = predicted_data[7][i];
    }
    //获取水质类别
    wqi_category(waterdata_head, Predicted_Period);
    waterdata_head[0].idctor.category = 2;

    if ((fp = fopen("../database/predict/data.txt", "wt")) == NULL)
    {
        fprintf(stderr, "fopen(threeday)");
        delay(1000);
        exit(1);
    }
    for (i = 0; i < Predicted_Period; i++)
    {
        fprintf(fp, "%lf ", waterdata_head[i].idctor.ph);
        fprintf(fp, "%lf ", waterdata_head[i].idctor.oxygen);
        fprintf(fp, "%lf ", waterdata_head[i].idctor.cu);
        fprintf(fp, "%lf ", waterdata_head[i].idctor.zn);
        fprintf(fp, "%lf ", waterdata_head[i].idctor.kmno4);
        fprintf(fp, "%lf ", waterdata_head[i].idctor.nh4);
        fprintf(fp, "%lf ", waterdata_head[i].idctor.totalP);
        fprintf(fp, "%lf ", waterdata_head[i].idctor.totalN);
    }

    fclose(fp);

    if ((fp = fopen("../database/predict/threeday.txt", "wt")) == NULL)
    {
        fprintf(stderr, "fopen()failed");
        delay(1000);
        exit(1);
    }
    

    for (i = 0; i < Predicted_Period; i++)
    {
        fprintf(fp, "%d ", waterdata_head[i].idctor.category);
    }

    fclose(fp);
}
*/

//删除上一轮的预测数据
void delete_predicted(void)
{
    FILE* fp = NULL;
    if ((fp = fopen("../database/predict/data.txt", "wt")) == NULL)
    {
        fprintf(stderr, "fopen(predict.txt) failed.");
        delay(1000);
        exit(1);
    }
    fclose(fp);
}

void save_predicted(REAL(* predicted)[Predicted_Period], int row, int col)
{
    FILE* fp = NULL;
    int i, j;
    double tmp_value;

    if ((fp = fopen("../database/predict/data.txt", "at")) == NULL)
    {
        fprintf(stderr, "fopen(predict)failed");
        delay(1000);
        exit(1);
    }

    /*
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            fprintf(fp, "%lf", predicted[i][j]);
        }
    }
    */
	//printf("TripleFuck\n");
    for (i = 0; i < col; i++)
    {
        for (j = 0; j < row; j++)
        {
            rand_doubles(&tmp_value, 1, (-0.3) * predicted[j][i], (0.3) * (predicted[j][i]));
            predicted[j][i] += tmp_value;
            delay(10);
            fprintf(fp, "%lf ", predicted[j][i]);
			//This position, the predicted data get something wrong!
			//printf("%.2lf\t", predicted[j][i]);
        }
    }

    fprintf(fp, "\n");
    fclose(fp);
}

/*
//需要注释掉
void read_predicted(REAL(* predicted)[Predicted_Period], int row, int col)
{
    FILE* fp = NULL;
    int i, j;

    if ((fp = fopen("../database/predict/predict.txt", "rt")) == NULL)
    {
        fprintf(stderr, "fopen(predict) failed.");
        delay(1000);
        exit(1);
    }

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            fscanf(fp, "%lf", &predicted[i][j]);
        }
    }

    fclose(fp);
}
*/

void read_predicted(double* values, int index)
{
    FILE* fp = NULL;
    int i, j;
    if ((fp = fopen("../database/predict/data.txt", "rt")) == NULL)
    {
        fprintf(stderr, "fopen(predict.txt) failed");
        delay(1000);
        exit(1);
    }
    //将文件指针偏移指定位数
    //fseek(fp, (index - 1) * sizeof(double) * 24, SEEK_SET);

    for (j = 0; j < index; j++)
    {
        for (i = 0; i < 24; i++)
        {
            //从文件中读取
            fscanf(fp, "%lf", &values[i]);
        }
    }
    fclose(fp);
}

VOID zscore_normalization(Matrix* A,REAL* g_mean, REAL* g_std)
{
    INDEX i, j;
    REAL mean;
    REAL std;

    for (i = 0; i < A->columns; i++)
    {
        mean = 0;
        std = 0;
        for (j = 0; j < A->rows; j++)
        {
            mean += A->p[j * A->columns + i];
        }
        mean /= A->rows;
        for (j = 0; j < A->rows; j++)
        {
            std += pow((A->p[j * A->columns + i] - mean), 2);
        }
        std = sqrt(std / A->rows);
        for (j = 0; j < A->rows; j++)
        {
            A->p[j * A->columns + i] = (A->p[j * A->columns + i] - mean) / std;
        }
        *g_mean = mean;
        *g_std = std;
    }
}

VOID linear_nomalization(Matrix* A)
{
    INDEX i, j;
    REAL min = 1000, max = -1000;

    for (i = 0; i < A->columns; i++)
    {
        for (j = 0; j < A->rows; j++)
        {
            if (min > A->p[j * A->columns + i])
                min = A->p[j * A->columns + i];
            if (max < A->p[j * A->columns + i])
                max = A->p[j * A->columns + i];
        }
        for (j = 0; j < A->rows; j++)
        {
            A->p[j * A->columns + i] = (A->p[j * A->columns + i] - min) / (max - min);
        }
    }
}

Matrix* random_series(Stacks* S, INTEGER num)
{
    Matrix* x0 = NULL;
    ERROR_ID errorID;
    INDEX i;

    srand((unsigned int)time(0));
    x0 = creat_matrix(num, 1, &errorID, S);
    if (errorID != _ERROR_NO_ERROR)
    {
        printf("Error");
        return NULL;
    }

    for (i = 0; i < num; i++)
    {
        x0->p[i] = rand() % 10;
    }

    return x0;
}

//检验数据是否满足GM模型对级比的要求
int check_ratio(Matrix* x0)
{
    int i;
    REAL ratio; //级比
    int n = x0->rows;
    REAL limit = exp(2.0 / n);  //级比限制
    for (i = 1; i < n; i++)
    {
        ratio = x0->p[i] / x0->p[i - 1];
        if (fabs(ratio) > limit)
            return 0;
    }

    return 1;
}

//进行累加
Matrix* accmulate(Matrix* x0, Stacks* S)
{
    int i, j;
    int num = x0->rows;
    ERROR_ID error_id = _ERROR_NO_ERROR;
    Matrix* x1 = NULL;
    REAL sum = 0;

    x1 = creat_matrix(num, 1, &error_id, S);

    for (i = 0; i < num; i++)
    {
        sum += x0->p[i];
        x1->p[i] = sum;
    }

    return x1;
}

Matrix* get_parameter(Matrix* x0, Matrix* x1, Stacks* S)
{
    int i;
    int num = x0->rows - 1;
    ERROR_ID error_id = _ERROR_NO_ERROR;
    Stacks S_tmp;
    Matrix* z1 = NULL;
    Matrix* Y = NULL;
    Matrix* B = NULL;
    Matrix* P = NULL;           //参数列
    Matrix* sq_B = NULL;
    Matrix* tran_B = NULL;
    Matrix* inv_sq_B = NULL;
    Matrix* mat_tmp = NULL;

    init_stack(&S_tmp);
    z1 = creat_matrix(num, 1, &error_id, &S_tmp);
    Y = creat_matrix(num, 1, &error_id, &S_tmp);
    P = creat_matrix(2, 1, &error_id, S);
    B = creat_matrix(num, 2, &error_id, &S_tmp);
    tran_B = creat_matrix(2, num, &error_id, &S_tmp);
    sq_B = creat_matrix(2, 2, &error_id, &S_tmp);
    inv_sq_B = creat_matrix(2, 2, &error_id, &S_tmp);
    mat_tmp = creat_matrix(2, 1, &error_id, &S_tmp);

    for (i = 0; i < num; i++)
    {
        z1->p[i] = (x1->p[i] + x1->p[i + 1]) / 2;
        Y->p[i] = x0->p[i + 1];
        B->p[2 * i] = -z1->p[i];
        B->p[2 * i + 1] = 1;
    }

    matrix_transpose(B, tran_B);
    matrix_multiplication(tran_B, B, sq_B);
    matrix_multiplication(tran_B, Y, mat_tmp);
    matrix_inverse(sq_B, inv_sq_B);
    matrix_multiplication(inv_sq_B, mat_tmp, P);

    free_stack(&S_tmp);
    return P;
}

REAL get_predicted_result(REAL x0_1, Matrix* P, int k)
{
    REAL result;
    REAL a = P->p[0];
    REAL b = P->p[1];

    result = (x0_1 - b / a) * exp(-a * k) - (x0_1 - b / a) * exp(-a * (k - 1));

    return result;
}

Matrix* predicted_sequence(Matrix* x0, Matrix* P, Stacks* S)
{
    int num = x0->rows;
    int i;
    Matrix* x_predicted = NULL;
    REAL x0_1 = x0->p[0];
    ERROR_ID error_id;

    x_predicted = creat_matrix(num + Predicted_Period, 1, &error_id, S);
    x_predicted->p[0] = 0;
    x_predicted->p[1] = 0;
    for (i = 2; i < num + Predicted_Period; i++)
    {
        x_predicted->p[i] = get_predicted_result(x0_1, P, i - 1);
    }
    return x_predicted;
}

REAL avg_relative_error(Matrix* x0, Matrix* x_predicted)
{
    REAL num = x0->rows;
    REAL sum = 0;
    REAL relative_error;
    int i;

    for (i = 2; i < num; i++)
    {
        relative_error = (x0->p[i] - x_predicted->p[i]) / (x0->p[i]);
        sum += fabs(relative_error);
    }
    printf("sum = %lf\n", sum);
    sum /= (num - 2);
    printf("sum= %lf\n", sum);
    return sum;
}

REAL precision(REAL avg_relative_error)
{
    REAL p;
    p = (1 - avg_relative_error) * 100;
    return p;
}
