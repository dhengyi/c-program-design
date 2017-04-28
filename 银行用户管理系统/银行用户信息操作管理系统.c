/*************************************************************************
	> File Name: 银行用户信息操作管理系统.c
	> Author: 
	> Mail: 
	> Created Time: 2016年06月23日 星期四 18时03分24秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 30 

struct storage{
    char Bank_number[N];//银行卡号
    int start_money;
    char save_sort[N];//存的类别
    int month;
};

typedef struct node{
    char name[N];
    char sex[N];
    int age;
    char ID_card[N];
    struct storage information;
    struct node *next;
}Node;

#include"Register.h"
#include"Password.h"
#include"Read_file.h"
#include"Amend_password.h"
#include"Created_user.h"
#include"Add_user.h"
#include"Revise_user.h"
#include"Delete_user.h"
#include"Query_user.h"
#include"File_user.h"
#include"View.h"

int main()
{
    int figure;
    Node *mid=NULL;

    my_password();
    my_register_1();

    while(1)
    {
        
        if(scanf("%d",&figure)==1)
        {

        while(getchar()!='\n')
            continue;

        switch(figure)
        {
            case 1:my_view();break;

            case 2:mid=created_user();break;

            case 3:mid=my_trade(figure);break;

            case 4:mid=my_revise(mid);break;

            case 5:mid=my_delete(mid);break;

            case 6:my_query(mid);break;

            case 7:my_file(mid);break;

            case 8:my_amend_password();break;

            default:printf("退出系统！\n");exit(0);break;
        }

        }

        else
        {
            printf("输入有误！请重新登录系统！\n");
            exit(1);
        }

    }

    return 0;
}

