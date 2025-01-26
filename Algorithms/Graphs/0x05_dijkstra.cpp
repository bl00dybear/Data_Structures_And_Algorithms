#include <bits/stdc++.h>
#define size 100
#define maxInt (1<<30)-1
using namespace std;

ifstream fin("~/input.txt");
ofstream fout("~/output.txt");

int m,n,start_node;
vector<pair<int,int>> weighted_graph[size];
vector<int>dist;
bitset<size> visited;

void read_adjacency_list_weighted() {
    int node1,node2,cost;
    fin>>n>>m>>start_node;
    for (int i = 1; i <= m; i+=1) {
        fin>>node1>>node2>>cost;
        weighted_graph[node1].push_back(make_pair(node2,cost));
        weighted_graph[node2].push_back(make_pair(node1,cost));
    }
}

void dijkstra(const int start) {
    dist.resize(n+1,1e9);
    dist[start]=0;

    priority_queue<pair<int,int>> heap;

    heap.push(make_pair(-0,start));
    while (!heap.empty()) {
        const int node1 = heap.top().second;
        heap.pop();
        if (!visited[node1]) {
            visited[node1] = true;
            for (const auto [node2, cost] : weighted_graph[node1]) {
                if (dist[node2]>dist[node1]+cost) {
                    dist[node2] = dist[node1]+cost;
                    heap.push(make_pair(-dist[node2],node2));
                }
            }
        }
    }
    for (int i=1; i<=n; i+=1) {
        if (dist[i]==1e9)
            fout<<-1<<' ';
        fout<<dist[i]<<' ';
    }
    cout<<'\n';
}

int main() {
    read_adjacency_list_weighted();
    dijkstra(start_node);
    return 0;
}