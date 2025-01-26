#include <bits/stdc++.h>
#define size 100

using namespace std;

ifstream fin("/home/sebi/Data_Structures_And_Algorithms/IO_files/input.txt");
ofstream fout("/home/sebi/Data_Structures_And_Algorithms/IO_files/output.txt");

int n,m;
vector<int> graph[size];
vector<int> t_graph[size];
bitset<size> visited;
stack<int> _stack;

void read_graph() {
    fin>>m>>n;
    for (int i=1;i<=m;i+=1) {
        int x,y;
        fin>>x>>y;
        graph[x].push_back(y);
        t_graph[y].push_back(x);
    }
}

void dfs(const int curr_node) {
    visited[curr_node] = true;
    for (const auto node : graph[curr_node]) {
        if (!visited[node]) {
            dfs(node);
            _stack.push(node);
        }
    }
}

void t_dfs(const int curr_node) {
    visited[curr_node] = true;
    fout<<curr_node<<" ";
    for (const auto node : t_graph[curr_node]) {
        if (!visited[node]) {
            t_dfs(node);
        }
    }
}

void reset_visited() {
    for (int i=1;i<=n;i+=1) {
        visited[i] = false;
    }
}

void kosaraju() {
    int num_scc=0;

    for (int i=1;i<=n;i+=1)
        if (!visited[i])
            dfs(i);

    reset_visited();
    while (!_stack.empty()) {
        const int stack_top = _stack.top();
        _stack.pop();
        if (!visited[stack_top]) {
            num_scc += 1;
            t_dfs(stack_top);
            fout<<'\n';
        }
    }
    fout<<num_scc<<'\n';
}

int main() {
    read_graph();
    kosaraju();
    return 0;
}
