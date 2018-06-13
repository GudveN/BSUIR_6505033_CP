#include "pci.h"

pci::pci() {

}

void pci::pci_inf() {
    system("lspci");
}

void pci::gpuinf() {
    system("lspci | grep -i vga");
    //system("lspci -vvnn | grep VGA");
}

void pci::gpunvidia() {
    system("nvidia-smi");
    system(" nvidia-settings");
}

void pci::gpuradeon() {
    system("fglrxinfo");
}

void pci::GET_INF()
{
    pci temp_object;
    cout << "1)PCI INFO" << endl;
    cout << "2)GPU INFO" << endl;
    cout << "3)INFO ABOUT NVIDIA GPU" << endl;
    cout << "4)INFO ABOUT RADEON GPU" << endl;
    char a;
    cin >> a;
    switch(a){
    case '1':{
        temp_object.pci_inf();
    }
    case '2':{
        temp_object.gpuinf();
        break;
    }
    case '3':{
        temp_object.gpunvidia();
        break;
    }
    case '4':{
        temp_object.gpuradeon();
        break;
    }
    default:{
        return;
    }
    }
}
