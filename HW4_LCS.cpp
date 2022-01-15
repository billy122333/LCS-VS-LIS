#include <bits/stdc++.h>
#include <windows.h>
#include <stdio.h>
using namespace std;

int  dp[10000][10000]; //補一個0
int pos[10000][10000];

int LCS(string str1, string str2){
    for (int i=0; i<=str1.length(); i++) {
        dp[i][0] = 0;
        pos[i][0] = -1;
    }
    for (int j=0; j<=str2.length(); j++) {
        dp[0][j] = 0;
        pos[0][j] = -1;
    }
    for(int i = 1; i <= str1.length(); i++){
        for(int j = 1; j <= str2.length(); j++){

            if(str1[i-1] == str2[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
                pos[i][j] = 1;
//                cout << i << " " << j << endl;
            }else{
                //left
                if(dp[i-1][j] >= dp[i][j-1]){
                    dp[i][j] = dp[i-1][j];
                    pos[i][j] = 2;
                }else{
                    //right
                    dp[i][j] =  dp[i][j-1];
                    pos[i][j] = 3;
                }
            }
        }
    }
}

void print(string str1, string str2){
    stack<char> ans;
    int str1_len = str1.length();
    int str2_len = str2.length();
    while(true){
        if(str1_len == 0 && str2_len == 0){
            break;
        }
        if(pos[str1_len][str2_len] == -1) break;

        if(pos[str1_len][str2_len] == 1){
            ans.push(str1[str1_len-1]);
            str1_len--;
            str2_len--;
        }else if(pos[str1_len][str2_len] == 2){
            // left
            str1_len--;
        }else{
            //rigth
            str2_len--;
        }

    }
    while(!ans.empty()){
        char a = ans.top();
        ans.pop();
        cout << a;
    }
    cout << endl;
}

int main(){
    string str1 = "" ,str2 = "";
    cin >> str1 >> str2;
    //counter
    LARGE_INTEGER t1, t2, ts;
    QueryPerformanceFrequency(&ts);
    QueryPerformanceCounter(&t1);
    //LCS
    LCS(str1 , str2);
    cout << dp[str1.length()][str2.length()] << endl;
    print(str1, str2);
    //finish counter
    QueryPerformanceCounter(&t2);
    printf("Lasting Time: %lf\n",(t2.QuadPart-t1.QuadPart)/(double)(ts.QuadPart));
    return 0;
 }
