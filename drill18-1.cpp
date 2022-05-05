#include "std_lib_facilities.h"

int ga[10] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

void f(int ar[], int n)
{
    int la[10] = { };
    for (int i = 0; i < n; ++i) la[i] = ar[i];

    cout << "elements from f array ";
    for (int i = 0; i < n; ++i) cout << la[i] << ' ';
    cout << '\n';

    int* p = new int[n];
    for (int i = 0; i <n; ++i) p[i] = ar[i];

    cout << "elements from f pointer: ";
    for (int i = 0; i < n; ++i) cout << p[i] << ' ';
    cout << '\n'; 

    delete[] p;
}

int fact(int n)
{
    return n > 1 ? n*fact(n-1) : 1;
}

int main()
{
    f(ga, 10);

    int aa[10] = {};
    for(int i = 0; i < 10; ++i)
    {
        aa[i] = fact(i + 1);
    }

    cout << "array of factorials:\n";
    f(aa, 10);

    return 0;
}
