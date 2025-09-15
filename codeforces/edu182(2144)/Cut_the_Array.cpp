#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin>>t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n+1);
        for(int i = 1; i <=n;i++) cin>>a[i];
        vector<int> preSum(n+1, 0);
        for(int i = 1; i <= n; ++i)
            preSum[i]=preSum[i-1]+a[i];
        int f =0;
        for (int l =1;l<n-1&&!f;l++) {
            for (int r=l+1;r<n;r++) {
                int s1 = preSum[l] % 3;
                int s2 = (preSum[r] - preSum[l]) % 3;
                int s3 = (preSum[n] - preSum[r]) % 3;
                if ((s1==s2&&s2==s3)||(s1!=s2&&s2!=s3&&s1!=s3)) {
                    cout<<l<<" "<<r<<'\n';
                    f =1;
                    break;
                }
            }
        }
        if (!f) cout << "0 0" <<'\n';
    }
    return 0;
}