#include<iostream>
#include<utility>
#include<list>
#include<math.h>

using namespace std;

unsigned long long fact(unsigned n) { return n < 2 ? 1ull : fact(n - 1u); }

int f(int n) { return n < 0 ?  (n*n*n)%243:(fact(n)-1)%143; }
int f(double d) { return (int)exp(1. / sin(d)) % 343; }
int f(string s) {
    int a = 0;
    for (auto c : s)  if (c == 'a' || c == 'e' || c == 'y' || c == 'u' || c == 'i' || c == 'o' ) {a++; }
    return a;
}
template<class T1, class T2>
int f(pair<T1, T2> p) { return (int)pow(f(p.second),  f(p.first))%543; }
template<class T>
int f(list<T> v) {
    int res = 0;
    auto a = v.end();
    for(auto i:v){res+=*--a*i;}
    return res%743;
}
template<class T>
int f(T n) { return 1251; }

int main() {
    int a = 1, b = -1;
    double d = 530.;
    string s = "straio";
    pair<int, int> p = { 12,5 };
    list<int> v = { 1,2,3,7,14 };
    char x = 'x';
    cout << x << "\t\t| " << "f(x)" << endl;
    cout << "________________|__________" << endl;
    cout << b << "\t\t| " << f(b) << endl;
    cout << a << "\t\t| " << f(a) << endl;
    cout << d << "\t\t| " << f(d) << endl;
    cout << s << "\t\t| " << f(s) << endl;
    cout << '(' << p.first << " " << p.second << ')' << "\t\t| " << f(p) << endl;
    cout << '{';
    for (auto e : v)cout << e << ' ';
    cout << '}' << "\t| " << f(v) << endl;
    cout << x << "\t\t| " << f(x) << endl;
    return 0;
}