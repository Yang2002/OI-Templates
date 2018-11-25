/*
  Given n prefixes, and ask m strings as queries, how many 
  prefixes given above can be a prefix of the given string
  
  Source: Contest Hunter 1601
*/

#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000009;
int trie[maxn][27], cnt[maxn];
char s[maxn];

int n, m, tot = 1, root = 1, len;

inline void Insert() {
	scanf("%s", s), len = strlen(s);
	int cur = root;
	for(int i = 0; i < len; ++i) {
		int ch = s[i] - 'a';
		if(!trie[cur][ch]) trie[cur][ch] = ++tot;
		cur = trie[cur][ch];
	}
	cnt[cur]++;
}
inline int Find() {
	scanf("%s", s), len = strlen(s);
	int cur = root, ret = 0;
	for(int i = 0; i < len; ++i) {
		int ch = s[i] - 'a';
		if(!trie[cur][ch]) return ret;
		cur = trie[cur][ch];
		ret += cnt[cur];
	}
	return ret;
}

int main() {
	scanf("%d%d", &n, &m);
	while(n--) Insert();
	while(m--) printf("%d\n", Find());
}
