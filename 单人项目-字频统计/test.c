#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<io.h>
#include<time.h>

// �ṹ��
struct fre_word
{
	int num;
	char a[18];
};
/*****************��������************/
void quick(struct fre_word *f, int i, int j)
{
	int m, n,temp,k;
	char b[18];
	m = i;
	n = j;
	k = f[(i + j) / 2].num;                            //ѡȡ�Ĳ���
	do
	{
		while (f[m].num>k&&m<j) m++;             // �������ұ�kС��Ԫ��
		while (f[n].num<k&&n>i) n--;             // ���ҵ����ұ�k���Ԫ��
		if (m <= n)
		{                                       //���ҵ��������������򽻻�
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
	if (m<j) quick(f, m, j);                      //���õݹ�
	if (n>i) quick(f, i, n);
}
/******************������****************/
int main(int argc, char *argv[])
{

	struct _finddata_t fa;
	long fHandle;
	FILE *fp;
	void quick(struct fre_word *f, int i, int j);
	int i, j = 0, m, n, flag, p = 1;
	int mode,count=0;                                                         //modeΪ��ͬ����,Ϊ1ʱ���뵥���ļ�
	char filename[20], b[18], ch;
	struct fre_word *w;
	w = (struct fre_word *)malloc(50000 * p * sizeof(struct fre_word));//���ṹ������ʼ�ڴ棬50000�ɴ�650kb���ҵ��ļ�
    /****************��ȡ�ı��ļ�****************************/
    printf("��������ļ������֣�");
    scanf("%s", filename);                                     //������Ҫͳ�ƴ�Ƶ���ļ���
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("�޷����ļ�\n");
        exit(0);
    }
    // ��ʼʱ��
    clock_t start,finish;
    double time;
    start=clock();
    /****************�����ʳ��ִ�������Ϊ1****************************/
    for (i = 0; i < 500; i++)
    {
        (w + i)->num = 1;
    }

    /****************����ƥ��****************************************/
    i = 0;
    while (!feof(fp))//�ļ���δ��ȡ���
    {
        ch = fgetc(fp);
        (w + i)->a[j] = '\0';
        if (ch >= 65 && ch <= 90 || ch >= 97 && ch <= 122)                            //ch��Ϊ��ĸ�����
        {
            (w + i)->a[j] = ch;
            j++;
            flag = 0;                                                  //���־λ�ж��Ƿ�������������߿ո�
        }
        else if (!(ch >= 65 && ch <= 90 || ch >= 97 && ch <= 122) && flag == 0)       //ch��������ĸ����һ���ַ�Ϊ��ĸ
        {
            i++;
            j = 0;
            flag = 1;
            for (m = 0; m < i - 1; m++)                                    //ƥ�䵥�ʣ����Ѵ�����num+1
            {
                if (stricmp((w + m)->a, (w + i - 1)->a) == 0)
                {
                    (w + m)->num++;
                    i--;
                }
            }
        }
        /****************��̬�����ڴ�****************************************/
        if (i == (p * 500))                                                      //��i�жϵ�ǰ�ڴ�����
        {
            p++;
            w = (struct fre_word*)realloc(w, 500 * p*(sizeof(struct fre_word)));
            for (n = i; n <= 500 * p; n++)                                           //���·����ڴ�Ľṹ�帳��ֵ
                (w + n)->num = 1;
        }
    }
    i = i - 2;
    quick(w, 0, i);
    //���
    FILE *fp_1;
    fp_1=fopen("out.txt","w");
    printf("���ظ��ĵ�������%d\n",i);
    fprintf(fp_1,"���ظ��ĵ�������%d\n",i);
    if(fp_1==NULL)
    {
        printf("cannot load out.txt...\n");
        exit(-1);
    }
    for (n = 0; n <= i; n++)
    {
        printf("�ĵ��г��ֵĵ��ʣ�");
        fprintf(fp_1,"�ĵ��г��ֵĵ��ʣ�");
        printf("%s,", (w + n)->a);
        fprintf(fp_1,"%s,",(w + n)->a);
        printf("����ִ���Ϊ:");
        fprintf(fp_1,"����ִ���Ϊ:");
        printf("%d\n", (w + n)->num);
        fprintf(fp_1,"%d;\n",(w + n)->num);
    }
    //����ʱ��
    finish=clock();
    time=(double)(finish-start)/CLOCKS_PER_SEC;
    fprintf(fp_1,"����ʱ��=%lf",time);
    printf("����ʱ��=%lf\n",time);

    fclose(fp);
    return 0;
    free(w);
}
