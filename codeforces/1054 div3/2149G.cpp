#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 100;
int cao[N];
bool flag = 0;
struct edge{
    int lson , rson , sum;
};

struct kcjh{
    int tot = 0;
    vector<int> T;
    vector<edge> tree;
    kcjh(int n) {
        int laoge = log2(n);
        T.resize(n + 1) , tree.resize((n + 1) * 40);
    }

    int Build(int l,int r){
        int root = ++tot;
        if(l < r){
            int mid = l + r >> 1;
            tree[root].lson = Build(l , mid);
            tree[root].rson = Build(mid + 1 , r);
        }
        return root;
    }

    int update(int pre , int l , int r ,int x){
        int root = ++ tot;
        tree[root].lson = tree[pre].lson;
        tree[root].rson = tree[pre].rson;
        tree[root].sum = tree[pre].sum + 1;
        if(l < r){
        int mid = l + r >> 1;
            if(x <= mid) tree[root].lson = update(tree[pre].lson , l , mid , x);
                else tree[root].rson = update(tree[pre].rson , mid + 1 , r , x);
        }
        return root;
    }

    void query(int u,int v,int l,int r,int k){
        if(l == r) {
            flag = 1;
            cout << cao[l] << ' ';
            return ;
        }
        int x = tree[tree[v].lson].sum - tree[tree[u].lson].sum;
        int y = tree[tree[v].rson].sum - tree[tree[u].rson].sum;
        int mid = l + r >> 1;
        if(x > k) query(tree[u].lson , tree[v].lson , l , mid , k);
        if(y > k) query(tree[u].rson , tree[v].rson , mid + 1 , r , k);
    }

};

void solve() {
    int n , q;
    cin >> n >> q;
    vector<int> a(n + 1) , b(n + 1);
    for(int i=1;i<=n;i++) {
        cin >> a[i]; b[i] = a[i];
    }
    sort(b.begin() + 1 , b.begin() + 1 + n);
    int len = unique(b.begin() + 1 , b.begin() + 1 + n) - b.begin() - 1;
    for(int i = 1;i <= len;i ++) 
        cao[i] = b[i];

    kcjh kj(n);
    kj.T[0] = kj.Build(1 , len);
    for(int i=1;i<=n;i++){
        a[i] = lower_bound(b.begin() + 1 , b.begin() + 1 + len , a[i]) - b.begin();
        kj.T[i] = kj.update(kj.T[i - 1] , 1 , len , a[i]);
    }

    // cout << "fk!\n";

    while(q --){
        int x , y;
        cin >> x >> y;
        flag = 0;
        kj.query(kj.T[x - 1] , kj.T[y] , 1 , len , (y - x + 1) / 3);
        if(flag)
            cout << "\n";
        else cout << -1 << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0) , cout.tie(0);

    int t; cin >> t; while(t --) solve();
    return 0;
}