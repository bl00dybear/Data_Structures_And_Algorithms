#include <bits/stdc++.h>
#define size_ 10002
#define maxInt (1<<30)
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int m, n;
vector<int> graph[size_ + 1];
bitset<size_>visited;
int flow[size_+1][size_+1];
int parent[size_+1];
int capacity[size_+1][size_+1];

void read_graph() {
    fin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int x,y,c;
        fin >> x >> y >> c;
        graph[x].emplace_back(y);
        graph[y].emplace_back(x);
        capacity[x][y]=c;
    }
}

void reset_visited_parent() {
    for (int i=1;i<=n;i+=1) {
        parent[i] = 0;
        visited[i] = false;
    }
}

void bfs(const int source) {
    queue<int> _queue;
    _queue.push(source);
    visited[source] = true;
    while(!_queue.empty()) {
        const int front_node = _queue.front();
        _queue.pop();
        for (const auto node : graph[front_node]) {
            if (!visited[node]) {
                if (capacity[front_node][node] -flow[front_node][node] > 0) {
                    _queue.push(node);
                    visited[node] = true;
                    parent[node] = front_node;
                }
            }
        }
    }
}

int flow_on_bfs(const int source, const int dest){
    vector<int> path;

    reset_visited_parent();
    bfs(source);

    // fout<<visited[dest]<<endl;
    if (!visited[dest]) return 0;
    // fout<<"aici\n";
    int len=0;
    int nod =dest;
    while (nod) {
        path.emplace_back(nod);
        nod = parent[nod];
        len+=1;
    }
    reverse(path.begin(), path.end());

    int min_capacity = maxInt;

    for (int i=0;i<len-1;i+=1) {
        const int node1 = path[i];
        const int node2 = path[i+1];
        min_capacity = min(min_capacity, capacity[node1][node2]-flow[node1][node2]);
    }

    for (int i=0;i<len-1;i+=1) {
        const int node1 = path[i];
        const int node2 = path[i+1];
        flow[node1][node2] += min_capacity;
        flow[node2][node1] -= min_capacity;
    }

    return min_capacity;
}


int main(){
    int maxFlow=0;

    read_graph();

    while (true) {
        const int flow_on_each_step = flow_on_bfs(1, n);
        if (!flow_on_each_step) break;
        maxFlow += flow_on_each_step;
    }

    fout<<maxFlow;
    return 0;
}