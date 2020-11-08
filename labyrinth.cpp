#include<cstdio> 
#include<iostream>
#include<algorithm>
#include<deque>
using namespace std;
struct base{
    int x,y,dir;
};

    int d[5][2]={{0,0},{0,1},{1,0},{0,-1},{-1,0}};    //依据题意先后搜索的四个方向，右，下，左，上 
    deque<base> s;
    int a[102][102]={0};
    int m,n;  //在main函数外定义a[100][100]不然内存不够 
    int startx,starty,endx,endy;
    base now;
    int flag=0; //flag=1表示已经找到终点，不需要在搜索，剪枝想法 
    
void search(){
	if(now.x==endx&&now.y==endy){
		flag=1; return;
	}
	else{
		for(int i=1;i<=4;i++){
			if(a[now.x+d[i][0]][now.y+d[i][1]]==0){
				now.dir=i;
				s.push_back(now);					//保存当前位置 
				a[now.x+d[i][0]][now.y+d[i][1]]=1;
				now.x+=d[i][0];
				now.y+=d[i][1];
				search();							//查找下一个点 
				if(flag==1)return;
				else{								//遇到障碍，退一步
					 now=s.at(s.size()-1);
					 s.pop_back();					 
				}
			}
		}
	}
}

void print(base i){
	cout<<"("<<i.x<<","<<i.y<<","<<i.dir<<")"<<",";
}

int main(){
    cin>>m>>n;
    cin>>startx>>starty>>endx>>endy;
    for(int i=0;i<m+2;i++){					//给迷宫周围围上边界 
        for(int j=0;j<n+2;j++){
            if(i==0||i==m+1||j==0||j==n+1)a[i][j]=1;
        }
    }
    for(int i=1;i<=m;i++){					//获取迷宫元素 
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
        }
    }
    now={startx,starty,1}; 					//初始位置 
    search();

    if(s.empty()){
        cout<<"no";   //没有搜到到，输出no 
    }else{
    	for_each(s.begin(),s.end(),print); 		//遍历输出 
    	cout<<"("<<endx<<","<<endy<<","<<1<<")";
	}
}

