#include<iostream>
#include<vector>
#include<chrono>
using namespace std;
using namespace std::chrono;
int max(int a[], int n){
    int max_ = a[0];
    for(int i=1;i<n;i++){
        if(max_ < a[i]) max_ = a[i];
    }
    return max_;
}

int max_counter(int a[], int n){
    int cnt = 0;
    int max_ = a[0];
    cnt += 2;
    for(int i=1;i<n;i++){
        cnt++;
        if(max_ < a[i]){
            max_ = a[i];
            cnt += 2;
        }
        cnt+=2;
    }
    return max_;

}
int main(){
#ifndef ABC
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    int t; cin >> t;
    while(t--){
        int n;
        cin>>n;
        int a[n] = {0};
        for(int i=0;i<n;i++){
            cin >> a[i];
        }
        auto start = high_resolution_clock::now();
        int k = max(a,n);
        auto end = high_resolution_clock::now();
        auto t = duration_cast<nanoseconds>(end-start);
        cout << "max: " << k << "  n: " << n <<  "  time: " << t.count() << "\n";
    }
    return 0;
}