#include "std_lib_facilities.h"

void fill (int* a, int size)
{
    int x = 1;
    for (int i = 0; i < size; ++i)
    {
        a[i] = x;
        x *= 2;
    }
}

ostream& print_array(ostream& os, int* a, int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << a[i] << ' ';
    }
    cout << '\n';
    return os;
}


int main()
try {
    // Arrays and Pointers
    int x = 7;
    int* p1 = &x;

    cout << "Pointer " << p1 << " point to " << *p1 << '\n';

    int* p2 = new int[7];
    fill(p2, 7);
    cout << "Array elements: ";
    print_array(cout, p2, 7);

    int* p3 = p2;
    p2 = p1;
    p2 = p3;

    cout << "Pointer " << p1 << " point to " << *p1 << '\n';
    cout << "Pointer " << p2 << " point to " << *p2 << '\n';

    delete[] p2;

    p1 = new int[10];
    fill(p1, 10);

    p2 = new int[10];

    cout << "Array elements: ";
    for(int i = 0; i < 10; ++i)
        p2[i] = p1[i];
    
    print_array(cout, p2, 10);

    // Vectors
    vector<int> v1 {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    vector<int> v2 (10);
    v2 = v1;
    cout << "Vector elements: ";
    for (int v : v2) cout << v << ' ';
    cout << '\n';

    return 0;
} 
catch(exception& e) {
    cerr << "Exception " << e.what() << '\n';
    return 1;
}
catch(...){
    cerr << "Unknown exception\n";
    return 2;
}
