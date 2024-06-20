#pragma once
#include <Array>
#include <iostream>
#include "RequestHandler.h"

using namespace std;

void quicksort(int* array, long left, long right, bool make_thread);

bool check(int* arr, int length);

class SortingArray
{
private:
	int* arr = nullptr;
	int length;
	bool make_thread = false;
public:
	SortingArray(int _length);
	SortingArray(int _length, bool _mt);
	~SortingArray();
	void setMultithreadingOn();
	void setMultithreadingOff();
	void fillArrayWithRandValues(int l_inter = 0, int r_interv = -1);
	void display();
	void startSorting();
};

