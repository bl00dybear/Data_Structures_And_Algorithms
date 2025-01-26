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

void bfs(const int currentNode) {
    queue<int> q;
    q.push(currentNode);
    visited[currentNode] = true;

    while (!q.empty()) {
        const int node = q.front();
        fout<<node<<" ";
        q.pop();
        for (const auto node_2 : graph[node]) {
            if (!visited[node_2]) {
                q.push(node_2);
                visited[node_2] = true;
            }
        }
    }
}

int main() {
    read_adjacency_list();
    bfs(start_node);
    return 0;
}
