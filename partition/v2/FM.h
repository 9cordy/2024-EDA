#ifndef FM_H
#define FM_H
#include<vector>
#include<unordered_map>
#include<string>
using namespace std;

class NODE
{
    public:
        int FS,TE,gain,ID;
        bool side,lock;
        NODE();
        NODE(int n,bool FT);
};

class FM
{
    private:
        int net,node,net_size;
        int left,right,best_left,best_right;
        int repeat,count;
        vector<vector<int>> net_arr,node_arr;
        vector<NODE> partition,best_partition;
        vector<unordered_map<int,NODE>> left_gain,right_gain,best_left_gain,best_right_gain;
        void initial_side(int node,int &left,int &right,vector<NODE>& part);
        void initial_gain(vector<NODE>& part);
        void gain_list(vector<NODE>& part,vector<unordered_map<int,NODE>>& left,vector<unordered_map<int,NODE>>& right);
        void find_max_gain(int &left_max,int &right_max,vector<unordered_map<int,NODE>>& left,vector<unordered_map<int,NODE>>& right);
        int find_move_side(int left,int right,int left_max,int right_max);
        int find_move_node(int from_side,int &left,int &right,int left_max,int right_max,vector<unordered_map<int,NODE>>& left_gain,vector<unordered_map<int,NODE>>& right_gain);
        void update_move_node(int move_node,vector<NODE>& part);
        void update_gain(int move_node,bool from_side,vector<NODE>& part,vector<unordered_map<int,NODE>>& left_gain,vector<unordered_map<int,NODE>>& right_gain);
        void unlock_partition(vector<NODE>& part);
        int repeat_until(int node);
        void clear_arr();

    public:
        FM(int net,int node,int net_size,vector<vector<int>>& net_arr,vector<vector<int>>& node_arr);
        void run();
        void output(string filename);
};

#endif