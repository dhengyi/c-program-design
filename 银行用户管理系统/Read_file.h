/*************************************************************************
	> File Name: Read_file.h
    > Author: 
	> Mail: 
	> Created Time: 2016年06月28日 星期二 12时53分00秒
 ************************************************************************/

Node *my_read_file(int number)
{
    FILE *fp;
    char file_name[N];
    Node *phead,*p,*q;

    phead=(Node *)malloc(sizeof(Node));
    if(phead==NULL)
        exit(1);

    phead->next=NULL;
    p=phead;

    if(number==3)
        printf("请确认要添加的文件名：\n");
    else
        printf("请输入要查找的文件名：\n");
    
    scanf("%s",file_name);

    fp=fopen(file_name,"r");

    if(fp==NULL)
    {
        printf("银行系统中没有这个账户文件！\n");
        printf("按下任意键退出系统！然后登录系统先新建账户文件！\n");

        while(getchar()!='\n')
            continue;

        getchar();

        exit(1);
    }
    else
    {
        while(!feof(fp))
        {
            q=(Node *)malloc(sizeof(Node));
            if(q==NULL)
                exit(1);

            fscanf(fp,"%s\t%s\t%d\t%s\t%s\t%d\t%s\t%d\n",q->name,q->sex,&q->age,q->ID_card,q->information.Bank_number,\
                    &q->information.start_money,q->information.save_sort,&q->information.month);

            p->next=q;
            p=q;
        }

        if(q->age<=0||q->age>=130)
        {
            phead->next=NULL;
        }

        p->next=NULL;

        fclose(fp);

        return phead->next;
    }
}
