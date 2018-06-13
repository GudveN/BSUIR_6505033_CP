#pragma once

#include "GUI_win.h"

#pragma comment(lib,"wsock32.lib")

#define BUFSIZE 1024

using namespace std;


class Service : protected GUI
{

public:
	void GET_INF() {
		cout << "1)Processes\n";
		cout << "2)Get Computep IP and Username\n";
		char temp = getch();
		switch (temp) {
		case '1': {
			ScanProcess();
			system("pause");
			break;
		}
		case '2': {
			GetCompIP();
			break;
		}
		default:
			break;
		}
	}

	void MyErrorExit(LPCTSTR ErrMsg)
	{
		printf("Error :");
		printf(ErrMsg);
		printf("Error :\r\n");
	}

	void GetCompIP()
	{
		WSADATA wsaData;
		if (!WSAStartup(!NULL, &wsaData))
		{
			char chInfo[64];
			if (!gethostname(chInfo, sizeof(chInfo)))
			{
				cout << chInfo << endl;
				hostent *sh;
				sh = gethostbyname((char*)&chInfo);
				if (sh != NULL)
				{
					cout << sh->h_name << endl;
					int nAdapter = 0;
					while (sh->h_addr_list[nAdapter])
					{
						struct sockaddr_in adr;
						memcpy(&adr.sin_addr, sh->h_addr_list[nAdapter], sh->h_length);
						cout << inet_ntoa(adr.sin_addr) << endl;
						nAdapter++;
					}
				}
			}
			else
				cout << "Error local host " << endl;
		}
		else
			cout << "Winsock initial Bad !!!!" << endl;
		WSACleanup();
		system("pause");
	}

	void ScanProcess()
	{
		HANDLE hSnap;
		hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hSnap == NULL)
		{
			MessageBox(NULL, "Error Load ToolHelp", NULL, MB_OK);
		}
		PROCESSENTRY32 proc;
		THREADENTRY32 te32;
		if (Process32First(hSnap, &proc))
		{
			printf(proc.szExeFile);
			//      cout <<  te32.th32ThreadID << " " << te32.th32OwnerProcessID << endl;
			printf("\r\n");
			while (Process32Next(hSnap, &proc))
			{
				printf(proc.szExeFile);
				//          Thread32Next(hSnap, &te32);
				//          cout <<  te32.th32ThreadID << " " << te32.th32OwnerProcessID << endl; 
				printf("\r\n");
			}
		}
	}
};
