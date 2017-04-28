/*************************************************************************
	> File Name: Created.h
	> Author: 
	> Mail: 
	> Created Time: 2016年06月24日 星期五 16时08分00秒
 ************************************************************************/

Node *created_user()
{
    Node *p,*q,*phead=NULL;
    int i;
    int number;

    printf("请输入您要创建的用户数：\n");
    scanf("%d",&number);

    while(number<=0)
    {
        printf("请输入用户数大于0！请再输入一次！\n");
        scanf("%d",&number);
    }

    if(number>0)
    {
        printf("请输入要创建的用户的姓名，性别，年龄，身份证号，银行卡号，要存的钱数，存储类型，存储时间（月）：\n");
        p=(Node *)malloc(sizeof(Node));
        if(p==NULL)
            exit(1);

        scanf("%s%s%d%s%s%d%s%d",p->name,p->sex,&p->age,p->ID_card,p->information.Bank_number,&p->\
            information.start_money,p->information.save_sort,&p->information.month);

        p->next=NULL;
        phead=p;

        for(i=0;i<number-1;i++)
        {
            q=(Node *)malloc(sizeof(Node));
            if(q==NULL)
                exit(1);

            scanf("%s%s%d%s%s%d%s%d",q->name,q->sex,&q->age,q->ID_card,q->information.Bank_number,&q->\
                 information.start_money,q->information.save_sort,&q->information.month);

            q->next=NULL;
            p->next=q;
            p=q;
        }

        printf("您成功的创建了%d个用户的资料！\n\n",number);
    }
    
    printf("请按下任意键返回登陆界面！\n");

    while(getchar()!='\n')
        continue;

    getchar();

    my_register_1();

    return phead;
}
