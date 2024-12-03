#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = double;
using ld = long double;
using pii = pair<int, int>;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) (int)(x).size()
#define dbg(x) cout << #x << " = " << x << 

#define dbg2(x) cout << #x << " = " << x << endl

template<typename T> void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
    while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
    x *= f;
}

template<typename T, typename... Args> void read(T &x, Args&... args) {
    read(x); read(args...);
}

template<typename T> void write(T x) {
    static int buf[42];
    int p = 0;
    if (x < 0) putchar('-'), x = -x;
    if (x == 0) return putchar('0'), void();
    while(x) {
        buf[p++] = x % 10;
        x /= 10;
    }
    for (int i = p - 1; i >= 0; i--) putchar(buf[i] + '0');
}

struct Node {
    int pos, id, type, l, r;
    Node(int pos=-1, int id=-1, int type=-1, int l=-1, int r=-1): 
        pos(pos), id(id), type(type), l(l), r(r) {}
    bool operator < (const Node& rhs) const {
        if (pos < rhs.pos) return true;
        else if (pos > rhs.pos) return false;
        else if (pos == rhs.pos) {
            if (type < rhs.type) return true;
            else if (type > rhs.type) return false;
            else if (type == rhs.type) {
                if (type == 0) return r < rhs.r;
                else if (type == 1) return l > rhs.l;
                else assert(0);
            }
        }
        return true;
    }
};

void solve() {
    int n; read(n);
    vector<pii> a(n);
    for (int i = 0; i < n; i++) read(a[i].fi, a[i].se);

    auto gao = [&](vector<pii>& a) {
        vector<int> ans(SZ(a));
        vector<Node> b;
        for (int i = 0; i < n; i++) {
            b.emplace_back(a[i].fi, i, 0, a[i].fi, a[i].se);
            b.emplace_back(a[i].se, i, 1, a[i].fi, a[i].se);
        }
        sort(b.begin(), b.end());
        multiset<int> S;
        for (int i = 0; i < SZ(b); i++) {
            if (b[i].type == 0) {
                // L
                S.insert(b[i].pos);
            }
            else if (b[i].type == 1) {
                // R
                int R = i;
                while (R < SZ(b) && b[R].l == b[i].l && b[R].r == b[i].r) R++;
                for (int j = i; j < R; j++) {
                    auto it = S.find(a[b[i].id].fi);
                    S.erase(it);
                }

                // multiple
                if (R > i + 1) {
                    for (int j = i; j < R; j++) {
                        ans[b[i].id] = 0;
                    }
                    i = R - 1;
                    continue;
                }
                
                // only one
                auto it = S.upper_bound(a[b[i].id].fi);
                int val;
                if (it == S.begin()) {
                    val = 0;
                }
                else {
                    it--;
                    val = a[b[i].id].fi - (*it);
                }
                for (int j = i; j < R; j++) {
                    ans[b[i].id] = val;
                }
                i = R - 1;
            }
            else assert(0);
        }
        return ans;
    };

    vector<int> ans1 = gao(a);
    for (int i = 0; i < n; i++) {
        a[i].fi = -a[i].fi; a[i].se = -a[i].se;
        swap(a[i].fi, a[i].se);
    }
    vector<int> ans2 = gao(a);
    for (int i = 0; i < n; i++) {
        write(ans1[i] + ans2[i]); putchar(10);
    }
}


int main() {
#ifdef LOCAL
    freopen("test.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T = 1;
    read(T);
    while (T--) solve();
    return 0;
}