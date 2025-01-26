#include <bits/stdc++.h>
#define size 100
#define maxInt (1<<30)-1
using namespace std;

ifstream fin("~/input.txt");
ofstream fout("~/output.txt");

int m,n;
vector<pair<int,int>> weighted_graph[size];
vector<int> parent;
vector<int>dist;
bitset<size> visited;

void read_adjacency_list_weighted() {
    int node1,node2,cost;
    fin>>n>>m;
    for (int i = 1; i <= m; i+=1) {
        fin>>node1>>node2>>cost;
        weighted_graph[node1].push_back(make_pair(node2,cost));
        weighted_graph[node2].push_back(make_pair(node1,cost));
    }
}

void prim() {
    int sum=0;

    dist.resize(n+1,maxInt);
    parent.resize(n+1,0);

    dist[1]=0;
    set<pair<int,int>> s;
    s.insert(make_pair(0,1));
    while (!s.empty()) {
        const auto x = s.begin();
        s.erase(x);
        const int cost = x->first;
        const int node = x->second;
        sum+=cost;
        visited[node] = true;

        for (const auto [fst, snd] : weighted_graph[node]) {
            if (dist[fst]>snd &&!visited[fst]) {
                s.erase(make_pair(dist[fst],fst));
                dist[fst] = snd;
                s.insert(make_pair(dist[fst],fst));
                parent[fst] = node;
            }
        }
    }

    fout<<sum<<'\n';
    for (int k=2;k<=n;k+=1)
        fout<<k<<' '<<parent[k]<<'\n';
}