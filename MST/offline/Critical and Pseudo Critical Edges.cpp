#include <iostream>
#include "2105118_header.cpp"
using namespace std;

void Differentiate_Edge(int n, int m, vector<Edge> graph[], vector<Edge> EdgeList)
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
    vector<int> critical, pseudo;
    for (int i=0;i<m;i++)
    {
        if (iterations[i]==mss) critical.push_back(i);
        else if (iterations[i]>0) pseudo.push_back(i);
    }
    cout<<"Critical edges: [";
    for (int i =0; i<critical.size(); i++)
    {
        cout<<critical[i];
        if (i!=critical.size()-1) cout<<",";
    }
    cout<<"]"<<endl;
    cout<<"Pseudo critical edges: [";
    for (int i =0; i<pseudo.size(); i++)
    {
        cout<<pseudo[i];
        if (i!=pseudo.size()-1) cout<<",";
    }
    cout<<"]"<<endl;
    

    
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
        Edge e1(s,d,w),e2(d,s,w);
        EdgeList.push_back(e1);
        graph[s].push_back(e1);
        graph[d].push_back(e2);
    }
    Differentiate_Edge(n,m,graph,EdgeList);
}