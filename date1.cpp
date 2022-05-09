#include "std_lib_facilities.h"

struct Date {      //defining a data type called date 
    int y;
    int m;
    int d;
};

void init_day(Date& dd, int y, int m, int d)
{
    if (m < 1 || m > 12) error("invalid month");
    if (d < 1 || d > 31) error("impossible day");
    dd.y = y;           // to be able to edit them
    dd.m = m;
    dd.d = d;
}
void add_day(Date& dd, int n)       // fun that adds n days 
{
   
    dd.d += n;
    if (dd.d > 31) dd.d %= 31;
}
//to print 
ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}
int main()
{
// define today 
    Date today;
    init_day(today, 1978, 6, 25);
// define tomorrow 
    Date tomorrow = today;
    add_day(tomorrow, 1);
    cout << today << '\n'
         << tomorrow << '\n';
    //Date bad_day;
    //init_day(bad_day, 2004, 13, -5);
}


