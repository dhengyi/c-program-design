/*************************************************************************
	> File Name: Amend_password.h
	> Author: 
	> Mail: 
	> Created Time: 2016年06月27日 星期一 16时56分30秒
 ************************************************************************/

void my_amend_password()
{
    FILE *fp,*f;

    fp=fopen("银行系统登录文件","r");
    if(fp==NULL)
    {
        printf("文件打开失败！\n");
        exit(1);
    }

    char old_password_1[N];
    char old_password_2[N];
    char new_password_1[N];
    char new_password_2[N];

    printf("您现在准备进行银行系统密码修改操作：\n");
    printf("请按下任意键进行确认！\n");

    getchar();

    fscanf(fp,"%s",old_password_1);

    printf("请输入原密码：\n");

    scanf("%s",old_password_2);

    if(strcmp(old_password_1,old_password_2)!=0)
    {
        printf("您输入的原密码错误，请按下任意键返回到登陆界面！\n");

        while(getchar()!='\n')
            continue;

        getchar();

        my_register_1();
    }
    else
    {
        f=fopen("银行系统登录文件","wt");

        if(f==NULL)
        {
            printf("文件打开失败！\n");
            exit(1);
        }

        printf("您输入的原密码正确！请输入要修改的密码：\n");

        scanf("%s",new_password_1);

        printf("请再输入一次要修改的密码：\n");

        scanf("%s",new_password_2);

        while(strcmp(new_password_1,new_password_2)!=0)
        {
            printf("您输入的两次密码不相同，请重新开始输入一个新密码：\n");

            scanf("%s",new_password_1);

            printf("请再输入一次要修改的密码：\n");

            scanf("%s",new_password_2);
        }

        if(strcmp(new_password_1,new_password_2)==0)
        {
            fprintf(f,"%s",new_password_1);

            printf("您的密码修改成功，请按下任意键返回到登陆界面！\n");

            while(getchar()!='\n')
                continue;

            getchar();

            my_register_1();
        }
    }

    fclose(fp);
}
