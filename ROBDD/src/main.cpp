#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include"parser.h"

using namespace std;

int main(int argc,char *argv[])
{
    ifstream fin;
    ofstream fout;
    fin.open(argv[1]);
    fout.open(argv[2]);
    vector<char> func;
    vector<vector<char>> pattern;
    get_func(fin,func);
    fin.open(argv[1]);
    get_pattern(fin,pattern);
    vector<node*> robdd;    
    fout<<get_min_bdd(robdd,func,pattern);
    fout.close();
    return 0;
}