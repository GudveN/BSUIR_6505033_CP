#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <comdef.h>
#include <Wbemidl.h>
#include <windows.h>
#include "GUI_win.h"
// чтобы получить результат в Kb, используем делитель.
#define DIV 1024
// #define DIV 1
char *divisor = "K";
// char *divisor = "";
// Ширина поля, в которой будут печаться цифры
// "%*ld" преобразует аргумент списка в int, и выравнивает вправо.
#define WIDTH 7

using namespace std;


# pragma comment(lib, "wbemuuid.lib")


class SystemInfo : protected GUI
{
public:
	void GET_INF() {
		cout << "1)System info and Windows environment\n";
		cout << "2)Devices information\n";
		cout << "3)MotherBoard name\n";
		char temp = getch();
		switch (temp) {
		case '1': {
			WindowsInf();
			break;
		}
		case '2': {
			other();
			break;
		}
		case '3': {
			system("wmic baseboard get product");
			system("pause");
			break;
		}
		default:
			break;
		}
	}

protected:
	int other()
	{
		setlocale(LC_CTYPE, "");

		DISPLAY_DEVICEW dd;
		OSVERSIONINFOEXW osv;

		osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
		dd.cb = sizeof(DISPLAY_DEVICEW);
		EnumDisplayDevicesW(NULL, 0, &dd, EDD_GET_DEVICE_INTERFACE_NAME);

		wcout << L"video: " << dd.DeviceString << endl;

		//=================================================================================================

		HRESULT hres;

		// Step 1: --------------------------------------------------
		// Initialize COM. ------------------------------------------

		hres = CoInitializeEx(0, COINIT_MULTITHREADED);
		if (FAILED(hres))
		{
			wcout << L"Failed to initialize COM library. Error code = 0x"
				<< hex << hres << endl;
			return 1;                  // Program has failed.
		}

		// Step 2: --------------------------------------------------
		// Set general COM security levels --------------------------

		hres = CoInitializeSecurity(
			NULL,
			-1,                          // COM authentication
			NULL,                        // Authentication services
			NULL,                        // Reserved
			RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
			RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
			NULL,                        // Authentication info
			EOAC_NONE,                   // Additional capabilities 
			NULL                         // Reserved
		);


		if (FAILED(hres))
		{
			wcout << L"Failed to initialize security. Error code = 0x"
				<< hex << hres << endl;
			CoUninitialize();
			return 1;                    // Program has failed.
		}

		// Step 3: ---------------------------------------------------
		// Obtain the initial locator to WMI -------------------------

		IWbemLocator *pLoc = NULL;

		hres = CoCreateInstance(
			CLSID_WbemLocator,
			0,
			CLSCTX_INPROC_SERVER,
			IID_IWbemLocator, (LPVOID *)&pLoc);

		if (FAILED(hres))
		{
			wcout << L"Failed to create IWbemLocator object."
				<< L" Err code = 0x"
				<< hex << hres << endl;
			CoUninitialize();
			return 1;                 // Program has failed.
		}

		// Step 4: -----------------------------------------------------
		// Connect to WMI through the IWbemLocator::ConnectServer method

		IWbemServices *pSvc = NULL;

		// Connect to the root\cimv2 namespace with
		// the current user and obtain pointer pSvc
		// to make IWbemServices calls.
		hres = pLoc->ConnectServer(
			_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
			NULL,                    // User name. NULL = current user
			NULL,                    // User password. NULL = current
			0,                       // Locale. NULL indicates current
			NULL,                    // Security flags.
			0,                       // Authority (for example, Kerberos)
			0,                       // Context object 
			&pSvc                    // pointer to IWbemServices proxy
		);

		if (FAILED(hres))
		{
			wcout << L"Could not connect. Error code = 0x"
				<< hex << hres << endl;
			pLoc->Release();
			CoUninitialize();
			return 1;                // Program has failed.
		}

		wcout << L"Connected to ROOT\\CIMV2 WMI namespace" << endl;


		// Step 5: --------------------------------------------------
		// Set security levels on the proxy -------------------------

		hres = CoSetProxyBlanket(
			pSvc,                        // Indicates the proxy to set
			RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
			RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
			NULL,                        // Server principal name 
			RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
			RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
			NULL,                        // client identity
			EOAC_NONE                    // proxy capabilities 
		);

		if (FAILED(hres))
		{
			wcout << L"Could not set proxy blanket. Error code = 0x"
				<< hex << hres << endl;
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return 1;               // Program has failed.
		}

		// Step 6: --------------------------------------------------
		// Use the IWbemServices pointer to make requests of WMI ----

		// ОС и версия
		//=================================================================================================
		IEnumWbemClassObject* pEnumerator = NULL;
		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("SELECT * FROM Win32_OperatingSystem"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator);

		if (FAILED(hres))
		{
			wcout << L"Query for operating system name failed."
				<< L" Error code = 0x"
				<< hex << hres << endl;
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return 1;               // Program has failed.
		}

		// Step 7: -------------------------------------------------
		// Get the data from the query in step 6 -------------------

		IWbemClassObject *pclsObj;
		ULONG uReturn = 0;

		while (pEnumerator)
		{
			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
				&pclsObj, &uReturn);

			if (0 == uReturn)
			{
				break;
			}

			VARIANT vtProp;

			// Get the value of the Name property
			hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
			wcout << L"OS : " << vtProp.bstrVal << endl;
			VariantClear(&vtProp);
			hr = pclsObj->Get(L"Version", 0, &vtProp, 0, 0);
			wcout << L"Version OS : " << vtProp.bstrVal << endl;
			VariantClear(&vtProp);

			pclsObj->Release();
		}
		// Звук
		//=================================================================================================
		pEnumerator->Release();
		pEnumerator = NULL;
		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("SELECT * FROM Win32_SoundDevice"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator);

		if (FAILED(hres))
		{
			wcout << L"Query for sound card name failed."
				<< L" Error code = 0x"
				<< hex << hres << endl;
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return 1;               // Program has failed.
		}
		uReturn = 0;
		while (pEnumerator)
		{
			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
				&pclsObj, &uReturn);

			if (0 == uReturn)
			{
				break;
			}

			VARIANT vtProp;

			// Get the value of the Name property
			hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
			wcout << "Sound : " << vtProp.bstrVal << endl;
			VariantClear(&vtProp);

			pclsObj->Release();
		}
		//Видео
		//=================================================================================================
		pEnumerator->Release();
		pEnumerator = NULL;
		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("SELECT * FROM Win32_VideoController"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator);

		if (FAILED(hres))
		{
			wcout << L"Query for sound card name failed."
				<< L" Error code = 0x"
				<< hex << hres << endl;
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return 1;               // Program has failed.
		}
		uReturn = 0;
		while (pEnumerator)
		{
			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
				&pclsObj, &uReturn);

			if (0 == uReturn)
			{
				break;
			}

			VARIANT vtProp;

			// Get the value of the Name property
			hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
			wcout << L"Video : " << vtProp.bstrVal << endl;
			VariantClear(&vtProp);

			pclsObj->Release();
		}


		// Cleanup
		// ========

		pSvc->Release();
		pLoc->Release();
		pEnumerator->Release();
		//	if (!pclsObj) pclsObj->Release();
		CoUninitialize();

		wcout << endl;
		system("pause");
		return 0;
	}

	LPSTR StrWinError(int _err)
	{
		LPSTR errString = NULL; // will be allocated and filled by FormatMessage
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM, // use windows internal message table
			0, // 0 since source is internal message table
			_err, // this is the error code 
				  // Could just as well have been an error code from generic
				  // Windows errors from GetLastError()
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // auto-determine language to use
			(LPSTR)&errString,
			0, // min size for buffer
			0);
		return errString;
	}

	void WindowsInf() {
		LPTSTR lpszSystemInfo;      // указатель на строку, в которой
									// будет информация о системе.
		DWORD cchBuff = 256;        // длина имени компьютера или
									// пользователя.
		TCHAR tchBuffer[BUFSIZE];   // буфер для строки.

		DWORD dwResult;             // возвращаемое значение функции.

		lpszSystemInfo = tchBuffer;

		// Получаем и отображаем имя компьютера.

		if (GetComputerName(lpszSystemInfo, &cchBuff))
			printf("Computer name:  %s\n", lpszSystemInfo);

		// Получаем и отображаем имя пользователя.

		if (GetUserName(lpszSystemInfo, &cchBuff))
			printf("User name:  %s\n\n", lpszSystemInfo);

		// Получаем и отображаем системную директорию.

		if (GetSystemDirectory(lpszSystemInfo, MAX_PATH + 1))
			printf("System directory:  %s\n", lpszSystemInfo);

		// Получаем и отображаем директорию Windows.

		if (GetWindowsDirectory(lpszSystemInfo, MAX_PATH + 1))
			printf("Windows directory:  %s\n\n", lpszSystemInfo);


		printf("Переменные окружения (partial list): \n");

		// Получаем переменную окружения OS.

		dwResult = ExpandEnvironmentStrings(
			"OS=%OS%",
			lpszSystemInfo,
			BUFSIZE);
		if (dwResult <= BUFSIZE)
			printf("  %s\n", lpszSystemInfo);


		// Получаем переменную окружения PATH.

		dwResult = ExpandEnvironmentStrings(
			"PATH=%PATH%",
			lpszSystemInfo,
			BUFSIZE);
		if (dwResult <= BUFSIZE)
			printf("  %s\n\n", lpszSystemInfo);

		// Получаем переменную окружения TMP.

		dwResult = ExpandEnvironmentStrings(
			"TEMP=%TEMP%",
			lpszSystemInfo,
			BUFSIZE);
		if (dwResult <= BUFSIZE)
			printf("  %s\n\n", lpszSystemInfo);
		system("pause");
	}

};