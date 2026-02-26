#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>
#include"route.h"

using namespace std;

NET::NET()
{
    total_grid=0;
}

NET::NET(int i,int x1,int y1,int x2,int y2)
{
    index=i;
    total_grid=0;
    source=make_pair(x1,y1);
    target=make_pair(x2,y2);
}

void maze_router(int row,int col,int net,vector<NET*> &net_list,vector<vector<int>> &grid_list)
{
    int routed_net=0;
    int count=0;
    while(routed_net<net)
    {   
        bool valid_route=route_net(row,col,&count,net_list[routed_net],grid_list);
        if(valid_route)
            routed_net++;
        else
        {
            count++;
            rip_up(row,col,grid_list);
            shuffle_net(routed_net,net,net_list);
            routed_net=0;
        }    
    }
}

bool route_net(int row,int col,int* count,NET* &net,vector<vector<int>> &grid_list)
{
    vector<int> x_dir,y_dir;
    if((*count)<10)
    {
        x_dir.push_back(-1);
        y_dir.push_back(0);
        x_dir.push_back(0);
        y_dir.push_back(-1);
        x_dir.push_back(1);
        y_dir.push_back(0);
        x_dir.push_back(0);
        y_dir.push_back(1);
    }
    else
    {
        x_dir.push_back(0);
        y_dir.push_back(1);
        x_dir.push_back(1);
        y_dir.push_back(0);
        x_dir.push_back(0);
        y_dir.push_back(-1);
        x_dir.push_back(-1);
        y_dir.push_back(0);
    }
    bool routed=0;
    vector<vector<pair<int,pair<int,int>>>> trace_back(col,vector<pair<int,pair<int,int>>>(row));//step, last position
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++)
            trace_back[i][j]=make_pair(0,make_pair(-1,-1));
    }
    pair<int,int> current_pos=net->source;
    queue<pair<int,pair<int,int>>> q;
    q.push(make_pair(0,current_pos));
    while(!q.empty())
    {
        pair<int,pair<int,int>> current=q.front();
        current_pos=current.second;
        q.pop();
        for(int i=0;i<4;i++)
        {
            pair<int,int> next_pos;
            next_pos=make_pair(current_pos.first+x_dir[i],current_pos.second+y_dir[i]);
            // cout<<current.first+1<<": "<<next_pos.first<<' '<<next_pos.second<<endl;
            if(next_pos==net->target)
            {
                trace_back[next_pos.first][next_pos.second]=make_pair(current.first+1,current_pos);
                routed=1;
                break;
            }
            if(!valid_pos(row,col,next_pos,grid_list))
                continue;
            if(occupied(net->source,next_pos,trace_back))
                continue;
            q.push(make_pair(current.first+1,next_pos));
            trace_back[next_pos.first][next_pos.second]=make_pair(current.first+1,current_pos);
        }
        if(routed==1)
            break;
    }
    // for(int i=row-1;i>=0;i--)
    // {
    //     for(int j=0;j<col;j++)
    //         cout<<trace_back[j][i].first<<' ';
    //     cout<<endl;
    // }
    x_dir.clear();
    y_dir.clear();
    if(routed)
    {
        get_path(net,grid_list,trace_back);
        // for(int i=0;i<net.path_list.size();i++)
        //     cout<<net.path_list[i].first<<' '<<net.path_list[i].second<<endl;
        return 1;
    }
    else
        return 0;
}

bool valid_pos(int row,int col,pair<int,int> pos,vector<vector<int>> &grid_list)
{
    if(pos.first<0)
        return 0;
    if(pos.first>=col)
        return 0;
    if(pos.second<0)
        return 0;
    if(pos.second>=row)
        return 0;
    if(grid_list[pos.first][pos.second]>0)
        return 0;
    return 1;
}

bool occupied(pair<int,int> source,pair<int,int> pos,vector<vector<pair<int,pair<int,int>>>> &trace_back)
{
    if(trace_back[pos.first][pos.second].first!=0)
        return 1;
    if(pos==source)
        return 1;
    return 0;
}

void get_path(NET* &net,vector<vector<int>> &grid_list,vector<vector<pair<int,pair<int,int>>>> &trace_back)
{
    pair<int,int> temp=net->target;
    vector<pair<int,int>> temp_path_list;
    int count=0;
    int previous_x=temp.first;
    int previous_y=temp.second;
    bool previous,current;
    if(temp.first==trace_back[temp.first][temp.second].second.first)
        current=0;
    else
        current=1;
    previous=!current;
    while(temp!=net->source)
    {
        if(previous!=current)
            temp_path_list.push_back(make_pair(previous_x,previous_y));
        previous=current;
        previous_x=temp.first;
        previous_y=temp.second;
        temp=trace_back[temp.first][temp.second].second;
        if(temp!=net->source)
            update_grid_list(net->index,temp,grid_list);
        if(temp.first==previous_x)
            current=0;
        else    
            current=1;
        count++;
    }
    if(previous!=current)
        temp_path_list.push_back(make_pair(previous_x,previous_y));
    net->total_grid=count-1;
    temp_path_list.push_back(net->source);
    reverse(temp_path_list.begin(),temp_path_list.end());
    net->path_list=temp_path_list;
}

void update_grid_list(int net,pair<int,int> pos,vector<vector<int>> &grid_list)
{
    grid_list[pos.first][pos.second]=1;
}

void rip_up(int row,int col,vector<vector<int>> &grid_list)
{
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++)
        {
            if(grid_list[i][j]==1)
                grid_list[i][j]=0;
        }
    }
}

void shuffle_net(int routed_net,int net,vector<NET*> &net_list)
{
    vector<NET*> old_net_list=net_list;
    net_list.clear();
    for(int i=0;i<routed_net;i++)
        old_net_list[i]->path_list.clear();  
    net_list.push_back(old_net_list[routed_net]);    
    for(int i=0;i<net;i++)
        if(i!=routed_net)
            net_list.push_back(old_net_list[i]);
}