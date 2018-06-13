#ifndef MEMORY_H
#define MEMORY_H

#include "gui.h"

#include <iostream>
#include <fstream>
#include <pwd.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <vector>
#include <cstdlib>

using namespace std;

class MEMORY : protected GUI
{
public:
    MEMORY();
    void freeMemory();
    void freeMemorym();
    void freeMemoryg();
    void freeMemoryh();
    void GET_INF();
};

#endif // MEMORY_H
