#pragma once
#include "Map.h" 
Map graph;
void menu()
{

	int x;
	std::cout << "********************լ���Ͷ��͹���ϵͳ********************" << std::endl;
	std::cout << "*          1-�ϰ�                2-��������              *" << std::endl;
	std::cout << "*          3-���Ͷ���            4-��������ά��          *" << std::endl;
	std::cout << "*          5-ͳ��                0-�°�                  *" << std::endl;
	std::cout << "**********************************************************" << std::endl;
	std::cout <<"��ѡ�������0-5��:";
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
		std::cout << "*************************��������*************************" << std::endl;
		std::cout << "*    1-���ն���   2-��ѯ����  3-��ʾ���ж���  0-�˳�     *" << std::endl;
		std::cout << "**********************************************************" << std::endl;
		std::cout << "��ѡ�������0-3��:";
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
		default:std::cout << "�����������������룡" << std::endl;
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
		std::cout << "***********************��������ά��***********************" << std::endl;
		std::cout << "*          1-�޸��ײͣ���ţ�    2-�޸��ײͣ����ƣ�      *" << std::endl;
		std::cout << "*          3-ɾ���ײ�            4-�ָ��ײ�              *" << std::endl;
		std::cout << "*          5-��ʾ����            0-�˳�                  *" << std::endl;
		std::cout << "**********************************************************" << std::endl;
		std::cout << "��ѡ�������0-5��:";
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
		default:std::cout << "�����������������룡" << std::endl;
		}
		system("pause");
		system("cls");
		break;
	}
	case 5:
	{
		int y;
		std::cout << "***************************ͳ��***************************" << std::endl;
		std::cout << "*      1-���충�����        2-�����ײ�       0-�˳�     *" << std::endl;
		std::cout << "**********************************************************" << std::endl;
		std::cout << "��ѡ�������0-2��:";
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
		default:std::cout << "�����������������룡" << std::endl;
		}
		system("pause");
		system("cls");
	}
		break;
	
	case 0:
	{
		return;
	}
	default:std::cout << "�����������������룡" << std::endl;
	}
	system("pause");
	system("cls");
}