// using doubling algorithm to get the LCA of any two nodes in a tree
// Complexity: O(nlogn) precalculate and O(logn) for each query

#include<bits/stdc++.h>
#define REP(i,n) for(int i = 0; i < n; ++i)
#define rep(i,n) for(int i = 1; i <= n; ++i)
#define boost ios::sync_with_stdio(0)
#define ms0(s) memset((s), 0, sizeof(s))
#define INF 0x3f3f3f3f
#define ABS(x) ((x)<0 ? (-(x)) : (x))
#define forvec(it,v) for(vector<int>::iterator it = v.begin(); it != v.end(); ++it)

using namespace std;
typedef long long ll;
template <typename T>
inline void read(T& x){
    int w = 1; T data = 0;
    char ch = getchar();
    while(!isdigit(ch) && ch != '-') ch = getchar();
    if(ch == '-') w = -1, ch = getchar();
    while(isdigit(ch))
        data = 10 * data + ch - '0', ch = getchar();
    x = data * w;
}
template <typename T>
void write(T x){
	 if (x < 0) putchar('-'),x = ~x + 1;
	 if (x > 9) write(x / 10);
	 putchar( x % 10 + '0');
}
const int maxn = 500020;
int anc[maxn][30], lg[maxn], dep[maxn], n, m, s;
int head[maxn], k = 0;
struct node{
    int v,next;
}e[maxn*2];
void add(int u,int v)
{
    e[k].v = v;
    e[k].next = head[u];
    head[u] = k++;
}
inline void init_log(){
    for(int i = 1; i <= n; ++i)
        lg[i] = lg[i - 1] + (1 << (lg[i-1]+1) == i);
}
void dfs(int v, int depth){
    dep[v] = depth;
    for(int i = head[v], u = e[i].v ; i != -1; i = e[i].next, u = e[i].v ) if(!dep[u]){
        anc[u][0] = v;
        dfs(u, depth + 1);
    }
}
inline void lca_init(){
    for(int j = 1; j <= lg[n]; ++j)
        for(int i = 1; i <= n; ++i)
            anc[i][j] = anc[anc[i][j-1]][j-1];
}
inline int LCA(int x, int y){
    if(dep[x] < dep[y]) swap(x, y);
    while(dep[x] > dep[y]) x = anc[x][lg[dep[x] - dep[y]]];
    if(x == y) return x;
    for(int k = lg[dep[x]]; k >= 0; --k){
        if(anc[x][k] != anc[y][k])
            x = anc[x][k], y = anc[y][k];
    }
    return anc[x][0];
}
int main()
{
    memset(head, -1, sizeof head);
    read(n), read(m), read(s);
    rep(i, n-1){
        int p, q; read(p), read(q);
        add(p, q), add(q, p);
    }
    init_log();
    dfs(s, 1);
    lca_init();
    rep(i, m){
        int p, q; read(p), read(q); 
        write(LCA(p, q)), putchar('\n');
    }
    return 0;
}

