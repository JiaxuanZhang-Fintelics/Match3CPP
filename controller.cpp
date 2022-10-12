#include <iostream>
#include "map.h"
#include "solver.h"
#include "renderer.h"


static void start(Map* m){
    render(m);
    while(solve(m)){
        while(m->reduce());
        render(m);
    }
}

int main() {
    Map m =  Map(10,10,4,1000,NULL,random);
    render(&m);
    start(&m);
    std::cout<<m.remain()<<"remaining\n";
    std::cout<<m.get_score()<<"\n";

}