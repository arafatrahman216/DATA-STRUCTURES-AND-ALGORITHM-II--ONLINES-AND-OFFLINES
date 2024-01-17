#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;

int n,m,s,d;
#define INF INT32_MAX

struct Edge
{
    int s,d;
    int w;
    Edge(int s,int d,int w)
    {
        this->s=s;
        this->d=d;
        this->w=w;
    }
};


void BellmanFord(vector<Edge> EdgeList, vector<int> &dist)
{
    dist[s]=0;
    for (int i=0; i<n-1; i++)
    {
        for (auto e: EdgeList)
        {
            if (dist[e.s]!=INT32_MAX && dist[e.s]+e.w<dist[e.d])
            {
                dist[e.d]=dist[e.s]+e.w;
            }
        }
    }
    // for ( int i=0;i<n;i++) cout<<"dist : "<<dist[i]<<"\t";

}

void leastTax(vector<Edge> EdgeList)
{
    vector<int> weights;
    vector<int> dist(n,INF );
    BellmanFord(EdgeList,dist);
    cout<<dist[d];
    
}

int main()
{
    cin>>n>>m;
    vector<Edge> EdgeList;
    int cost[n];
    for ( int i=0;i<n;i++)
    {
        cin>>cost[i];
    }
    for (int i=0; i<m; i++)
    {
        int a,b;
        cin>>a>>b;
        a--;b--;
        int w=cost[b];
        Edge e1(a,b,w);
        EdgeList.push_back(e1);
        w=cost[a];
        Edge e2(b,a,w);
        EdgeList.push_back(e2);
    }
    s=0; d=n-1;
    leastTax(EdgeList);
    return 0;
}