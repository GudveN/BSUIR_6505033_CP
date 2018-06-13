#ifndef HDD_H
#define HDD_H

#include "gui.h"

#include <iostream>
#include <fstream>
#include <pwd.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <vector>
#include <cstdlib>

using namespace std;

class HDD : protected GUI
{
public:
    HDD();
    void HDDINF();
    void HDDBlock();
    void freespace();
    void GET_INF();
};

#endif // HDD_H
