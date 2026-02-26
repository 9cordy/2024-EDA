#include<iostream>
#include<fstream>
#include<vector>
#include<utility>
#include<list>

using namespace std;

#ifndef ROUTE_H
#define ROUTE_H
    class NET
    {
        public:
            int index;
            int total_grid;
            pair<int,int> source;
            pair<int,int> target;
            vector<pair<int,int>> path_list;
            NET();
            NET(int i,int x1,int y1,int x2,int y2);
    };
    void maze_router(int row,int col,int net,vector<NET*> &net_list,vector<vector<int>> &grid_list);
    bool route_net(int row,int col,int* count,NET* &net,vector<vector<int>> &grid_list);
    bool valid_pos(int row,int col,pair<int,int> pos,vector<vector<int>> &grid_list);
    bool occupied(pair<int,int> source,pair<int,int> pos,vector<vector<pair<int,pair<int,int>>>> &trace_back);
    void get_path(NET* &net,vector<vector<int>> &grid_list,vector<vector<pair<int,pair<int,int>>>> &trace_back);
    void update_grid_list(int net,pair<int,int> pos,vector<vector<int>> &grid_list);
    void rip_up(int net,int row,vector<vector<int>> &grid_list);
    void shuffle_net(int routed_net,int net,vector<NET*> &net_list);
#endif