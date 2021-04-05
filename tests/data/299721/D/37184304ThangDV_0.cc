#include<iostream>
#include<vector>
using namespace std;
int n,m,k;
int main()
{
    int result=0;
    cin>>n>>m>>k;
       vector<int>s;
    int c[n][m];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {


            cin>>c[n][m];
            s.push_back(c[n][m]);
    }}
    int a;
    int min;
//    for(int i=0;i<s.size();i++)
//    {
//        cout << s[i];
//    }
    for(int j=0;j<m*k;j++){
            min=999999999;
     for(int i=0;i<s.size();i++)
     {
       if(s[i]<min)
       {min=s[i];
        a=i;
     }

     //cout<<min<<" ";

    // s.erase(s.begin()+a);
     }
        s[a]=9999;
         result+=min;
     //cout<<min<<endl;




}
   cout<<result<< endl;
}

