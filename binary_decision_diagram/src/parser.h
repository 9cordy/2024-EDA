#include<vector>

using namespace std;

#ifndef PARSER_H
#define PARSER_H
    class node
    {
        public:
            char var;
            node *high,*low;
            vector<char> cur_func;//for debug
            node();
    };
    void get_func(ifstream& fin,vector<char> &func);
    void get_pattern(ifstream& fin,vector<vector<char>> &pattern);
    int get_min_bdd(vector<node*> &robdd,vector<char> &func,vector<vector<char>> &pattern);
    node* robdd_build(int i,vector<node*> &robdd,vector<char> func,vector<char> pattern);
    vector<char> get_sub_func(char replace,char c,vector<char> func);
    bool node_exist(node* current_node,node* robdd);
    void print_sub_func(char c,vector<char> &func);
    void print_robdd(vector<node*> &robdd);
#endif