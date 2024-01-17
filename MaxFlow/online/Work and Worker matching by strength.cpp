#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int m,n ; //Worker and Work

class Work
{
public:
    int st;
    Work(int strength)
    {
        this->st = strength;
    }
};

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

vector<Work> Worker;
vector<Work>work;

bool validate(Work worker, Work work)
{
    if (worker.st>= work.st) return true;
    return false;
}

void AddEdge(Edge e, vector<Edge> adj[], vector<Edge> residual[])
{
    adj[e.u].push_back(e);
    residual[e.u].push_back(e);
    residual[e.v].push_back(Edge(e.v, e.u, 0, 0));

}

int BFS(int s, int t, int n, vector<Edge> residual[], vector<Edge> adj[])
{

    bool visited[m+n+1];
    int parent[m+n+1], dist[m+n+1];
    for (int i = 0; i < m+n+2; i++)
    {
        visited[i] = false;
        parent[i] = -1;
        dist[i] = 1000000;
    }
    queue<int> q;
    q.push(s);
    visited[s] = true;
    dist[s] = 1000000;
    // cout<<"BFS"<<t<<endl;
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
        return INT32_MIN;
    }
    int bottleneck = dist[t];
    int v = t;
    while (v != s)
    {
        int u = parent[v];
        int flag=-1;
        int flag2=-1;
        int i=0;
        for (auto &e : adj[u])
        {
            if(e.v==v)
            {
                flag=i;
                e.f += bottleneck;
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
    // cout<<bottleneck<<endl;
    return bottleneck;
}



void BipartiteMatching(int s, int t, int n, vector<Edge> adj[], vector<Edge> residual[])
{
    int x=BFS(s, t, n, residual, adj);
    int maxFlow = 0;
    while (x != INT32_MIN)
    {
        maxFlow += x;
        x=BFS(s, t, n, residual,adj);
    }
    cout<<maxFlow << endl;


}


int main()
{

    cin>>m>>n;
    // m=2;n=2;
    vector<Edge> adj[m+n+2];
    vector<Edge> residual[m+n+2];

    for (int i=0;i<m; i++)
    {
        int h;
        cin>>h;
        Worker.push_back(Work(h));
    }
    for (int i=0;i<n; i++)
    {
        int h;
        cin>>h;
        work.push_back(Work(h));
    }
    //node 0= source s
    //node 1 to m = Worker
    // node m+1 to m+n = Work
    // node m+n+1 = sink t
    int f=0;
    for (int i=1;i<= m;i++)
    {
        Edge e(0,i,0,1);
        AddEdge(e,adj,residual);
        for ( int j=1;j<=n;j++)
        {
            if (validate(Worker[i-1],work[j-1]))
            {
                Edge e(i,m+j,0,1);
                AddEdge(e,adj,residual);
            }
        }
    }
    for (int i=1;i<=n;i++)
    {
        Edge e(m+i,m+n+1,0,1);
        AddEdge(e,adj,residual);
    }
    int s=0,t=m+n+1;
    BipartiteMatching(s,t,m+n+2,adj,residual);

}
    