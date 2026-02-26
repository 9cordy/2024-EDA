#include<iostream>
#include<fstream>
#include<vector>
#include"parser.h"
#include"route.h"

using namespace std;

int main(int argc,char *argv[])
{
    ifstream fin;
    ofstream fout;
    fin.open(argv[1]);
    int row,col,block,net,net_index;
    vector<NET*> net_list;
    vector<vector<int>> grid_list;
    get_info(fin,&row,&col,&block,&net,&net_index,net_list,grid_list);
    // print_grid(row,col,grid_list);
    // print_net(net_list);
    maze_router(row,col,net,net_list,grid_list);
    fout.open(argv[2]);
    print_maze(fout,net_index,net,net_list);
    return 0;
}

