#include <bits/stdc++.h>
#define size 100
#define maxInt (1<<30)-1
using namespace std;

ifstream fin("/home/sebi/Data_Structures_And_Algorithms/IO_files/input.txt");
ofstream fout("/home/sebi/Data_Structures_And_Algorithms/IO_files/output.txt");


int n,m;
vector<int> graph[size];
vector<int> inDegree;
vector<int> result;

void read_dag() {
    fin >> n >>m;
    inDegree.resize(n+2);
    for (int i = 1; i <= m; i++) {
        int x, y;
        fin >> x >> y;
        graph[x].push_back(y);
        inDegree[y]+=1;
    }
    cout << n << " " << m << endl;
}

void topologicalSort() {
    queue<int> q;
    for (int i = 1; i <= n; i+=1) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);

        for (int nod : graph[node]) {
            inDegree[nod]--;
            if (inDegree[nod] == 0) {
                q.push(nod);
            }
        }
    }

    for (const int v : result) {
        fout << v << " ";
    }
}

int main() {
    read_dag();
    topologicalSort();
    return 0;
}