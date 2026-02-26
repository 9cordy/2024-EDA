#include<vector>
#include<unordered_map>

using namespace std;

#ifndef FM_H
#define FM_H
    class NODE
    {
        public:
            int FS;
            int TE;
            int gain;
            int ID;
            bool side;
            bool lock;
            NODE();
            NODE(int n,bool FT); 
    };
    void initial_side(int node,int *left,int *right,vector<NODE> &partition);
    void initial_gain(int net,int node,vector<NODE> &partition,vector<vector<int>> &net_arr);
    void gain_list(int node,int net_size,vector<NODE> &partition,vector<unordered_map<int,NODE>> &left_gain,vector<unordered_map<int,NODE>> &right_gain);
    void find_max_gain(int net_size,int *left_max,int *right_max,vector<unordered_map<int,NODE>> &left_gain,vector<unordered_map<int,NODE>> &right_gain);
    int find_move_side(int node,int left,int right,int left_max,int right_max);
    int find_move_node(int from_side,int *left,int *right,int left_max,int right_max,vector<unordered_map<int,NODE>> &left_gain,vector<unordered_map<int,NODE>> &right_gain);
    void update_move_node(int move_node,vector<NODE> &partition);
    void update_gain(int move_node,int net_size,bool from_side,vector<NODE> &partition,vector<vector<int>> &net_arr,vector<vector<int>> &node_arr,vector<unordered_map<int,NODE>> &left_gain,vector<unordered_map<int,NODE>> &right_gain);
    void unlock_partition(int node,vector<NODE> &partition);
#endif