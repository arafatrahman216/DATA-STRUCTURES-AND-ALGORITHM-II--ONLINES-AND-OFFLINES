
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class vertex
{
    public :
    int city;
    int gas;
    vertex()
    {
        this->city=-1;
        this->gas=-1;
    }
    vertex(int city, int gas)
    {
        this->city=city;
        this->gas=gas;
    }
};

class keypair
{
    public :
        vertex v;
        int key;
        keypair(vertex vq)
        {
            this->v=vq;
            this->key=INT32_MAX;
          }
        keypair(vertex vq, int key)
        {
            this->v=vq;
            this->key=key;
        }
};

class Edge
{
    public :
    vertex s,d;
    int w;
    Edge(vertex s, vertex d, int w)
    {
        this->s=s;
        this->d=d;
        this->w=w;
    }
};
vector<Edge> EdgeList;


class Priority_Queue
{
    vector<keypair> queue;
    public :
        void insert(keypair k)
        {
            queue.push_back(k);
        }
        void decrease_key( vertex v,int key)
        {
            for (int i=0;i<queue.size();i++)
            {
                if (queue[i].v.city==v.city && queue[i].v.gas==v.gas)
                {
                    queue[i].key=key;
                    break;
                }
            }
        }
        keypair extract_min()
        {
            if (queue.size()==0) return keypair(vertex(-1,-1),-1);
            sort(queue.begin(),queue.end(),[](keypair a,keypair b){return a.key<b.key;});
            keypair x= queue.at(0);
            queue.erase(queue.begin());
            sort(queue.begin(),queue.end(),[](keypair a,keypair b){return a.key>b.key;});
            return x;
        }
        bool empty()
        {
            return queue.size()==0;
        }
        int get_key( vertex v)
        {
            for (int i=0;i<queue.size();i++)
            {
                if (queue[i].v.city==v.city && queue[i].v.gas==v.gas) return queue[i].key;
            }
            return INT32_MIN;
        }
};
