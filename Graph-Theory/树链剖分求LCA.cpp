#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

const int maxn = 500200;
int n, root, q, top[maxn];
int fa[maxn], dep[maxn], sz[maxn], son[maxn];
vector<int> G[maxn];

void dfs1(int v, int fath, int depth) {
    dep[v] = depth, fa[v] = fath, sz[v] = 1;
    for(auto u : G[v]) if(u != fath) {
        dfs1(u, v, depth + 1);
        sz[v] += sz[u];
    }
}

void dfs2(int v, int fath, int tp) {
    int mxsz = 0; top[v] = tp;
    for(auto u : G[v]) if(u != fath)
        if(sz[u] > mxsz) mxsz = sz[u], son[v] = u;
    if(!son[v]) return;
    dfs2(son[v], v, tp);
    for(auto u : G[v]) if(u != fath && u != son[v])
        dfs2(u, v, u);
}

inline int lca(int x, int y) {
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if(dep[x] < dep[y]) return x;
    return y;
}

int main(){
    scanf("%d%d%d", &n, &q, &root);
    for(int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs1(root, -1, 1);
    dfs2(root, -1, root);
    
    while(q--) {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", lca(x, y));
    }
    return 0;
}
