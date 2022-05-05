#include "std_lib_facilities.h"

ostream& print_vector(ostream& os, vector<int>& v, int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << v[i] << ' ';
    }
    cout << '\n';
    return os;
}

void fill (vector<int>& v, int size)
{
    int x = 100;
    for (int& v : v)
    {
        v = x;
        ++x;
    }
}

int main()
{
    int n = 20;
    vector<int> v(n);
    fill(v, n);
    print_vector(cout, v, n);

    return 0;
}
