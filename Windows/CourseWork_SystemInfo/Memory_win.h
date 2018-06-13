#pragma once

#include "GUI_win.h"

#define DIV 1024
#define WIDTH 7

using namespace std;

DWORD WINAPI thread4(LPVOID t);

class Memory : protected GUI
{
public:
	void GET_INF()
	{
		MemoryInf();
		cout << endl;

		HANDLE thread = CreateThread(NULL, 0, thread4, NULL, 0, NULL);
		HANDLE Close = CreateEvent(NULL, FALSE, FALSE, "Close2");
		getch();
		SetEvent(Close);
		WaitForSingleObject(thread, INFINITE);
		CloseHandle(thread);
		CloseHandle(Close);
	}

	void MemoryInf() //Память
	{
		MEMORYSTATUS stat;
		GlobalMemoryStatus(&stat);

		printf("The MemoryStatus structure is %ld bytes long.\n",
			stat.dwLength);
		printf("It should be %d.\n", sizeof(stat));
		printf("There are %*d total %sbytes of physical memory.\n",
			WIDTH, stat.dwTotalPhys / DIV, divisor);
		printf("There are %*d free %sbytes of physical memory.\n",
			WIDTH, stat.dwAvailPhys / DIV, divisor);
		printf("There are %*d total %sbytes of paging file.\n",
			WIDTH, stat.dwTotalPageFile / DIV, divisor);
		printf("There are %*d free %sbytes of paging file.\n",
			WIDTH, stat.dwAvailPageFile / DIV, divisor);
		printf("There are %*d total %sbytes of virtual memory.\n",
			WIDTH, stat.dwTotalVirtual / DIV, divisor);
		printf("There are %*d free %sbytes of virtual memory.\n",
			WIDTH, stat.dwAvailVirtual / DIV, divisor);
	}

	void MemoryUsed()
	{
		HANDLE Close = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Close2");
		COORD position = { 0,10 };
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		MEMORYSTATUS stat;
		GlobalMemoryStatus(&stat);
		while (1)
		{
			SetConsoleCursorPosition(hConsole, position);
			printf("\r%80c\r", ' ');
			cout << "Percent of memory is in use : ";
			cout << stat.dwMemoryLoad;
			Sleep(1000);
			if (WaitForSingleObject(Close, 0) == WAIT_OBJECT_0)
				return;
		}
	}
};

DWORD WINAPI thread4(LPVOID t)
{
	Memory b;
	b.MemoryUsed();
	return 1;
}

