#include<fstream>
#include<sstream>
#include<vector>
#include<unordered_map>
#include<ctime>
#include "FM.h"
#include "parser.h"

int main(int argc,char *argv[])
{
    int net,node,net_size;
    ifstream fin(argv[1]);
    get_net_node(fin,&net,&node);
    vector<vector<int>> net_arr;
    vector<vector<int>> node_arr(node);
    fin.open(argv[1]);
    get_net_node_arr(fin,&net_size,net_arr,node_arr);
    FM fm(net,node,net_size,net_arr,node_arr);
	fm.run();
	fm.output("output.txt");
}