很简单，动态开点线段树即可。合并考虑区间长度即可。

对于我来说，我需要重新规范化我的 $Dynamictree$ 和多加练习动态开点线段树的题目。


```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

template <class Info>
struct DynamicTree {
    int tot = 0, now = 1;
    std::vector<Info> dt;
    std::vector<int> rt;
    std::stack<int> sta;
    DynamicTree(int _) : dt(_ + 1 << 6), rt(_ + 1) {}
    int New() {
    	int u = 0;
    	if (!sta.empty()) {
    		u = sta.top();
    		sta.pop();
    	} else {
    		u = ++tot;
    	}
    	return u;
    }
    void pushup(int i) {
    	int ls = dt[i].l, rs = dt[i].r;
    	dt[i] = dt[ls] + dt[rs];
    	dt[i].l = ls;
    	dt[i].r = rs;
    }
    int modify(int p, int l, int r, int v) {
    	if (!p) {
    		p = New();
    	}
    	if (l == r) {
    		dt[p] = dt[p] + Info {0, 0, 1, 0LL, 1LL * v};
    		return p;
    	}
    	int mid = (l + r) / 2;
    	if (v <= mid) {
    		dt[p].l = modify(dt[p].l, l, mid, v);
    	} else {
    		dt[p].r = modify(dt[p].r, mid + 1, r, v);
    	}
    	pushup(p);
    	return p;
    }
    void modify(int u, int v, int l, int r, int x) {
    	rt[u] = modify(rt[v], l, r, x);
    }
};

struct Info {
    int l, r;
    int len;
    i64 sum0, sum1;
};

Info operator + (const Info &u, const Info &v) {
	Info res {};
	res.sum0 = u.sum0 + (u.len & 1 ? v.sum1 : v.sum0);
	res.sum1 = u.sum1 + (u.len & 1 ? v.sum0 : v.sum1);
	res.len = u.len + v.len;
	return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

 	int Q;
 	std::cin >> Q;

 	DynamicTree<Info> dt(Q);
 	i64 Z = 0;
 	for (int i = 0; i < Q; ++i) {
 		int Y;
 		std::cin >> Y;

 		int X = (Y + Z) % 1000000000 + 1;
 		dt.modify(i, std::max(i - 1, 0), 1, 1E9 + 1, X);
 		i64 ans = dt.dt[dt.rt[i]].sum1;
 		Z = ans;
 		std::cout << ans << "\n";
 	}

    return 0;
}
```

