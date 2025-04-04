赛时大胆猜测移动回 $1 - n$ 是最少的操作次数，然后会发现这样移动的话，某些数会构成一个连通块，对于一个连通块的数 $x \leftarrow 0$ 此时消耗的次数是连通块的大小， 所以用并查集搞一下就行。


```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

template <class T>
struct DSU {
    int n;
    std::vector<T> f, sz, dep;
    DSU(int _) {
        init(_);
    }
    void init(int _) {
        n = _;
        f.assign(n + 1, T{});
        sz.assign(n + 1, 1);
        dep.assign(n + 1, {});
        std::iota(f.begin(), f.end(), 0);
    }
    int find(int x) {
        while (x not_eq f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    int Find(int x) {
        if (x not_eq f[x]) {
            int t = Find(f[x]);
            dep[x] += dep[f[x]];
            f[x] = t;
        }
        return f[x];
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }

    bool Same(int u, int v) {
        return Find(u) == Find(v);
    }
    void merge(int u, int v) {
        int fu = Find(u), fv = Find(v);
        if (fu == fv) {
            return;
        }
        f[fv] = fu;
        sz[fu] += sz[fv];
    }
    void Merge(int u, int v) {
        int fu = Find(u), fv = Find(v);
        if (fu == fv) {
            return;
        }
        f[fv] = fu;
        dep[v] = dep[u] + 1; 
    }
    int size(int u) {
        return sz[find(u)];
    }
    int Size(int u) {
        return sz[Find(u)];
    }
};

void solve() {
	int n;
	std::cin >> n;

	std::vector<int> p(n), d(n), pos(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> p[i];
		p[i]--;
		pos[p[i]] = i;
	}
	for (int i = 0; i < n; ++i) {
		std::cin >> d[i];
		d[i]--;
	}

	DSU<int> dsu(n);

	std::vector<int> vis(n);
	vis = p;
	for (int i = 0; i < n; ++i) {
		if (vis[i] == i) {
			continue;
		}
		int now = i;
		while (now != vis[now]) {
			// std::cerr << vis[now] << " <-> ";
			int tnow = vis[vis[now]];
			dsu.merge(vis[now] + 1, vis[vis[now]] + 1);
			std::swap(vis[now], vis[vis[now]]);
			// std::cerr << vis[now] << "\n";
		}
	}

	int ans = 0;
	std::vector<int> tvis(n);
	for (int i = 0; i < n; ++i) {
		int f = dsu.find(p[d[i]] + 1);
		if (!tvis[f - 1]) {
			ans += dsu.size(p[d[i]] + 1);
			tvis[f - 1] = 1;
		}
		std::cout << ans << " \n"[i == n - 1];
	}
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
```
