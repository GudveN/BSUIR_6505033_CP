#include "systeminf.h"

systeminf::systeminf()
{

}

void systeminf::hostname() {
    system("hostname");
}

void systeminf::uname() {
    system("uname");
}

void systeminf::unamen() {
    system("uname -n");
}

void systeminf::unamev() {
    system("uname -v");
}

void systeminf::unamer() {
    system("uname -r");
}

void systeminf::unamem() {
    system("uname -m");
}

void systeminf::unamefull() {
    system("uname -a");
}

void systeminf::manufacture() {
    system("sudo dmidecode -s system-manufacturer");
}

void systeminf::productname() {
    system("sudo dmidecode -s system-product-name");
}

void systeminf::serialnumber() {
    system("sudo dmidecode -s system-serial-number");
}

void systeminf::fullinf() {
    system("sudo dmidecode | more");
}

void systeminf::uptime() {
    //system("uptime");
    //system("who");
    system("w");
}

void systeminf::load() {
   system("cat /proc/loadavg");
   system("sudo top");
}

void systeminf::GET_INF()
{
    systeminf temp_object;
    cout << "1)HOSTNAME" << endl;
    cout << "2)SYSTEM INFO" << endl;
    cout << "3)MANUFACTURE" << endl;
    cout << "4)NAME OF PRODUCT" << endl;
    cout << "5)SERIAL NUMBER" << endl;
    cout << "6)FULL INFO ABOUT SYSTEM" << endl;
    cout << "7)UPTIME" << endl;
    cout << "8)LOAD OF SYSTEM" << endl;
    char a;
    cin >> a;
    switch(a){
    case '1':{
        temp_object.hostname();
    }
    case '2':{
        temp_object.unamefull();
        break;
    }
    case '3':{
        temp_object.manufacture();
        break;
    }
    case '4':{
        temp_object.productname();
        break;
    }
    case '5':{
        temp_object.serialnumber();
    }
    case '6':{
        temp_object.fullinf();
        break;
    }
    case '7':{
        temp_object.uptime();
        break;
    }
    case '8':{
        temp_object.load();
        break;
    }
    default:{
        return;
    }
    }
}
