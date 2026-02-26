#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<algorithm>
#include"parser.h"
#include"route.h"

using namespace std;

void get_info(ifstream& fin,int* row,int* col,int* block,int* net,int* net_index,vector<NET*> &net_list,vector<vector<int>> &grid_list)
{
    char c;
    while(fin>>c)
        if(c=='w')
            break;
    fin>>(*row);
    while(fin>>c)
        if(c=='l')
            break;
    fin>>(*col);
    for(int i=0;i<(*col);i++)
    {
        vector<int> temp;
        for(int j=0;j<(*row);j++)
            temp.push_back(0);
        grid_list.push_back(temp);
        temp.clear();
    }
    
    while(fin>>c)
        if(c=='k')
            break;
    fin>>(*block);
    for(int i=0;i<(*block);i++)
    {
        int left_x,left_y,right_x,right_y;
        fin>>left_x>>right_x>>left_y>>right_y;
        for(int j=left_y;j<=right_y;j++)
        {
            for(int k=left_x;k<=right_x;k++)
                grid_list[k][j]=3;
        }
    }    
    while(fin>>c)
        if(c=='t')
            break;
    fin>>(*net);
    for(int i=0;i<(*net);i++)
    {
        while(fin>>c)
        if(c=='t')
            break;
        int index,source_x,source_y,target_x,target_y;
        fin>>index>>source_x>>source_y>>target_x>>target_y;
        grid_list[source_x][source_y]=2;
        grid_list[target_x][target_y]=2;
        NET* new_net=new NET(index,source_x,source_y,target_x,target_y);
        net_list.push_back(new_net);
        if(i==0)
            (*net_index)=index;
    }
    sort(net_list.begin(),net_list.end(),sort_net);
}

bool sort_net(const NET* a,const NET* b) 
{
    int a_dis=abs(a->target.first-a->source.first)*abs(a->target.first-a->source.first)+abs(a->target.second-a->source.second)*abs(a->target.second-a->source.second);
    int b_dis=abs(b->target.first-b->source.first)*abs(b->target.first-b->source.first)+abs(b->target.second-b->source.second)*abs(b->target.second-b->source.second);
    return a_dis<b_dis;
}

void print_grid(int row,int col,vector<vector<int>> &grid_list)
{
    for(int i=row-1;i>=0;i--)
    {
        for(int j=0;j<col;j++)
            cout<<grid_list[j][i]<<' ';
        cout<<endl;
    }
}

void print_net(vector<NET*> &net_list)
{
    for(int i=0;i<net_list.size();i++)
        cout<<net_list[i]->index<<": "<<net_list[i]->source.first<<' '<<net_list[i]->source.second<<' '<<net_list[i]->target.first<<' '<<net_list[i]->target.second<<endl;
}

void print_maze(ofstream& fout,int net_index,int net,vector<NET*> &net_list)
{
    int count=0;
    while(count!=net)
    {
        for(int i=0;i<net_list.size();i++)
        {
            if(net_list[i]->index==net_index)
            {
                fout<<"net"<<net_list[i]->index<<' '<<net_list[i]->total_grid<<endl;
                fout<<"begin"<<endl;
                for(int j=0;j<net_list[i]->path_list.size()-1;j++)
                    fout<<net_list[i]->path_list[j].first<<' '<<net_list[i]->path_list[j].second<<' '<<net_list[i]->path_list[j+1].first<<' '<<net_list[i]->path_list[j+1].second<<endl;
                fout<<"end"<<endl;
                count++;
                net_index++;
            }
        }
    }
}