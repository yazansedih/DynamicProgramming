#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <unistd.h>

// Yazan Al Sedih
using namespace std;

void findPath(vector<vector<int>>& board, vector<vector<int>>& temp, int n, vector<int>& path);
int getSumLine(vector<vector<int>>& board, int x, int y, int n, bool flag);
void getCosts(vector<vector<int>>& board, int i, int j, int n, vector<vector<int>>& temp);
void printMatrix(const vector<vector<int>>& matrix);

void findPath(vector<vector<int>>& board, vector<vector<int>>& temp, int n, vector<int>& path) {
    int maximum = -9999;
    int x = 0, y = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (temp[i][j] > maximum) {
                maximum = temp[i][j];
                x = i;
                y = j;
            }
        }
    }

    int i = x, j = y;
    while (i < n && j < n) {
        path.push_back(board[i][j]);

        if (i + 1 < n && temp[i+1][j] > temp[i][j+1]) {
            i++;
        } 
        else {
            if (temp[i][j+1] > 0)
                j++;
            else
                break;
        }
    }
}

int getSumLine(vector<vector<int>>& temp, int x, int y, int n, bool flag){
    int sum = 0;
    if (!flag) // vertical line
        sum += temp[x][y];
    else // horizontal line
        sum += temp[x][y];  

    return sum;
}

void getCosts(vector<vector<int>>& board, int i, int j, int n, vector<vector<int>>& temp) {
    for (i = n - 1; i >= 0; i--) {
        for (j = n - 1; j >= 0; j--) {            
            if (i == n - 1 && j == n - 1)
                temp[i][j] = board[i][j];
            else if (i == n - 1)
                temp[i][j] = board[i][j] + max(getSumLine(temp, i, j + 1, n, true), 0);
            else if (j == n - 1)
                temp[i][j] = board[i][j] + max(getSumLine(temp, i + 1, j, n, false), 0);
            else
                temp[i][j] = board[i][j] + max(getSumLine(temp, i, j + 1, n, true), getSumLine(temp, i + 1, j, n, false));
        }
    }
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {

    int n;
    cin >> n;
    cin.ignore();

    vector<vector<int>> board(n, vector<int>(n));
    vector<vector<int>> temp(n, vector<int>(n));
    vector<int> path; 

    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        istringstream iss(line);
        string token;
        int j = 0;
        while (getline(iss, token, ',')) {
            board[i][j++] = stoi(token);
        }
    }
    
    getCosts(board, n-1, n-1, n, temp); 
    // cout << "eeeeeeeeeeeeeee\n\n";
    // printMatrix(temp);
    // cout << "eeeeeeeeeeeeeee\n\n";
    findPath(board, temp, n, path);

    for (int ele : path) {
        cout << ele << endl;
    }

    return 0;
}