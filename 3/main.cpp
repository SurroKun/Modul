#include <iostream>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <memory>

using namespace std;

static int S = 100;                      //Глобальна змінна яку змінюють деструктори
int n;

class Base                          //Базовий абстрактний
{
public:
  virtual void r() = 0;                  //Чисто віртуальна функція
  Base() {}                        //Конструктор
  ~Base() { S = S / 2 - 3 * n - 3; }            //Деструктор
  int N;                          //Порядковий номер
  static vector<pair<int, void*>> v;            //Список об'єктів
  Base* base1, * base2;                  //Вкладені екземпляри
  static int number;                    //Загальна кількість всіх об'єктів
};

vector<pair<int, void*>> Base::v;              //static поля
int Base::number = 0;                    //

class Alpha :Base
{
public:
  void r() {}
  Alpha();
  ~Alpha();
  int N;
};

Alpha::Alpha()
{
  N = ++number;                      //Ініціалізуемо номер N при створенні нового об'єкта і збільшуемо number на 1
  v.push_back({ 1,this });                //Додаємо в список об'єктів новий об'єкт
}

Alpha::~Alpha()
{
  S = S + N;
  number--;
  n = N;
}

class Beta :Base
{
public:
  void r() {}
  Beta();
  ~Beta();
  int N;
};

Beta::Beta()
{
  N = ++number;
  v.push_back({ 2,this });
}

Beta::~Beta()
{
  S = S - 2 * N;
  number--;
  n = N;
}

class Gamma :Base
{
public:
  void r() {}
  Gamma();
  ~Gamma();
  int N;
};

Gamma::Gamma()
{
  N = ++number;
  v.push_back({ 3,this });
}

Gamma::~Gamma()
{
  S = S + N - 1;
  number--;
  n = N;
}

pair<int, int> t(pair<int, void*>& a, pair<int, void*>& b) {//Функція яка кладе 2 int в 1 pair<int, int>
  int N1, N2;
  if (a.first == 1)N1 = ((Alpha*)a.second)->N;
  if (a.first == 2)N1 = ((Beta*)a.second)->N;
  if (a.first == 3)N1 = ((Gamma*)a.second)->N;

  if (b.first == 1)N2 = ((Alpha*)b.second)->N;
  if (b.first == 2)N2 = ((Beta*)b.second)->N;
  if (b.first == 3)N2 = ((Gamma*)b.second)->N;
  pair<int, int> N;
  N.first = N1;
  N.second = N2;
  return N;
}

bool operator < (pair<int, void*>& a, pair<int, void*>& b) {//Перевантаження операторів порівняння
  pair<int, int> l = t(a, b);
  return l.first < l.second;
}

bool operator == (pair<int, void*>& a, pair<int, void*>& b) {
  pair<int, int> l = t(a, b);
  return l.first == l.second;
}

bool operator != (pair<int, void*>& a, pair<int, void*>& b) {
  pair<int, int> l = t(a, b);
  return l.first != l.second;
}


int oracle(vector<pair<int, void*>>& v) {          //Функція передбачення значення глобальної змінної
  if (!v.size())return S;
  int res = S;
  reverse(v.begin(), v.end());
  for (auto a : v) {
    if (a.first == 1) { res = res + ((Alpha*)a.second)->N; res = res / 2 - 3 * ((Alpha*)a.second)->N - 3; }
    if (a.first == 2) { res = res - 2 * ((Beta*)a.second)->N; res = res / 2 - 3 * ((Beta*)a.second)->N - 3; }
    if (a.first == 3) { res = res + ((Gamma*)a.second)->N - 1; res = res / 2 - 3 * ((Gamma*)a.second)->N - 3; }
  }
  reverse(v.begin(), v.end());
  return res;
}

void foo() {                        //Тестова функція
  shared_ptr<Alpha> alpha(new Alpha);
  shared_ptr<Beta> beta1(new Beta);
  shared_ptr<Beta> beta2(new Beta);
  shared_ptr<Gamma> gamma(new Gamma);
  cout << "S will be equal " << oracle(Base::v) << endl;
  Base::v.clear();
}

int main() {
  foo();
  cout << "S = " << S << endl;
  cout << "_____________________" << endl;
  shared_ptr<Alpha> alpha(new Alpha);
  shared_ptr<Beta> beta1(new Beta);
  shared_ptr<Beta> beta2(new Beta);
  shared_ptr<Gamma> gamma(new Gamma);
  while (next_permutation(Base::v.begin(), Base::v.end()))//Перебір усіх варіантів
  {
    S = 100;
    cout << "S will be equal |" << oracle(Base::v) << endl;
  }

}