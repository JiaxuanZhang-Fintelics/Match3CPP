#include"renderer.h"
#include <iostream>

void render(Map* m){
    for (int i=0;i<m->get_row();i++){
        for (int j=0;j<m->get_col();j++){
            std::cout<<m->map[m->get_col()*i+j];
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}
