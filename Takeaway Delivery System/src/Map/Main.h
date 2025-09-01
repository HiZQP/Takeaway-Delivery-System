#pragma once
#include "Map.h" 
Map graph;
void menu()
{

	int x;
	std::cout << "********************宅急送订餐管理系统********************" << std::endl;
	std::cout << "*          1-上班                2-订单管理              *" << std::endl;
	std::cout << "*          3-派送订单            4-基础数据维护          *" << std::endl;
	std::cout << "*          5-统计                0-下班                  *" << std::endl;
	std::cout << "**********************************************************" << std::endl;
	std::cout <<"请选择操作（0-5）:";
	std::cin >> x;
	switch (x)
	{
	case 1:
	{
		
		break;
	}
	case 2:
	{
		int y;
		std::cout << "*************************订单管理*************************" << std::endl;
		std::cout << "*    1-接收订单   2-查询订单  3-显示所有订单  0-退出     *" << std::endl;
		std::cout << "**********************************************************" << std::endl;
		std::cout << "请选择操作（0-3）:";
		std::cin >> y;
		switch (y)
		{
		case 1:
		{

			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			break;
		}
		case 0:
		{
			return;
		}
		default:std::cout << "输入有误，请重新输入！" << std::endl;
		}
		system("pause");
		system("cls");
		break;
	}	
	
	case 3:
	{
		graph.Create();
		graph.floyd();
		break;
	}
	case 4:
	{
		int z;
		std::cout << "***********************基础数据维护***********************" << std::endl;
		std::cout << "*          1-修改套餐（编号）    2-修改套餐（名称）      *" << std::endl;
		std::cout << "*          3-删除套餐            4-恢复套餐              *" << std::endl;
		std::cout << "*          5-显示所有            0-退出                  *" << std::endl;
		std::cout << "**********************************************************" << std::endl;
		std::cout << "请选择操作（0-5）:";
		std::cin >> z;
		switch (z)
		{
		case 1:
		{

			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			break;
		}
		case 4:
		{
			break;
		}
		case 5:
		{
			break;
		}
		case 0:
		{
			return;
		}
		default:std::cout << "输入有误，请重新输入！" << std::endl;
		}
		system("pause");
		system("cls");
		break;
	}
	case 5:
	{
		int y;
		std::cout << "***************************统计***************************" << std::endl;
		std::cout << "*      1-当天订单情况        2-当月套餐       0-退出     *" << std::endl;
		std::cout << "**********************************************************" << std::endl;
		std::cout << "请选择操作（0-2）:";
		std::cin >> y;
		switch (y)
		{
		case 1:
		{

			break;
		}
		case 2:
		{
			break;
		}
		case 0:
		{
			return;
		}
		default:std::cout << "输入有误，请重新输入！" << std::endl;
		}
		system("pause");
		system("cls");
	}
		break;
	
	case 0:
	{
		return;
	}
	default:std::cout << "输入有误，请重新输入！" << std::endl;
	}
	system("pause");
	system("cls");
}