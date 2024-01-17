#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
vector<vector<int>> subsetIndex;
int parent[100];
int in_mst[100];
int Tweight=0;
class Edge {
public:
    int s,d, w;

    Edge(int s, int d, int w) 
    {
        this->s = s;
        this->d = d;
        this->w = w;
    }
};

class keypair
{
    public :
        int vertex;
        int key;
        keypair(int vertex,int key)
        {
            this->vertex=vertex;
            this->key=key;
        }
        keypair(int v)
        {
            this->vertex=v;
            this->key=INT32_MAX;
        }
};

class Priority_Queue
{
    vector<keypair> queue;
    public :
        void insert(keypair k)
        {
            queue.push_back(k);
        }
        void decrease_key(int vertex,int key)
        {
            for (int i=0;i<queue.size();i++)
            {
                if (queue[i].vertex==vertex)
                {
                    queue[i].key=key;
                    break;
                }
            }
        }
        keypair extract_min()
        {
            if (queue.size()==0) return keypair(-1);
            sort(queue.begin(),queue.end(),[](keypair a,keypair b){return a.key<b.key;});
            // cout<<"PQ : \n";
            // for (auto x: queue) cout<<x.vertex<<" "<<x.key<<endl;
            // cout<<"----------------"<<endl;
            keypair x= queue.at(0);
            queue.erase(queue.begin());
            sort(queue.begin(),queue.end(),[](keypair a,keypair b){return a.key>b.key;});
            // queue.pop_back();
            return x;
        }
        bool empty()
        {
            return queue.size()==0;
        }
        bool contains(int vertex)
        {
            for (int i=0;i<queue.size();i++)
            {
                if (queue[i].vertex==vertex) return true;
            }
            return false;
        }
        int get_key(int vertex)
        {
            for (int i=0;i<queue.size();i++)
            {
                if (queue[i].vertex==vertex) return queue[i].key;
            }
            return INT32_MIN;
        }
};

vector<vector<Edge>> MSTlist;

bool MSTchecker(vector<Edge> MSTedge)
{
    vector<set<int>> MSTset;
    for (auto x: MSTedge)
    {
        int s=x.s;
        int d=x.d;
        int inds=-1,indd=-1;
        // cout<<"MSTset size"<<MSTset.size()<<endl;
        for (int i=0;i<MSTset.size();i++)
        {
            if (MSTset[i].find(s)!=MSTset[i].end()) inds=i;
            if (MSTset[i].find(d)!=MSTset[i].end()) indd=i;
        }
        if (inds==-1 && indd==-1)
        {
            set<int> temp;
            temp.insert(s);
            temp.insert(d);
            MSTset.push_back(temp);
        }
        else if (inds==-1)
        {
            MSTset[indd].insert(s);
        }
        else if (indd==-1)
        {
            MSTset[inds].insert(d);
        }
        else if (inds!=indd)
        {
            MSTset[inds].insert(MSTset[indd].begin(),MSTset[indd].end());
            MSTset.erase(MSTset.begin()+indd);
        }
        // cout<<"s "<<s<<" d "<<d<<" inds "<<inds<<" indd "<<indd<<endl;
    }
    // cout<<"MSTset size"<<MSTset.size()<<endl;
    if (MSTset.size()==1) return true;
    else return false;
}

void all_subsets(vector<int> edges,vector<Edge>EdgeList, int s, int e, int ind, int n)
{
    
    if (ind==n) 
    {
        // cout<<"***********"<<endl;
        sort(edges.begin(),edges.end());
        subsetIndex.push_back(edges);
        // for (auto x: edges) cout<< x<<"\n";
        // cout<<"***********"<<endl;
        edges.clear();
        return ;
    }
    for (int i = s; i <= e && e - i + 1 >= n - ind; i++) 
    {
        edges[ind]=i;
        all_subsets(edges,EdgeList,i+1,e,ind+1,n);
    }
}

void GenerateMST(int n,int m, vector<Edge> EdgeList)
{
    vector<int> edges(n-1);
    edges[0]=0;
    all_subsets(edges,EdgeList,0,m-1,0,n-1);
    for (auto x: subsetIndex)
    {
        vector<Edge> MSTedge;
        vector<bool> selected(n,false);
        int wt=0;
        for (auto y: x) 
        {   
            selected[EdgeList[y].s]=true;
            selected[EdgeList[y].d]=true;
            wt+=EdgeList[y].w;
            MSTedge.push_back(EdgeList[y]);
        }
        bool select=true;
        for (auto z: selected )
        {
            if (z==false) 
            {
                select=false;
                break;
            }
        }
        if (wt==Tweight && select && MSTchecker(MSTedge)) 
        {
            sort(MSTedge.begin(),MSTedge.end(), [](Edge a,Edge b){return a.w<b.w;});
            // cout<<"[";
            for (int i=0;i< MSTedge.size();i++)
            {
                Edge p=MSTedge[i];
                // cout<<"["<<p.s<<","<<p.d<<","<<p.w<<"]";
                // if (i!=MSTedge.size()-1) cout<<",";
            }
            // cout<<"]"<<endl;
            MSTlist.push_back(MSTedge);
        }
    }
}

void Prims(int n, int m, vector<Edge> graph[], vector<Edge> EdgeList)
{
    Priority_Queue pq;//n is vertices, m is edges
    vector<Edge> mst;
    Tweight=0;
    for (int i=0; i<n; i++)
    {
        pq.insert(keypair(i));
    }
    pq.decrease_key(0,0);
    while (!pq.empty())
    {
        keypair min_keypair=pq.extract_min();
        int u=min_keypair.vertex;
        int weight= min_keypair.key;
        if (weight==0) 
        {
            parent[u]=-1;
        }
        else
        {
            mst.push_back(Edge(parent[u],u,weight));
        }
        Tweight+=weight;
        in_mst[u]=true;
        for (int i=0; i<graph[u].size(); i++)
        {
            int v=graph[u][i].d;
            int w=graph[u][i].w;
            if (in_mst[v]==false && pq.get_key(v)>w )
            {
                // cout<<"for "<<v<<" "<<pq.get_key(v)<<"is changed to "<<w<<endl;
                pq.decrease_key(v,w);
                parent[v]=u;
            }
        }
    }
    // cout<<"mst :"<<Tweight<<endl;
    // cout<<"MSTs :"<<endl;
    GenerateMST(n,m,EdgeList);
}
