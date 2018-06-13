#ifndef SYSTEMINF_H
#define SYSTEMINF_H

#include "gui.h"

#include <iostream>
#include <fstream>
#include <pwd.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <vector>
#include <cstdlib>

using namespace std;

class systeminf : protected GUI
{
public:
    systeminf();

    void hostname();
    void uname();
    void unamen();
    void unamev();
    void unamer();
    void unamem();
    void unamefull();

    void serialnumber();
    void manufacture();
    void productname();

    void fullinf();

    void uptime();
    void load();
    void GET_INF();
};

#endif // SYSTEMINF_H
