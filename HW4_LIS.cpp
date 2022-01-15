#include <bits/stdc++.h>
#include <vector>
#include <windows.h>
using namespace std;

vector<int> lis[128];

vector<int> v;

stack<int> a;
int pos[100000];
int tran_str[100000];
int pos_length = 0;

int bs(int l , int r , int t ){ //binary search 
    int m ;
    while(r >= l ){
        m = (l+r) >> 1 ;
        if( v[m] <= t) l = m + 1 ;
        else if (t < v[m]) r = m - 1;
    }
    return l ;
}

void print(string str1, string str2, int length){
    //從後面往前找，找任意一個答案的位置
    for(int i = pos_length-1 ; i >= 0; i-- ){
        if(pos[i] == length){
            //存答案位置
            a.push(i);
            length--;
        }
    }
    while(!a.empty()){
        int tmp = a.top();
        a.pop();
        cout << str2[tran_str[tmp]];
    }
    cout << endl;
}

int LIS(string str1, string str2){  
    for(int i = 0; i < str1.length(); i++){
        int tmp = (int)str1[i];
        lis[tmp].push_back(i);
    }  
    //a 0 2 b 3 4 c 5 6  
    // 6 3 2 4 1 6 3 2 5
    // 先塞入一個冗餘數字，免得稍後 v.back() 出錯。
    v.clear();
    v.push_back(-1);
    
    int i = 0;
    int s = 0;
   for(int i = 0; i < str2.length(); i++){
        for(int j = lis[str2[i]].size() - 1; j >= 0; j--){
            int n = lis[str2[i]][j] ;

            if( n > v.back()){
                v.push_back(n);
                pos[s] = v.size() - 1;
                tran_str[s++] = i;
                pos_length++;
            }else{
                //reference : https://bear-1111.medium.com/longest-increasing-subsequence-lis-dp-1211fc7933f6
                //找到比n大的位置取代
                //lowerbound只能用來找最常長度
                //真正回朔要用position找數字
                //lowerbound用來存前面有幾個比她小的數字(涵蓋本身的最大子字串)
                *lower_bound(v.begin(), v.end(),n) = n ;
              //  int *t = lower_bound(v.begin(), v.end(),n) ;
                int n_pos = bs(1, v.size()-1, n);
                pos[s] = n_pos - 1 ;
                tran_str[s++] = i;
                pos_length++;
            }        
        }    
    }
    return v.size()-1;
}

int main(){
    string str1 = "" ,str2 = "";
    cin >> str1 >> str2;
    LARGE_INTEGER t1, t2, ts;
    QueryPerformanceFrequency(&ts);
    QueryPerformanceCounter(&t1);
    int length = LIS(str1,str2);
    cout << length <<endl;
    print(str1,str2,length);
    QueryPerformanceCounter(&t2);
    printf("Lasting Time: %lf\n",(t2.QuadPart-t1.QuadPart)/(double)(ts.QuadPart));

    
}