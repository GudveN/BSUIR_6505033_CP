#ifndef CPU_H
#define CPU_H

#include "gui.h"

#include <iostream>
#include <fstream>
#include <pwd.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <vector>
#include <cstdlib>


using namespace std;

class CPU : protected GUI
{
public:
    CPU();
    void MAIN_INF();
    void CPU_INF();
    void GET_INF();
};

#endif // CPU_H
