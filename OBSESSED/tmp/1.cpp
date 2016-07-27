#include <cstdio>
static const int MAXN = 100007;
static const int INF = 0x3fffffff;
template <typename T> inline T min(const T a, const T b) {
    return a < b ? a : b;
}

int n, m;

namespace sgt {

static const int MAXN = ::MAXN * 2;
int l[MAXN], r[MAXN], lch[MAXN], rch[MAXN];
int val[MAXN], lmost[MAXN][2], rmost[MAXN][2];
bool tag[MAXN];
int sz = 0;

int build(int _l, int _r)
{
    int idx = sz++;
    l[idx] = _l; r[idx] = _r;
    if (_l == _r) {
        lch[idx] = rch[idx] = -1;
    } else {
        int m = (_l + _r) >> 1;
        lch[idx] = build(_l, m);
        rch[idx] = build(m + 1, _r);
    }
    val[idx] = INF;
    lmost[idx][0] = lmost[idx][1] =
    rmost[idx][0] = rmost[idx][1] = INF;
    tag[idx] = false;
    return idx;
}

inline void push(int idx)
{
}

inline int len(int idx) { return r[idx] - l[idx] + 1; }
inline void update(int idx)
{
    if (lch[idx] == -1) return;
    val[idx] = min(val[lch[idx]], val[rch[idx]]);
    for (int i = 0; i <= 1; ++i) {
        lmost[idx][i] = lmost[lch[idx]][i];
        if (lmost[idx][i] == INF)
            lmost[idx][i] = min(INF, lmost[rch[idx]][i] + len(lch[idx]));
        rmost[idx][i] = rmost[rch[idx]][i];
        if (rmost[idx][i] == INF)
            rmost[idx][i] = min(INF, rmost[lch[idx]][i] + len(rch[idx]));
        val[idx] = min(val[idx], lmost[rch[idx]][i] + rmost[lch[idx]][i] + 1);
    }
}

void put(int pos, int tar, int idx = 0)
{
    push(idx);
    if (l[idx] == r[idx]) {
        lmost[idx][tar] = rmost[idx][tar] = 0;
        lmost[idx][tar ^ 1] = rmost[idx][tar ^ 1] = INF;
        return;
    }
    if (pos <= r[lch[idx]]) put(pos, tar, lch[idx]);
    else put(pos, tar, rch[idx]);
    update(idx);
}

int query(int ql, int qr, int idx = 0)
{
    push(idx);
    if (l[idx] >= ql && r[idx] <= qr) return val[idx];
    int ans = INF;
    if (r[lch[idx]] >= ql) ans = min(ans, query(ql, qr, lch[idx]));
    if (l[rch[idx]] <= qr) ans = min(ans, query(ql, qr, rch[idx]));
    if (r[lch[idx]] >= ql && l[rch[idx]] <= qr)
        for (int i = 0; i <= 1; ++i)
            if (rmost[lch[idx]][i] <= r[lch[idx]] - ql &&
                lmost[rch[idx]][i] <= qr - l[rch[idx]])
                ans = min(ans, rmost[lch[idx]][i] + lmost[rch[idx]][i] + 1);
    //printf("Query #%d = %d\n", idx, ans);
    return ans;
}

void print()
{
    for (int i = 0; i < sz; ++i)
        printf("#%d | [%d, %d] Lch=%d Rch=%d | Lmost=%d %d Rmost=%d %d Val=%d\n",
            i, l[i], r[i], lch[i], rch[i],
            lmost[i][0], lmost[i][1], rmost[i][0], rmost[i][1], val[i]);
}

}

inline void don(int x) { sgt::put(x, 0); }
inline void katsu(int x) { sgt::put(x, 1); }
inline void invert(int l, int r) {
}
inline int inspect(int l, int r) {
    //sgt::print();
    int ret = sgt::query(l, r);
    return (ret == INF ? -1 : ret);
}

int main()
{
    scanf("%d%d", &n, &m);
    sgt::build(1, n);

    char op[16];
    int arg1, arg2;
    for (int i = 0; i < m; ++i) {
        scanf("%s%d", op, &arg1);
        if (op[0] == 'D') don(arg1);
        else if (op[0] == 'K') katsu(arg1);
        else {
            scanf("%d", &arg2);
            if (op[2] == 'v') invert(arg1, arg2);
            else printf("%d\n", inspect(arg1, arg2));
        }
    }

    return 0;
}

