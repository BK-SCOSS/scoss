    #include<iostream>
    #include<bits/stdc++.h>
    using namespace std;
    int n, m, k;
    int f;
    int min_f;
    int c[80][80];
    bool appear[80];
    int x[80];
    void input(){
        cin >> n >> m >> k;
        for(int i = 1;i<= m;i++){
            appear[i] = false;
            for(int j = 1;j<=n;j++){
                cin >> c[i][j];
            }
        }
    }
    void solution(){
        int count = 1;
        int t = 1;
        for(int i =1;i<=n;i++){
            if(count <= k){
                f = f+c[t][x[i]];
                count++;
            }
            else{
                t++;
                count = 1;
            }
        }
        if(f<min_f){
            min_f = f;
        }
    }
    void TRY(int t){
        int v;
        for(v = 1;v<=n;v++){
            if(!appear[v]){
                x[t] = v;
                appear[v] = true;
                if(t==n){
                    solution();
                }
                else{
                    TRY(t+1);
                }
                appear[v] = false;
            }
        }
    }
    void solve(){
        appear[0] = false;
        min_f = 10000000;
        f = 0;
        TRY(1);
        cout << min_f;
    }
    int main(){
        input();
        solve();
        return 0;
    }