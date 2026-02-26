#include<vector>
#include<unordered_map>
#include"FM.h"

using namespace std;

#ifndef PARSER_H
#define PARSER_H    
    void get_net_node(ifstream& fin,int *net,int *node);
    void get_net_node_arr(ifstream& fin,int *net_size,vector<vector<int>> &net_arr,vector<vector<int>> &node_arr);
    int repeat_until(int node);
    void clear_arr(int net_size,vector<NODE> &partition,vector<unordered_map<int,NODE>> &left_gain,vector<unordered_map<int,NODE>> &right_gain,vector<unordered_map<int,NODE>> &best_left_gain,vector<unordered_map<int,NODE>> &best_right_gain);
    void output(ofstream &fout,int node,vector<NODE> &partition);
#endif