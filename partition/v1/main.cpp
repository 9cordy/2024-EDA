#include<fstream>
#include<sstream>
#include<vector>
#include<unordered_map>
#include<ctime>
#include"parser.h"
#include"FM.h"
using namespace std;

int main(int argc,char *argv[])
{
	ifstream fin;
	ofstream fout;
	clock_t start=clock();
	int net,node,net_size;
	fin.open(argv[1]);
	get_net_node(fin,&net,&node);
	vector<vector<int>> net_arr;
	vector<vector<int>> node_arr(node);//which net is connected to the node
	fin.open(argv[1]);
	get_net_node_arr(fin,&net_size,net_arr,node_arr);
	
	int left,right,best_left,best_right,max_step,max_gain,partial_gain,count,repeat;
	vector<NODE> partition;
	vector<NODE> best_partition;	
	initial_side(node,&left,&right,best_partition);
	repeat=repeat_until(node);
	best_left=left;
	best_right=right;
	count=0;
	while(1)//repeat until max partial sum<=0 or time>29
	{
		vector<unordered_map<int,NODE>> left_gain(net_size*2+1);//for finding max partial sum
		vector<unordered_map<int,NODE>> right_gain(net_size*2+1);
		vector<unordered_map<int,NODE>> best_left_gain(net_size*2+1);
		vector<unordered_map<int,NODE>> best_right_gain(net_size*2+1);
		initial_gain(net,node,best_partition,net_arr);//calculate FS and TE
		gain_list(node,net_size,best_partition,best_left_gain,best_right_gain);
		partition=best_partition;
		left_gain=best_left_gain;
		right_gain=best_right_gain;
		max_step=0;
		max_gain=0;
		partial_gain=0;
		count++;
		for(int lock=0;lock<node;lock++)//find max partial sum
		{			
			int left_max,right_max;			
			find_max_gain(net_size,&left_max,&right_max,left_gain,right_gain);
			int from_side=find_move_side(node,left,right,left_max,right_max);
			if(from_side==-1)
				break;
			if(from_side==0)//left to right 0
				partial_gain+=(left_max-net_size);
			else//right to left 1
				partial_gain+=(right_max-net_size);
			if(partial_gain>max_gain)
			{
				max_gain=partial_gain;
				max_step=lock;				
			}
			int move_node=find_move_node(from_side,&left,&right,left_max,right_max,left_gain,right_gain);
			update_move_node(move_node,partition);
			update_gain(move_node,net_size,from_side,partition,net_arr,node_arr,left_gain,right_gain);
		}//end of finding partial sum
		if(max_gain>0)//partition until max partial sum
		{
			for(int step=0;step<=max_step;step++)//same partition process
			{
				int left_max,right_max;			
				find_max_gain(net_size,&left_max,&right_max,best_left_gain,best_right_gain);
				int from_side=find_move_side(node,best_left,best_right,left_max,right_max);
				if(from_side==-1)
					break;
				int move_node=find_move_node(from_side,&best_left,&best_right,left_max,right_max,best_left_gain,best_right_gain);
				update_move_node(move_node,best_partition);
				update_gain(move_node,net_size,from_side,best_partition,net_arr,node_arr,best_left_gain,best_right_gain);
			}
		}
		else//if max partial sum<=0 break
			break;
		if(count>repeat)
			break;
		clock_t end=clock();
        double time=double(end-start)/CLOCKS_PER_SEC;
		if(time>29)
            break;
		unlock_partition(node,best_partition);
		clear_arr(net_size,partition,left_gain,right_gain,best_left_gain,best_right_gain);
	}
	fout.open("output.txt");
	output(fout,node,best_partition);
	return 0;
}