#include<fstream>
#include<sstream>
#include<vector>
#include<unordered_map>
#include"parser.h"
#include"FM.h"

using namespace std;
using std::vector;
using std::unordered_map;

void get_net_node(ifstream& fin,int *net,int *node)
{
	string s;
	stringstream ss;
	getline(fin,s);
	ss<<s;
	ss>>(*net)>>(*node);
	ss.clear();
	fin.close();
}

void get_net_node_arr(ifstream& fin,int *net_size,vector<vector<int>> &net_arr,vector<vector<int>> &node_arr)
{
	int net,node;
	string s;
	stringstream ss;
	getline(fin,s);
	ss<<s;
	ss>>net>>node;
	ss.clear();
	vector<int> v;
	vector<int> count(node,0);
	for(int i=0;i<net;i++)
	{
		getline(fin,s);
		ss<<s;
		int temp;
		while(ss>>temp)
		{
			v.push_back(temp);
			node_arr[temp-1].push_back(i);
			count[temp-1]++;
		}
		net_arr.push_back(v);
		
		v.clear();
		ss.clear();
	}
	(*net_size)=0;
	for(int i=0;i<count.size();i++)
		if(count[i]>(*net_size))
			(*net_size)=count[i];
	fin.close();
}

int repeat_until(int node)
{
	int repeat=0;
	while(node>10)
	{
		repeat++;
		node=node/10;
	}
	repeat=(repeat+1)*10;
	if(node>5)
		repeat+=5;
	return repeat;
}

void clear_arr(int net_size,vector<NODE> &partition,vector<unordered_map<int,NODE>> &left_gain,vector<unordered_map<int,NODE>> &right_gain,vector<unordered_map<int,NODE>> &best_left_gain,vector<unordered_map<int,NODE>> &best_right_gain)
{
	for(int i=0;i<2*net_size+1;i++)
	{
		left_gain[i].clear();
		right_gain[i].clear();
		best_left_gain[i].clear();
		best_right_gain[i].clear();
	}
	partition.clear();
	left_gain.clear();
	right_gain.clear();
	best_left_gain.clear();
	best_right_gain.clear();
}

void output(ofstream &fout,int node,vector<NODE> &partition)
{
	for(int i=0;i<node;i++)
		fout<<partition[i].side<<endl;
	fout.close();	
}