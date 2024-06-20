#include "SortingArray.h"

SortingArray::SortingArray(int _length)
{
    if (_length <= 0)
        return;

    length = _length;
    arr = new int[length];
}
SortingArray::SortingArray(int _length, bool _mt) : SortingArray(_length)
{
    make_thread = _mt;
}

SortingArray::~SortingArray()
{
    if (arr)
        delete[] arr;
}

void SortingArray::setMultithreadingOn()
{
	make_thread = true;
}
void SortingArray::setMultithreadingOff()
{
	make_thread = false;
}
void SortingArray::display()
{
    for (int i{ 0 }; i < length; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void SortingArray::startSorting()
{
    switch (make_thread)
    {
    case true:
        cout << "Многопоточная сортировка!\n{\n";
        break;
    case false:
        cout << "Однопоточная сортировка!\n{\n";
        break;
    }

    auto start = chrono::high_resolution_clock::now();
    quicksort(arr, 0, length - 1, make_thread);
    auto finish = chrono::high_resolution_clock::now();
    auto duration = chrono::duration<double>(finish - start);
    cout << "Затраченное время: " << std::setprecision(3) << duration.count() << "секунд." << endl;

    cout << "Проверка на правильность сортировки...\n";
    switch (check(arr, length))
    {
    case true:
        cout << "Отсортировано корректно\n";
        break;
    case false:
        cout << "Ошибка сортировки\n";
        break;
    }
    cout << "}\n\n";
}
void SortingArray::fillArrayWithRandValues(int l_inter, int r_interv)
{
    int l = l_inter;
    int r = (r_interv == -1) ? 1000 : r_interv;

	for (int i{ 0 }; i < length; i++)
		arr[i] = ( rand() % (r - l) ) + l;
}

bool check(int* arr, int length)
{
    for (int i{ 0 }; i < length - 1; i++)
        if (arr[i] > arr[i + 1])
            return false;
    return true;
}
void quicksort(int* array, long left, long right, bool make_thread)
{
    if (left >= right) return;
    long left_bound = left;
    long right_bound = right;

    long middle = array[(left_bound + right_bound) / 2];

    do {
        while (array[left_bound] < middle) {
            left_bound++;
        }
        while (array[right_bound] > middle) {
            right_bound--;
        }

        //Меняем элементы местами
        if (left_bound <= right_bound) {
            std::swap(array[left_bound], array[right_bound]);
            left_bound++;
            right_bound--;
        }
    } while (left_bound <= right_bound);

    if (make_thread && (right_bound - left > 100000))
    {
        RequestHandler rh;
        // если элементов в левой части больше чем 10000
        // вызываем асинхронно рекурсию для правой части
        std::future<void> t = rh.pushRequest(quicksort, array, left, right_bound, make_thread);
        quicksort(array, left_bound, right, make_thread);
        t.wait();
    }
    else {
        // запускаем обе части синхронно
        quicksort(array, left, right_bound, make_thread);
        quicksort(array, left_bound, right, make_thread);
    }
}