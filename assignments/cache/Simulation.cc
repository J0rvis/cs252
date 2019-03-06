#include <iostream>
#include "Cache.h"
//#include "Block.h"
//#include "Cache.cc"

using namespace std;


int main(){
cout << "Learning how to use c++\n";
cout << "Calling\n\n";

Cache* c = new Cache(4,8,2,1);
c->display();

cout << "\n\n\n\n" ;

c->read(7);

return 0;
}




