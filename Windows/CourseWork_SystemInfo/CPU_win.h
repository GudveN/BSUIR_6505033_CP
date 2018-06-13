#pragma once

#include "GUI_win.h"

using namespace std;

DWORD WINAPI thread2(LPVOID t);

class CPU : protected GUI
{

private:
	struct cpuid_regs
	{
		DWORD   Eax;
		DWORD   Ebx;
		DWORD   Ecx;
		DWORD   Edx;
	};

public:

	void GET_INF()
	{
		cout << "1)Information about CPU\n";
		cout << "2)Begin CPU usage\n";
		cout << "3)Stop CPU usage\n";

		cout << "Load of CPU = ";
		COORD position = { 0,5 };
		COORD defposition = { 14,3 };
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		HANDLE thread = CreateThread(NULL, 0, thread2, NULL, 0, NULL);
		HANDLE Print = CreateEvent(NULL, TRUE, TRUE, "Print");
		HANDLE Close = CreateEvent(NULL, FALSE, FALSE, "Close");

		while (1) {
			char temp = getch();
			switch (temp) {
			case '1': {
				SetConsoleCursorPosition(hConsole, position);
				CPUInf();
				SetConsoleCursorPosition(hConsole, defposition);
				break;
			}
			case '2': {
				SetEvent(Print);
				break;
			}
			case '3': {
				ResetEvent(Print);
				break;
			}
			default: {
				SetEvent(Print);
				SetEvent(Close);
				WaitForSingleObject(thread, INFINITE);
				CloseHandle(thread);
				CloseHandle(Print);
				CloseHandle(Close);
				return;
			}
			}
		}

	}

	void LoadCPU(COORD position, HANDLE hConsole)
	{

		FILETIME idle, prev_idle;
		FILETIME kernel, prev_kernel;
		FILETIME user, prev_user;
		GetSystemTimes(&prev_idle, &prev_kernel, &prev_user);
		Sleep(1000);
		GetSystemTimes(&idle, &kernel, &user);
		ULONGLONG sys = (ft2ull(user) - ft2ull(prev_user)) +
			(ft2ull(kernel) - ft2ull(prev_kernel));
		SetConsoleCursorPosition(hConsole, position);
		cout << "    ";
		SetConsoleCursorPosition(hConsole, position);
		cout << int((sys - ft2ull(idle) + ft2ull(prev_idle)) * 100.0 / sys) << "%";
		prev_idle = idle;
		prev_kernel = kernel;
		prev_user = user;
		Sleep(300);
	}

	void CPUInf() //Процессор
	{
		int i = 0;
		string temp_string;
		temp_string = GetCpuVendorString();
		while (temp_string[i] == ' ')
			i++;
		temp_string = temp_string.substr(i);
		cout << temp_string << endl;
		SYSTEM_INFO siSysInfo;
		GetSystemInfo(&siSysInfo);
		printf("Hardware information: \n");
		printf("  OEM ID: %u\n", siSysInfo.dwOemId);
		printf("  Number of processors: %u\n",
			siSysInfo.dwNumberOfProcessors);
		printf("  Page size: %u\n", siSysInfo.dwPageSize);
		printf("  Processor type: %u\n", siSysInfo.dwProcessorType);
		printf("  Minimum application address: %lx\n",
			siSysInfo.lpMinimumApplicationAddress);
		printf("  Maximum application address: %lx\n",
			siSysInfo.lpMaximumApplicationAddress);
		printf("  Active processor mask: %u\n",
			siSysInfo.dwActiveProcessorMask);
	}

	string SplitIntoChars(DWORD Value)
	{
		string Str;
		char const * pCursor = (char const *)&Value;
		for (int i = 0; i < sizeof(Value); ++i) {
			Str += pCursor[i];
		}
		return Str;
	}

	string GetCpuVendorSubstring(DWORD Eax)
	{
		cpuid_regs Regs;
		__cpuid((int *)&Regs, Eax);
		string Str;
		Str += SplitIntoChars(Regs.Eax);
		Str += SplitIntoChars(Regs.Ebx);
		Str += SplitIntoChars(Regs.Ecx);
		Str += SplitIntoChars(Regs.Edx);
		return Str;
	}

	string GetCpuVendorString()
	{
		string VendorString;
		cpuid_regs Regs;
		__cpuid((int *)&Regs, 0x80000000);
		if (Regs.Eax >= 0x80000004)
		{
			VendorString =
				GetCpuVendorSubstring(0x80000002) +
				GetCpuVendorSubstring(0x80000003) +
				GetCpuVendorSubstring(0x80000004);
		}
		return VendorString;
	}

	ULONGLONG ft2ull(FILETIME &ft)
	{
		ULARGE_INTEGER ul;
		ul.HighPart = ft.dwHighDateTime;
		ul.LowPart = ft.dwLowDateTime;
		return ul.QuadPart;
	}
};

DWORD WINAPI thread2(LPVOID t)
{
	COORD position = { 14,3 };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CPU a;
	HANDLE Print = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Print");
	HANDLE Close = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Close");
	while (1)
	{
		if (WaitForSingleObject(Print, INFINITE) == WAIT_OBJECT_0)
		{
			a.LoadCPU(position, hConsole);
		}
		if (WaitForSingleObject(Close, 0) == WAIT_OBJECT_0)
		{
			CloseHandle(Print);
			CloseHandle(Close);
			return 1;
		}
	}
}
