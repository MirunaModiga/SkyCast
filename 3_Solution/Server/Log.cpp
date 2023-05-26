#define _CRT_SECURE_NO_WARNINGS
#include "Log.h"

void Log::write(std::string message)
{
    ofstream outfile;
    time_t now = time(0);
    string time = ctime(&now);
    outfile.open("logfile.txt", std::ios_base::app);
    outfile << time << " ...... " << message << std::endl;
    cout << endl << message << endl;
}
