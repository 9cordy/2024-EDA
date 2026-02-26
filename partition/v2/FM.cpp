#include"FM.h"
#include<fstream>
#include<ctime>
#define balance_factor 0.45
using namespace std;

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

FM::FM(int net,int node,int net_size,vector<vector<int>>& net_arr,vector<vector<int>>& node_arr)
{
	this->net=net;
	this->node=node;
	this->net_size=net_size;
	this->net_arr=net_arr;
	this->node_arr=node_arr;
	initial_side(node,best_left,best_right,best_partition);
	repeat=repeat_until(node);
	count=0;
}

void FM::initial_side(int node,int &left,int &right,vector<NODE>& part)
{
	for(int i=0;i<node;i++)
		if(i<(node+1)/2)
			part.push_back(NODE(i+1,0));
		else
			part.push_back(NODE(i+1,1));
	left=(node+1)/2;
	right=node-left;
}

void FM::initial_gain(vector<NODE>& part)
{
	for(int i=0;i<net;i++)
	{
		int left=0,right=0;
		for(int j=0;j<net_arr[i].size();j++)
			if(part[net_arr[i][j]-1].side==0)
				left++;
			else 
				right++;
		for(int j=0;j<net_arr[i].size();j++)
		{
			int id=net_arr[i][j]-1;
			if(part[id].side==0)
			{
				if(left==1)
					part[id].FS++;
				else if(right==0)
					part[id].TE++;
			}
			else
			{
				if(right==1)
					part[id].FS++;
				else if(left==0)
					part[id].TE++;
			}
		}
	}
	for(int i=0;i<node;i++)
		part[i].gain=part[i].FS-part[i].TE;
}

void FM::gain_list(vector<NODE>& part,vector<unordered_map<int,NODE>>& left,vector<unordered_map<int,NODE>>& right)
{
	for(int i=0;i<node;i++)
		if(part[i].side==0)
			left[part[i].gain+net_size].emplace(part[i].ID,part[i]);
		else 
			right[part[i].gain+net_size].emplace(part[i].ID,part[i]);
}

void FM::find_max_gain(int &left_max,int &right_max,vector<unordered_map<int,NODE>>& left,vector<unordered_map<int,NODE>>& right)
{
	left_max=right_max=-1;
	for(int i=2*net_size;i>=0;i--)
	{
		if(!left[i].empty())
		{
			left_max=i;
			break;
		}
	}		
	for(int i=2*net_size;i>=0;i--)
	{
		if(!right[i].empty())
		{
			right_max=i;
			break;
		}
	}
}

int FM::find_move_side(int left,int right,int left_max,int right_max)
{
	if(right<balance_factor*node&&left_max==-1)
		return -1;
	if(left<balance_factor*node&&right_max==-1)
		return -1;
	if(left<balance_factor*node)
		return 1;
	else if(right<balance_factor*node)
		return 0;
	else if(left_max>=right_max)
		return 0;
	else 
		return 1;
}

int FM::find_move_node(int from_side,int &left,int &right,int left_max,int right_max,vector<unordered_map<int,NODE>>& left_gain,vector<unordered_map<int,NODE>>& right_gain)
{
	NODE move_node;
	if(from_side==0)
	{
		left--;
		right++;
		auto ptr=left_gain[left_max].begin();
		move_node=ptr->second;
		left_gain[left_max].erase(ptr);
	}
	else
	{
		left++;
		right--;
		auto ptr=right_gain[right_max].begin();
		move_node=ptr->second;
		right_gain[right_max].erase(ptr);
	}
	return move_node.ID-1;
}

void FM::update_move_node(int move_node,vector<NODE>& part)
{
	part[move_node].lock=1;
	part[move_node].side=!part[move_node].side;
}

void FM::update_gain(int move_node,bool from_side,vector<NODE>& part,vector<unordered_map<int,NODE>>& left_gain,vector<unordered_map<int,NODE>>& right_gain)
{
	int from,to;
	for(int i=0;i<node_arr[move_node].size();i++)
	{
		int netpos=node_arr[move_node][i];
		from=to=0;
		for(int j=0;j<net_arr[netpos].size();j++)
		{
			int nodepos=net_arr[netpos][j]-1;
			if(part[nodepos].side==from_side)
				from++;
			else 
				to++;
		}
		to--;
		for(int j=0;j<net_arr[netpos].size();j++)
		{
			int nodepos=net_arr[netpos][j]-1;
			int old_gain=part[nodepos].gain;
			if(part[nodepos].side==from_side)
			{
				if(to==0)
					part[nodepos].gain++;
				if(from==1)
					part[nodepos].gain++;
			}
			else
			{
				if(to==1)
					part[nodepos].gain--;
				if(from==0)
					part[nodepos].gain--;
			}
			if(old_gain!=part[nodepos].gain&&!part[nodepos].lock)
			{
				if(!part[nodepos].side)
				{
					left_gain[old_gain+net_size].erase(nodepos+1);
					left_gain[part[nodepos].gain+net_size].emplace(part[nodepos].ID,part[nodepos]);
				}
				else
				{
					right_gain[old_gain+net_size].erase(nodepos+1);
					right_gain[part[nodepos].gain+net_size].emplace(part[nodepos].ID,part[nodepos]);
				}
			}
		}
	}
}

void FM::unlock_partition(vector<NODE>& part)
{
	for(int i=0;i<node;i++)
	{
		part[i].FS=0;
		part[i].TE=0;
		part[i].lock=0;
	}
}

int FM::repeat_until(int node)
{
	int repeat=0;
	while(node>10)
	{
		repeat++;
		node/=10;
	}
	repeat=(repeat+1)*10;
	if(node>5)
		repeat+=5;
	return repeat;
}

void FM::clear_arr()
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

void FM::run()
{
	clock_t start=clock();
	while(1)
	{
		left_gain.assign(net_size*2+1,{});
		right_gain.assign(net_size*2+1,{});
		best_left_gain.assign(net_size*2+1,{});
		best_right_gain.assign(net_size*2+1,{});
		initial_gain(best_partition);
		gain_list(best_partition,best_left_gain,best_right_gain);
		partition=best_partition;
		left_gain=best_left_gain;
		right_gain=best_right_gain;
		int max_step=0,max_gain=0,partial_gain=0;
		count++;
		for(int lock=0;lock<node;lock++)
		{
			int left_max,right_max;
			find_max_gain(left_max,right_max,left_gain,right_gain);
			int from_side=find_move_side(left,right,left_max,right_max);
			if(from_side==-1)
				break;
			if(from_side==0)
				partial_gain+=(left_max-net_size);
			else 
				partial_gain+=(right_max-net_size);
			if(partial_gain>max_gain)
			{
				max_gain=partial_gain;
				max_step=lock;
			}
			int move_node=find_move_node(from_side,left,right,left_max,right_max,left_gain,right_gain);
			update_move_node(move_node,partition);
			update_gain(move_node,from_side,partition,left_gain,right_gain);
		}
		if(max_gain>0)
		{
			for(int step=0;step<=max_step;step++)
			{
				int left_max,right_max;
				find_max_gain(left_max,right_max,best_left_gain,best_right_gain);
				int from_side=find_move_side(best_left,best_right,left_max,right_max);
				if(from_side==-1)
					break;
				int move_node=find_move_node(from_side,best_left,best_right,left_max,right_max,best_left_gain,best_right_gain);
				update_move_node(move_node,best_partition);
				update_gain(move_node,from_side,best_partition,best_left_gain,best_right_gain);
			}
		}
		else 
			break;
		if(count>repeat)
			break;
		double time=(double)(clock()-start)/CLOCKS_PER_SEC;
		if(time>29)
			break;
		unlock_partition(best_partition);
		clear_arr();
	}
}

void FM::output(string filename)
{
	ofstream fout(filename);
	for(int i=0;i<node;i++)
		fout<<best_partition[i].side<<endl;
}