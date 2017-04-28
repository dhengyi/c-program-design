/*************************************************************************
	> File Name: 哈弗曼编码译码器.c
	> Author: Paranoid
	> Mail: championhengyi@gmail.com
	> Created Time: 2016年12月25日 星期日 17时19分56秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define N 256
#define LEAVECODE 256
#define CODE 2* LEAVECODE -1
#define MAX 30000
#define DEPTH LEAVECODE -1

typedef struct{                               //哈弗曼树结点的数据结构
    int weight;
    int parent, lchild, rchild;
}HUFFMAN_CODE;

char file_name[N];                            //源文件名是全局变量
unsigned long int od_file_size;                             //临时二进制文件的大小
HUFFMAN_CODE huffman_code[CODE];              //哈弗曼树

int interface();
void code();
void decode();
void R_file(unsigned char string[]);
void Huffman_tree(unsigned char leave_code[]);
void sele_ct(int *s1, int *s2);
void Create_Code(char *str_code[]);
void Tmp_file(char *str_code[]);
void Cut_file();
void revert();
void Source_file();

int interface()      //界面
{
    int number;

    printf("1.编码\n");
    printf("2.译码\n");

    printf("请输入您的选项:\n");
    scanf("%d", &number);

    return number;
}

void code()                    //编码
{
    int i;
    unsigned char leave_code[LEAVECODE];
    char *str_code[LEAVECODE];
    HUFFMAN_CODE huffman_code[CODE];

    for(i = 0; i < LEAVECODE; i++)          //初始化叶子节点权值
    {
        leave_code[i] = 0;
    }

    for(i = 0; i < LEAVECODE; i++)          //初始化叶子节点编码
    {
        str_code[i] = NULL;
    }

    R_file(leave_code);            //读文件，将字符权值记录下来

    Huffman_tree(leave_code);      //拥有字符权值，构建哈弗曼树

    Create_Code(str_code);                  //构造每个字符编码

    Tmp_file(str_code);                           //创建临时文件，将编码写入文件之中

    Cut_file();                                   //压缩文件
}

void R_file(unsigned char leave_code[])     //读文件，将字符权值记录下来
{
    int fd;
    int ret;
    unsigned char tmp_str;

    printf("请输入您要进行编码的文件名:\n");
    scanf("%s", file_name);

    if((fd = open(file_name, O_RDONLY)) == -1)
    {
        printf("进行编码的文件打开失败\n");
        exit(1);
    }

    while((ret = read(fd, &tmp_str, 1)) > 0)       //每次从文件中读一个字节，直到文件读完为止
    {
        leave_code[tmp_str]++;                     //记录文件中字符的权值
    }
}

void Huffman_tree(unsigned char leave_code[])              //构建哈弗曼树
{
    int i;
    int s1, s2;

    for(i = 0; i < LEAVECODE; i++)                                  //初始化叶子节点
    {
        huffman_code[i].weight = leave_code[i];
        huffman_code[i].parent = 0;
        huffman_code[i].lchild = 0;
        huffman_code[i].rchild = 0;
    }

    for(i = LEAVECODE; i < CODE; i++)                               //初始化构造节点
    {
        huffman_code[i].weight = 0;
        huffman_code[i].parent = 0;
        huffman_code[i].lchild = 0;
        huffman_code[i].rchild = 0;
    }

    for(i = LEAVECODE; i < CODE; i++)                               //构建新结点
    {
        s1 = -1; s2 = -1;
        sele_ct(&s1, &s2);                            //在叶子结点中找到最小值和次小值
        if(s2 == -1 || s1 == -1)                                    //若次小值没被找到，则哈弗曼树建立完成
        {
            break;
        }
        
        huffman_code[i].weight = huffman_code[s1].weight + huffman_code[s2].weight;
        huffman_code[i].lchild = s1;
        huffman_code[i].rchild = s2;
        huffman_code[s1].parent = i;
        huffman_code[s2].parent = i;
    }
}

void sele_ct(int *s1, int *s2)         //在叶子结点中找到最小值和次小值
{
    int i;
    int min = MAX, minor = MAX;

    for(i = 0; i < CODE; i++)                                  //最小值
    {
        if(huffman_code[i].weight != 0 && huffman_code[i].parent == 0)
        {
            if(min > huffman_code[i].weight)
            {
                min = huffman_code[i].weight;
                *s1 = i;
            }
        }
    }

    for(i = 0; i < CODE; i++)                                  //次小值
    {
        if(huffman_code[i].weight != 0 && huffman_code[i].parent == 0 && i != *s1)
        {
            if(minor > huffman_code[i].weight)
            {
                minor = huffman_code[i].weight;
                *s2 = i;
            }
        }
    }

    printf("%d, %d\n", *s1, *s2);                              //打印每次找到的最小值和次小值的位置
}

void Create_Code(char *str_code[])        //构造每个字符的编码
{
    char *cd;
    int start;
    int i, c, p;

    cd = (char *)malloc(LEAVECODE * sizeof(char));
    cd[LEAVECODE -1] = '\0';

    for(i = 0; i < LEAVECODE; i++)
    {
        if(huffman_code[i].weight == 0)
            continue;

        start = LEAVECODE -1;
        c = i;                               //当前结点
        p = huffman_code[i].parent;          //双亲结点

        while(p != 0)                        //双亲结点不为0
        {
            --start;

            if(huffman_code[p].lchild == c)
                cd[start] = '0';

            if(huffman_code[p].rchild == c)
                cd[start] = '1';

            c = p;
            p = huffman_code[p].parent;
        }

        str_code[i] = (char *)malloc((LEAVECODE -start)*sizeof(char));      //申请编码空间
        strcpy(str_code[i], &cd[start]);
    }

    free(cd);
}

void Tmp_file(char *str_code[])                 //创建临时文件，将编码写入文件之中
{
    int fd1, fd2;
    int ret;
    unsigned char tmp_str;
    struct stat buf;

    if((fd1 = open("tmp", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
    {
        printf("建立临时文件失败\n");
        exit(1);
    }

    if((fd2 = open(file_name, O_RDONLY)) == -1)
    {
        printf("打开源文件失败\n");
        exit(1);
    }

    for(int i = 0; i < LEAVECODE; i++)               //打印每个字符的编码
    {
        printf("str_code[%d]: %s\n", i, str_code[i]);
    }

    while((ret = read(fd2, &tmp_str, 1)) == 1)       //每次从文件中读一个字节，直到文件读完为止
    {
        //if(str_code[tmp_str] == NULL)
        //    continue;

        if(write(fd1, str_code[tmp_str], strlen(str_code[tmp_str])) == -1)
        {
            printf("编码写入临时文件失败\n");
            exit(1);
        }
    }

    if(fstat(fd1, &buf) == -1)
    {
        printf("获取编码临时文件属性失败\n");
        exit(1);
    }

    od_file_size = (unsigned long int) buf.st_size;                       //最初的二进制文件大小
    printf("od_file_size: %ld\n", od_file_size);

    if(buf.st_size % 8 != 0)                          //补齐临时文件字节
    {
        for(int i = 0; i < buf.st_size % 8; i++)
        {
            tmp_str = '0';
            if(write(fd1, &tmp_str, 1) == -1)
            {
                printf("补齐临时文件失败\n");
                exit(1);
            }
        }
    }
}

void Cut_file()                         //压缩文件
{
    int fd1, fd2;
    int count;
    unsigned char str = 0;              //将八位二进制转换为一个无符号字节
    unsigned char tmp_str;
    char cut_file_name[N];
    struct stat buf;

    printf("请输入压缩文件名:\n");
    scanf("%s", cut_file_name);

    if((fd1 = open("tmp", O_RDONLY)) == -1)
    {
        printf("打开临时文件失败\n");
        exit(1);
    }

    if(fstat(fd1, &buf) == -1)
    {
        printf("获取临时文件属性失败\n");
        exit(1);
    }

    printf("buf.st_size: %d\n", buf.st_size);           //补齐字节后的文件大小
    count = buf.st_size / 8;                            //记录八位二进制转换为一个无符号字节的次数

    if(lseek(fd1, SEEK_SET, 0) == -1)
    {
        printf("文件指针移动失败\n");
        exit(1);
    }

    if((fd2 = open(cut_file_name, O_CREAT | O_APPEND | O_RDWR, S_IRWXU)) != -1)         //创建压缩文件，向压缩文件中先记录最初二进制文件大小
    {
        if(write(fd2, &od_file_size, sizeof(unsigned long int)) != sizeof(unsigned long int))
        {
            printf("向压缩文件中写入文件大小失败\n");
            exit(1);
        }
    }

    for(int i = 0; i < CODE; i++)                    //向压缩文件中写入哈弗曼树
    {
        if(write(fd2, &huffman_code[i], sizeof(HUFFMAN_CODE)) != sizeof(HUFFMAN_CODE))
        {
            printf("向文件中写入哈弗曼树失败\n");
            exit(1);
        }
    }

    for(int j = 0; j < count; j++)
    {
        str = 0;
        for(int i = 0; i < 8; i++)                   //将8位二进制码转换为一位无符号字节数
        {
            if(read(fd1, &tmp_str, 1) == 1)
            {
                str = str *2 + (tmp_str -48);
            }
        }

        printf("str: %d\n", str);                    //八个二进制转换为一个字节所表示的大小

        if(write(fd2, &str, 1) != 1)
        {
            printf("向压缩文件中写入数据失败\n");
            exit(1);
        }
    }

    if(remove("tmp") == -1)          
    {
        printf("删除临时文件失败\n");
        exit(1);
    }
}

void decode()                  //解压文件
{
    revert();                  //还原文件成二进制文件

    Source_file();             //由二进制文件得到原文件
}

void revert()                  //还原文件成二进制文件
{
    int fd1, fd2;
    int i;
    unsigned char tmp;
    unsigned char str;
    unsigned char string[8];

    printf("请输入要解压缩的文件名:\n");
    scanf("%s", file_name);

    if((fd1 = open(file_name, O_RDONLY)) == -1)
    {
        printf("打开解压缩文件失败\n");
        exit(1);
    }

    if(read(fd1, &od_file_size, sizeof(unsigned long int)) != sizeof(unsigned long int))
    {
        printf("提取原二进制文件大小失败\n");
        exit(1);
    }

    for(i = 0; i < CODE; i++)
    {
        if(read(fd1, &huffman_code[i], sizeof(HUFFMAN_CODE)) != sizeof(HUFFMAN_CODE))
        {
            printf("提取原二进制文件所属哈弗曼树失败\n");
            exit(1);
        }
    }

    if((fd2 = open("tmp", O_CREAT | O_APPEND | O_RDWR, S_IRUSR | S_IWUSR)) == -1)
    {
        printf("建立解压缩临时文件失败\n");
        exit(1);
    }

    while(read(fd1, &str, sizeof(unsigned char)) == 1)
    {
        for(i = 7; i >= 0; i--)
        {
            tmp = str % 2;                 //得到二进制字符
            string[i] = tmp +48;
            str = str / 2;
        }

        if(write(fd2, string, 8) != 8)     //将二进制字符写入压缩临时文件之中
        {
            printf("二进制字符写入压缩临时文件失败\n");
            exit(1);
        }
    }
}

void Source_file()             //由二进制文件得到原文件
{
    int fd1, fd2;
    int foot, current;
    char source_file_name[N];
    unsigned char tmp_str;
    unsigned char str;
    int i;
    HUFFMAN_CODE root;

    printf("请输入解压后的文件名:\n");
    scanf("%s", source_file_name);

    if((fd1 = open("tmp", O_RDONLY)) == -1)
    {
        printf("打开解压缩临时二进制文件失败\n");
        exit(1);
    }

    if((fd2 = open(source_file_name, O_CREAT | O_APPEND | O_RDWR, S_IRUSR | S_IWUSR)) == -1)
    {
        printf("建立源文件失败\n");
        exit(1);
    }

    for(i = 0; i < CODE; i++)                   //找到根节点
    {
        if(huffman_code[i].weight != 0 && huffman_code[i].parent == 0)
        {
            root = huffman_code[i];
            foot = i;
            current = foot;
            break;
        }
    }

    for(i = 0; i < CODE; i++)                   //打印哈弗曼树
    {
        printf("%d: weight:%d          parent:%d          lchild:%d          rchild:%d ", i, huffman_code[i].weight, huffman_code[i].parent,
              huffman_code[i].lchild, huffman_code[i].rchild);
        printf("\n");
    }

    for(i = 0; i < od_file_size; i++)
    {
        if(read(fd1, &tmp_str, 1) == 1)
        {
            if(tmp_str == '0')
            {
                current = root.lchild;
                root = huffman_code[root.lchild];
            }
            if(tmp_str == '1')
            {
                current = root.rchild;
                root = huffman_code[root.rchild];
            }

            if(root.lchild == 0 && root.rchild == 0)
            {
                str = (unsigned char) current;                       
                printf("str: %c\n", str);                         //得到源文件的源字符 

                if(write(fd2, &str, 1) != 1)
                {
                    printf("向源文件中写入字符失败\n");
                    exit(1);
                }

                root = huffman_code[foot];
            }
        }
    }

    if(remove("tmp") == -1)
    {
        printf("删除解压缩临时文件失败\n");
        exit(1);
    }
}

int main()
{
    int number;

    number = interface();      //界面

    switch(number)
    {
        case 1:
            code();            //编码
        break;

        case 2:
            decode();          //译码
        break;
    }
}
