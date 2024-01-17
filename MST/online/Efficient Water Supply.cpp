#include<iostream>
#include<cmath>
#include"2105118_header.cpp"
using namespace std;

int distances(int xi, int yi, int xj, int yj)
{
    return abs(abs((xi-xj))+abs((yi-yj)));
}

int findcost(int n, int m, vector<Edge> graph[], vector<Edge> EdgeList)
{
    Prims(n,EdgeList.size(),graph,EdgeList);
    cout<<Tweight<<endl;
    return Tweight;
}

int main()
{
    int n;
    cin>>n;
    vector<Edge> graph[n];
    vector<Edge> EdgeList;
    int xcor[n], ycor[n];
    for ( int i=0;i<n ;i++)
    {
        cin>>xcor[i]>>ycor[i];
    }


    
    for (int i=0; i<n; i++)
    {
        for (int j=i+1; j<n; j++)
        {   
            int s,d,w;
            s=i; d=j;
            w= distances(xcor[i],ycor[i],xcor[j],ycor[j]);
            Edge e1(s,d,w),e2(d,s,w);
            EdgeList.push_back(e1);
            graph[s].push_back(e1);
            graph[d].push_back(e2);
        }
    }
    findcost(n,EdgeList.size(),graph,EdgeList);
    return 0;



}