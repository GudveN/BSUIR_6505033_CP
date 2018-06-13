#include "hdd.h"

HDD::HDD() {
}

void HDD::HDDINF() {
    system("sudo fdisk -l | grep '^Disk /dev'");
    system("sudo fdisk -l /dev/sda");
    //system("sudo fdisk /dev/sda");
    //system("sudo e2label /dev/sda1");
    //system("sudo cfdisk /dev/sda");
}

void HDD::HDDBlock() {
    system("lsblk");
}

void HDD::freespace() {
    system("df -H");
}

void HDD::GET_INF()
{
    HDD temp_object;
    cout << "1)HDD INFO" << endl;
    cout << "2)FREE SPACE" << endl;
    cout << "3)BLOCK INFO" << endl;
    char a;
    cin >> a;
    switch(a){
    case '1':{
        temp_object.HDDINF();
    }
    case '2':{
        temp_object.freespace();
        break;
    }
    case '3':{
        temp_object.HDDBlock();
        break;
    }
    default:{
        return;
    }
    }
}
