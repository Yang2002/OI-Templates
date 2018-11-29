// Now EK supports long long.
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

typedef long long ll;

const int maxn = 3030, maxm = 303200;
int n, m, ss, tt;
long long tot = 0;

namespace adjlist{
    int head[maxn], nxt[maxm], ecnt = 1;
    struct Edge{
        int from, to, cap, flow;
        Edge(int a = 0, int b = 0, int c = 0, int d = 0): from(a), to(b), cap(c), flow(d){}
    } e[maxm];
    inline void addedge(int x, int y, int w){
        e[++ecnt] = Edge(x, y, w, 0);
        nxt[ecnt] = head[x];
        head[x] = ecnt;

        e[++ecnt] = Edge(y, x);
        nxt[ecnt] = head[y];
        head[y] = ecnt;
    }
    inline void init(){
        memset(head, 0, sizeof head);
        ecnt = 1;
    }
}
namespace EK{
    #define INF 0x3f3f3f3f
    using namespace adjlist;
    int a[maxn], p[maxn];
    inline ll maxflow(int s, int t){
        ll flow = 0;
        for(;;){
            memset(a, 0, sizeof a);
            queue<int> q;
            q.push(s), a[s] = INF;
            while(!q.empty()){
                int x = q.front(); q.pop();
                for(int i = head[x]; i ; i = nxt[i]){
                    if(!a[e[i].to] && e[i].cap > e[i].flow){
                        a[e[i].to ] = min(a[x], e[i].cap - e[i].flow);
                        p[e[i].to] = i;
                        q.push(e[i].to);
                    }
                }
                if(a[t]) break;
            }
            if(!a[t]) break;
            for(int u = t; u != s; u = e[p[u]].from ){
                e[p[u]].flow += a[t];
                e[p[u] ^ 1].flow -= a[t];
            }
            flow += a[t];
        }
        return flow;
    }
}

using EK::addedge;
using EK::maxflow;

