#include "std_lib_facilities.h"


void print( int a,int b)
{
   cout << "after swapping :" <<a<<'\t'<<b<<endl;
}

void swap_v(int a, int b)      // passing as copies
{
    int temp;
    temp = a;
    a = b;
    b = temp;
    print(a,b);
}

void swap_r(int& a, int& b)       // passing as refrences
{
    int temp;
    temp = a;
    a = b;
    b = temp;
    print(a,b);
}


void swap_cr(const int& a, const int& b)     //passing as constants , constants cannot be edited so we store in temp
{
    int temp, temp1;
    temp = a;
    temp1 = b;
    swap_r(temp,temp1);
}


int main()
{
    int x = 7;
    int y = 9;
    
    swap_v(x, y);
    swap_v(7, 9);
    
    const int cx = 7;
    const int cy = 9;
    
    swap_cr(cx, cy);
    swap_cr(7.7, 9.9);
    
    double dx = 7.7;
    double dy = 9.9;
    
    swap_v(dx, dy);
    swap_cr(7.7, 9.9);

   
}
