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

static void end(Map* m){
    render(m);
    std::cout<<m->remain()<<"remaining\n";
    std::cout<<"Score:"<<m->get_score()<<"\n";
    m->free_map();
}

int main() {
    int pool[30]=
    {0,0,0,0,0,
    1,1,1,1,1,
    0,0,1,0,0,
    0,0,1,0,1,
    1,0,0,0,0,
    1,1,1,0,0};
    Map m =  Map(6,5,4,30,&pool[0],zero);
    //Map m =  Map(10,10,4,1000,NULL,random);
    render(&m);
    start(&m);
    end(&m);

}