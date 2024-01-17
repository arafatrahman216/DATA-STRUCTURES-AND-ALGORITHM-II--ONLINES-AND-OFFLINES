#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include "2105118_header.cpp"
//All important classes and functions are in "MSTHeader.cpp" because task 2 and 3 also require them
using namespace std;

void AllPossibleMST(int n, int m, vector<Edge> graph[], vector<Edge> EdgeList)
{
    Prims(n,m,graph,EdgeList);
    // cout<<MSTlist.size()<<endl;
    cout<<"MSTs :"<<endl;
    int x=1;
    for ( auto MSTedge : MSTlist )
    {    
        cout<<x<<" : ";
        cout<<"[";
        x++;
        for (int i=0;i< MSTedge.size();i++)
        {
            Edge p=MSTedge[i];
            cout<<"["<<p.s<<", "<<p.d<<", "<<p.w<<"]";
            if (i!=MSTedge.size()-1) cout<<", ";
        }
        cout<<"]"<<endl;
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
        Edge e1(s,d,w),e2(d,s,w);
        EdgeList.push_back(e1);
        graph[s].push_back(e1);
        graph[d].push_back(e2);
    }
    AllPossibleMST(n,m,graph,EdgeList);
    return 0;
}


//----------------------------------------------------------------
    // Edge e1(0,1,1),e2(1,0,1);
    //     graph[0].push_back(e1);
    //     graph[1].push_back(e2);
    //     EdgeList.push_back(e1);
    
    // // 2 4 1
    // Edge e3(2,4 ,1) ,e4(4,2,1);
    //     graph[2].push_back(e3);
    //     graph[4].push_back(e4);
    //     EdgeList.push_back(e3);
    // // 1 2 2
    // Edge e5(1,2,2),e6(2,1,2);
    //     graph[1].push_back(e5);
    //     graph[2].push_back(e6);
    //     EdgeList.push_back(e5);
    // // 0 4 2
    // Edge e7(0,4,2),e8(4,0,2);
    //     graph[0].push_back(e7);
    //     graph[4].push_back(e8);
    //     EdgeList.push_back(e7);
    // // 3 4 3
    // Edge e9(3,4,3),e10(4,3,3);
    //     graph[3].push_back(e9);
    //     graph[4].push_back(e10);
    //     EdgeList.push_back(e9);
    // // 0 3 5
    // Edge e11(0,3,5),e12(3,0,5);
    //     graph[0].push_back(e11);
    //     graph[3].push_back(e12);
    //     EdgeList.push_back(e11);
    // //  1 4 6
    // Edge e13(1,4,6),e14(4,1,6);
    //     graph[1].push_back(e13);
    //     graph[4].push_back(e14);
    //     EdgeList.push_back(e13);
    // // 2 3 8

    // Edge e15(2,3,8),e16(3,2,8);
    //     graph[2].push_back(e15);
    //     graph[3].push_back(e16);
    //     EdgeList.push_back(e15);
    // // 0 2 9
    // Edge e17(0,2,9),e18(2,0,9);
    //     graph[0].push_back(e17);
    //     graph[2].push_back(e18);
    //     EdgeList.push_back(e17);
    // // 1 3 9
    // Edge e19(1,3,9),e20(3,1,9);
    //     graph[1].push_back(e19);
    //     graph[3].push_back(e20);
    //     EdgeList.push_back(e19);
