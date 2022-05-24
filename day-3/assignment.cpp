#include <iostream>
#include <memory>
using namespace std;

class CityGroups
{
    int sum, grp, n, m;
    // initialise the 2d matrix arr and visited dynamically
    unique_ptr<unique_ptr<int[]>[]> arr;
    unique_ptr<unique_ptr<int[]>[]> visited;
    unique_ptr<int[]> groupSum;
    unique_ptr<int[]> grpDist;

    int leaderGrpSum;
    int leaderGrp;

public:
    CityGroups(int n, int m)
    {
        this->n = n;
        this->m = m;
        this->sum = 0;
        this->grp = 1;
        // arr - stores the number of person living in each building
        this->arr = make_unique<unique_ptr<int[]>[]>(n);
        // visited - stores the current state (visited or not) and the group number of the current building
        this->visited = make_unique<unique_ptr<int[]>[]>(n);
        // stores the sum of people in each grp
        this->groupSum = make_unique<int[]>(n * m);
        this->grpDist = make_unique<int[]>(grp);
        // add m cells to each row in arr and visited
        for (int i = 0; i < n; i++)
        {
            unique_ptr<int[]> rowPointer = make_unique<int[]>(m);
            unique_ptr<int[]> visitedRow = make_unique<int[]>(m);
            for (int i = 0; i < m; i++)
            {
                rowPointer[i] = 0;
            }
            arr[i] = move(rowPointer);
            visited[i] = move(visitedRow);
        }
        this->leaderGrpSum = INT_MIN;
        this->leaderGrp = 0;
    }

    // get the values for arr matrix
    void getBuildings()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> arr[i][j];
                visited[i][j] = 0;
            }
        }
    }
    // dfs to find groups and group sizes.
    void dfs(int n, int m, int i, int j)
    {
        if (i >= n || j >= m || i < 0 || j < 0 || arr[i][j] == 0 || visited[i][j] != 0)
        {
            return;
        }
        sum += arr[i][j];
        // set visited[i][j] to the grp arr[i][j] it belongs to.(to identify the grps)
        visited[i][j] = grp;
        dfs(n, m, i - 1, j);
        dfs(n, m, i, j + 1);
        dfs(n, m, i + 1, j);
        dfs(n, m, i, j - 1);
        return;
    }

    // dfs to find the path with lesser distance from the leaderGrp to others
    void minPath(int i, int j, int n, int m, int leaderGrp, int c)
    {
        if (i < 0 || i >= n || j < 0 || j >= m || visited[i][j] == leaderGrp || visited[i][j] == -1 || grpDist[visited[i][j] - 1] == 1)
            return;
        if (visited[i][j] != 0)
        {
            grpDist[visited[i][j] - 1] = min(grpDist[visited[i][j] - 1], c);
            return;
        }
        c++;
        visited[i][j] = -1;
        minPath(i - 1, j, n, m, leaderGrp, c);
        minPath(i, j + 1, n, m, leaderGrp, c);
        minPath(i + 1, j, n, m, leaderGrp, c);
        minPath(i, j - 1, n, m, leaderGrp, c);
        visited[i][j] = 0;
    }
    void findMaxGroup()
    {
        // dfs to identify the groups and to find the one with max sum
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (visited[i][j] == 0 && arr[i][j] != 0)
                {
                    dfs(n, m, i, j);
                    if (sum > 0)
                    {
                        groupSum[grp - 1] = sum;
                        if (sum > leaderGrpSum)
                        {
                            leaderGrpSum = sum;
                            leaderGrp = grp;
                        }
                        sum = 0;
                    }
                    grp++;
                }
            }
        }
        grp--; // decrement grp since it will be one greater than the actual number of groups
    }
    void findLeaderGroup()
    {
        // grpDist stores the minimum distance from the leaderGrp to the current grp(current index)
        for (int i = 0; i < grp; i++)
        {
            grpDist[i] = INT_MAX;
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (visited[i][j] == leaderGrp)
                {
                    minPath(i - 1, j, n, m, leaderGrp, 0);
                    minPath(i, j + 1, n, m, leaderGrp, 0);
                    minPath(i + 1, j, n, m, leaderGrp, 0);
                    minPath(i, j - 1, n, m, leaderGrp, 0);
                }
            }
        }
    }

    void printGroups()
    {
        // print the groupSum and leader group.
        cout << "\nGroups : ";
        for (int i = 0; i < grp; i++)
        {
            cout << groupSum[i] << "  ";
        }

        cout << "\nLeader Group - " << leaderGrpSum << endl;

        cout << "Shortest distance between group " << leaderGrpSum << " and remaining groups: \n";
        for (int i = 0; i < grp; i++)
        {
            if (leaderGrpSum != groupSum[i])
                cout << "{" << leaderGrpSum << "} - {" << groupSum[i] << "} is " << grpDist[i] << "\n";
        }
    }
};

int main()
{
    int n, m;
    cout << "Enter n and m: ";
    cin >> n >> m;
    CityGroups cg(n, m);
    cg.getBuildings();
    cg.findMaxGroup();
    cg.findLeaderGroup();
    cg.printGroups();
}