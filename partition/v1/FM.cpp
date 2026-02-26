#include<fstream>
#include<sstream>
#include<vector>
#include<unordered_map>
#include"FM.h"

using namespace std;

#define balance_factor 0.45

NODE::NODE()
{
	FS=0;
	TE=0;
	gain=0;
	lock=0;
}

NODE::NODE(int n,bool FT)
{
	FS=0;
	TE=0;
	gain=0;
	ID=n;
	side=FT;
	lock=0;
}

void initial_side(int node,int *left,int *right,vector<NODE> &partition)
{
	for(int i=0;i<node;i++)
		if(i<(node+1)/2)
			partition.push_back(NODE(i+1,0));
		else
			partition.push_back(NODE(i+1,1));
	(*left)=(node+1)/2;
	(*right)=node-(*left);
}

void initial_gain(int net,int node,vector<NODE> &partition,vector<vector<int>> &net_arr)
{
	for(int i=0;i<net;i++)//calculate initial gain with FS TE;
	{
		int left=0;
		int right=0;
		for(int j=0;j<net_arr[i].size();j++)
			if(partition[net_arr[i][j]-1].side==0)
				left++;
			else
				right++;
		for(int j=0;j<net_arr[i].size();j++)//traverse all nets
		{
			
			if(partition[net_arr[i][j]-1].side==0)//node on the left side
			{
				if(left==1)//only one node on the left side FS+1
					partition[net_arr[i][j]-1].FS+=1;
				else if(right==0)//no node on the right side TE+1
					partition[net_arr[i][j]-1].TE+=1;
			}
			else//same but on the other side
			{
				if(right==1)
					partition[net_arr[i][j]-1].FS+=1;
				else if(left==0)
					partition[net_arr[i][j]-1].TE+=1;
			}
		}
	}
	for(int i=0;i<node;i++)
		partition[i].gain=partition[i].FS-partition[i].TE;
		
}

void gain_list(int node,int net_size,vector<NODE> &partition,vector<unordered_map<int,NODE>> &left_gain,vector<unordered_map<int,NODE>> &right_gain)
{
	for(int i=0;i<node;i++)
		if(partition[i].side==0)
			left_gain[partition[i].gain+net_size].emplace(partition[i].ID,partition[i]);
		else
			right_gain[partition[i].gain+net_size].emplace(partition[i].ID,partition[i]);
}

void find_max_gain(int net_size,int *left_max,int *right_max,vector<unordered_map<int,NODE>> &left_gain,vector<unordered_map<int,NODE>> &right_gain)
{
	(*left_max)=INT8_MIN;
	(*right_max)=INT8_MIN;
	for(int i=2*net_size;i>=0;i--)
	{
		if(!left_gain[i].empty())
		{
			(*left_max)=i;
			break;
		}		
	}
	for(int i=2*net_size;i>=0;i--)
	{
		if(!right_gain[i].empty())
		{
			(*right_max)=i;
			break;
		}
	}
}

int find_move_side(int node,int left,int right,int left_max,int right_max)
{
	if(right<balance_factor*node&&left_max==INT8_MIN)
		return -1;
	if(left<balance_factor*node&&right_max==INT8_MIN)
		return -1;
	if(left<balance_factor*node)//only from left to right
		return 1;
	else if(right<balance_factor*node)//only from right to left
		return 0;
	else if(left_max>=right_max)
		return 0;
	else
		return 1;
}

int find_move_node(int from_side,int *left,int *right,int left_max,int right_max,vector<unordered_map<int,NODE>> &left_gain,vector<unordered_map<int,NODE>> &right_gain)
{
	NODE move_node;
	if(from_side==0)//left to right 0
	{
		(*left)--;
		(*right)++;
		auto node_ptr=left_gain[left_max].begin();
		move_node=node_ptr->second;
		left_gain[left_max].erase(move_node.ID);
	}
	else//right to left 1
	{
		(*left)++;
		(*right)--;
		auto node_ptr=right_gain[right_max].begin();
		move_node=node_ptr->second;
		right_gain[right_max].erase(move_node.ID);
	}
	return move_node.ID-1;
}

void update_move_node(int move_node,vector<NODE> &partition)
{
	partition[move_node].lock=1;//lock the node and change the side
	partition[move_node].side=!partition[move_node].side;
}

void update_gain(int move_node,int net_size,bool from_side,vector<NODE> &partition,vector<vector<int>> &net_arr,vector<vector<int>> &node_arr,vector<unordered_map<int,NODE>> &left_gain,vector<unordered_map<int,NODE>> &right_gain)
{
	int from=0;
	int to=0;
	int old_gain;
	for(int i=0;i<node_arr[move_node].size();i++)//find all the nets connected to the node that u want to move
	{
		int netpos=node_arr[move_node][i];//get all net connected to the node
		for(int j=0;j<net_arr[netpos].size();j++)//traverse each net
		{
			int nodepos=net_arr[netpos][j]-1;//pos of node 1 in partition is 0
			if(partition[nodepos].side==from_side)
				from++;
			else
				to++;
		}
		to--;//moved the node before counting the total from and to nodes so -1
		for(int j=0;j<net_arr[netpos].size();j++)//traverse all nodes connected with the moved one
		{
			int nodepos=net_arr[netpos][j]-1;//actual pos of node
			old_gain=partition[nodepos].gain;
			if(partition[nodepos].side==from_side)//at the from side
			{
				if(to==0)//to=0 before move add 1 to all nodes at from side
					partition[nodepos].gain++;
				if(from==1)//from=1 after move add 1 to the node
					partition[nodepos].gain++;
			}
			else//at the to side
			{
				if(to==1)//to=1 before move subtract 1 from the node
					partition[nodepos].gain--;
				if(from==0)//from=0 after move subtract 1 from all the nodes
					partition[nodepos].gain--;
			}
			if(old_gain!=partition[nodepos].gain&&!partition[nodepos].lock)
			{			
				if(!partition[nodepos].side)
				{
					left_gain[old_gain+net_size].erase(nodepos+1);
					left_gain[partition[nodepos].gain+net_size].emplace(partition[nodepos].ID,partition[nodepos]);
				}
				else
				{
					right_gain[old_gain+net_size].erase(nodepos+1);
					right_gain[partition[nodepos].gain+net_size].emplace(partition[nodepos].ID,partition[nodepos]);;
				}
			}
		}
		from=0;
		to=0;
	}
}

void unlock_partition(int node,vector<NODE> &partition)
{
	for(int i=0;i<node;i++)
	{
		partition[i].FS=0;
		partition[i].TE=0;
		partition[i].lock=0;
	}
}