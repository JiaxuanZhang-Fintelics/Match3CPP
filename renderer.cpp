#include"map.cpp"
#include <iostream>
void render(Map* m){
    for (int i=0;i<m->row;i++){
        for (int j=0;j<m->col;i++){
            std::cout<<m->map[m->col*i+j];
        }
        std::cout<<"\n";
    }
}