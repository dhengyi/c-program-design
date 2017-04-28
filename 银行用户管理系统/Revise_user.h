/*************************************************************************
	> File Name: Revise_user.h
	> Author: 
	> Mail: 
	> Created Time: 2016年06月26日 星期日 14时33分09秒
 ************************************************************************/

Node *my_revise(Node *loop)
{
    char bank_number[N];
    Node *Phead;
    int number=0;

    loop=my_read_file(number);
    
    Phead=loop;

    if(loop==NULL)
    {
        printf("银行系统里面此时没有任何账户！\n");
        printf("请按下任意键返回登录界面！\n");

        getchar();

        my_register_1();
    }

    if(loop!=NULL)
    {
        printf("请输入您要修改的账户信息的银行卡号：\n");

        scanf("%s",bank_number);

        while(strcmp(loop->information.Bank_number,bank_number)!=0)
        {
            loop=loop->next;
        }

        printf("请输入您现在要修改的账户信息！\n");
        printf("请输入要修改的用户的姓名，性别，年龄，身份证号，银行卡号，要存的钱数，存储类型，存储时间（月）：\n");

        scanf("%s%s%d%s%s%d%s%d",loop->name,loop->sex,&loop->age,loop->ID_card,loop->information.Bank_number,\
              &loop->information.start_money,loop->information.save_sort,&loop->information.month);

        printf("您成功的修改了用户的资料！\n\n");
        printf("请按下任意键返回登录界面！\n");

        while(getchar()!='\n')
            continue;

        getchar();

        my_register_1();
    }

    return Phead;
}
