#include"renderer.h"
#include <iostream>

void render(Map* m){
    int* map=m->get_map();
    for (int i=0;i<m->get_row();i++){
        for (int j=0;j<m->get_col();j++){
            std::cout<<map[m->get_col()*i+j];
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}
