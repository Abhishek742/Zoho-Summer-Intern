#include<iostream>
using namespace std;

int sum = 0;
//dfs to find groups and group sizes.
void helper(int n,int m,int i,int j,int **arr,int **visited){
    if(i >= n || j >= m || i < 0 || j < 0 || arr[i][j] == 0 || visited[i][j] == 1){
        return;
    }
    sum += arr[i][j];
    visited[i][j] = 1;
    helper(n,m,i-1,j,arr,visited);
    helper(n,m,i,j+1,arr,visited);
    helper(n,m,i+1,j,arr,visited);
    helper(n,m,i,j-1,arr,visited);
    return;
}

int main(){
    int n,m;
    cout<<"Enter n and m: ";
    cin>>n>>m;
    int **arr = new int*[n];
    int **visited = new int*[n];
    for(int i = 0;i<n;i++){
        arr[i] = new int(m);
        visited[i] = new int(m);
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            cin>>arr[i][j];
            visited[i][j] = 0;
        }
    }

    int *groups = new int[n*m];
    int count = 0;
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            if(visited[i][j]==0 && arr[i][j] != 0){
                helper(n,m,i,j,arr,visited);
                if(sum > 0){
                    groups[count] = sum;
                    count++;
                    sum = 0;
                }
            }
        }
    }

    //print the groups and leader group.
    int leaderGrp = INT_MIN;
    cout<<"Groups : ";
    for(int i = 0;i<count;i++){
        cout<<groups[i]<<"  ";
        leaderGrp = max(groups[i],leaderGrp);
    }
    cout<<"\nLeader Group size - "<<leaderGrp<<endl;
    
    //delete the allocated memory from the heap.
    for(int i = 0;i<n;i++){
        delete[] visited[i];
        delete[] arr[i];
    }
    delete[] groups;
    delete[] visited;
    delete[] arr;
}