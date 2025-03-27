很经典的树形 $dp$ ，设 $dp_u$ 表示以节点 $u$ 为根的树的答案， $sum_u$ 表示其子树的答案和。

转移很显然就是首先是 $\sum dp_v$ ，然后就是以 $u$ 为 $lca$ 的路径上的 $\sum dp_v$ ，这个是难点。

<img src="https://github.com/aboutliu/Daily_Problem/blob/main/pictures/2025-03-27.png" alt="image-20250327224130566" style="zoom:50%;" />

假设 $1 \rightarrow 5$ ，就是 $sum_1 - dp_1 + sum_2 - dp_5 + sum_5$ 。使用树链剖分即可。

```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

template <class T>
struct Fenwick {
    int N;
    std::vector<T> f;
    Fenwick() {}
    Fenwick(int _) {
        init(_);
    }
    void init(int _) {
        N = _;
        f.assign(_ + 1, T());
    }
    void add(int x, T v) {
        for (int i = x; i <= N; i += (i bitand -i)) {
            f[i] += v;
        }
    }
    T query(int x) {
        if (x > N or x <= 0) {
            return T(0);
        }
        T res = 0;
        for (int i = x; i; i -= (i bitand -i)) {
            res += f[i];
        }
        return res;
    }
    T rangesum(int l, int r) {
        if (l > r) {
            return T(0);
        }
        return query(r) - query(l - 1);
    }
    // int select(const T &k) {
    //     int x = 0;
    //     T cur{};
    //     for (int i = 1 << std::bit_width(1U * N) - 1; i; i /= 2) {
    //         if (x + i <= N && cur + f[x + i] <= k) {
    //             x += i;
    //             cur = cur + f[x];
    //         }
    //     }
    //     return x;
    // }
};

Fenwick<i64> fen1, fen2;

std::vector<std::vector<std::array<int, 2>>> e;

struct HeavyLightDecomposition {
    int n, DFN = 0, rt = 1;
    std::vector<int> L, R, dep, fa, top, sz, son, re;
    HeavyLightDecomposition() {}
    HeavyLightDecomposition(int _, int RT = 1) {
        init(_, RT);
    }
    void init(int _, int RT) {
        this->n = _;
        this->rt = RT;
        L.resize(n + 1);
        R.resize(n + 1);
        fa.resize(n + 1);
        re.resize(n + 1);
        sz.resize(n + 1);
        son.resize(n + 1);
        top.resize(n + 1);
        dep.resize(n + 1);
        dfs1(rt, 0);
        dfs2(rt, rt);
    }
    void dfs1(int u, int F) { // 重链剖分
        dep[u] = dep[F] + 1;
        sz[u] = 1;
        fa[u] = F;
        son[u] = -1;
        for (auto [v, w] : e[u]) {
            if (v != F) {
                dfs1(v, u);
                sz[u] += sz[v];
                if (son[u] == -1 || sz[v] > sz[son[u]]) {
                    son[u] = v;
                }
            }
        }
    }
    void dfs2(int u, int tp) { // top 为该重链的深度最小节点， dfn 顺序要按照重链遍历顺序
        L[u] = ++DFN;
        re[DFN] = u;
        top[u] = tp;
        if (son[u] == -1) {
            R[u] = DFN;
            return;
        }

        dfs2(son[u], tp);
        for (auto [v, w] : e[u]) {
            if (v != son[u] && v != fa[u]) {
                dfs2(v, v);
            }
        }
        R[u] = DFN;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = fa[top[u]];
            } else {
                v = fa[top[v]];
            }
        }

        return dep[u] < dep[v] ? u : v;
    }
    int Kth_ancestor(int u, int k) {
        int fu = top[u];
        while (dep[u] - dep[fu] < k && u != rt) {
            k -= dep[u] - dep[fu] + 1;
            u = fa[fu];
            fu = top[u];
        }

        return re[L[u] - k];
    }
    //自定义函数
    i64 rangesum1(int u, int v, int z = 0) {
        int fu = top[u], fv = top[v];
        i64 res = 0;
        while (fu != fv) {
            if (dep[fu] >= dep[fv]) {
                // lseg.modify(1, L[fu], L[u], z);
                res += fen1.rangesum(L[fu], L[u]);
                u = fa[fu];
            } else {
                // lseg.modify(1, L[fv], L[v], z);
                res += fen1.rangesum(L[fv], L[v]);
                v = fa[fv];
            }
            fu = top[u];
            fv = top[v];
        }
        if (dep[u] > dep[v]) {
            // lseg.modify(1, L[v], L[u], z);
            res += fen1.rangesum(L[v], L[u]);
        } else {
            // lseg.modify(1, L[u], L[v], z);
            res += fen1.rangesum(L[u], L[v]);
        }
        return res;
    }
    i64 rangesum2(int u, int v, int z = 0) {
        int fu = top[u], fv = top[v];
        i64 res = 0;
        while (fu != fv) {
            if (dep[fu] >= dep[fv]) {
                // lseg.modify(2, L[fu], L[u], z);
                res += fen2.rangesum(L[fu], L[u]);
                u = fa[fu];
            } else {
                // lseg.modify(2, L[fv], L[v], z);
                res += fen2.rangesum(L[fv], L[v]);
                v = fa[fv];
            }
            fu = top[u];
            fv = top[v];
        }
        if (dep[u] > dep[v]) {
            // lseg.modify(2, L[v], L[u], z);
            res += fen2.rangesum(L[v], L[u]);
        } else {
            // lseg.modify(2, L[u], L[v], z);
            res += fen2.rangesum(L[u], L[v]);
        }
        return res;
    }
};

void solve() {
    int n, m;
    std::cin >> n >> m;

    e.assign(n + 1, {});
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        e[u].emplace_back(std::array {v, 0});
        e[v].emplace_back(std::array {u, 0});
    }

    fen1.init(n);
    fen2.init(n);
    HeavyLightDecomposition hld(n);

    std::vector<std::vector<std::array<int, 3>>> b(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;

        int lca = hld.lca(u, v);
        b[lca].emplace_back(std::array {u, v, w});
    }

    std::vector<i64> dp(n + 1), sum(n + 1);

    auto dfs = [&](auto &&self, int u, int F) -> void {
        for (auto [v, w] : e[u]) {
            if (v != F) {
                self(self, v, u);
                sum[u] += dp[v];
            }
        }
        dp[u] = sum[u];
        fen2.add(hld.L[u], sum[u]);

        auto calc = [&](int x) -> i64 {
            i64 tsum = hld.rangesum2(u, x);
            i64 tdp = hld.rangesum1(u, x);
            int tv = hld.Kth_ancestor(x, hld.dep[x] - 1 - hld.dep[u]);
            i64 res = tsum - tdp;
            return res;
        };

        for (auto [x, y, z] : b[u]) {
            i64 a = calc(x), b = calc(y);
            dp[u] = std::max(dp[u], a + b + z - sum[u]);
        }
        fen1.add(hld.L[u], dp[u]);
    };

    dfs(dfs, 1, 0);
    i64 ans = dp[1];
    std::cout << ans << "\n";
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

