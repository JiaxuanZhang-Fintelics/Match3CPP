#ifndef MAP_H
#define MAP_H
#define MAX_DIM 40
// mode of generating pool
enum mode { random,three,zero };
bool compare(int v1,int h1,int v2,int h2); // return true if 2 is better than 1
class Map{
    private:
    int row; // number of rows
    int col; // number of cols
    int objs; // number of objects kinds 
    int pool_size; // size of pool
    int score; // score (reduce 1 object=1 score)
    int obj_count; // track objects adding to the pool, only used when mode is three
    int* pool; // the pool, array of size pool_size
    int pool_idx; // index of next object in the pool
    mode m; // mode of game 
    // find_direction functions are modified recursive dfs that only find 
    // consective objects in one direction
    void find_up(int i, int*v, int* v_idx); 
    void find_down(int i, int*v, int* v_idx);
    void find_left(int i, int*h, int* h_idx);
    void find_right(int i, int*h, int* h_idx);
    void reduce_and_fill_pool();// keep reducing untill no match objects exist. and fill the pool with amount of objects removed 
    void fill(int index); // fill index with object in the pool
    void remove(int index); // use the value above to cover value in index recursively
    bool reduce_around(int i,int* v,int* h,int* v_idx,int* h_idx); //reduce consecutive objects around i, including i

    public:
    int* map; // actual map (array of size row*col)
    // constructor
    Map(int row, int col, int objs,int pool_size,int* init_pool,mode m);
    void find_around(int i,int* v,int* h,int* v_idx,int* h_idx);// find consecutive objects in four directions
    // for each gird, find consecutive objects and compare, then reduce the best
    bool reduce();
    int remain(); // count not empty gird
    // getters of private attributes
    int get_row();
    int get_col();
    int get_score();
};
#endif