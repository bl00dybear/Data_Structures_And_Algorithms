#include <bits/stdc++.h>
#define size 100
#define maxInt (1<<30)-1
using namespace std;

ifstream fin("/home/sebi/Data_Structures_And_Algorithms/IO_files/input.txt");
ofstream fout("/home/sebi/Data_Structures_And_Algorithms/IO_files/output.txt");

int n, m,start_node;
vector<pair<int, int>> graph[size];
vector<int> inDegree;
vector<int> dist;
bitset<size> visited;

void read_dag() {
    fin >> n >> m>> start_node;
    inDegree.resize(n + 2, 0);
    dist.resize(n + 2, maxInt);

    for (int i = 1; i <= m; i++) {
        int x, y, w;
        fin >> x >> y >> w;
        graph[x].push_back({y, w});
        inDegree[y] += 1;
    }
}

void topologicalSort() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topoOrder;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topoOrder.push_back(node);

        for (const auto &key: graph[node] | views::keys) {
            int neighbor = key;
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
}

void shortestPathDAG(const int start) {
    vector<int> topoOrder;
    queue<int> q;

    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topoOrder.push_back(node);

        for (const auto &key: graph[node] | views::keys) {
            int neighbor = key;
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    dist[start] = 0;

    for (const int u : topoOrder) {
        if (dist[u] != maxInt) {
            for (const auto&[fst, snd] : graph[u]) {
                const int v = fst;
                if (const int w = snd; dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }

    fout << "Distante minime de la nodul " << start << ":\n";
    for (int i = 1; i <= n; i++) {
        if (dist[i] == maxInt) {
            fout << "Nod " << i << ": Infinit\n";
        } else {
            fout << "Nod " << i << ": " << dist[i] << "\n";
        }
    }
}

int main() {
    read_dag();
    topologicalSort();
    shortestPathDAG(start_node);

    return 0;
}