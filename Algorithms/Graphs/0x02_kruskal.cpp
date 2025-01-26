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

int m,n;
vector<edge> edges;
vector<int> tree;
vector<int> parent;
vector<int> height;

void read_edge_list() {
    fin>>n>>m;
    edges.resize(m+1);
    for (int i = 1; i <= m; i+=1) {
        fin>>edges[i].node1>>edges[i].node2;
        fin>>edges[i].cost;
    }
}

int _root(const int node) {
    if (!parent[node])
        return node;
    else {
        const int node_root = _root(parent[node]);
        parent[node] = node_root;
        return node_root;
    }
}

void _union(const int node1, const int node2){
    const int root1 = _root(node1);
    if (const int root2 = _root(node2); root1 != root2) {
        if (height[root1] > height[root2])
            parent[root2] = root1;
        else {
            parent[root1] = root2;
            if (height[root1] == height[root2])
                height[root1]+=1;
        }
    }
}

void kruskal() {
    parent.resize(n+1,0);
    height.resize(n+1,0);
    tree.resize(n+1);
    int sum=0;

    sort(edges.begin(), edges.end(),[](const edge &a, const edge &b) {return a.cost < b.cost;});

    for (int i = 1,num=0; i <= m && num<=n-1; i+=1)
        if (_root(edges[i].node2)!= _root(edges[i].node1))
            _union(edges[i].node1, edges[i].node2),num += 1, sum += edges[i].cost, tree[num] = i;

    fout<<sum<<'\n';
    for (int k = 1; k <= n-1; k+=1)
        fout<<edges[tree[k]].node1<<" "<<edges[tree[k]].node2<<'\n';
}

int main() {
    read_edge_list();
    kruskal();
    return 0;
}