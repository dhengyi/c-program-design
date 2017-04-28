/*************************************************************************
	> File Name: Delete_user.h
	> Author: 
	> Mail: 
	> Created Time: 2016年06月26日 星期日 15时33分27秒
 ************************************************************************/

Node *my_delete(Node *loop)
{
    char bank_number[N];
    int number=0;

    loop=my_read_file(number);

    Node *Phead,*pre;

    Phead=loop;
    pre=loop;

    if(loop==NULL)
    {
        printf("银行系统里面此时没有任何账户！\n");
        printf("请按下任意键返回登陆界面！\n");

        while(getchar()!='\n')
            continue;

        getchar();

        my_register_1();
    }

    if(loop!=NULL)
    {
        printf("请输入您要删除的账户的银行卡号：\n");
        scanf("%s",bank_number);

        if(strcmp(Phead->information.Bank_number,bank_number)==0)
        {
            Phead=Phead->next;
        }
        else
        {
            while(strcmp(loop->information.Bank_number,bank_number)!=0)
            {
                pre=loop;
                loop=loop->next;
            }
            
            pre->next=loop->next;
        }

        printf("您成功的删除了指定的银行账户！\n");
        printf("请按下任意键返回登陆界面！\n");

        while(getchar()!='\n')
            continue;

        getchar();

        my_register_1();
    }

    return Phead;
}
