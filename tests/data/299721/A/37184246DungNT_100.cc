#include <iostream>


using namespace std;



int main()
{
    int N,M,a[100007],countt=0;
     cin >> N >> M;
     for (int i=0;i<N;i++){
        cin >> a[i];
     }
      for (int i=0;i<N;i++){
            int k = (i+1),weight = 0;
        for (int j = i;j<k;j++){
        
            if (weight+a[j]<=M){
                weight+=a[j];
                countt++;
                 k++;
            }
            if (j==N-1) break;
        }
     }
     cout<<countt;


    return 0;
}
