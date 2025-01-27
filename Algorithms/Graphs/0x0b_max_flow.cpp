#include <bits/stdc++.h>
#define size_ 100
using namespace std;

ifstream fin("in.txt");
ofstream fout("out.txt"); 

int m, n;
vector<int> graph[size_ + 1];
bitset<size_>visited;
int flux[size_+1][size_+1];
int capacity[size_+1][size_+1];
int p[size_+1];


int bfs(const int s, const int d){
    queue<int> q;
    for (int i =1;i<=n;i+=1){
        visited[i]=false;
        p[i]=0;
    }
    q.push(s);
    visited[s]=true;
    while(!q.empty()){
        const int node = q.front();
        q.pop();
        for(auto node2:graph[node]){
            if(!visited[node2]){
                if(capacity[node][node2] - flux[node][node2] > 0){
                    q.push(node2);
                    visited[node2] = true;
                    p[node2] = node;
                }
            }
        }
    }

    if(!visited[d])
        return 0;

    vector<int> path;
    int x = d;
    
    while(x!=0){
        path.push_back(x);
        x=p[x];
    }

    //reverse(path.begin(),path.end());
    ranges::reverse(path);
    int flow=1e9;
    for(int i = 0; i<path.size()-1;i+=1){
        const int x1 = path[i];
        int y = path[i+1];
        flow = min(flow, capacity[x1][y]-flux[x1][y]);
    }
    for(int i=0;i<path.size()-1;i+=1){
        const int x1 = path[i];
        const int y = path[i+1];
        flux[x1][y] += flow;
        flux[y][x1] -=flow;
    }
    return flow;

}


int main(){
    int m,n;
    fin>>n>>m;
    for(int i = 1;i<=m;i+=1){
        int x,y,c;
        fin>>x>>y>>c;
        capacity[x][y]=c;
        graph[x].push_back(y);
    }

    int maxFlow = 0;
    while (true){
        const int flow= bfs(1,n);
        if(flow == 0){
            break;
        }
        maxFlow += flow;
    }
    fout<<maxFlow;
    return 0;
}