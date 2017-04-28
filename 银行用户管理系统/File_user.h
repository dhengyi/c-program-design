/*************************************************************************
	> File Name: File_user.h
	> Author: 
	> Mail: 
	> Created Time: 2016年06月27日 星期一 22时08分11秒
 ************************************************************************/

void my_file(Node *loop)
{

    char fp_name[N];
    FILE *fp_save;
    printf("请输入您要保存的文件名：\n");
    
    scanf("%s",fp_name);

    fp_save=fopen(fp_name,"wt+");

    if(fp_save==NULL)
    {
        printf("文件创建或打开失败！\n");
        printf("请按下任意键返回到登录界面！\n");

        while(getchar()!='\n')
            continue;

        getchar();

        my_register_1();
    }

    else
    {
        if(loop==NULL)
        {
            printf("账户文件创建成功，但此时系统中没有可保存的用户资料！\n");
            printf("请按下任意键返回到登录界面！\n");

            while(getchar()!='\n')
                continue;

            getchar();

            my_register_1();
        }
        else
        {
            while(loop!=NULL)
            {
                fprintf(fp_save,"%s\t%s\t%d\t%s\t\t%s\t\t%d\t%s\t\t%d\n",loop->name,loop->sex,loop->age,\
                        loop->ID_card,loop->information.Bank_number,loop->information.start_money,\
                        loop->information.save_sort,loop->information.month);

                loop=loop->next;
            }
            printf("账户资料已成功保存到磁盘文件中！\n");
            printf("请按下任意键返回到登录界面！\n");

            while(getchar()!='\n')
                continue;

            getchar();

            my_register_1();
        }
    }
    fclose(fp_save);
}
