//calculator discussed in the videos.


#include "std_lib_facilities.h"

constexpr char number = '8';
constexpr char quit = 'q';
constexpr char print = ';';
constexpr char result = '=';
constexpr char let = '#';
constexpr char name = 'a';
//const string declkey = "let";

const string quitkey = "exit";


constexpr char squarer = 's';
const string sqrtkey = "sqrt";

constexpr char power = '^';
const string powkey = "pow";

double expression();
double powernum();

class Variable {
public:
    string name;
    double value;
};

vector<Variable> var_table;

bool is_declared(string var)
{
    for (const auto& v : var_table)
        if (v.name == var) return true;
    return false;
}

double define_name (string var, double val)
{
    if (is_declared(var)) error(var, "declared twice");
    var_table.push_back(Variable{var, val});
    return val;
}

double get_value(string var)
{
    for (const auto& v : var_table)
        if (v.name == var) return v.value;
    error(var, "undefined variable");
}

void set_value(string var, double val)
{
    for (auto& v : var_table)
        if(v.name == var)
        {
            v.value = val;
            return;
        }
        error(var, "undefined variable");
}

class Token {
public:
    char kind;
    double value;
    string name;
    Token(char ch): kind(ch), value(0) {}
    Token(char ch, double val): kind(ch), value(val) {}
    Token(char ch, string n) : kind(ch), name(n) {}
};

class Token_stream {
public:
    Token_stream();
    Token get();
    void putback(Token t);
    void ignore(char c);
private:
    Token buffer;
    bool full;
};

Token_stream::Token_stream(): full(false), buffer(0) {}

void Token_stream::putback(Token t)
{
    if(full) error ("Token stream buffer is full!");
    buffer = t;
    full = true;
}

Token Token_stream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;

    switch(ch)
    {
        case let:
        case quit:
        case print:
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '=':
        case ',':
            return Token(ch);
        case '.':
        case '0': case '1':
        case '2': case '3':
        case '4': case '5':
        case '6': case '7':
        case '8': case '9':
        {
            // 34*5;
            cin.putback(ch);
            double val;
            cin >> val;
            return Token(number, val);
        }
        default:
        {
            if (isalpha(ch)){
                string s;
                s += ch;
                while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
                cin.putback(ch);
                /*if ( s == declkey) return Token{let};
                else if (is_declared(s))
                    return Token(number, get_value(s)); */

                if (s == sqrtkey) return Token{squarer};

                if (s == powkey) return Token{power};

                if (s == quitkey) return Token{quit};

                return Token(name, s);

            }
            error("Invalid token!");
        }
    }
}

void Token_stream::ignore(char c)
{
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }

    full = false;

    char ch = 0;
    while (cin >> ch)
        if (ch == c) return;
}

Token_stream ts;

void clean_up_mess(){
    ts.ignore(print);
}

double primary()
{
    Token t = ts.get();
    switch(t.kind)
    {
        case '(':
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error (") is expected!");
            return d;
        }
        case number:
            return t.value;
        case name:
            return get_value(t.name);
        case '-':
            return - primary();
        case '+':
            return primary();
        default:
            error("Primary expected!");
    }
}

double term()
{
    double left = primary();
    Token t = ts.get();
    while(true)
    {
        switch(t.kind)
        {
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/':
                left /= primary(); // check zero divider
                t = ts.get();
                break;
            case '%':
            {
                /*
                double d = primary();
                if (d == 0) error("Zero divider at %");
                left = fmod(left, d);
                t = ts.get();
                break;
                */
                int i1 = narrow_cast<int> (left);
                int i2 = narrow_cast<int> (primary());
                if (i2 == 0) error("Zero divider at %");
                left = i1 % i2;
                t =ts.get();
                break;
            }
            default:
                ts.putback(t);
                return left;
        }
    }
}

double expression()
{
    double left = term(); // 43-34;
    Token t = ts.get();
    while (true)
    {
        switch(t.kind)
        {
            case '+':
                left += term();
                t = ts.get();
                break;
            case '-':
                left -= term();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}

double declaration()
{
    Token t = ts.get();
    if (t.kind != name) error("name expected in declaration");
    string var_name = t.name;


    Token t2 = ts.get();
    if (t2.kind != '=') error("= expected");

    double d = expression();
    define_name(var_name, d);
    return d;
}

double square_root()
{
    double d = expression(); //handles brackets in primary.
    if (d < 0) error(d, " is a negative number, can't perform a sqrt");
    return sqrt(d);
}

double powernum()
{
    Token t = ts.get();
    if(t.kind != '(') error(" '(' was expected");
    double base = expression();

    t = ts.get();
    if (t.kind != ',') error(" ',' was expected");

    int exponent = narrow_cast<int> (expression());

    t = ts.get();
    if(t.kind != ')') error("')' was expected");

    return pow(base,exponent);
   
}

double statement()
{
    Token t = ts.get();
    switch(t.kind)
    {
        case let:
            return declaration();
        case squarer:
            return square_root();
        case power:
            return powernum();
        default:
            ts.putback(t);
            return expression();
    }
}

void calculate()
{
    while(cin)
    try {
        Token t = ts.get();
        while(t.kind == print) t =ts.get();
        if (t.kind == quit) return;
        ts.putback(t);
        cout << result << statement() << endl;
    } catch (exception& e) {
        cerr << e.what() << endl;
        clean_up_mess();
    }
    /*
    double val = 0;
    while(cin)
    {
        Token t = ts.get();
        if (t.kind == quit) break;
        if (t.kind == print)
            cout << result << val << endl;
        else
        ts.putback(t);
        
        val = expression();
    }
    */
}

int main () 
try {
    //predefine names:
    define_name("pi", 3.1415926535);
    define_name("e", 2.7182818284);

	// Question 6
    define_name("k", 1000);
    
    calculate();

    return 0;

} catch (exception& e) {
    cerr << e.what() << endl;
    return 1;
} catch (...) {
    cerr << "Some exception!" << endl;
    return 2;
}


	
