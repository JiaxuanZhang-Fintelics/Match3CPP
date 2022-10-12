#ifndef MAP_CPP
#define MAP_CPP
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include<iostream>    
#include<algorithm>
#include <random>       // std::default_random_engine  
using namespace std;
#include "map.h"

// return true if 2 is better than 1
bool compare(int v1,int h1,int v2,int h2){
    // both 1 and 2 are L or T shape
    if(v1>1 && h1>1 && v2>1 && h2>1 
    && v1+h1<v2+h2){
        return true;
    }
    // only 2 is L or T shape
    else if (v2>1 && h2>1
    && (std::max(v1,h1)< v2+h2)){
        return true;
    }
    // only vertical or horizontal
    else if((std::max(v1,h1)< std::max(v2,h2))){
        return true;
    }
    return false;
}


     // Constructor, generate random int in every grid and reduce
    Map::Map(int row, int col, int objs,int pool_size,int* init_pool,mode m){
        // initialization
        this->row=row;
        this->col=col;
        this->objs=objs;
        this->pool_size=pool_size;
        this->m=m;
        this->pool=(int*)malloc(pool_size*sizeof(int));
        this->map=(int*)malloc(row*col*sizeof(int));
        this->pool_idx=0;
        this->score=0;
        this->obj_count=0;
        // set up pool
        for(int i=0;i<pool_size;i++){
            // copy init_pool if exist
            if(init_pool){
               pool[i]=init_pool[i];
            }
            // generate random int
            else if (m==random){
                pool[i]=rand()%objs+1;
            }
            // fill 0
            else if (m==zero){
                pool[i]=0;
            }
            // three same objects in a set
            else{
                int obj=rand()%objs+1;
                for(int j=0;j<3;j++){
                    pool[i]=obj;
                    i++;
                }
                i--;
            }
        }
        // shuffle only in three and no init_pool
        if(!init_pool && m==three){
            std::shuffle(pool,pool+pool_size,default_random_engine());
        }
        // load to map
        for(int i=0;i<col*row;i++){
            map[i]=pool[pool_idx];
            pool_idx++;
        }
        reduce_and_fill_pool();
        score=0;
    }

    // fill index with object in the pool
    void Map::fill(int index){
        // empty pool, fill 0
        if(pool_idx==pool_size){
            map[index]=0;
        }
        // fill from pool
        else{
            map[index]=pool[pool_idx];
            pool_idx++;
        }
        score++;
    }

    // use the value above to cover value in index recursively
    void Map::remove(int index){
        if(index<col){
            fill(index);
            return;
        }
        map[index]=map[index-col];
        remove(index-col);
    }

     // find_direction functions are modified recursive dfs that only find 
    // consective objects in one direction

    void Map::find_up(int i, int*v, int* v_idx){
        if(i<0) return;
        if(i>col*row) return;
        if(map[i]==0) return;
        if(i>=col && map[i]==map[i-col]){
            v[*v_idx]=i-col;
            *v_idx=*v_idx+1;
            find_up(i-col,v,v_idx);
        }
    }
    void Map::find_down(int i, int*v, int* v_idx){
        if(i<0) return;
        if(i>col*row) return;
        if(map[i]==0) return;
        if(i/col<(row-1) && map[i]==map[i+col]){
            v[*v_idx]=i+col;
            *v_idx=*v_idx+1;
            find_down(i+col,v,v_idx);
        }
    }
    void Map::find_left(int i, int*h, int* h_idx){
        if(i<0) return;
        if(i>col*row) return;
        if(map[i]==0) return;
        if(i%col>0 && map[i]==map[i-1]){
            h[*h_idx]=i-1;
            *h_idx=*h_idx+1;
            find_left(i-1,h,h_idx);
        }
    }
    void Map::find_right(int i, int*h, int* h_idx){
        if(i<0) return;
        if(i>col*row) return;
        if(map[i]==0) return;
        if(i%col<(col-1) && map[i]==map[i+1]){
            h[*h_idx]=i+1;
            *h_idx=*h_idx+1;
            find_right(i+1,h,h_idx);
        }
    }

    // find consecutive objects in four directions
    void Map::find_around(int i,int* v,int* h,int* v_idx,int* h_idx){
        find_up(i,v,v_idx);
        find_down(i,v,v_idx);
        find_left(i,h,h_idx);
        find_right(i,h,h_idx);
    }

    //reduce consecutive objects around i, including i
    bool Map::reduce_around(int i,int* v,int* h,int* v_idx,int* h_idx){
        bool reduced=false;
        if(*h_idx>1){
            for (int j=0;j<*h_idx;j++){
                remove(h[j]);
            }
            reduced=true;
            if(*v_idx<2) remove(i);
        }
        if(*v_idx>1){
            v[*v_idx]=i;
            *v_idx=*v_idx+1;
            std::sort(v,v+*v_idx);
            for(int j=0;j<*v_idx;j++){
                remove(v[j]);
            }
            reduced=true;
        }
        return reduced;
    }

    // for each gird, find consecutive objects and compare, then reduce the best
    bool Map::reduce(){
        int max_idx=0;
        int vmax[MAX_DIM]={0};
        int hmax[MAX_DIM]={0};
        int v_max_idx=0;
        int h_max_idx=0;
        for(int i=0;i<row*col;i++){
            int v[MAX_DIM]={0};
            int h[MAX_DIM]={0};
            int v_idx=0;
            int h_idx=0;
            find_around(i,v,h,&v_idx,&h_idx);
            if(compare(v_max_idx,h_max_idx,v_idx,h_idx)){
                max_idx=i;
                v_max_idx=v_idx;
                h_max_idx=h_idx;
                for(int j =0;j<MAX_DIM;j++){
                    vmax[j]=v[j];
                    hmax[j]=h[j];
                }
            }
        }
        bool res= reduce_around(max_idx,vmax,hmax,&v_max_idx,&h_max_idx);
        return res;

    }

    // keep reducing untill no match objects exist. and fill the pool with amount of objects removed 
    void Map:: reduce_and_fill_pool(){
        while(reduce()){
            for (int i=col*row-1;i<pool_idx;i++){
                if(m==three){
                    pool[i]=obj_count%3+1;
                    obj_count++;
                }
                if(m==random){
                    pool[i]=rand()%objs+1;
                }
            }
            std::shuffle(pool+col*row,pool+pool_size,default_random_engine());
            pool_idx=col*row;
        }
    }

    // count not empty gird
    int Map::remain(){
        int count=0;
        for (int i=0;i<col*row;i++){
            if(map[i]!=0)count++;
        }
        return count;
    }
    
    // getters of private attributes
    int Map::get_row(){
        return row;
    }
    int Map::get_col(){
        return col;
    }
    int Map::get_score(){
        return score;
    }

#endif