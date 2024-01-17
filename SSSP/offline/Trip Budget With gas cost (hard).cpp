#include<iostream>
#include<vector>
#include<algorithm>
#include "2105118_header.cpp"
using namespace std;

int n,m,s,d,c,p;
bool checked[100][100];
int dist[100][100];
vector<Edge> graph[100][100];


void dijkstra( vector<Edge> EdgeList)
{
    Priority_Queue pq;//n is vertices, m is edges
    vector<vertex> distance_graph[n+1];
    for (int i=0; i<n; i++)
    {
        for ( int j=0;j<=c;j++)
        {
            pq.insert(keypair(vertex(i,j)));
        }
    }
    pq.decrease_key(vertex(s-1,0),0);
    while (!pq.empty())
    {
        keypair min_keypair=pq.extract_min();
        vertex u=min_keypair.v;
        int wt=min_keypair.key;
        dist[u.city][u.gas]=wt;
        pq.decrease_key(u,wt);
        checked[u.city][u.gas]=true;
        for (int i=0; i<graph[u.city][u.gas].size(); i++)
        {
            vertex v=graph[u.city][u.gas][i].d;
            int w=graph[u.city][u.gas][i].w;
            if (checked[v.city][v.gas]==false && pq.get_key(v)>w+ dist[u.city][u.gas] )
            {
                // cout<<"for "<<v.city <<" and "<<v.gas<<" "<<pq.get_key(v)<<"is changed to "<<w<<endl;
                pq.decrease_key(v,w+dist[u.city][u.gas]);
            }
        }
    }
    if(dist[d-1][0]< m*100000 && dist[d-1][0]> m*(-100000))
    {
        cout<<dist[d-1][0]<<endl;
    }
    else 
    {
        cout<<"impossible"<<endl;
    }
}

    
int main()
{
    cin>>n>>m>>c;
    int cost[n];
    for (int i=0; i<n; i++)
    {
        cin>>cost[i];
    }
    vector<Edge>CostEdgeList;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<c;j++)
        {
            dist[i][j]=INT32_MAX;
            vertex u(vertex(i,j)), v (vertex(i,j+1));
            CostEdgeList.push_back(Edge(u,v,cost[i]));
            graph[i][j].push_back(Edge(u,v,cost[i]));
        }
    }
    for (int i=0; i<m; i++)
    {
        int s,d,w;
        cin>>s>>d>>w;
        s--;d--;
        for ( int j=c;j>=w; j--)
        {
            vertex u(s,j), v(d,j-w);
            CostEdgeList.push_back(Edge(u,v,0));
            graph[s][j].push_back(Edge(u,v,0));
        }
    }
    cin>>s>>d;
    dijkstra(CostEdgeList);
    return 0;
}