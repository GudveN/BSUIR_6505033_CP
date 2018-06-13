#include <iostream>
#include <fstream>
#include <pwd.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <vector>
#include <cstdlib>

#include "cpu.h"
#include "systeminf.h"
#include "pci.h"
#include "hardware.h"
#include "hdd.h"
#include "memory.h"

using namespace std;

int main()
{

    while(1)
    {
        cout << "1)CPU INFO" << endl;
        cout << "2)PCI INFO" << endl;
        cout << "3)HARDWARE INFO" << endl;
        cout << "4)HDD INFO" << endl;
        cout << "5)MEMORY INFO" << endl;
        cout << "6)SYSTEM INFO" << endl;
        char a;
        cin >> a;
        switch(a){
        case '1':{
            CPU ab;
            system("clear");
            ab.GET_INF();
            cin.ignore();
            cin.get();
            system("clear");
            break;
        }
        case '2':{
            pci b;
            system("clear");
            b.GET_INF();
            cin.ignore();
            cin.get();
            system("clear");
            break;
        }
        case '3':{
            HARDWARE c;
            system("clear");
            c.GET_INF();
            cin.ignore();
            cin.get();
            system("clear");
            break;
        }
        case '4':{
            HDD d;
            system("clear");
            d.GET_INF();
            cin.ignore();
            cin.get();
            system("clear");
            break;
        }
        case '5':{
            MEMORY e;
            system("clear");
            e.GET_INF();
            cin.ignore();
            cin.get();
            system("clear");
            break;
        }
        case '6':{
            systeminf f;
            system("clear");
            f.GET_INF();
            cin.ignore();
            cin.get();
            system("clear");
            break;
        }
        default:{
            return 1;
        }
        }
    }
    return 0;
}

