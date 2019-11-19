#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<io.h>
#include<time.h>

// 结构体
struct fre_word
{
	int num;
	char a[18];
};
/*****************快速排序************/
void quick(struct fre_word *f, int i, int j)
{
	int m, n,temp,k;
	char b[18];
	m = i;
	n = j;
	k = f[(i + j) / 2].num;                            //选取的参照
	do
	{
		while (f[m].num>k&&m<j) m++;             // 从左到右找比k小的元素
		while (f[n].num<k&&n>i) n--;             // 从右到左找比k大的元素
		if (m <= n)
		{                                       //若找到且满足条件，则交换
			temp = f[m].num;
			strcpy(b, f[m].a);
			f[m].num = f[n].num;
			strcpy(f[m].a, f[n].a);
			f[n].num = temp;
			strcpy(f[n].a, b);
			m++;
			n--;
		}
	} while (m <= n);
	if (m<j) quick(f, m, j);                      //运用递归
	if (n>i) quick(f, i, n);
}
/******************主函数****************/
int main(int argc, char *argv[])
{

	struct _finddata_t fa;
	long fHandle;
	FILE *fp;
	void quick(struct fre_word *f, int i, int j);
	int i, j = 0, m, n, flag, p = 1;
	int mode,count=0;                                                         //mode为不同功能,为1时输入单个文件
	char filename[20], b[18], ch;
	struct fre_word *w;
	w = (struct fre_word *)malloc(50000 * p * sizeof(struct fre_word));//给结构体分配初始内存，50000可打开650kb左右的文件
    /****************读取文本文件****************************/
    printf("输入读入文件的名字：");
    scanf("%s", filename);                                     //输入需要统计词频的文件名
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("无法打开文件\n");
        exit(0);
    }
    // 开始时间
    clock_t start,finish;
    double time;
    start=clock();
    /****************将单词出现次数设置为1****************************/
    for (i = 0; i < 500; i++)
    {
        (w + i)->num = 1;
    }

    /****************单词匹配****************************************/
    i = 0;
    while (!feof(fp))//文件尚未读取完毕
    {
        ch = fgetc(fp);
        (w + i)->a[j] = '\0';
        if (ch >= 65 && ch <= 90 || ch >= 97 && ch <= 122)                            //ch若为字母则存入
        {
            (w + i)->a[j] = ch;
            j++;
            flag = 0;                                                  //设标志位判断是否存在连续标点或者空格
        }
        else if (!(ch >= 65 && ch <= 90 || ch >= 97 && ch <= 122) && flag == 0)       //ch若不是字母且上一个字符为字母
        {
            i++;
            j = 0;
            flag = 1;
            for (m = 0; m < i - 1; m++)                                    //匹配单词，若已存在则num+1
            {
                if (stricmp((w + m)->a, (w + i - 1)->a) == 0)
                {
                    (w + m)->num++;
                    i--;
                }
            }
        }
        /****************动态分配内存****************************************/
        if (i == (p * 500))                                                      //用i判断当前内存已满
        {
            p++;
            w = (struct fre_word*)realloc(w, 500 * p*(sizeof(struct fre_word)));
            for (n = i; n <= 500 * p; n++)                                           //给新分配内存的结构体赋初值
                (w + n)->num = 1;
        }
    }
    i = i - 2;
    quick(w, 0, i);
    //输出
    FILE *fp_1;
    fp_1=fopen("out.txt","w");
    printf("不重复的单词数：%d\n",i);
    fprintf(fp_1,"不重复的单词数：%d\n",i);
    if(fp_1==NULL)
    {
        printf("cannot load out.txt...\n");
        exit(-1);
    }
    for (n = 0; n <= i; n++)
    {
        printf("文档中出现的单词：");
        fprintf(fp_1,"文档中出现的单词：");
        printf("%s,", (w + n)->a);
        fprintf(fp_1,"%s,",(w + n)->a);
        printf("其出现次数为:");
        fprintf(fp_1,"其出现次数为:");
        printf("%d\n", (w + n)->num);
        fprintf(fp_1,"%d;\n",(w + n)->num);
    }
    //结束时间
    finish=clock();
    time=(double)(finish-start)/CLOCKS_PER_SEC;
    fprintf(fp_1,"处理时间=%lf",time);
    printf("处理时间=%lf\n",time);

    fclose(fp);
    return 0;
    free(w);
}
