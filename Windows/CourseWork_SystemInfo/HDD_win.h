#pragma once

#include "GUI_win.h"

#define DRIVE_UNKNOWN     0   // Ќеправильное им€
#define DRIVE_NO_ROOT_DIR 1   // Ќеправильное им€: отсутствует диск
#define DRIVE_REMOVABLE   2   // —ъЄмное устройство (магнито-оптика, zip)
#define DRIVE_FIXED       3   // жЄсткий диск (обычный винчестер)
#define DRIVE_REMOTE      4   // сетевой диск
#define DRIVE_CDROM       5   // CD-ROM
#define DRIVE_RAMDISK     6   // RAM диск

//////////////////
// ѕроста€ таблица соответстви€ кодов из GetDriveType и читабельным
// названи€м типов дисков
//
struct {
	UINT type;        // возвращаемый код из GetDriveType
	LPCSTR name;      // ascii им€
} DriveTypeFlags[] = {
	{ DRIVE_UNKNOWN,     "Unknown" },
	{ DRIVE_NO_ROOT_DIR, "Invalid path" },
	{ DRIVE_REMOVABLE,   "Removable" },
	{ DRIVE_FIXED,       "Fixed" },
	{ DRIVE_REMOTE,      "Network drive" },
	{ DRIVE_CDROM,       "CD-ROM" },
	{ DRIVE_RAMDISK,     "RAM disk" },
	{ 0, NULL },
};


class HDD : protected GUI
{

public:
	void GET_INF() {				
		HDDInf();
		system("pause");
	}

	void HDDInf() //HDD
	{
		TCHAR buf[100];
		DWORD len = GetLogicalDriveStrings(sizeof(buf) / sizeof(TCHAR), buf);

		LPCTSTR msg = "Logical Drives:\n";  // строка STL
		printf(msg);
		for (TCHAR* s = buf; *s; s += _tcslen(s) + 1)
		{
			LPCTSTR sDrivePath = s;
			//msg += sDrivePath;
			//msg += " ";
			printf(sDrivePath);
			printf(" ");

			// GetDriveType получает одно из перечисленных значений
			// DRIVE_UNKNOWN, и т.д.
			//
			UINT uDriveType = GetDriveType(sDrivePath);

			// Ќаходим тип диска в таблице.
			//
			for (int i = 0; DriveTypeFlags[i].name; i++)
			{
				if (uDriveType == DriveTypeFlags[i].type)
				{
					//              msg += DriveTypeFlags[i].name;
					printf(DriveTypeFlags[i].name);
					strcpy(buf, sDrivePath);
					GetVolumeInfo(buf);
					break;
				}
			}
			//      msg += '\n';
			printf("\n");
		}
		//  cout << msg.c_str()*/;
		//return 0;
	}

	void GetVolumeInfo(char* Volume)
	{
		char Name[MAX_PATH];
		char FileSysName[256];
		DWORD SerialNumber;
		DWORD MaxLength;
		DWORD FileSysFlags;
		DWORD SectorsPerCluster;
		DWORD BytesPerSector;
		DWORD NumberOfFreeClusters;
		DWORD TotalNumberOfClusters;

		char str[MAX_PATH];
		if (GetVolumeInformation(
			Volume,
			Name,
			256,
			&SerialNumber,
			&MaxLength,
			&FileSysFlags,
			FileSysName,
			256))
		{
			GetDiskFreeSpace(
				Volume,
				&SectorsPerCluster,
				&BytesPerSector,
				&NumberOfFreeClusters,
				&TotalNumberOfClusters);

			sprintf(str,
				"\t## VOLUME %s INFO\n Name : %s\n Serial number : %p\n File system : %s\n",
				Volume, Name, SerialNumber, FileSysName);
			//printf(str);
			sprintf(str,
				"%s SectorsPerCluster :\t%d\n BytesPerSector :\t%d\n NumberOfFreeClusters :\t%d\n TotalNumberOfClusters : \t%d\n",
				str, SectorsPerCluster, BytesPerSector, NumberOfFreeClusters, TotalNumberOfClusters);
		}
		else
			sprintf(str, "\t## WRONG VOLUME NAME OR NOT READY!");
		printf(str);
	}
};

