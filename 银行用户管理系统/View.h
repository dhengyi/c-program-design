/*************************************************************************
	> File Name: View.h
	> Author: 
	> Mail: 
	> Created Time: 2016年06月23日 星期四 21时53分17秒
 ************************************************************************/

void my_view()
{
    Node * loop;
    int number=0;
    loop=my_read_file(number);

    if(loop==NULL)
    {
        printf("银行系统里面没有用户信息！\n");
        printf("请按下任意键返回到登陆界面！先给账户文件中添加新用户！\n");
        
        while(getchar()!='\n')
            continue;

        getchar();

        my_register_1();
    }
    else
    {
        printf("======================================================================================================\n\n\n");
        printf("姓名\t性别\t年龄\t身份证号\t银行卡号\t存钱数\t存储类别\t存储时间（月）\n\n\n");

        for(;loop!=NULL;loop=loop->next)
        {
            printf("%s\t%s\t%d\t%s\t\t%s\t\t%d\t%s\t\t%d\n\n\n",loop->name,loop->sex,loop->age,loop->ID_card,\
                   loop->information.Bank_number,loop->information.start_money,loop->information.save_sort,loop->information.month);
        }

        printf("======================================================================================================\n\n\n");
        printf("用户资料显示成功！请按下任意键返回到登陆界面！\n");

        while(getchar()!='\n')
            continue;

        getchar();

        my_register_1();
    }
}
