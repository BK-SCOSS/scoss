#include <iostream>

using namespace std;
int n;
int a[15][15];
int m,count=0;
int Bool[16] = { 0 };//Đánh dấu chưa có phần tử nào sử dụng hết
unsigned int A[16];//Lưu hoán vị vào mảng A
int dem=0, soHoanvi;

int giaiThua(int n)
{
    if (n == 1)
        return 1;
    return n * giaiThua(n - 1);
}
         unsigned int sum= 0;
 
    
    void xuat() {
     
        sum = 0;
        
    for (int i = 1; i <= n; i++){
        
        if (i<n){
              sum+=a[A[i]-1][A[i+1]-1];
              
        }
        else {
                          sum+=a[A[n]-1][0];
 
 
        }
 
    
    }
    if (sum<=m){
        count++;
    }
    
}
 
 
void Try(int k) {
    //cout<<dem<<endl;
   
    for (int i = 1; i <= n; i++) {
        //Kiểm tra nếu phần tử chưa được chọn thì sẽ đánh dấu
         if (dem <= soHoanvi)
        if (!Bool[i]) {
            
            A[k] = i; // Lưu một phần tử vào hoán vị
          
            Bool[i] = 1;//Đánh dấu đã dùng
            if (k == n)//Kiểm tra nếu đã chứa một hoán vị thì xuất
            {
                 if (dem <= soHoanvi){
                xuat();
                dem++;
                 }
            }
            else{
                if (dem <= soHoanvi)
                                Try(k + 1);

            }
            Bool[i] = 0;
        }
    }
}
int main()
{
    A[1] = -1;
   cin >> n >> m;
       soHoanvi = giaiThua(n)/n;

   for (int i=0;i<n;i++){
       for (int j=0;j<n;j++){
        cin>>a[i][j];
       }
           // cout << endl;
   
  }
   Try(1);
   std::cout << count << std::endl;
    
    
    
    
    
}