#include <iostream>
#include <liste.h>

using namespace std;

int main()
{
    Liste<int> liste;
    liste.menu();
    liste.print();
   // liste.ins(5.4);
    liste.print();
  //  liste.ins(6.2);
    liste.print();
  //  liste.ins(7);
    liste.print();
    liste.del();
    liste.del();
    liste.del();
   // liste.ins(8);
  //  liste.ins(9);;
    cout << liste.end() << '\n';
    liste.print();
    liste.del();
    cout << liste.end() << '\n';
    cout << liste.empty() << '\n';
    liste.print();
    return 0;
}
