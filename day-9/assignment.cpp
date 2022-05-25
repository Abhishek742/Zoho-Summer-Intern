#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<vector<char>> economic;
    vector<vector<char>> business;
    ifstream iFile;
    iFile.open("file.txt");
    string temp;
    string res;
    while (getline(iFile, temp))
    {
        int i = 0;
        vector<int> cols;
        int rows;
        while (i < temp.size())
        {
            if (temp[i] == '{')
            {
                while (temp[i] != '}')
                {
                    string number = "";
                    i++;
                    while (temp[i] != ',' && temp[i] != ' ' && temp[i] != '}')
                    {
                        number += temp[i];
                        i++;
                    }
                    if (number.length() != 0)
                        cols.push_back(stoi(number));
                }
                string rowNumber = "";
                while (i < temp.size())
                {
                    if (temp[i] != ',' && temp[i] != ' ' && temp[i] != '}')
                    {
                        rowNumber += temp[i];
                    }
                    i++;
                }
                rows = stoi(rowNumber);
            }
            else
                i++;
        }
        vector<char> columns;
        for (int i = 0; i < cols.size(); i++)
        {
            for (int j = 0; j < cols[i]; j++)
            {
                if ((i == 0 && j == 0) || (i == cols.size() - 1 && j == cols[i] - 1))
                {
                    columns.push_back('W');
                }
                else if (j == 0 || j == cols[i] - 1)
                {
                    columns.push_back('A');
                }
                else
                    columns.push_back('M');
            }
        }
        cout << endl;
        for (int i = 0; i < columns.size(); i++)
        {
            cout << columns[i];
        }
    }
    cout << res;
}