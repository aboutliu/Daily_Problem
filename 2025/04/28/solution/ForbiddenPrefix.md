首先考虑 $X$ 显然如果同时存在 $X_1,X_2$ 且 $X_1$ 是 $X_2$ 的前缀只保留 $X_1$ 即可。

- $T=1$ ，查询是否存在 $X$ 的前缀，是 $\rightarrow continue$ ，否 $\rightarrow$ 插入 $X$ ，查询 $X$ 的所有后缀数量，答案删去，并删除这些后缀的贡献。
- $T=2$ ，查询是否存在 $X$ 的前缀，是 $\rightarrow continue$ ，否 $\rightarrow$ 插入 $X$ ，答案加 $1$ 。


```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

template<class T>
struct Trie {
    int id = 0;
    std::vector<std::map<T, int>> trie {std::map<T, int>()};
    std::vector<int> ed {0}, sz {0};
    Trie() {}
    void init() {
    	ed.assign(1, {});
    	sz.assign(1, {});
    	trie.assign(1, std::map<T, int>());
    }
    void insert(std::string s, int u = 1, int v = 1) { // 插入 s
        int p = 0;
        for (auto it : s) {
            if (!trie[p][it]) {
                trie[p][it] = ++id;
                trie.push_back(std::map<T, int>());
                ed.push_back({});
                sz.push_back({});
            }
            p = trie[p][it];
            sz[p] += u;
        }
        ed[p] += v;
    }
    int exactfind(std::string s) { // s 是否存在
        int p = 0;
        for (auto it : s) {
            if (!trie[p][it]) {
                return 0;
            }
            p = trie[p][it];
        }
        return 1;
    }
    int prefixcount(std::string s) { // s 不为空的前缀数量和
    	int p = 0, res = 0;
    	for (auto it : s) {
    		if (!trie[p][it]) {
    			return res;
    		}
    		p = trie[p][it];
    		res += ed[p];
    	}
    	return res;
    }
    int suffixcount(std::string s) { // s 不为空的后缀数量和
    	int p = 0;
    	for (auto it : s) {
    		if (!trie[p][it]) {
    			return 0;
    		}
    		p = trie[p][it];
    	}
    	return sz[p];
    }
    // 自定义函数
    void clear(std::string s, int v) {
    	int p = 0;
    	for (auto it : s) {
    		p = trie[p][it];
    		sz[p] -= v;
    	}
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int Q;
    std::cin >> Q;

    Trie<char> trie;
    int ans = 0;
    while (Q--) {
    	int T;
    	std::cin >> T;

		std::string s;
		std::cin >> s;

		if (trie.prefixcount(s)) {
			std::cout << ans << "\n";
			continue;
		}
    	if (T & 1) {
    		trie.insert(s, 0, 1);
    		int t = trie.suffixcount(s); 
    		ans -= t;
    		trie.clear(s, t);
    	} else {
    		trie.insert(s, 1, 0);
    		ans++;
    	}
    	std::cout << ans << "\n";
    }

    return 0;
}
```

