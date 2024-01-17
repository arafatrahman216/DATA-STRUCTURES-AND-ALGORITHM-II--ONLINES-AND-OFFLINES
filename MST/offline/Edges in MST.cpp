#include <iostream>
#include "2105118_header.cpp"
using namespace std;

void CheckEachEdge(int n, int m, vector<Edge> graph[], vector<Edge> EdgeList)
{
    Prims(n,m,graph,EdgeList);
    vector<int> iterations(m,0);
    // cout<<MSTlist.size()<<endl;
    for (auto MST : MSTlist)
    {
        int x=0;
        // cout<<"COWARDS";
        for (auto MSTedge : MST)
        {
            for (int i=x;i< m ; i++)
            {
                if (EdgeList[i].s==MSTedge.s && EdgeList[i].d==MSTedge.d && EdgeList[i].w==MSTedge.w)
                {
                    iterations[i]++;
                    // cout<<EdgeList[i].s<<" "<<EdgeList[i].d<<" "<<EdgeList[i].w<<" "<<iterations[i]<<endl;
                    // x=i;
                    break;
                }
            
            }
        }
    }
    int mss=MSTlist.size();
    for (int i=0;i<m;i++)
    {
        if (iterations[i]==mss) cout<<"any"<<endl;
        else if (iterations[i]>0) cout<<"at least one"<<endl;
        else cout<<"none"<<endl;
    }
    
}

int main()
{
    int n,m;
    cin>>n>>m;
    // n=5; m=10;
    vector<Edge> graph[n];
    vector<Edge> EdgeList;
    for (int i=0; i<m; i++)
    {
        int s,d,w;
        cin>>s>>d>>w;
        s--;d--;
        Edge e1(s,d,w),e2(d,s,w);
        EdgeList.push_back(e1);
        graph[s].push_back(e1);
        graph[d].push_back(e2);
    }
    CheckEachEdge(n,m,graph,EdgeList);
}