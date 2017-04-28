/*************************************************************************
	> File Name: Query_user.h
	> Author: 
	> Mail: 
	> Created Time: 2016年06月27日 星期一 16时32分54秒
 ************************************************************************/

void my_query(Node *loop)
{
    int number=0;

    loop=my_read_file(number);

    if(loop==NULL)
    {
        printf("银行系统里面此时没有任何账户！\n");
        printf("请按下任意键返回到登陆界面！\n");

        getchar();

        my_register_1();
    }
    else
    {
        char bank_number[N];

        printf("请输入您要查询的用户帐号的银行卡号：\n");

        scanf("%s",bank_number);

        while(loop!=NULL && strcmp(loop->information.Bank_number,bank_number)!=0)
        {
            loop=loop->next;
        }

        if(loop!=NULL)
        {
            printf("您查询的用户信息如下：\n");
            printf("=====================================================================================================\n\n\n");
            printf("姓名\t性别\t年龄\t身份证号\t银行卡号\t存钱数\t存储类别\t存储时间（月）\n\n\n");
            printf("%s\t%s\t%d\t%s\t\t%s\t\t%d\t%s\t\t%d\n\n\n",loop->name,loop->sex,loop->age,loop->ID_card,\
                    loop->information.Bank_number,loop->information.start_money,loop->information.save_sort,\
                    loop->information.month);
            printf("=====================================================================================================\n\n\n");

            printf("请按下任意键返回到登陆界面！");

            while(getchar()!='\n')
                continue;

            getchar();

            my_register_1();
        }
        else
        {
            printf("您输入的银行卡号在银行系统中没有对应的账户资料！\n");
            printf("请按下任意键返回到登陆界面！\n");

            while(getchar()!='\n')
                continue;

            getchar();

            my_register_1();
        }
    }
}
