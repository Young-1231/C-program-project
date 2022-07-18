#include"common.h"
#include"data.h"
#include"my_t.h"
#include"coord.h"

/*
void write_data(Data head)		//将数据写入文件
{
	Data data_tmp = NULL;
	FILE* fp = NULL;
	char s[30];	//目标文件地址
	
	sprintf(s, "../database/historydata/data.dat");
	
	if (fp = fopen(s, "ab") == NULL)	//文件打开失败
	{
		cleardevice();
		printf("Fail to open file %s", s);
		getch();
		exit(1);
	}
	else								//文件打开成功
	{
		data_tmp = head->next;
		while (data_tmp != NULL)
		{
			fwrite(&data_tmp->waterdata, sizeof(WaterData), 1, fp);
			data_tmp = data_tmp->next;
		}
	}
	fclose(fp);
}

void read_data(Data head)				//从文件中读出数据到有序链表
{
	FILE* fp;
	Data data1 = NULL, data2 = NULL;
	char s[30];							//目标文件地址
	data1 = head;
	sprintf(s, "../database/historydata/data.dat");
	data2 = new_data();
	if(fp = fopen(s,"rb") == NULL)		//文件打开失败
	{
		cleardevice();
		printf("Fail to open file %s", s);
		getch();
		exit(1);
	}
	else								//文件打开成功
	{
		while (fread(&data2->waterdata,sizeof(WaterData),1,fp) == 1 && feof(fp) == 0)
		{
			data1->next = data2;
			data1 = data1->next;
			data2 = new_data();
		}
	}

	fclose(fp);
}


//保存水质数据
void save_data(WaterData head, int num)
{
	int i;
	FILE* fp = NULL;
	
	if ((fp = fopen("boat\database\historydata\data.dat", "ab")) == NULL)
	{
		fprintf(stderr, "Error:Allocate memory for waterdata");
		exit(1);
	}

	fread(&head, sizeof(WaterData), num, fp);	
	
	fclose(fp);
}

/*
Data generate_data(int num, Point* points)
{
	Data head = NULL;
	CSV_Data csv_data = NULL;
	CSV_Data csv_tmp = NULL;
	Data tmp = head;
	int i;

	if ((csv_data = random_read_csv_data(num)) == NULL)
	{
		printf("Fail to read csv data.");
		delay(1000);
		exit(1);
	}

	if ((head = InitList(num)) == NULL)
	{
		printf("Fail to init datalist.");
		delay(1000);
		exit(1);
	}
	tmp = head;
	csv_tmp = csv_data;
	for (i = 0; i < num; i++)
	{
		tmp->waterdata.index = i + 1;
		tmp->waterdata.idctor = csv_tmp->indicator;
		get_time(&tmp->waterdata.time);
		tmp->waterdata.location = points[i];
		csv_tmp = csv_tmp->next;
		tmp = tmp->next;
	}
	free_csv_data(csv_data);

	return head;
}
*/
/*
WaterData* generate_data(int num, Point* points, Indicator* indicators)
{
	WaterData* head = NULL;
	int i;
	Time time;
	get_time(&time);

	if ((head = (WaterData*)malloc(num * sizeof(WaterData))) == NULL)
	{
		fprintf(stderr , "Error:Allocate memory for waterdata failed.");
		exit(1);
	}

	get_time(&time);
	
	for (i = 0; i < num; i++)
	{
		head[i].gc = points[i].gc;
		head[i].index = i + 1;
		head[i].idctor = indicators[i];
		renew_time(&time, 45);
		head[i].time = time;
	}

	return head;
}
*/
/*
Data new_data(void)
{
	Data d = NULL;
	
	if (d = (Data)malloc(sizeof(struct Node)) == NULL)
	{
		cleardevice();
		setcolor(RED);
		outtextxy(100, 100, "Out of memory!");
		outtextxy(100, 130, "Press any key...");
		getch();
		exit(1);
	}
	else
	{
		d->next = NULL;
		return d;
	}
}
*/

/*
Data InitList(int num)
{
	Data head = NULL;
	Data current = NULL;
	head = new_data();
	while (--num)
	{
		current = new_data();
		head->next = current;
		current = current->next;
	}
	current = NULL;
	return head;
}
*/

void generate_data(Indicator* indicators, Point* points, WaterData* waterdata_head, int num)
{
	Time tmp_time;
	int i;
	get_time(&tmp_time);
	for (i = 0; i < num; i++)
	{
		pc_to_gc(&points[i]);
		waterdata_head[i].index = i + 1;
		waterdata_head[i].gc.lon = points[i].gc.lon;
		waterdata_head[i].gc.lat = points[i].gc.lat;
		waterdata_head[i].time = tmp_time;
		//waterdata_head[i].idctor = indicators[i];
		waterdata_head[i].idctor.category = indicators[i].category;
		waterdata_head[i].idctor.kmno4 = indicators[i].kmno4;
		waterdata_head[i].idctor.cu = indicators[i].cu;
		waterdata_head[i].idctor.zn = indicators[i].zn;
		waterdata_head[i].idctor.oxygen = indicators[i].oxygen;
		waterdata_head[i].idctor.ph = indicators[i].ph;
		waterdata_head[i].idctor.totalN = indicators[i].totalN;
		waterdata_head[i].idctor.totalP = indicators[i].totalP;
		waterdata_head[i].idctor.nh4 = indicators[i].nh4;
		waterdata_head[i].idctor.temperature = indicators[i].temperature;
		renew_time(&tmp_time, 45);
	}
}

//将当前水质数据保存到文件中
void write_data(WaterData*  waterdata_head, int num)
{
	int i;
	FILE* fp = NULL;
	int temp;
	if ((fp = fopen("../database/histdata/data.txt", "at")) == NULL)		//文件打开失败
	{
		fprintf(stderr, "fopen()failed");
		delay(1000);
		exit(1);
	}
	srand((unsigned)time(NULL));
	temp = rand() % 5;

	/*
	for (i = 0; i < 1; i++)
	{
		fprintf(stdout, "%d-%d-%d-%d-%d-%d\n", waterdata_head[i].time.year, waterdata_head[i].time.mon, waterdata_head[i].time.day, waterdata_head[i].time.hour,
			waterdata_head[i].time.min, waterdata_head[i].time.sec);
		fprintf(stdout, "%d\n", waterdata_head[i].index);
		fprintf(stdout, "%d\t%.2lf\t%.2lf\t%.2lf\t%.2lf\t%.2lf\%.2lf\t%.2lf\t%.2lf\t%.2lf\n", waterdata_head[i].idctor.category, waterdata_head[i].idctor.temperature, waterdata_head[i].idctor.ph, waterdata_head[i].idctor.oxygen,
			waterdata_head[i].idctor.cu, waterdata_head[i].idctor.zn, waterdata_head[i].idctor.kmno4, waterdata_head[i].idctor.nh4,
			waterdata_head[i].idctor.totalP, waterdata_head[i].idctor.totalN);
		fprintf(stdout, "%.2lf-%.2lf\n", waterdata_head[i].gc.lon, waterdata_head[i].gc.lat);
	}
	*/
	for (i = 0; i < num; i++)
	{
		fprintf(fp, "%d\t%d\t%d\t%d\t%d\t%d\n", waterdata_head[i].time.year, waterdata_head[i].time.mon, waterdata_head[i].time.day, waterdata_head[i].time.hour, 
			waterdata_head[i].time.min, waterdata_head[i].time.sec);
		fprintf(fp, "%d\n", waterdata_head[i].index);
		fprintf(fp, "%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", waterdata_head[i].idctor.category, waterdata_head[i].idctor.temperature, waterdata_head[i].idctor.ph, waterdata_head[i].idctor.oxygen,
			waterdata_head[i].idctor.cu, waterdata_head[i].idctor.zn, waterdata_head[i].idctor.kmno4, waterdata_head[i].idctor.nh4,
			waterdata_head[i].idctor.totalP, waterdata_head[i].idctor.totalN);
		//printf("temperatrue: %.2lf\n", waterdata_head[i].idctor.temperature);
		waterdata_head[temp].idctor.category = 4;
		fprintf(fp, "%lf\t%lf\n", waterdata_head[i].gc.lon, waterdata_head[i].gc.lat);
		
	}
	fclose(fp);
	
	if ((fp = fopen("../database/category/region.txt", "wt")) == NULL)
	{
		fprintf(stderr, "fopen(region.txt)failed.");
		delay(1000);
		exit(1);
	}
	
		
	for (i = 0; i < num; i++)
	{
		fprintf(fp, "%d ", waterdata_head[i].idctor.category);
	}

	fclose(fp);
}

int check_data(WaterData* waterdata, Time* lower_limit, Time* upper_limit, int num_limit)
{
	int num = 0;
	FILE* fp = NULL;
	///WaterData* tmp_data = NULL;
	WaterData tmp_data;
	//int count = 0;			//确定文件指针偏移量
	int i;
	//int flag = 0;			//是否读取到相应时间段中数据的标志

	if ((fp = fopen("../database/histdata/data.txt", "rt")) == NULL)
	{
		fprintf(stderr, "fopen()failed");
		delay(1000);
		exit(1);
	}
	/*
	if ((tmp_data = (WaterData*)malloc(sizeof(WaterData))) == NULL)
	{
		fprintf(stderr, "Error:Allocate memory for waterdata.");
		delay(1000);
		exit(1);
	}
	*/
	while ((fscanf(fp, "%d\t%d\t%d\t%d\t%d\t%d\n", &tmp_data.time.year, &tmp_data.time.mon, &tmp_data.time.day, &tmp_data.time.hour,
		&tmp_data.time.min, &tmp_data.time.sec) == 6) && num < num_limit)
	{
		//fscanf(fp, "%d%d%d%d%d%d", &tmp_data.time.year, &tmp_data.time.mon, &tmp_data.time.day, &tmp_data.time.hour,
		//	&tmp_data.time.min, &tmp_data.time.sec);
		fscanf(fp, "%d\n", &tmp_data.index);
		fscanf(fp, "%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t", &tmp_data.idctor.category, &tmp_data.idctor.temperature, &tmp_data.idctor.ph, &tmp_data.idctor.oxygen,
			&tmp_data.idctor.cu, &tmp_data.idctor.zn, &tmp_data.idctor.kmno4, &tmp_data.idctor.nh4, &tmp_data.idctor.totalP, &tmp_data.idctor.totalN);
		fscanf(fp, "%lf\t%lf\n", &tmp_data.gc.lon, &tmp_data.gc.lat);
		//fprintf(stdout, "%d-%d-%d-%d-%d-%d\n", tmp_data.time.year, tmp_data.time.mon, tmp_data.time.day, tmp_data.time.hour, tmp_data.time.min, tmp_data.time.sec);
		if (compare_time(tmp_data.time, *(upper_limit)) == 1 && compare_time(tmp_data.time, *(lower_limit)) == 0)
		{
			waterdata[num] = tmp_data;
			num++;
			//fprintf(stdout, "%d-%d-%d-%d-%d-%d\n", tmp_data.time.year, tmp_data.time.mon, tmp_data.time.day, tmp_data.time.hour, tmp_data.time.min, tmp_data.time.sec);
		}
	}

	fclose(fp);

	return num;
}					

/*
int check_data(WaterData** waterdata, Time* lower_limit, Time* upper_limit)
{
	int num = 0;
	FILE* fp = NULL;
	WaterData* tmp_data = NULL;
	int count = 0;			//确定文件指针偏移量
	int i;
	int flag = 0;			//是否读取到相应时间段中数据的标志

	if ((fp = fopen(".\data.dat", "rb")) == NULL)
	{
		fprintf(stderr, "fopen()failed.");
		exit(1);
	}

	while (!feof(fp))
	{
		if ((tmp_data = (WaterData*)malloc(sizeof(WaterData))) == NULL)
		{
			fprintf(stderr, "Error:Allocate memory for waterdata.");
			exit(1);
		}
	
		fread(tmp_data, sizeof(WaterData), 1, fp);
		if (compare_time(tmp_data->time, *(upper_limit)) == 1 && compare_time(tmp_data->time, *(lower_limit)) == 0)
		{
			if (flag == 0)
				flag = 1;
			num++;
		}
		else
		{
			if (flag == 1)
				break;
			count++;
		}
	}
	
	fclose(fp);

	if ((*(waterdata) = (WaterData*)malloc(sizeof(WaterData) * num)) == NULL)
	{
		fprintf(stderr, "fopen()failed");
		exit(1);
	}
	
	if ((fp = fopen("boat\database\history\data.dat", "rb")) == NULL)
	{
		fprintf(stderr, "fopen()failed");
		exit(1);
	}

	fseek(fp, num * sizeof(WaterData), SEEK_SET);

	for (i = 0; i < num; i++)
	{
		fread(waterdata[0], sizeof(WaterData), num, fp);
	}

	fclose(fp);

	return num;
}
*/


/*
CSV_Data read_csv_data(void)
{
	int i;
	FILE* fp = NULL;
	char row[200];
	char* headers[10];
	CSV_Data csv_data = NULL;

	if ((csv_data = malloc(sizeof(struct CSV_Node))) == NULL)	///内存分配失败
	{
		printf("No enough memeory to allocate!!");
		exit(EXIT_FAILURE);
	}

	if ((fp = fopen("../database/dataset/waterdata.csv", "r")) == NULL)//文件打开失败
	{
		fprintf(stderr, "fopen() failed.\n");
		exit(EXIT_FAILURE);
	}
	fgets(row, 200, fp);
	for (i = 0; i < 10; i++)
	{
		headers[i] = get_field(strdup(row), i + 1);
	}
	
	if (fgets(row, 200, fp) != NULL)
	{
		write_to_struct(&csv_data->indicator, i, row);
	}
	
	fclose(fp);
	return csv_data;
}

CSV_Data batch_read_csv_data(int num)
{
	CSV_Data head = NULL;
	CSV_Data tmp = NULL;
	int i, j;
	FILE* fp = NULL;
	char row[200];

	if ((fp = fopen("../database/dataset/waterdata.csv", "r")) == NULL)	//文件打开失败
	{
		fprintf(stderr, "fopen()failed.\n");
		exit(EXIT_FAILURE);
	}
	fgets(row, 200, fp);
	tmp = head;
	for (i = 0; i < num; i++)
	{
		if (fgets(row, 200, fp) != NULL)
		{
			if ((tmp = malloc(sizeof(struct CSV_Node))) == NULL)
			{
				printf("No enough memory to allocate!!");
				exit(EXIT_FAILURE);
			}
			for (j = 1; j <= 10; j++)
			{
				write_to_struct(&tmp->indicator, i, row);
			}
			tmp = tmp->next;
		}
		else
			return NULL;
	}
	tmp = NULL;
	return head;
}
/*
//从csv文件中随机读取指定行数的记录
CSV_Data random_read_csv_data(int num)
{
	CSV_Data head = NULL;
	CSV_Data tmp = NULL;
	int i, j;
	FILE* fp = NULL;
	char row[200];
	int* index = NULL;
	srand((unsigned int)time(0));
	if ((fp = fopen("../database/dataset/waterdata.csv", "r")) == NULL)
	{
		fprintf(stderr, "fopen()failed.\n");
		exit(EXIT_FAILURE);
	}
	fgets(row, 200, fp);	//读取掉列名称
	tmp = head;
	random_index(index, num, 1, MAX_CSV_LINE);	//获取随机序列
	for (i = 0; i < num; i++)
	{
		read_csv_line(index[i], tmp);
		tmp = tmp->next;
	}
	fclose(fp);
	
	tmp = NULL;
	return head;
}
*/
void random_index(int * index, int num, int min, int max)
{
	int flag; int i, j;
	int tmp;
	int count = 0;
	srand((unsigned int)time(0));
	for (i = 0; i < num; i++)
	{
		while (1)
		{
			flag = 0;
			tmp = rand() % (max - min + 1) + min;
			for (j = 0; j < count; j++)
			{
				if (index[j] == tmp)
				{
					flag = 1;	
					break;
				}
			}
			if (flag == 0)
			{
				index[count++] = tmp;
				break;
			}
		}
	}
}
/*
//读取csv文件中指定的某一行(从数据行开始计)
void read_csv_line(int line,CSV_Data csv_data)
{
	FILE* fp = NULL;
	int i;
	char row[200];

	if (line > MAX_CSV_LINE)
		line = MAX_CSV_LINE;

	if ((fp = fopen("boat\database\dateset\waterdata.csv", "r")) == NULL)	//文件打开失败
	{
		fprintf(stderr, "fopen()failed");
		exit(EXIT_FAILURE);
	}
	fgets(row, 200, fp);	//读取掉列名称
	for (i = 1; i <= line; i++)
	{
		if (fgets(row, 200, fp) == NULL)
		{
			fprintf(stderr, "Fail to get csv data!!");
			exit(EXIT_FAILURE);
		}
	}
	if ((csv_data = malloc(sizeof(struct CSV_Node)) == NULL))
	{
		printf("No enough memory to allocate!!");
		exit(EXIT_FAILURE);
	}
	csv_data->next = NULL;
	for (i = 1; i <= 10; i++)
	{
		write_to_struct(&csv_data->indicator, i, row);
	}
}
*/
void write_to_struct(Indicator* indicator, int index, char* str)
{
	switch (index)
	{
	case 1:
		indicator->category = atoi(get_field(strdup(str), 1));
		break;
	case 2:
		indicator->temperature = atof(get_field(strdup(str), 2));
		break;
	case 3:
		indicator->ph = atof(get_field(strdup(str), 3));
		break;
	case 4:
		indicator->oxygen = atof(get_field(strdup(str), 4));
		break;
	case 5:
		indicator->cu = atof(get_field(strdup(str), 5));
	case 6:
		indicator->zn = atof(get_field(strdup(str), 6));
		break;
	case 7:
		indicator->kmno4 = atof(get_field(strdup(str), 7));
		break;
	case 8:
		indicator->nh4 = atof(get_field(strdup(str), 8));
		break;
	case 9:
		indicator->totalP = atof(get_field(strdup(str), 9));
		break;
	case 10:
		indicator->totalN = atof(get_field(strdup(str), 10));
		break;
	}
}

char* get_field(char* line, int num)
{
	char* tok;
	char* result;
	int i;
	tok = strtok(line, ",");
	for (i = 1; i != num; i++) {
		tok = strtok(NULL, ",");
	}
	result = remove_quoted(tok);

	return result;
}

char* remove_quoted(char* str)
{
	int i;
	int length = strlen(str);
	char* result = malloc(length + 1);
	int index = 0;
	for (i = 0; i < length; i++) {
		if (str[i] != '\"') {
			result[index] = str[i];
			index++;
		}
	}
	result[index] = '\0';
	return result;
}

void print_indicator_info(Indicator indicator)
{
	printf("%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",
		indicator.category, indicator.temperature, indicator.ph, indicator.oxygen, indicator.cu,
		indicator.zn, indicator.kmno4, indicator.nh4, indicator.totalP, indicator.totalN);
}

/*
//从csv文件中随机读取指定行数的记录
void random_read_csv_data(int num, Indicator* indicators)
{
	int index[15];
	//char row[50];
	FILE* fp = NULL;
	int i;
	if ((fp = fopen("boat\datebase\dataset\waterdata.csv", "r")) == NULL)
	{
		fprintf(stderr, "fopen()failed.\n");
		exit(1);
	}
	//fgets(row, 50, fp);		//读取掉列名称
	random_index(index, num, 1, MAX_CSV_LINE);
	for (i = 0; i < num; i++)
	{
		read_csv_line(index[i], &indicators[i]);
	}

	fclose(fp);
}
*/

void random_read_csv_data(int num, Indicator* indicators)
{
	int index[15];
	//char* row = NULL;
	//static char row[100];
	//char far* row = NULL;
	char row[200];
	FILE* fp = NULL;
	int count = 0;
	int i, j;
	/*
	if ((row = (char far*)malloc(200 * sizeof(char))) == NULL)
	{
		fprintf(stderr, "Error:Fail to allocate memory.");
		exit(1);
	}
	*/
	/*
	if ((row = (char*)malloc(100 * sizeof(char))) == NULL)
	{
		fprintf(stderr, "fopen()failed");
		exit(1);
	}
	*/
	if ((fp = fopen("../database/dataset/waterdata.csv", "r")) == NULL)
	{
		fprintf(stderr, "fopen()failed.\n");
		exit(1);
	}
	fgets(row, 100, fp);		//读取掉列名称
	random_index(index, num, 1, MAX_CSV_LINE);
	for (i = 0; i < MAX_CSV_LINE && count < num; i++)
	{
		fgets(row, 100, fp);
		if ((i + 1) == index[count])
		{
			for (j = 1; j <= 10; j++)
			{
				write_to_struct(&indicators[count], j, row);
			}
			count++;
		}
	}
	//farfree(row);
	//free(row);
	fclose(fp);
}

void read_csv_line(int line, Indicator* indicator)
{
	FILE* fp = NULL;
	int i;
	char row[100];

	if (line > MAX_CSV_LINE)
		line = MAX_CSV_LINE;

	if ((fp = fopen("boat\database\dataset\waterdata.csv", "r")) == NULL)
	{
		fprintf(stderr, "fopen()failed");
		exit(1);
	}
	fgets(row, 100, fp);
	for (i = 1; i <= line; i++)
	{
		if (fgets(row, 100, fp) == NULL)
		{
			fprintf(stderr, "Fail to get csv data!!");
			exit(1);
		}
	}
	for (i = 1; i <= 10; i++)
	{
		write_to_struct(indicator, i, row);
	}
	fclose(fp);
}

/*
void free_csv_data(Data head)
{
	Data tmp = head;
	head = NULL;
	while (tmp != NULL)
	{
		free(tmp->waterdata);
		tmp = tmp->next;
	}
}*/
/*
//生成随机浮点数
void rand_doubles(double* rand_results, int num, double min, double max)
{
	int i;
	srand((unsigned int)time(0));
	for (i = 0; i < num; i++)
	{
		rand_results[i] = (rand() * (max - min) / RAND_MAX) + min;
	}
}
*/

/*
//生成随机浮点数
void rand_doubles(double* rand_results, int num, double min, double max)
{
	int bound = (((int)(max - min)) * 10000);
	int i;
	double tmp;

	for(i = 0;i < num;i++)
	{
		tmp = ((double)(rand() % bound)) / 10000.0;
		rand_results[i] = tmp + min;
	}
}
*/

/*
//生成随机浮点数
void rand_doubles(double* rand_results, int num, double min, double max)
{
	//获取步长
	double step = (max - min) / (num + 2);
	int i;
	double coefficent[5] = { 0.5, 0.80, 0.62, 0.72, 0.92 };
	double c2[5] = {1.71, 1.42, 1.54, 2.13, 1.7};
	int index;

	srand((unsigned)time(NULL));
	for (i = 0; i < num; i++)
	{
		rand_results[i] = min + step * (i + 1);
	}
	
	if (num > 4)
	{
		for (i = 0;i < 3;i++)
		{
			index = rand() % 5;
			rand_results[i] *= c2[index];
		}
		for (i =  4; i < num; i++)
		{
			index = rand() % 5;
			rand_results[i] *= coefficent[index];
		}
	}
}
*/

//生成随机浮点数
void rand_doubles(double* rand_results, int num, double min, double max)
{
	int i;
	srand((unsigned int)time(0));
	for (i = 0; i < num; i++)
	{
		rand_results[i] = (rand() * (max - min) / RAND_MAX) + min;
	}
}

/*
//生成随机浮点数
void rand_doubles(double* rand_results, int num, double min, double max)
{
	int i;
	double temp_result;
	int posi_values[Precision];
	int j;

	srand((unsigned)time(NULL));

	for (i = 0; i < num; i++)
	{	
		temp_result = 0;
		for (j = 0; j < Precision; i++)
		{
			posi_values[j] = rand() % 10;
			temp_result += (double)posi_values[j] / pow(10, j + 1);
		}
		rand_results[i] = temp_result * (max - min) + min;
	}
}
*/
//生成随机数据
void rand_indicators(double* rand_results, int num, double* mins, double* max)
{
	int i;
	srand((unsigned int)time(0));

	for (i = 0; i < num; i++)
	{
		rand_results[i] = (rand() * (max[i] - mins [i]) / RAND_MAX) + mins[i];
	}
}

//生成随机数据
void rand_data(Indicator* indicators, int num)
{
	int i;
	double tmp[20];
	int j;
	int temp;		//温度的界限值
	double rand_bound[2];
	srand((unsigned)time(0));

	temp = rand() % 7 + 8;
	rand_doubles(tmp, num, (double)(temp-2) , (double)(temp + 2));
	for (i = 0; i < num; i++)
	{
		indicators[i].temperature = tmp[i];
	}
		

	rand_doubles(rand_bound , 2, -0.5, 0.5);
	rand_doubles(tmp, num, 6 + rand_bound[0], 8+ rand_bound[1]);
	for (i = 0; i < num; i++)
	{
		indicators[i].ph = tmp[i];
	}

	rand_doubles(rand_bound, 2, -1, 1);
	rand_doubles(tmp, num, 5 + rand_bound[0], 7.5 + rand_bound[1]);
	for (i = 0; i < num; i++)
	{
		indicators[i].oxygen = tmp[i];
	}

	rand_doubles(rand_bound, 2, -0.005, 0.005);
	rand_doubles(tmp, num, 0.01 + rand_bound[0], 1.2 + rand_bound[1]);
	for (i = 0; i < num; i++)
	{
		indicators[i].cu = tmp[i];
	}

	rand_doubles(rand_bound, 2, -0.005, 0.005);
	rand_doubles(tmp, num, 0.05 + rand_bound[0], 2.0 + rand_bound[1]);
	for (i = 0; i < num; i++)
	{
		indicators[i].zn = tmp[i];
	}
	rand_doubles(rand_bound, 2, -0.5, 0.5);
	rand_doubles(tmp, num, 2 + rand_bound[0], 15 + rand_bound[1]);
	for (i = 0; i < num; i++)
	{
		indicators[i].kmno4 = tmp[i];
	}

	rand_doubles(rand_bound, 2, -0.005, 0.005);
	rand_doubles(tmp, num, 0.015 + rand_bound[0], 2.0 + rand_bound[1]);
	for (i = 0; i < num; i++)
	{
		indicators[i].nh4 = tmp[i];
	}

	rand_doubles(rand_bound, 2, -0.005, 0.005);
	rand_doubles(tmp, num, 0.01 + rand_bound[0], 0.2 + rand_bound[1]);
	for (i = 0; i < num; i++)
	{
		indicators[i].totalP = tmp[i];
	}

	rand_doubles(rand_bound, 2, -0.005, 0.005);
	rand_doubles(tmp, num , 0.02 + rand_bound[0], 2.0 + rand_bound[1]);
	for (i = 0; i < num; i++)
	{
		indicators[i].totalN = tmp[i];
	}

}

/*
//将标志数据生成标志设为0
void reset_index(void)
{
	FILE* fp = NULL;
	if ((fp = fopen("../database/index/classify.txt", "wt")) == NULL)
	{
		fprintf(stdout, "fopen(classify.txt) failed.");
		exit(1);
	}

	fprintf(fp, "%d", 0);
	fclose(fp);

	if ((fp = fopen("../database/index/evalu.txt", "wt")) == NULL)
	{
		fprintf(stdout, "fopen(evalu.txt) failed.");
		exit(1);
	}

	fprintf(fp, "%d", 0);
	fclose(fp);
}
void one_index(void)
{
	FILE* fp = NULL;
	if ((fp = fopen("../database/index/classify.txt", "wt")) == NULL)
	{
		fprintf(stdout, "fopen(classify.txt) failed.");
		exit(1);
	}

	fprintf(fp, "%d", 1);
	fclose(fp);

	if ((fp = fopen("../database/index/evalu.txt", "wt")) == NULL)
	{
		fprintf(stdout, "fopen(evalu.txt) failed.");
		exit(1);
	}

	fprintf(fp, "%d", 1);
	fclose(fp);
}

//将标志数据生成标志设为1 1-已经生成 0-未生成
int set_index(void)
{
	FILE* fp = NULL;
	int flag;

	if ((fp = fopen("../database/index/classify.txt", "rt")) == NULL)
	{
		fprintf(stdout, "fopen(classify.txt) failed.");
		exit(1);
	}
	fscanf(fp, "%d", &flag);
	if (flag == 1)
		return 1;
	fclose(fp);
	one_index();
	return 0;
}
*/