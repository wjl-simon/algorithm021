/*
 * @lc app=leetcode.cn id=529 lang=cpp
 *
 * [529] 扫雷游戏
 */

// @lc code=start
class Solution {
    void marker(vector<vector<char>>& board, int x, int y){
        int const m = board.size();
        int const n = board[0].size();
        
        int mines = 0;
        for(int i = x - 1; i <= x + 1; ++i){
            for(int j = y - 1; j <= y + 1; ++j){
                if(i < 0 || i >= m || j < 0 || j >= n || i == x && j == y){
                    continue;
                }
                mines += board[i][j] == 'M';
            }
        }

        if(mines > 0){
            board[x][y] = '0' + mines;
        }
        else{
            board[x][y] = 'B';
            for(int i = x - 1; i <= x + 1; ++i){
                for(int j = y - 1; j <= y + 1; ++j){
                    if(i == x && j == y ){
                        continue;
                    }
                    if(i < 0 || i >= m || j < 0 || j >= n || board[i][j] != 'E'){
                        continue;
                    }
                    marker(board, i, j);
                }
            }   
        }
    }
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int x = click[0], y = click[1];
        if(board[x][y] == 'M'){
            board[x][y] = 'X';
        }
        else{
            marker(board, x, y);
        }
        return board;
    }
};
// @lc code=end

