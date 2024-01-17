#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n,m,s,d,l,h,a,b;

struct Edge
{
    int s,d,w;
    Edge(int s,int d,int w)
    {
        this->s=s;
        this->d=d;
        this->w=w;
    }
};

void minDist(int source, vector<Edge> EdgeList, vector<int>& dist)
{
    dist[source-1]=0;
    for (int i=0; i<n-1; i++)
    {
        for (auto e: EdgeList)
        {
            if (dist[e.s-1]!=INT32_MAX && dist[e.s-1]+e.w<dist[e.d-1])
            {
                dist[e.d-1]=dist[e.s-1]+e.w;
            }
        }
    }

}

void BellmanFord(vector<Edge> EdgeList, vector<int> &dist)
{
    dist[s-1]=0;
    for (int i=0; i<n-1; i++)
    {
        for (auto e: EdgeList)
        {
            if (dist[e.s-1]!=INT32_MAX && dist[e.s-1]+e.w<dist[e.d-1])
            {
                dist[e.d-1]=dist[e.s-1]+e.w;
            }
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
    vector<int> dist(n,INT32_MAX );
    vector<int> dist_B(n,INT32_MAX );
    BellmanFord(EdgeList,dist);
    minDist(b,EdgeList,dist_B);
    // cout<<dist_B[d-1]<<endl;
    // cout<<dist_B[a-1]<<endl;
    int lower_limit= -1*dist_B[a-1];
    int upper_limit= dist[d-1]- dist[a-1]-dist_B[d-1];
    // cout<<lower_limit<<" "<<upper_limit<<endl;
    int w= max(lower_limit, l);
    if (w>upper_limit || w>h)
    {
        cout<<"Impossible"<<endl;
        return;
    }
    else
    {
        int p=dist[a-1]+w+dist_B[d-1];
        cout<<w<<" ";
        cout<<p<<endl;
        return;
    }
}

int main()
{
    cin>>n>>m;
    vector<Edge> EdgeList;
    for (int i=0; i<m; i++)
    {
        int s,d,w;
        cin>>s>>d>>w;
        Edge e1(s,d,w);
        EdgeList.push_back(e1);
    }
    cin>>a>>b; 
    cin>>l>>h; 
    cin>>s>>d;
    AssignWeights(EdgeList);
    cout<<endl;
    return 0;
}