#include "std_lib_facilities.h"

enum class Month
{
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec        // constants now not later stored in a vector
};

struct Date {
    int y; Month m; int d;
public:
    Date(int y, Month m, int d);

    void add_day(int n);

    Month month() const { return m; }
    int day() const { return d; }
    int year() const {return y; }
};

Date::Date(int yy, Month mm, int dd)
{

        if (int(mm) < 1 || int(mm) > 12)
        cout << "Error, invalid month." << endl;
        else if (dd < 1 || dd > 31)
        cout << "Error, invalid day." << endl;
        
   else
    {
        y = yy;
        m = mm;
        d = dd;
    }

    return;
}

void Date::add_day(int n)
{
    bool lastDay = false;
    bool endYear = false;
    for (int i = 0; i < n; ++i)
    {
        if (d == 31) 
        {
            lastDay = true;
            d = 1;
        }
        else ++d;

        if (lastDay)
        {
            lastDay = false;
            if (int(m) == 12)
            {
                m = Month::jan;
                endYear = true;
            }
            m = Month(int(m) + 1);
        }
       
        
    }
    
}

//to print
ostream& operator<<(ostream& os, const Date& d)
{
    return os << d.d << "/" << int(d.m) << "/" << d.y << endl; 
}

int main()
{
    
    Date today {1978, Month::jun, 25};
    cout << "Today: " << today << endl;

    Date tomorrow {today};
    tomorrow.add_day(1);
    
    cout << "Tomorrow: " << tomorrow << endl;

    //Date bad_date {2008, Month::dec, -4};

    return 0;

}
