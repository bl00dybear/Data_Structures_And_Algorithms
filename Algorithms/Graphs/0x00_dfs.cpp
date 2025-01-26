#include <bits/stdc++.h>
#define size 100
#define maxInt (1<<30)-1
using namespace std;

ifstream fin("~/input.txt");
ofstream fout("~/output.txt");

int m,n;
int start_node;
vector<int> graph[size];
bitset<size> visited;

void read_adjacency_list() {
    int a,b;
    fin>>n>>m>>start_node;
    for (int i = 1; i <= m; i+=1) {
        fin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
}

void dfs(const int currentNode) {
    visited[currentNode] = true;
    fout<<currentNode<<" ";
    for (const auto node : graph[currentNode]) {
        if (!visited[node]) {
            dfs(node);
        }
    }
}

int main() {
    read_adjacency_list();
    dfs(start_node);
    return 0;
}