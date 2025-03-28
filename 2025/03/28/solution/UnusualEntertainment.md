经典二维数点。

用主席树，按照 $dfs$ 序继承，单个更新按照节点 $u$ 在 $p$ 的索引更新。

查询直接在以 $x$ 为根的树上前缀和即可。

```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

template <class Info>
struct PersistentTree {
    int n, tot = 0;
    std::vector<int> rt;
    std::vector<Info> per;
    PersistentTree() {}
    PersistentTree(int _, int m) : n(m), rt(_ + 2), per(_ << 5) {} // _ 是 rt 长度，n 是值域大小
    PersistentTree(int _, std::vector<int> a) : PersistentTree(_, a.size()) {
        auto build = [&](auto &&self, int &p, int l, int r) -> void {
            p = ++tot;
            if (l == r) {
                per[p].apply(a[l - 1]);
                return;
            }
            int mid = (l + r) / 2;
            self(self, per[p].l, l, mid);
            self(self, per[p].r, mid + 1, r);
            pushup(p);
        };

        build(build, rt[1], 1, n);
    }
    void init(int _, int m) {
        n = m;
        rt.resize(_ + 1);
        per.resize(_ << 5);
    }
    void pushup(int i) {
        int l = per[i].l, r = per[i].r;
        per[i] = per[l] + per[r];
        per[i].l = l;
        per[i].r = r;
    }
    int modify(int p, int l, int r, int ind, int v) {
        per[++tot] = per[p];
        p = tot;
        if (l == r) {
            per[p].apply(v);
            return p;
        }
        int mid = (l + r) / 2;
        if (ind <= mid) {
            per[p].l = modify(per[p].l, l, mid, ind, v);
        } else {
            per[p].r = modify(per[p].r, mid + 1, r, ind, v);
        }
        pushup(p);
        return p;
    }
    void modify(int u, int v, int p, int s) {
        rt[u] = modify(rt[v], 1, n, p, s);
    }
    Info rangeInfo(int u, int v, int l, int r, int x, int y) {
        if (x > r || y < l || x > y) {
            return Info().inf();
        }
        if (x <= l && r <= y) {
            return per[v] - per[u];
        }
        int mid = (l + r) / 2;
        return rangeInfo(per[u].l, per[v].l, l, mid, x, y) + rangeInfo(per[u].r, per[v].r, mid + 1, r, x, y);
    }
    Info rangeInfo(int u, int v, int l, int r) {
        return rangeInfo(rt[u], rt[v], 1, n, l, r);
    }
    Info rangeInfo(int v, int l, int r) {
        return rangeInfo(rt[0], rt[v], 1, n, l, r);
    }
    template <class F>
    int findFirst(int u, int v, int l, int r, int x, int y, F &&pred, Info d) {
        if (x > r || y < l || x > y || !pred(per[v] - per[u] + d)) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int mid = (l + r) / 2;
        int res = findFirst(per[u].l, per[v].l, l, mid, x, y, pred, d);
        if (res == -1) {
            Info ls = per[per[v].l] - per[per[u].l];
            res = findFirst(per[u].r, per[v].r, mid + 1, r, x, y, pred, d + ls);
        }
        return res;
    }
    template <class F>
    int findFirst(int u, int v, int x, int y, F &&pred) {
        return findFirst(u, v, 1, n, x, y, pred, Info());
    }
    template <class F>
    int findFirst(int v, int x, int y, F &&pred) {
        return findFirst(rt[0], rt[v], 1, n, x, y, pred, Info());
    }
    template <class F>
    int findLast(int u, int v, int l, int r, int x, int y, F &&pred, Info d) {
        if (x > r || y < l || x > y || !pred(per[v] - per[u] + d)) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int mid = (l + r) / 2;
        int res = findLast(per[u].r, per[v].r, mid + 1, r, pred, d);
        if (res == -1) {
            Info rs = per[per[v].r] - per[per[u].r];
            return findLast(per[u].l, per[v].l, l, mid, x, y, pred, d + rs);
        }
        return res;
    }
    template <class F>
    int findLast(int u, int v, int x, int y, F &&pred) {
        return findLast(u, v, 1, n, x, y, pred, Info());
    }
    template <class F>
    int findLast(int v, int x, int y, F &&pred) {
        return findLast(rt[v], 1, n, x, y, pred, Info());
    }
};

struct Info {
    int l, r;
    int sum;
    void apply(int x) {
	    sum += x;
    }
    Info inf() { // 阻断值
        Info res {0, 0, 0};
        return res;
    }
};

Info operator + (const Info &u, const Info &v) {
    Info res {};
    res.sum = u.sum + v.sum;
    return res;
}

Info operator - (const Info &u, const Info &v) {
    Info res {};
    res.sum = u.sum - v.sum;
    return res;
}

void solve() {
	int n, q;
	std::cin >> n >> q;

	std::vector<std::vector<int>> e(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}

	std::vector<int> pos(n + 1);
	for (int i = 1; i <= n; ++i) {
		int p;
		std::cin >> p;
		pos[p] = i;
	}

	PersistentTree<Info> per(n, n);
	int DFN = 0;
	std::vector<int> L(n + 1), R(n + 1), re(n + 1);

	auto dfs = [&](auto &&self, int u, int F) -> void {
		L[u] = ++DFN;
		re[DFN] = u;
		for (auto v : e[u]) {
			if (v != F) {
				self(self, v, u);
			}
		}
		R[u] = DFN;
	};

	dfs(dfs, 1, 0);

	for (int i = 1; i <= n; ++i) {
		int u = re[i];
		per.modify(i, i - 1, pos[u], 1);
	}

	for (int i = 0; i < q; ++i) {
		int l, r, x;
		std::cin >> l >> r >> x;

		auto ans = per.rangeInfo(L[x] - 1, R[x], l, r).sum > 0 ? "YES" : "NO";
		std::cout << ans << "\n";
	}
	std::cout << "\n";
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

