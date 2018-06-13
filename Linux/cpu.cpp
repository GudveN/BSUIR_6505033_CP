#include "cpu.h"

CPU::CPU()
{

}

void CPU::MAIN_INF()
{
        ifstream stream("/proc/sys/kernel/hostname");
        string str;
        getline(stream,str);
        cout << str << endl;
        uid_t uid = geteuid();
        passwd *pw = getpwuid(uid);
        cout << pw->pw_name << endl;
        struct sysinfo o;
        sysinfo(&o);
        long up = o.uptime;
        int hour = up/60/60;
        int min = (up - hour*60*60) / 60;
        int sec =  ((up - hour*60*60) - min*60);
        cout << hour << " h. " << min << " m. " << sec <<" s." << endl;
        stream.close(); stream.open("/proc/cpuinfo");
        for(int i = 0; i < 16;i++) stream >> str;
        getline(stream,str);
        cout << "Процессор: " << str << endl;
        for(int i = 0; i< 7; i++)  stream >> str;
        cout << "Частота: "  << str << " MHz" << endl;
        while(getline(stream,str))
            cout << str << endl;
        stream.close();
        stream.open("/proc/meminfo");
        stream >> str; stream >> str;
        int num = atoi(str.c_str());
        int percent = num / 100;
        int gb = (num / 1024) / 1024;
        int mb = (num-gb*1024*1024) /1024;
        int kb = (num - (gb*1024*1024+mb*1024));
        if (gb > 0)
           cout << gb <<" Gb ";
        else
           cout << "";
        if (mb > 0)
           cout << (mb) << " Mb ";
        if (kb > 0)
           cout << kb << " Kb " << endl;
        int free = 0;
        for (int i = 0 ; i < 3 ; i++) {
            stream >> str; stream >> str; stream >> str;
            free += atoi(str.c_str());
        }
        num -= free;
        gb = num / 1024 / 1024;
        mb = (num - gb*1024*1024) / 1024;
        kb = (num - ((mb*1024) + (gb * 1024 * 1024)));
        if (gb > 0)
          cout << gb  << " Gb ";
        else
           cout << "";
        if (mb > 0)
           cout << mb << " Mb ";
        if (kb > 0)
          cout << kb << " Kb ";
        percent = num / percent;
        cout << percent << endl;
}

void CPU::CPU_INF()
{
    system("cat /proc/cpuinfo");
}

void CPU::GET_INF()
{
    CPU temp_object;
    cout << "1)INFO FROM FILE" << endl;
    cout << "2)INFO FROM COMMAND" << endl;
    char a;
    cin >> a;
    switch(a){
    case '1':{
        temp_object.MAIN_INF();
        break;
    }
    case '2':{
        temp_object.CPU_INF();
        break;
    }
    default:{
        return;
    }
    }
}
