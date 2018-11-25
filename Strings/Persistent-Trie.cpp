#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= (n); ++i)
using namespace std;
typedef long long ll;

/*
all lowercase English letters
q
1 str: Insert
2	 : Undo
3 str: Find
*/

const int maxn = 50030;
int trie[maxn][30], Q, roots[maxn], Root = 1, tot = 1, len, rcnt = 1, End[maxn];
char s[maxn];
inline void Insert() {
	scanf("%s", s), len = strlen(s);
	int rt = ++tot, p = Root, q = rt; roots[++rcnt] = rt;
	for(int i = 0; i < len;  ++i) {
		if(p) for(int c = 0; c < 26; ++c) trie[q][c] = trie[p][c];
		int New = ++tot, ch = s[i] - 'a';
		trie[q][ch] = New;
		p = trie[p][ch], q = trie[q][ch];
		if(End[p]) End[q] = true;
	}
	Root = rt, End[q] = true;
}

inline void Undo() { Root = roots[--rcnt]; }
inline bool Find() {
	scanf("%s", s), len = strlen(s);
	int q = Root;
	for(int i = 0; i < len; ++i) {
		int ch = s[i] - 'a';	
		if(!trie[q][ch]) return false;
		q = trie[q][ch];
	}
	return End[q];
}

int main() {
	scanf("%d", &Q);
	while(Q--) {
		int opt; scanf("%d", &opt);
		switch(opt) {
			case 1: Insert(); break;
			case 2: Undo(); break;
			case 3: puts(Find() ? "Yes" : "No");
		}
	}
	return 0;
}
