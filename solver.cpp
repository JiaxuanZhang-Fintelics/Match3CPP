#include "map.h"
#include "solver.h"


// // for each grid, swap the objects with adjacent objects and find the best swap
bool solve(Map* m){
    int max_idx=0;
    int vmax[MAX_DIM]={0};
    int hmax[MAX_DIM]={0};
    int v_max_idx=0;
    int h_max_idx=0;
    int max_swap=0;
    int* map=m->get_map();
    for(int i =0;i<m->get_col()*m->get_row();i++){
        //  swap to left
        if(i%m->get_col()>0){
            m->swap(i,i-1);
            if(map[i]!=0){
                int v[MAX_DIM]={0};
                int h[MAX_DIM]={0};
                int v_idx=0;
                int h_idx=0;
                m->find_around(i,v,h,&v_idx,&h_idx);
                if(compare(v_max_idx,h_max_idx,v_idx,h_idx)){
                    max_idx=i;
                    max_swap=i-1;
                    v_max_idx=v_idx;
                    h_max_idx=h_idx;
                    for(int j =0;j<MAX_DIM;j++){
                        vmax[j]=v[j];
                        hmax[j]=h[j];
                    }
                }
            }
            m->swap(i,i-1);
        }
        //  swap to right
        if(i%m->get_col()<m->get_col()-1){
            m->swap(i,i+1);
            if(map[i]!=0){
                int v[MAX_DIM]={0};
                int h[MAX_DIM]={0};
                int v_idx=0;
                int h_idx=0;
                m->find_around(i,v,h,&v_idx,&h_idx);
                if(compare(v_max_idx,h_max_idx,v_idx,h_idx)){
                    max_idx=i;
                    max_swap=i+1;
                    v_max_idx=v_idx;
                    h_max_idx=h_idx;
                    for(int j =0;j<MAX_DIM;j++){
                        vmax[j]=v[j];
                        hmax[j]=h[j];
                    }
                }
            }
            m->swap(i,i+1);
        }
        //  swap up
        if(i>m->get_col()){
            m->swap(i,i-m->get_col());
            if(map[i]!=0){
                int v[MAX_DIM]={0};
                int h[MAX_DIM]={0};
                int v_idx=0;
                int h_idx=0;
                m->find_around(i,v,h,&v_idx,&h_idx);
                if(compare(v_max_idx,h_max_idx,v_idx,h_idx)){
                    max_idx=i;
                    max_swap=i-m->get_col();
                    v_max_idx=v_idx;
                    h_max_idx=h_idx;
                    for(int j =0;j<MAX_DIM;j++){
                        vmax[j]=v[j];
                        hmax[j]=h[j];
                    }
                }
            }
            m->swap(i,i-m->get_col());
        }
        //  swap to down
        if(i<(m->get_row()-1)*m->get_col()){
            m->swap(i,i+m->get_col());
            if(map[i]!=0){
                int v[MAX_DIM]={0};
                int h[MAX_DIM]={0};
                int v_idx=0;
                int h_idx=0;
                m->find_around(i,v,h,&v_idx,&h_idx);
                if(compare(v_max_idx,h_max_idx,v_idx,h_idx)){
                    max_idx=i;
                    max_swap=i+m->get_col();
                    v_max_idx=v_idx;
                    h_max_idx=h_idx;
                    for(int j =0;j<MAX_DIM;j++){
                        vmax[j]=v[j];
                        hmax[j]=h[j];
                    }
                }
            }
            m->swap(i,i+m->get_col());
        }
    }
    // check solved or not
    if(v_max_idx>1 || h_max_idx>1){
        m->swap(max_idx,max_swap);
        return true;
    }
    return false;
}
