#include <iostream>
#include <random>
#include "SortingArray.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    srand(0);
    
    SortingArray a(10000000);
    a.fillArrayWithRandValues();
    a.setMultithreadingOn();
    a.startSorting(); 
    a.fillArrayWithRandValues();
    a.setMultithreadingOff();
    a.startSorting();

    return 0;
}