#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include <time.h>

/*机位、顾客信息结构体*/
 
typedef struct   PCInfo
{
	int State[6];                 //机位状态，2小时为一个时间段，8时到20时共6个时间段，0表示有空位，1表示无空位
	char name[20];            //各时间段运行顾客
	char sex[30];
	char tel[20];
	int year;
	int month;
	int day;
	int start_Time;
	int end_Time;
}PCInfo;
PCInfo info[100][100];            //存放100天，20台机位信息


	int Month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };  /*数组定义每月天数*/
	int date[12][31];                                              /*定义日期和机位信息数组*/

	

/******************************空白函数模块*****************************/

void s_line(int n)                      /*空行*/
{
	int i;
	for (i = 1; i <= n; i++)
		printf("\n");
}



void space(int n)                   /*空白*/
{
	int i;
	for (i = 1; i <= n; i++)
	{
		printf(" ");
	}
}



/******************************清空机位信息模块*****************************/
void Empty()   
{
	int i,j,k,a;
	for (i = 0; i <=20 ; i++)      /*此循环作用是将0赋给机位状态*/
	{
		for (a = 0; a <= 20; a++)
		{
			for (j = 0; j <= 6; j++)
			{
				info[i][a].State[j] = 0;
			}
		}
	
	}
	for (j = 0; j <= 12; j++)    /*此循环作用是将0赋给日期*/
	{
		for (k = 0; k <= 31; k++)
		{
			date[j][k] = 0;
		}
	}
}

/******************************查询机位信息模块*****************************/

void Query()
{
	int year, month, day, start_Time, end_Time, time,a=1;
	int n = 0;
	int i;
	while (1)
	{
		printf("\t\t    ********************此处你可以输入时间来查看20个计算机的机位信息********************\n\n");
		
		printf("\t\t\t\t       请输入您想要查询的日期时间：（例如：2016/7/22/8-10表示）                                  \n\n");
		scanf_s("%d/%d/%d/%d-%d", &year, &month, &day, &start_Time, &end_Time);  /*输入查询时间*/

		if ((start_Time - 8) / 2 >= 0 && (start_Time - 8) / 2 <= 6)
		{
			time = (start_Time - 8) / 2;
		}
		else
		{
			printf("输入时间段错误！                                                                        \n");
			system("pause");
			return;
		}



		if (month < 1 || month > 12 || day < 0 || day > Month[month])
			/*如果输入时间不对就回出错，显示出错信息并且给出提示*/
		{
			printf(" 输入错误！    \n");
			printf(" 请选择输入指令：1.重新输入  2.返回菜单    \n");
			scanf_s("%d", &n);
			if (n == 2) { break; }
			if (n == 1){break;}
		}
			else break;     //未出错则跳出循环，继续执行后面程序

	}
		if (n == 2) return;

		printf("当前您要查询第几次预约的机位信息？（相同日期视为一次）\n\n");
		scanf_s("%d", &a);
		for (i = 1; i <= 20; i++)                          /*此循环的作用是判断是否有空的机位*/
		{
			if (date[month][day] == 1 && info[i][a].State[time] == 1)
				printf("\t\t\t\t      第 %d 号计算机在这段时间已经被预定. \n\n", i);
			else
				printf("\t\t\t\t      第 %d 号计算机在这段时间内没有被预定.  \n\n", i);
		}


		system("pause");                              /*系统暂停，按任意键继续 */
}



/******************************机位预定模块*****************************/


void book_computer()                                /*此函数的作用是预定机位*/
{
	int  year, month, day, start_Time, end_Time, time;
	int b = 0, m = 0;
	int n = 0, i = 0, j, k, s,t;

	while (1) 
	{
		printf("\t\t********************此处你可以输入（年/月/日/XX-XX时间段）来查看是否有空位计算机********************\n\n");
		printf("\t\t如果有空闲机位将会自动预约，如果无空位，您可以选择最近时间段空位计算机进行预约！\n\n");
		
		printf("\t\t\t\t      请输入您想要预约的日期时间：（例如：2016/7/22/8-10表示）                                  \n");
		scanf_s("%d/%d/%d/%d-%d",&year,&month, &day, &start_Time, &end_Time);
		/*输入查询时间*/

		if ((start_Time - 8) / 2 >= 0 && (start_Time - 8) / 2 <= 6)
		{
			time = (start_Time - 8) / 2;
		}
		else
		{
			printf(" 输入时间段错误！\n");
		}

		if (month < 1 || month > 12 || day < 0 || day > Month[month])
			/*检验查询时间是否出错，并给出提示信息*/
		{
			printf(" 输入错误！ \n");
			printf(" 请选择输入指令：1.重新输入  2.返回菜单\n");
			scanf_s("%d", &n);
			if (n == 2) break;
		}
		else break;     //未出错则跳出循环，继续执行后面程序

	}

	if (n == 2) return;
	int a=0;

	s = timeone();     //该函数负责将不同时间段信息放置在二维数组结构体的不同列

	printf(" 请选择预约模式：\n");

	printf(" 1.按顺序预约          2.选择编号预约\n");
	scanf_s("%d", &a);
	if (a == 1)           //顺序预约模块
	{
		for (i = 1; i <= 20; i++)
		{
			if (date[month][day] == 0 || info[i][s].State[time] == 0)
			{
				date[month][day] = 1;
				info[i][s].State[time] = 1;
				printf("\t\t    ==================第 %d 号计算机已经成功预约！==================\n  ", i);
				printf("\t\t    ================您可以在预约的时间段内使用计算机！============= \n \n ");
				printf("\t\t 本次为 机位预约模拟系统  第%d次预约（不同时期）.请留意次数. \n", s);
				system("pause");
				return;  //有一个符合条件的计算机，则return跳出该函数
			}
		}
		printf("您查询的时间段内无空闲机位！\n\n");
		printf("是否仍在非空闲时间段内使用电脑：\n\n");
		printf("1.是(加入等待队列)\n");
		printf("2.否(查找临近的空位计算机)\n");
		scanf_s("%d", &n);
		if (n == 1)                     /*如果加入等待列表，就输入相关的姓名，性别，电话和机位号*/
		{

			printf("请输入您想要等待的机位号：:\n\n");
			scanf_s("%d", &m);
			printf("请输入您的姓名:\n\n");
			scanf_s("%s", info[m][s].name, 20);
			printf("请输入您的性别:（男或女）\n\n");
			scanf_s("%s", info[m][s].sex, 30);
			printf("请输入您的电话号码:\n\n");
			scanf_s("%s", info[m][s].tel, 20);
			info[m][s].year = year;
			info[m][s].month = month;
			info[m][s].day = day;
			info[m][s].start_Time = start_Time;
			info[m][s].end_Time = end_Time;

			printf("您已经成功加入等待队列......\n");

			system("pause");
			return;
		}

		/*通过四层嵌套循环寻找顺次向后推时间段内空机位信息*/

		for (i = month; i <= 12; i++)            //月份
		{
			for (j = day; j <= Month[i]; j++)   //日期
			{
				for (k = 1; k <= 6; k++)          //0-6时间段
				{
					for (m= 1; m < 20; m++)      //1-20号机器
					{
						if (date[i][j] == 0 || info[m][s].State[time] == 0)
						{
							printf("你可以预约到的最近时间段的计算机:第%d号计算机 %d年%d月%d日%d时-%d时  \n", s, year, i, j, (2 * k + 6), (2 * k + 8));
							printf(" 1.预约第 %d 号计算机的该段时间  \n", s);
							printf(" 2.不预约并退出\n");
							printf(" 请输入1&2进行选择:  \n");
							scanf_s("%d", &n);
							if (n == 1)
							{
								printf("\t\t    ==================第 %d 号计算机已经成功预约！==================\n  ", m);
								printf("\t\t    ================您可以在预约的时间段内使用计算机！============= \n \n ");
								printf("\t\t         本次为 机位预约模拟系统  第%d次预约（不同时期）.请留意次数. \n", s);
								date[i][j] = 1;                           /*将机位状态调整为1*/
								info[m][s].State[time] = 1;
							}
							system("pause");   /*系统暂停，按任意键继续*/
							return;
						}
					}
				}
			}
		}
	}
	if (a == 2)    /*选择编号进行预约*/
	{
		printf("请输入您要预约的计算机机位号：\n");
		scanf_s("%d", &i);
		if (date[month][day] == 0 || info[i][s].State[time] == 0)
		{
			date[month][day] = 1;
			info[i][s].State[time] = 1;
			printf("\t\t    ==================第 %d 号计算机已经成功预约！==================\n   ", i);
			printf("\t\t    ================您可以在预约的时间段内使用计算机！============= \n \n ");
			printf("\t\t         本次为 机位预约模拟系统  第%d次预约（不同时期）.请留意次数. \n", s);
			system("pause");
		}
		else
		{
			     printf("第%d号机位已经被他人预约！",i);             /*重复之前等待信息载入代码*/
				 printf("是否仍在非空闲时间段内使用电脑：\n");
				 printf("1.是(加入等待队列)\n");
				 printf("2.否(查找临近的空位计算机)\n");
				 scanf_s("%d", &n);
				 if (n == 1)                     /*如果预定机位，就输入相关的姓名，性别，时间段*/
				 {

					 printf("请输入您想要等待的机位号：:\n\n");
					 scanf_s("%d", &b);
					 printf("请输入您的姓名:\n\n");
					 scanf_s("%s", info[b][s].name,30);
					 printf("请输入您的性别:（男或女）\n\n");
					 scanf_s("%s", info[b][s].sex, 30);
					 printf("请输入您的电话号码:\n\n");
					 scanf_s("%s", info[b][s].tel, 20);
					 info[b][s].year = year;
					 info[b][s].month = month;
					 info[b][s].day = day;
					 info[b][s].start_Time = start_Time;
					 info[b][s].end_Time = end_Time;

					 printf("您已经成功加入等待队列......\n");

					 system("pause");
					 return;
				 }
				 for (i = month; i <= 12; i++)            //月份
				 {
					 for (j = day; j <= Month[i]; j++)   //日期
					 {
						 for (k = 1; k <= 6; k++)          //0-6时间段
						 {
							 for (t = 1; t < 20; t++)      //1-20号机器
							 {
								 if (date[i][j] == 0 || info[t][s].State[time] == 0)
								 {
									 printf("你可以预约到的最近时间段的计算机:第%d号计算机 %d年%d月%d日%d时-%d时  \n\n", t, year, i, j, (2 * k + 6), (2 * k + 8));
									 printf(" 1.预约第 %d 号计算机的该段时间  \n\n", t);
									 printf(" 2.不预约并退出\n\n");
									 printf(" 请输入1&2进行选择:  \n\n");
									 scanf_s("%d", &n);
									 if (n == 1)
									 {
										 printf("****************第 %d 号计算机已经成功预约！****************   \n   ", t);
										 printf("***************您可以在该时间段内使用计算机！**************    \n    ");
										 date[i][j] = 1;
										 info[t][s].State[time] = 1;
									 }
									 system("pause");
									 return;
								 }
							 }
						 }
					 }
				 }
		}
	}


}



/******************************取消预约模块*****************************/
void book_exit()                           /*此函数的作用是退出预定*/
{
	int year,month, day, start_Time, end_Time,time,s=0;
	int n = 0;

	while (1) 
	{
		printf("\n在此处您可以取消预约已预订的计算机\n");
		system("pause");
		printf("\n请输入您想要取消预约的日期时间：（例如：2016/7/22/8-10表示） \n");
		scanf_s("%d/%d/%d/%d-%d", &year,&month, &day, &start_Time, &end_Time);
		if ((start_Time - 8) / 2 >= 0 && (start_Time - 8) / 2 <= 6)
		{
			time = (start_Time - 8) / 2;
		}
		else
		{
			printf("\n输入时间段错误！                                                                        \n");
			system("pause");
			return;
		}
		if (month < 1 || month > 12 || day < 0 || day > Month[month])
		{
			printf(" 输入错误！ \n");
			printf(" 请选择输入指令：1.重新输入  2.返回菜单\n");
			scanf_s("%d", &n);
			if (n == 2) break;
		}

		else break;
	}

	if (n == 2) return;
	printf("请输入您想要取消预约的计算机编号：.\n");
	scanf_s("%d", &n);
	printf("您要取消预约第几次预约的计算机机位：.\n");
	scanf_s("%d", &s);
	if (info[n][s].State[time] == 1)
	{
		info[n][s].State[time] = 0;
		printf("第%d号机位 取消预约成功！\n",n);
	}
	else
	{
		printf("在该段时间内您没有预约任何编号的计算机！\n");
	}

	system("pause");
}

/******************************查询等待信息模块*****************************/


void Look_wait()                /*此函数的作用是查询等待机位的人，并按序显示*/
{
	int m;
	int year, month, day, start_Time, end_Time,s;

	printf("请输入您想要查询的日期时间：（例如：2016/7/22/8-10表示） \n\n");
	scanf_s("%d/%d/%d/%d-%d", &year, &month, &day, &start_Time, &end_Time);
	printf("请输入您要查询等待信息的机位号： \n\n");
	scanf_s("%d", &m);
	printf("正在查询，请稍候~\n\n");



	printf("第%d号计算机：\n\n", m);
	printf("  您准备查找第几次预约的信息？\n\n ");
	scanf_s("%d", &s);
	printf("姓名：%s\n\n", info[m][s].name);
	printf("性别：%s\n\n", info[m][s].sex);
	printf("联系方式：%s\n\n", info[m][s].tel);
	printf("该成员于%d年%d月%d日加入本台计算机的等待队列\n\n", info[m][s].year, info[m][s].month, info[m][s].day);
	system("pause");
	return;
}

/******************************预约次数（不同时期）判别模块*****************************/

int timeone()           /*为了便于对不同预约时间相同机位信息判别加设 */
{

	int n=0,k;
    int s = 1;
	printf("如果在本系统首次预约请选择 1 ，再次预约请选择 2\n\n");
	scanf_s("%d", &n);
	if (n == 1)
	{
		return s;
	}
	if (n == 2)
	{
		int i=0;
		printf("预约日期与前几次是否相同？  1.相同   2.不同 \n\n");
		scanf_s("%d",& i);
		if (i == 1)
		{
			s = 0;
			printf("预约日期与第几次相同？ \n");
			scanf_s("%d", &k);
			s = s + k;
			return s;
		}
		if (i == 2)
		{
			s = 0;
			printf("本次为第几次预约（不同时期）？ \n");
			scanf_s("%d", &k);
			s = s + k;
			printf("本次为 机位预约模拟系统  第%d次预约（不同时期）.请留意次数. \n",s);
			return s;
		}
	}
	
}

/**********************************主函数模块*************************************/
main()                               
{
	Empty();
	int num;
	while (1) 
	{
		system("cls");                    /* 清除文本模式窗口 */
		s_line(4);                      
		space(40);
		printf("********************主菜单********************\n");    /*使用空行函数排版*/
		s_line(2);
		space(55);
		printf("1.查询机位信息\n");
		s_line(1);
		space(55);
		printf("2.预约机位\n");
		s_line(1);
		space(55);
		printf("3.取消机位预约\n");
		s_line(1);
		space(55);
		printf("4.查询等待人员信息\n");
		s_line(1);
		space(55);
		printf("5.退出系统\n");
		s_line(2);
		space(40);
		printf("********************************************\n\n");
		printf("请输入1~5进行功能操作: \n");
		scanf_s("%d", &num);            /*输入数字进行相应的函数的调用*/
		if (num == 5)  break;
		switch (num) 
		{
		case 1:
			Query();
			break;
		case 2:
			book_computer();
			break;
		case 3:
			book_exit();
			break;
		case 4:
			Look_wait();
			break;
		default:
			printf("输入错误！\n");
			system("pause");
			exit(0);
		}

	}

}
/****************************************************************************/
