#include <bits/stdc++.h>
#define size 100
#define maxInt (1<<30)-1
using namespace std;

ifstream fin("/home/sebi/Data_Structures_And_Algorithms/IO_files/input.txt");
ofstream fout("/home/sebi/Data_Structures_And_Algorithms/IO_files/output.txt");

long long a[size][size];

void in(int&n)
{
    int m,c;
    fin>>n>>m;
    int x,y,j;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (i!=j) 
                a[i][j]=maxInt;
    for(int i = 1;i<=m;i++)
    {
        fin>>x>>y>>c;
        a[x][y]=c;
    }
}
void roy_warshall(const int n)
{
    for(int k = 1;k<=n;k++)
        for(int i = 1;i<=n;i++)
            for(int j = 1;j<=n;j++)
                if (i!=j&&a[i][j]>a[i][k]+a[k][j])
                    a[i][j]=a[i][k]+a[k][j];
}
void out(const int n)
{
    int i,j;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(a[i][j]==0 and (i-j)!=0)
                a[i][j]=-1;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            if(a[i][j]!=maxInt)
                fout<<a[i][j]<<' ';
            else 
                fout<<"-1 ";
        fout<<'\n';
    }
}
int main()
{
    int n;
    in(n);
    roy_warshall(n);
    out(n);
    return 0;
}