#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include"parser.h"

using namespace std;

node::node()
{
    var='\0';
    high=nullptr;
    low=nullptr;
}

void get_func(ifstream& fin,vector<char> &func)
{
    char c;
    fin>>c;
    while(c!='.')
    {
		func.push_back(c);		
		fin>>c;
    }
    fin.close(); 
}

void get_pattern(ifstream& fin,vector<vector<char>> &pattern)
{
    char c;
    fin>>c;
    while(c!='.')
    	fin>>c;
    vector<char> tmp;
    while(fin>>c)
    {
        while(c!='.')
        {
            tmp.push_back(c);
            fin>>c;
        }
        reverse(tmp.begin(),tmp.end());
        pattern.push_back(tmp);
        tmp.clear();
    }
    fin.close();    
}

int get_min_bdd(vector<node*> &robdd,vector<char> &func,vector<vector<char>> &pattern)
{
    int min_node;    
    node *tmp;
    for(int i=0;i<pattern.size();i++)
    {
        tmp=robdd_build(1,robdd,func,pattern[i]);
        // print_robdd(robdd);
        if(i==0||robdd.size()<min_node)
            min_node=robdd.size();
        robdd.clear();
    }
    return min_node;
}

node* robdd_build(int i,vector<node*> &robdd,vector<char> func,vector<char> pattern)
{
    bool delete_node;
    char c;
    node *current_node=new node;
    current_node->cur_func=func;
    vector<char> high_func,low_func;
    if(func.size()==1&&func[0]=='0')
        current_node->var='0';
    else if(func.size()==1&&func[0]=='1')
        current_node->var='1';
    else
    {
        delete_node=1;
        c=pattern[pattern.size()-1];
        pattern.pop_back();
        current_node->var=c;
        high_func=get_sub_func('1',c,func);
        current_node->high=robdd_build(i+1,robdd,high_func,pattern);
        low_func=get_sub_func('0',c,func);
        current_node->low=robdd_build(i+1,robdd,low_func,pattern);
        if(current_node->high==current_node->low)
        {
            delete_node=0;
            current_node=current_node->high;
        }
            
    }
    for(int i=0;i<robdd.size();i++)
    {
        if(node_exist(current_node,robdd[i]))
        {
            if(delete_node)
                delete current_node;
            return robdd[i];
        }            
    } 
    robdd.push_back(current_node);
    return robdd.back();
}

vector<char> get_sub_func(char replace,char c,vector<char> func)
{
    vector<char> tmp,bdd;
    bool keep_plus,check_complement;
    check_complement=0;
    for(int i=0;i<func.size();i++)
    {
        if(func[i]==c-32)
            check_complement=1;
        if(func[i]!=c)
            tmp.push_back(func[i]);
        else
        {
            keep_plus=0;
            if(replace=='0')
            {
                int func_pos,tmp_pos;
                tmp_pos=tmp.size()-1;
                while(tmp_pos>=0&&tmp[tmp_pos]!='+')
                {
                    tmp.pop_back();
                    tmp_pos--;
                }
                if(tmp_pos>=0)
                {
                    tmp.pop_back();
                    tmp_pos--;
                    keep_plus=1;
                }
                func_pos=i+1;
                while(func[func_pos]!='+')
                {
                    i++;
                    if(func_pos<func.size()-1)
                        func_pos++;
                    else
                        break;     
                }
                if(func[func_pos]=='+'&&!keep_plus)
                    i++;
            }
            else if(replace=='1')
            {
                if((i==0||func[i-1]=='+')&&(i==func.size()-1||func[i+1]=='+'))
                {
                    tmp.clear();
                    break;
                }
                    
            }
        }        
    }
    if(c>96&&tmp.size()!=0&&check_complement)
    {
        func.clear();
        func=tmp;
        tmp.clear();
        if(replace=='0')
            tmp=get_sub_func('1',c-32,func);
        else
            tmp=get_sub_func('0',c-32,func);
        // print_sub_func(c,tmp);
    }
    if(tmp.size()==0)
        tmp.push_back(replace);
    return tmp;
}

bool node_exist(node* current_node,node* robdd)
{
    if(robdd->var=='0'&&current_node->var=='0')
        return 1;
    if(robdd->var=='1'&&current_node->var=='1')
        return 1;
    if(robdd->var==current_node->var&&robdd->high==current_node->high&&robdd->low==current_node->low)
        return 1;
    return 0;
}

void print_sub_func(char c,vector<char> &func)
{
    cout<<"current node: "<<c<<endl;
    for(int i=0;i<func.size();i++)
        cout<<func[i];
    cout<<endl;
}

void print_robdd(vector<node*> &robdd)
{
    for(int i=0;i<robdd.size();i++)
    {
        cout<<robdd[i]->var<<" ";
        for(int j=0;j<robdd[i]->cur_func.size();j++)
            cout<<robdd[i]->cur_func[j];
        cout<<endl;
    }
}

