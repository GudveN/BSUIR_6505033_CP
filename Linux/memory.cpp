#include "memory.h"

MEMORY::MEMORY()
{

}

void MEMORY::freeMemory() {
    system("less /proc/meminfo");
}

void MEMORY::freeMemorym() {
    system("free -m");
}

void MEMORY::freeMemoryg() {
    system("free -g");
}

void MEMORY::freeMemoryh() {
    system("free -h");
}

void MEMORY::GET_INF()
{
    MEMORY temp_object;
    cout << "1)FREE MEMORY" << endl;
    cout << "2)FREE MEMORY IN MB" << endl;
    cout << "3)FREE MEMORY IN GB" << endl;
    cout << "4)FREE MEMORY IN NORMAL VIEW" << endl;
    char a;
    cin >> a;
    switch(a){
    case '1':{
        temp_object.freeMemory();
    }
    case '2':{
        temp_object.freeMemorym();
        break;
    }
    case '3':{
        temp_object.freeMemoryg();
        break;
    }
    case '4':{
        temp_object.freeMemoryh();
        break;
    }
    default:{
        return;
    }
    }
}
