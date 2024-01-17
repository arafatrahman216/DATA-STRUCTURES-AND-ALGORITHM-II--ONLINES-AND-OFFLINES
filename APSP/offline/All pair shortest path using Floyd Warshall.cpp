#include <iostream>
#include <vector>
#define INF INT32_MAX
using namespace std;

class Edge
{
    public:
        int s,d,w;
        Edge(int s,int d,int w)
        {
            this->s=s;
            this->d=d;
            this->w=w;
        }
};

vector<Edge> EdgeList;
int n,m,t;

void Initialize(vector<vector<int>> &adj)
{
    for (int i=0; i<n; i++)
    {
        adj[i][i]=0;
    }
    for (auto e: EdgeList)
    {
        adj[e.s-1][e.d-1]=e.w;
        adj[e.d-1][e.s-1]=e.w;
    }
}
void PrintMatrix(vector<vector<int>> adj)
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            cout<<adj[i][j]<<"\t";
            if (adj[i][j]!=INF)
            {
                cout<<"\t";
            }
        }
        cout<<endl;
    }
}

void Floyd_warshall(vector<vector<int>> &adj)
{
    Initialize(adj);
    vector<int> smallest_reachable(n,0);
    vector<vector<int>> dist(adj.begin(),adj.end());
    int min_city=INF;
    for (int k=0; k<n; k++)
    {
        for (int u=0; u<n; u++)
        {
            for (int v=0; v<n; v++)
            {   
                if (adj[u][k]!=INF && adj[k][v]!=INF) dist[u][v]=min(adj[u][v],adj[u][k]+adj[k][v]);
                if (k==n-1)
                {
                    if (dist[u][v]<=t) smallest_reachable[u]++;
                }
            }
        }
        adj=dist;
    }
    // PrintMatrix(adj);
    for ( int i=0; i<n; i++)
    {
        if (smallest_reachable[i]<min_city)
        {
            min_city= smallest_reachable[i];
        }
    }
    // cout<<min_city<<endl;
    for (int i=0; i<n; i++)
    {
        if (smallest_reachable[i]==min_city)
        {
            cout<<i+1<<" ";
        }
    }
}

int main()
{
    cin>>n>>m;
    vector<vector<int>> adj(n,vector<int>(n,INF));
    for (int i=0;i<m; i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        EdgeList.push_back(Edge(u,v,w));
        // EdgeList.push_back(Edge(v,u,w));
    }
    cin>>t;
    Floyd_warshall(adj);
    

}