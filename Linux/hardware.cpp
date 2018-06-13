#include "hardware.h"

using namespace std;

HARDWARE::HARDWARE() {
}

void HARDWARE::USB() {
    system("lsusb");
    std::cout << std::endl;
    system("lsusb -vt");
}

void HARDWARE::internet() {
    system("iwconfig");
    getchar();
    system("clear");
    system("watch -n 1 cat /proc/net/wireless");
}

void HARDWARE::audio() {
    system("arecord -l");
}

void HARDWARE::systeminf() {
    system("sudo dmidecode -t system");
}

void HARDWARE::bios() {
    system("sudo dmidecode -t bios");
}

void HARDWARE::GET_INF()
{
    HARDWARE temp_object;
    cout << "1)AUDIO INFO" << endl;
    cout << "2)BIOS INFO" << endl;
    cout << "3)LAN INFO" << endl;
    cout << "4)SYSTEM INFO" << endl;
    cout << "5)USB INFO" << endl;
    char a;
    cin >> a;
    switch(a){
    case '1':{
        temp_object.audio();
        break;
    }
    case '2':{
        temp_object.bios();
        break;
    }
    case '3':{
        temp_object.internet();
        break;
    }
    case '4':{
        temp_object.systeminf();
        break;
    }
    case '5':{
        temp_object.USB();
        break;
    }
    default:{
        return;
    }
    }
}
