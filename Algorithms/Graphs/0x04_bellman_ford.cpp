#include <bits/stdc++.h>
#define size 100
#define maxInt (1<<30)-1
using namespace std;

ifstream fin("~/input.txt");
ofstream fout("~/output.txt");

struct edge {
    int node1, node2;
    int cost;
};

int m,n,start_node;
vector<edge> edges;
vector<int>dist;

void read_edge_list() {
    fin>>n>>m>>start_node;
    edges.resize(m+1);
    for (int i = 1; i <= m; i+=1) {
        fin>>edges[i].node1>>edges[i].node2;
        fin>>edges[i].cost;
    }
}

void bellman_ford(const int start=1) {
    dist.resize(n+1,maxInt);
    dist[start]=0;

    for (int i = 1; i <= n; i+=1) {
        for (const auto [node1, node2, cost] : edges) {
            if (dist[node2]>dist[node1]+cost)
                dist[node2] = dist[node1]+cost;
        }
    }

    for (const auto [node1, node2, cost] : edges) {
        if (dist[node2]>dist[node1]+cost) {
            fout<<"negative cycle\n";
            return;
        }
    }
    for (int i = 2; i <= n; i+=1)
        fout<<dist[i]<<' ';
    fout<<'\n';
}

int main() {
    read_edge_list();
    bellman_ford(start_node);
    return 0;
}