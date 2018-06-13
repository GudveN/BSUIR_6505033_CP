#pragma once
#include <conio.h>
#include <process.h>
#include <Windows.h>
#include <string>
#include <intrin.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <dxgi.h>
#include <string>
#include <iomanip>
#include <comdef.h>
#include <Wbemidl.h>

#include <wchar.h>
#include <tlhelp32.h>
#include "tchar.h"
#include "winbase.h"

class GUI
{
public:
	virtual void GET_INF() = 0;
	int getch_noblock()
	{
		if (_kbhit())
			return _getch();
		else
			return -1;
	}
};
