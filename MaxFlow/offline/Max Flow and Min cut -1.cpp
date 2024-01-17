#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> MincutArea1;
vector<int> MincutArea2;

class Edge
{
public:
    int u, v, f,c;
    Edge(int u, int v, int f, int c)
    {
        this->u = u;
        this->v = v;
        this->f = f;
        this->c = c;
    }
};

int BFS(int s, int t, int n, vector<Edge> residual[], vector<int> &INflow, vector<Edge> adj[])
{

    bool visited[n];
    int parent[n], dist[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
        parent[i] = -1;
        dist[i] = 1000000;
    }
    queue<int> q;
    q.push(s);
    visited[s] = true;
    dist[s] = 1000000;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (Edge e : residual[u])
        {
            if (!visited[e.v] && e.c > 0)
            {
                q.push(e.v);
                visited[e.v] = true;
                dist[e.v] =min( dist[u] , e.c);
                parent[e.v] = u;
            }
        }
    }
    if (visited[t] == false)
    {
        for (int i=0;i<n;i++)
        {
            if (visited[i]==true)
            {
                MincutArea1.push_back(i+1);
            }
            else
            {
                MincutArea2.push_back(i+1);
            }
        }
        return INT32_MIN;
    }
    int bottleneck = dist[t];
    int v = t;
    while (v != s)
    {
        int u = parent[v];
        INflow[v] += bottleneck;
        int flag=-1;
        int flag2=-1;
        int i=0;
        for (auto &e : adj[u])
        {
            if(e.v==v)
            {
                flag=i;
                // cout<<adj[u].size()<<endl;
                e.f += bottleneck;
                // cout<<adj[u][i].f<<endl;
                break;
            }
            i++;
        }
        if (flag==-1)
        {
            for (auto &e : adj[v])
            {
                if(e.v==u)
                {
                    flag2=i;
                    e.f -= bottleneck;
                    break;
                }
            }
        }
        for (auto &e : residual[u])
        {
            if(e.v ==v)
            {
                e.c -= bottleneck;
                break;
            }
        }
        for (auto &e : residual[v])
        {
            if(e.v==u)
            {
                e.c += bottleneck;
                break;
            }
        }
        v = u;
    }
    return bottleneck;
}


void maxFlowNode(int s, int t, int n, vector<Edge> adj[], vector<Edge> residual[])
{
    vector<int> INflow(n, 0);
    int x=BFS(s, t, n, residual, INflow, adj);
    int maxFlow = 0;
    while (x != INT32_MIN)
    {
        maxFlow += x;
        x=BFS(s, t, n, residual, INflow, adj);
    }
    int NodeOfMaxFlow=0;
    int MaxNodeFlow=0;
    for (int i = 1; i < n-1; i++)
    {
        if (INflow[i] > MaxNodeFlow)
        {
            MaxNodeFlow=INflow[i];
            NodeOfMaxFlow=i+1;
        }
    }
    cout<<"Solution of (a)"<<endl;
    cout<<NodeOfMaxFlow<<" "<<MaxNodeFlow<<endl;
    cout<<"\nSolution of (b)"<<endl;
    cout<<"[{";
    for (int i=0;i<MincutArea1.size();i++)
    {
        cout<<MincutArea1[i];
        if (i!=MincutArea1.size()-1) cout<<",";
    }
    cout<<"},{";
    for (int i=0;i<MincutArea2.size();i++)
    {
        cout<<MincutArea2[i];
        if (i!=MincutArea2.size()-1) cout<<",";
    }
    cout<<"}]"<<endl;
    cout <<maxFlow << endl;


}


int	main()
{
    int n, m; 
    int s, t; 
    cin >> n >> m;
    vector<Edge> edges;
    vector<Edge> adj[n];
    vector<Edge> residual[n];

    for (int i = 0; i < m; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        edges.push_back(Edge(u, v, 0, c));
        adj[u].push_back(Edge(u, v, 0, c));
        residual[u].push_back(Edge(u, v, 0, c));
        residual[v].push_back(Edge(v, u, 0, 0));
    }
    cin >> s >> t;
    s--; t--;
    maxFlowNode(s, t, n, adj, residual);
}


//!--------------------------Test-case------------------------------------
    // int u, v, c;
    // // 1 2 16
    // u=0; v=1; c=16;
    // edges.push_back(Edge(u, v, 0, c));
    // adj[u].push_back(Edge(u, v, 0, c));
    // residual[u].push_back(Edge(u, v, 0, c));
    // residual[v].push_back(Edge(v, u, 0, 0));
    // // 1 3 13
    // u=0; v=2; c=13;
    // edges.push_back(Edge(u, v, 0, c));
    // adj[u].push_back(Edge(u, v, 0, c));
    // residual[u].push_back(Edge(u, v, 0, c));
    // residual[v].push_back(Edge(v, u, 0, 0));
    // // 3 2 4
    // u=2; v=1; c=4;
    // edges.push_back(Edge(u, v, 0, c));
    // adj[u].push_back(Edge(u, v, 0, c));
    // residual[u].push_back(Edge(u, v, 0, c));
    // residual[v].push_back(Edge(v, u, 0, 0));
    // // 2 4 12
    // u=1; v=3; c=12;
    // edges.push_back(Edge(u, v, 0, c));
    // adj[u].push_back(Edge(u, v, 0, c));
    // residual[u].push_back(Edge(u, v, 0, c));
    // residual[v].push_back(Edge(v, u, 0, 0));
    // // 3 5 14
    // u=2; v=4; c=14;
    // edges.push_back(Edge(u, v, 0, c));
    // adj[u].push_back(Edge(u, v, 0, c));
    // residual[u].push_back(Edge(u, v, 0, c));
    // residual[v].push_back(Edge(v, u, 0, 0));
    // // 4 3 9
    // u=3; v=2; c=9;
    // edges.push_back(Edge(u, v, 0, c));
    // adj[u].push_back(Edge(u, v, 0, c));
    // residual[u].push_back(Edge(u, v, 0, c));
    // residual[v].push_back(Edge(v, u, 0, 0));
    // // 5 4 7
    // u=4; v=3; c=7;
    // edges.push_back(Edge(u, v, 0, c));
    // adj[u].push_back(Edge(u, v, 0, c));
    // residual[u].push_back(Edge(u, v, 0, c));
    // residual[v].push_back(Edge(v, u, 0, 0));
    // // 4 6 20
    // u=3; v=5; c=20;
    // edges.push_back(Edge(u, v, 0, c));
    // adj[u].push_back(Edge(u, v, 0, c));
    // residual[u].push_back(Edge(u, v, 0, c));
    // residual[v].push_back(Edge(v, u, 0, 0));
    // // 5 6 4
    // u=4; v=5; c=4;
    // edges.push_back(Edge(u, v, 0, c));
    // adj[u].push_back(Edge(u, v, 0, c));
    // residual[u].push_back(Edge(u, v, 0, c));
    // residual[v].push_back(Edge(v, u, 0, 0));
