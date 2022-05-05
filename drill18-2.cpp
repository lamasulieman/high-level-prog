#include "std_lib_facilities.h"

vector<int> gv {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

void f(vector<int> v)
{
    vector<int> lv(v.size());
    lv = v;

    vector<int> lv2 = v;

    for(int x : lv2) cout << x << ' '; 
    cout << '\n';
}

int fact(int n)
{
    return n > 1 ? n*fact(n-1) : 1;
}

int main()
{
    f(gv);

    vector<int> vv(10); 
    for(int i = 0; i < vv.size(); ++i) 
           vv[i] = fact(i+1);

            f(vv);

    return 0;
}
