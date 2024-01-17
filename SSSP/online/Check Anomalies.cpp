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

// void minDist(int source, vector<Edge> EdgeList, vector<int>& dist)
// {
//     dist[source-1]=0;
//     for (int i=0; i<n-1; i++)
//     {
//         for (auto e: EdgeList)
//         {
//             if (dist[e.s-1]!=INT32_MAX && dist[e.s-1]+e.w<dist[e.d-1])
//             {
//                 dist[e.d-1]=dist[e.s-1]+e.w;
//             }
//         }
//     }
// }

void BellmanFord(vector<Edge> EdgeList, vector<int> &dist)
{
    vector<int> parent(n,-1 );
    dist[s]=0;
    for (int i=0; i<n-1; i++)
    {
        for (auto e: EdgeList)
        {
            if (dist[e.s]!=INF && dist[e.s]+e.w<dist[e.d])
            {
                dist[e.d]=dist[e.s]+e.w;
                // cout<<e.s<<" "<<e.d<<" ";
                parent[e.d]=e.s;
                // cout<<dist[e.s]<<" "<<dist[e.d]<<endl;
            }
        }
    }
    //check for negative cycle
    for (auto e: EdgeList)
    {
        if (dist[e.s]!=INF && dist[e.s]+e.w<dist[e.d])
        {
            cout<<"there is an anomaly"<<endl;
            return;
        }
    }
    cout<<"there is no anomalies"<<endl;
    cout<<"Best exchange rate: "<<dist[d]<<endl;
    stack<int> path;
    int i=d;
    while (i!=-1)
    {
        path.push(i);
        i=parent[i];
    }
    while (!path.empty())
    {
        cout<<path.top();
        path.pop();
        if (!path.empty())
        {
            cout<<" -> ";
        }
    }
    
    // for (auto x: dist)
    // {
    //     cout<<x<<" ";
    // }
    // cout<<endl;

}

void AssignWeights(vector<Edge> EdgeList)
{
    vector<int> weights;
    vector<int> dist(n,INF );
    BellmanFord(EdgeList,dist);
    
}

int main()
{
    cin>>n>>m;
    vector<Edge> EdgeList;
    for (int i=0; i<m; i++)
    {
        int s,d;
        int w;
        cin>>s>>d>>w;
        Edge e1(s,d,w);
        EdgeList.push_back(e1);
    }
    cin>>s>>d;
    AssignWeights(EdgeList);
    cout<<endl;
    return 0;
}