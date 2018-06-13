#ifndef PCI_H
#define PCI_H

#include "gui.h"

#include <iostream>
#include <fstream>
#include <pwd.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <vector>
#include <cstdlib>

using namespace std;

class pci : protected GUI
{
public:
    pci();
    void pci_inf();
    void gpuinf();
    void gpunvidia();
    void gpuradeon();
    void GET_INF();
};

#endif // PCI_H
