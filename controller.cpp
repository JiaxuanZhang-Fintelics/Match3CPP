#include <iostream>
#include "map.cpp"

int main() {
    int pool[25]={1,1,1,0,0,
0,0,1,0,1,
0,0,0,0,1,
0,0,0,0,1,
1,1,1,1,1};
    Map m =  Map(5,5,4,25,pool,zero);
    render(&m);
}