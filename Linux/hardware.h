#ifndef HARDWARE_H
#define HARDWARE_H

#include "gui.h"

#include <iostream>
#include <fstream>
#include <pwd.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <vector>
#include <cstdlib>

class HARDWARE : protected GUI
{
public:
    HARDWARE();
    void USB();
    void internet();
    void audio();
    void systeminf();
    void bios();
    void GET_INF();
};

#endif // HARDWARE_H
