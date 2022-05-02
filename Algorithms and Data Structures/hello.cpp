#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>

using namespace std;

class Time {
  private:
    int a;

  public:
    Time() {};

    ~Time() { };

    void DoSomething() {
      cout << "Hi";
    }

};

Time A;
Time *B;

int main () {
  B = new Time;
  A.DoSomething();
  B->DoSomething();
  return 1;
}
