#include<iostream>
#include<vector>
using namespace std;


int multiply(int a[][4], int b[][3],int row, int col){
    int cnt = 0;
    int ans[row][col];

    for(int i=0;i<row;i++){
        cnt+=2;
        for(int j=0;j<col;j++){
            cnt+=2;
            ans[i][j] = 0;
            cnt+=4;
            for(int k=0;k<row;k++){
                cnt+=2;
                ans[i][j] += a[i][k]*b[k][j];
                cnt+=14;
            }
        }
    }
    return cnt;
}

int main(){
    int a[3][4] = {{1,2,3,4},
                    {5,6,7,8},
                    {9,10,11,12}};
    int b[4][3] = {{1,2,3},
                    {4,5,6},
                    {7,8,9},
                    {10,11,12}};
    cout << multiply(a,b,3,3);
    return 0;
}