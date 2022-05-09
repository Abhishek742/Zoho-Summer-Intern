#include<iostream>
using namespace std;

int sum = 0,grp = 1;
//dfs to find groups and group sizes.
void dfs(int n,int m,int i,int j,int **arr,int **visited){
    if(i >= n || j >= m || i < 0 || j < 0 || arr[i][j] == 0 || visited[i][j] != 0){
        return;
    }
    sum += arr[i][j];
    //set visited[i][j] to the grp arr[i][j] it belongs to.(to identify the grps)
    visited[i][j] = grp;
    dfs(n,m,i-1,j,arr,visited);
    dfs(n,m,i,j+1,arr,visited);
    dfs(n,m,i+1,j,arr,visited);
    dfs(n,m,i,j-1,arr,visited);
    return;
}


//dfs to find the path with lesser distance from the leaderGrp to others
void minPath(int i,int j, int n,int m,int** visited,int* grpDist,int leaderGrp,int c){
    if(i<0 || i>=n || j<0 || j>=m || visited[i][j] == leaderGrp || visited[i][j] == -1 || grpDist[visited[i][j] - 1] == 1) return;
    if(visited[i][j] != 0){
        grpDist[visited[i][j] - 1] = min(grpDist[visited[i][j] - 1],c);
        return;
    }
    c++;
    visited[i][j] = -1;
    minPath(i-1,j,n,m,visited,grpDist,leaderGrp,c);
    minPath(i,j+1,n,m,visited,grpDist,leaderGrp,c);
    minPath(i+1,j,n,m,visited,grpDist,leaderGrp,c);
    minPath(i,j-1,n,m,visited,grpDist,leaderGrp,c);
    visited[i][j] = 0;
}

int main(){
    int n,m;
    cout<<"Enter n and m: ";
    cin>>n>>m;

    //initialise the 2d matrix arr and visited dynamically
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

    int *groupSum = new int[n*m];   //groupSum stores the sum of values in each grp
    int leaderGrpSum = INT_MIN;
    int leaderGrp = 0;

    //dfs to identify the groups and to find the one with max sum
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            if(visited[i][j]==0 && arr[i][j] != 0){
                dfs(n,m,i,j,arr,visited);
                if(sum > 0){
                    groupSum[grp-1] = sum;
                    if(sum > leaderGrpSum){
                        leaderGrpSum = sum;
                        leaderGrp = grp;
                    }
                    sum = 0;
                }
                grp++;
            }
        }
    }    
    grp--;  //decrement grp since it will be one greater than the actual number of groups

    //grpDist stores the minimum distance from the leaderGrp to the current grp(current index)
    int *grpDist = new int[grp];
    for(int i = 0;i<grp;i++){
        grpDist[i] = INT_MAX;
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            if(visited[i][j] == leaderGrp){
                minPath(i-1,j,n,m,visited,grpDist,leaderGrp,0);
                minPath(i,j+1,n,m,visited,grpDist,leaderGrp,0);
                minPath(i+1,j,n,m,visited,grpDist,leaderGrp,0);
                minPath(i,j-1,n,m,visited,grpDist,leaderGrp,0);
            }
        }
    }

    // print the groupSum and leader group.
    cout<<"\nGroups : ";
    for(int i = 0;i<grp;i++){
        cout<<groupSum[i]<<"  ";
    }

    cout<<"\nLeader Group - "<<leaderGrpSum<<endl;

    cout<<"Shortest distance between group "<<leaderGrpSum<<" and remaining groups: \n";
    for(int i = 0;i<grp;i++){
        if(leaderGrpSum != groupSum[i])
        cout<<"{"<<leaderGrpSum<<"} - {"<<groupSum[i]<<"} is "<<grpDist[i]<<"\n";
    }
    //delete the allocated memory from the heap.
    for(int i = 0;i<n;i++){
        delete[] visited[i];
        delete[] arr[i];
    }
    delete[] grpDist;
    delete[] groupSum;
    delete[] visited;
    delete[] arr;
}