#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include"route.h"

using namespace std;

#ifndef PARSER_H
#define PARSER_H    
    void get_info(ifstream& fin,int* row,int* col,int* block,int* net,int* net_index,vector<NET*> &net_list,vector<vector<int>> &grid_list);
    bool sort_net(const NET* a,const NET* b);
    void print_grid(int row,int col,vector<vector<int>> &grid_list);
    void print_net(vector<NET*> &net_list);
    void print_maze(ofstream& fout,int net_index,int net,vector<NET*> &net_list);
#endif