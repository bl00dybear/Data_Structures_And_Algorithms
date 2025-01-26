#include <bits/stdc++.h>
#define size 100
using namespace std;

ifstream fin("/home/sebi/Data_Structures_And_Algorithms/IO_files/input.txt");
ofstream fout("/home/sebi/Data_Structures_And_Algorithms/IO_files/output.txt");

int n, m;
vector<int> graph[size]; // Listă de adiacență pentru graf
vector<int> eulerCycle; // Vector pentru stocarea ciclului eulerian

void read_graph() {
    fin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        fin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x); // Graf neorientat
    }
}

void hierholzer(const int start) {
    stack<int> stack;
    stack.push(start);

    while (!stack.empty()) {
        int u = stack.top();

        if (!graph[u].empty()) {
            // Există muchii neparcurse din nodul u
            int v = graph[u].back(); // Luăm ultimul vecin
            graph[u].pop_back(); // Ștergem muchia (u, v)

            // Ștergem muchia (v, u) din graf (deoarece este neorientat)
            for (auto it = graph[v].begin(); it != graph[v].end(); ++it) {
                if (*it == u) {
                    graph[v].erase(it);
                    break;
                }
            }

            stack.push(v); // Continuăm din nodul v
        } else {
            // Nu mai există muchii neparcurse din nodul u
            eulerCycle.push_back(u); // Adăugăm nodul la ciclul eulerian
            stack.pop(); // Îl scoatem din stivă
        }
    }
}

void print_euler_cycle() {
    fout << "Ciclu Eulerian: ";
    for (int node : eulerCycle) {
        fout << node << " ";
    }
    fout << endl;
}

int main() {
    read_graph();

    // Verificăm dacă graful are un ciclu eulerian
    bool hasEulerCycle = true;
    for (int i = 1; i <= n; i++) {
        if (graph[i].size() % 2 != 0) { // Grad impar
            hasEulerCycle = false;
            break;
        }
    }

    if (hasEulerCycle) {
        hierholzer(1); // Pornim de la un nod arbitrar (în acest caz, nodul 1)
        print_euler_cycle();
    } else {
        fout << "Graful nu are un ciclu eulerian!\n";
    }

    return 0;
}
/*
//Algoritmul lui Hierholzer
//O(m+n) pt orientate
//O(mn) pt neorientate din cauza eliminarii
#include <bits/stdc++.h>
using namespace std;
ifstream fin("sch.txt");
ofstream fout("schh.txt");
vector<int> g[201];
bool viz[201];
int gr[201];
int n;
void in()
{
    fin>>n;
    int x,y;
    while (fin>>x>>y)
    {
        g[x].push_back(y);
        g[y].push_back(x);
        gr[x]+=1;
        gr[y]+=1;
    }
    
}
void elimin(int a,int b)
{
    int l1=g[a].size(),r1=0;
    int l2=g[b].size(),r2=0;
    for(int t=0;t<l1;t++)
        if(g[a][t]==b)
            r1=t;
    for(int t=0;t<l2;t++)
        if(g[b][t]==a)
            r2=t;
    g[a].erase(g[a].begin() + r1);
    g[b].erase(g[b].begin() + r2);
}
void euler(int nc)
{
    int v;
    stack<int> s;
    s.push(nc);
    while (!s.empty())
    {
        nc=s.top();
        if(gr[nc]!=0)
        {
            v=g[nc].front();
            gr[nc]--;
            gr[v]--;
            elimin(v,nc);
            s.push(v);
        }
        else
        {
            int q=s.top();
            s.pop();
            fout<<q<<' ';
        }
    }
}
int main()
{
    in();
    euler(1);
}

Pseudocod
void euler(int u) {
  Stack S = { u };
  while (!S.empty()) {
    u ← S.top();
    if (u are muchii netraversate) {
      v ← vecin al lui u;
      șterge (u,v) din listele de adiacență ale lui u (și v, dacă G este neorientat);
      S.push(v);
    } else {
      S.pop();
      print u;
    }
  }
}
 
 */