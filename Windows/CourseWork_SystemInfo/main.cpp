#include "Service_win.h"
#include "HDD_win.h"
#include "CPU_win.h"
#include "GPU_win.h"
#include "SystemInfo_win.h"
#include "Memory_win.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <dxgi.h>
#include <string>

static void outputInf()
{
	cout << " ———————————————— " << endl;
	cout << "| 1)CPU INFO     |" << endl;
	cout << "| 2)GPU INFO     |" << endl;
	cout << "| 3)HDD INFO     |" << endl;
	cout << "| 4)MEMORY INFO  |" << endl;
	cout << "| 5)SERVICE INFO |" << endl;
	cout << "| 6)SYSTEM INFO  |" << endl;
	cout << "  ——————————————— " << endl;
}
static void output()
{
	outputInf();
	while (1)
	{
		switch (getch())
		{
		case '1': {
			system("cls");
			CPU a;
			a.GET_INF();
			system("cls");
			outputInf();
			break;
		}
		case '2': {
			system("cls");
			GPU b;
			b.GET_INF();
			system("cls");
			outputInf();
			break;
		}
		case '3': {
			system("cls");
			HDD c;
			c.GET_INF();
			system("cls");
			outputInf();
			break;
		}
		case '4': {
			system("cls");
			Memory d;
			d.GET_INF();
			system("cls");
			outputInf();
			break;
		}
		case '5': {
			system("cls");
			Service e;
			e.GET_INF();
			system("cls");
			outputInf();
			break;
		}
		case '6': {
			system("cls");
			SystemInfo f;
			f.GET_INF();
			system("cls");
			outputInf();
			break;
		}
		default:
			return;
		}
	}
}

int main(void)
{
	setlocale(LC_ALL, "rus");
	output();
	system("pause");
}