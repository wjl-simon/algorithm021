/*
 * @lc app=leetcode.cn id=860 lang=cpp
 *
 * [860] 柠檬水找零
 */

// @lc code=start
class Solution {
private:
    vector<int> notes;

public:

    Solution(): notes(3, 0) {}

    bool lemonadeChange(vector<int>& bills) {
        int const LEN = bills.size();

        for(int i = 0; i < LEN; ++i){
            receive(bills[i]);
            if(!change(bills[i])){
                return false;
            }
        }
        return true;
    }

    void receive(int money){
        if(money == 5){
            notes[0]++;
        }
        else if(money == 10){
            notes[1]++;
        }
        else{
            notes[2]++;
        }
    }

    bool change(int money){
        if(money == 5){
            return true;
        }
        else if(money == 10){
            if(notes[0]-- >= 0){
                return true;
            }
            else{
                return false;
            }
        }
        else if(money == 20){
            if(notes[0] >= 1 && notes[1] >= 1){
                notes[0]--; notes[1]--;
                return true;
            }
            else if(notes[0] >= 3){
                notes[0] -= 3;
                return true;
            }
            else{
                return false;
            }
        }
        return false;
    }
};
// @lc code=end

