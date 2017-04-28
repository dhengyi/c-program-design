/*************************************************************************
	> File Name: 银行用户信息操作管理系统（密码登录）.c
	> Author: 
	> Mail: 
	> Created Time: 2016年06月23日 星期四 17时23分31秒
 ************************************************************************/
void my_password()
{
    int flag=0;
    char Tpassword[N];
    char Ipassword[N];
    char *password;
    FILE *fp;

    fp=fopen("银行系统登录文件","r+");
    if(fp==NULL)
    {
        printf("文件打开失败\n");
        exit(1);
    }

    password=Tpassword;

    fscanf(fp,"%s",password);

    printf("如要登录请先请输入登录密码：\n");

    scanf("%s",Ipassword);
    
    while(getchar()!='\n')
        continue;

    while(flag==0)
    {    
        if(strcmp(Ipassword,password)==0)
        {
            printf("\n正确！\n");
            printf("按下任意键继续！\n");

            flag=1;
            getchar();
        }
        else
        {
            printf("错误！请再试一次！\n");
            scanf("%s",Ipassword);
            
            while(getchar()!='\n')
                continue;
        }
    }

    fclose(fp);
}
