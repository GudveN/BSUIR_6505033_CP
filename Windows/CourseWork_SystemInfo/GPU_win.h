#pragma once

#include "GUI_win.h"

#define NVAPI_MAX_PHYSICAL_GPUS   64
#define NVAPI_MAX_USAGES_PER_GPU  34

#pragma comment (lib, "dxgi.lib")

// function pointer types
typedef int *(*NvAPI_QueryInterface_t)(unsigned int offset);
typedef int(*NvAPI_Initialize_t)();
typedef int(*NvAPI_EnumPhysicalGPUs_t)(int **handles, int *count);
typedef int(*NvAPI_GPU_GetUsages_t)(int *handle, unsigned int *usages);

DWORD WINAPI thread3(LPVOID t);

class GPU : protected GUI
{
public:

	void GET_INF()
	{
		cout << "1)Information about GPU\n";
		cout << "2)Begin GPU usage\n";
		cout << "3)Stop GPU usage\n";


		cout << "Load of GPU = ";
		COORD position = { 0,5 };
		COORD defposition = { 14,3 };
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		HANDLE thread = CreateThread(NULL, 0, thread3, NULL, 0, NULL);
		HANDLE Print = CreateEvent(NULL, TRUE, TRUE, "Print1");
		HANDLE Close = CreateEvent(NULL, FALSE, FALSE, "Close1");
		while (1) {
			char temp = getch();
			switch (temp) {
			case '1': {
				SetConsoleCursorPosition(hConsole, position);
				VideoChip();
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

	void VideoChip()//Видеокарта
	{
		IDXGIFactory1 * pFactory;
		HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)(&pFactory));
		int AdapterNumber = 0;
		IDXGIAdapter1* Adapter;
		cout << "Adapters:" << endl;
		while (pFactory->EnumAdapters1(AdapterNumber++, &Adapter) != DXGI_ERROR_NOT_FOUND) {
			DXGI_ADAPTER_DESC1 Desc;
			Adapter->GetDesc1(&Desc);
			wprintf(L"%s\n", Desc.Description);
			Adapter->Release();
		}
		pFactory->Release();
		
	}

	int start()
	{
		HMODULE hmod = LoadLibraryA("nvapi.dll");
		if (hmod == NULL)
		{
			std::cerr << "Couldn't find nvapi.dll" << std::endl;
			return 1;
		}

		// nvapi.dll internal function pointers
		NvAPI_QueryInterface_t      NvAPI_QueryInterface = NULL;
		NvAPI_Initialize_t          NvAPI_Initialize = NULL;
		NvAPI_EnumPhysicalGPUs_t    NvAPI_EnumPhysicalGPUs = NULL;
		NvAPI_GPU_GetUsages_t       NvAPI_GPU_GetUsages = NULL;

		// nvapi_QueryInterface is a function used to retrieve other internal functions in nvapi.dll
		NvAPI_QueryInterface = (NvAPI_QueryInterface_t)GetProcAddress(hmod, "nvapi_QueryInterface");

		// some useful internal functions that aren't exported by nvapi.dll
		NvAPI_Initialize = (NvAPI_Initialize_t)(*NvAPI_QueryInterface)(0x0150E828);
		NvAPI_EnumPhysicalGPUs = (NvAPI_EnumPhysicalGPUs_t)(*NvAPI_QueryInterface)(0xE5AC921F);
		NvAPI_GPU_GetUsages = (NvAPI_GPU_GetUsages_t)(*NvAPI_QueryInterface)(0x189A1FDF);

		if (NvAPI_Initialize == NULL || NvAPI_EnumPhysicalGPUs == NULL ||
			NvAPI_EnumPhysicalGPUs == NULL || NvAPI_GPU_GetUsages == NULL)
		{
			std::cerr << "Couldn't get functions in nvapi.dll" << std::endl;
			return 2;
		}

		// initialize NvAPI library, call it once before calling any other NvAPI functions
		(*NvAPI_Initialize)();

		int          gpuCount = 0;
		int         *gpuHandles[NVAPI_MAX_PHYSICAL_GPUS] = { NULL };
		unsigned int gpuUsages[NVAPI_MAX_USAGES_PER_GPU] = { 0 };

		// gpuUsages[0] must be this value, otherwise NvAPI_GPU_GetUsages won't work
		gpuUsages[0] = (NVAPI_MAX_USAGES_PER_GPU * 4) | 0x10000;

		(*NvAPI_EnumPhysicalGPUs)(gpuHandles, &gpuCount);

		// print GPU usage every second
		COORD position = { 0,3 };
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		HANDLE Print = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Print1");
		HANDLE Close = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Close1");
		while (1)
		{
			if (WaitForSingleObject(Print, INFINITE) == WAIT_OBJECT_0)
			{
				SetConsoleCursorPosition(hConsole, position);
				printf("\r%80c\r", ' ');
				(*NvAPI_GPU_GetUsages)(gpuHandles[0], gpuUsages);
				int usage = gpuUsages[3];
				cout << "GPU Usage: " << usage;
				Sleep(1000);
			}
			if (WaitForSingleObject(Close, 0) == WAIT_OBJECT_0)
			{
				CloseHandle(Print);
				CloseHandle(Close);
				return 1;
			}
		}
		return 0;
	}

	int getch_noblock()
	{
		if (_kbhit())
			return _getch();
		else
			return -1;
	}
};

DWORD WINAPI thread3(LPVOID t)
{
	GPU b;
	b.start();
	return 1;
}
