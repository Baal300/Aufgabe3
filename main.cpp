#include <iostream>
#include "liste.h"
#include "item.h"

using namespace std;

int main()
{
   Liste<int> liste;
   liste.print();
   liste.ins(5);
   liste.print();
   liste.ins(6);
   liste.print();
   liste.ins(7);
   liste.print();
   liste.del();
   liste.del();
   liste.del();
   liste.del();
   cout << liste.empty() << '\n';
   liste.print();
   return 0;
}
