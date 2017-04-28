/*************************************************************************
	> File Name: Options.h
	> Author: 
	> Mail: 
	> Created Time: 2016年06月23日 星期四 16时07分30秒
 ************************************************************************/

Node *add_user(Node *temp,int amount);

Node *my_trade(int large)
{
    int number;//要进行的选项
    int people;//要添加的账户人数
    int Out_money;//取钱数
    char Bank_figure[N];//输入的银行卡号
    Node *tmp,*loop=NULL;
    FILE *fp;
    char fp_name[N];

    printf("请输入要添加进的文件名：\n");
    scanf("%s",fp_name);
    
    fp=fopen(fp_name,"r");

    if(fp==NULL)
    {
        printf("系统中没有账户文件！请先新建账户文件！\n");
        printf("请按下任意键返回到登陆界面！\n");

        while(getchar()!='\n')
            continue;

        getchar();

        my_register_1();
    }
    else
    {
        int number=1;

        loop=my_read_file(large);

        if(loop==NULL)
        {
            printf("银行里没有任何用户信息！\n");
            printf("请添加银行用户信息！\n");
            printf("请按下任意键进行下一步！\n");

            while(getchar()!='\n')
                continue;

            getchar();
        }

        my_register_3();
        
        scanf("%d",&number);

        if(number==1)
        {
            printf("请输入要添加用户的个数:\n");

            scanf("%d",&people);
        
            while(people<=0)
            {
                printf("请输入的用户数大于0！请再输入一次！\n");
                scanf("%d",&people);
            }

            if(people>0)
            {
                tmp=add_user(loop,people);
            }

            return tmp;
        }

        if(number==2)
        {
            tmp=loop;

            if(loop==NULL)
            {
                printf("此时银行账户文件中没有任何用户！\n");
                printf("请按下任意键返回到登陆界面，先添加新用户！\n");

                while(getchar()!='\n')
                    continue;

                getchar();

                my_register_1();
            }
            else
            {
                printf("请输入您的银行卡号：\n");
                scanf("%s",Bank_figure);

                if(loop!=NULL)
                {
                    while(loop!=NULL&&strcmp(loop->information.Bank_number,Bank_figure)!=0)
                    {
                        loop=loop->next;
                    }

                    if(loop==NULL)
                    {
                        printf("您输入的银行帐户资料查找不到！\n");
                        printf("请按下任意键返回到登陆界面！\n");

                        while(getchar()!='\n')
                            continue;

                        getchar();

                        my_register_1();
                    }
                    else
                    {
                        printf("请输入您要取的钱数：\n");

                        while(scanf("%d",&Out_money)!=1)
                        {
                            printf("您输入的数字有误！\n请重新输入！\n");
                            scanf("%d",&Out_money);
                        }

                        loop->information.start_money=loop->information.start_money-Out_money;

                        printf("您已经成功取出%d元，您的账户中还剩下%d元！\n",Out_money,loop->information.start_money);

                        printf("请按下任意键返回到登陆界面！\n");

                        while(getchar()!='\n')
                            continue;

                        getchar();

                        my_register_1();
            
                        return tmp;
                    }
                }
            }
        }    
    }
}

Node *add_user(Node *temp,int amount)
{
    int figure;
    char bank_number[N];

    my_register_2();

    scanf("%d",&figure);

    Node *p,*q,*phead=NULL;
    int i;

    p=(Node *)malloc(sizeof(Node));
    if(p==NULL)
        exit(1);

    printf("请输入要添加用户的姓名，性别，年龄，身份证号，银行卡号，要存的钱数，存储类型，存储时间（月）：\n");
    scanf("%s%s%d%s%s%d%s%d",p->name,p->sex,&p->age,p->ID_card,p->information.Bank_number,&p->information.start_money\
         ,p->information.save_sort,&p->information.month);

    phead=p;

    for(i=0;i<amount-1;i++)
    {
        q=(Node *)malloc(sizeof(Node));
        if(p==NULL)
            exit(1);

        scanf("%s%s%d%s%s%d%s%d",q->name,q->sex,&q->age,q->ID_card,q->information.Bank_number,&q->information.start_money\
            ,q->information.save_sort,&q->information.month);

        q->next=NULL;
        p->next=q;
        p=q;
    }

    Node *pre,*Phead;

    if(figure==1)
    {
        pre=temp;
        Phead=pre;

        while(temp!=NULL)
        {
            pre=temp;
            temp=temp->next;
        }

        pre->next=phead;
    }

    if(figure==2)
    {
        Phead=temp;

        printf("您将要把这些用户添加到您指定的位置后面！\n");
        printf("请输入您要指定的位置（指定位置上前一个用户的银行卡号）：\n");

        scanf("%s",bank_number);

        while(strcmp(bank_number,temp->information.Bank_number)!=0)
        {
            temp=temp->next;
        }
        
        p->next=temp->next;
        temp->next=phead;
    }

    if(figure==3)
    {
        p->next=temp;
        Phead=phead;
    }
    
    printf("您成功的添加了%d个用户的资料！\n\n",amount);
    printf("请按下任意键返回到登陆界面！\n");

    while(getchar()!='\n')
        continue;

    getchar();

    my_register_1();

    return Phead;
}
