//
// Created by root on 12/7/23.
//

#ifndef ALGO_BACKTRACKING_H
#define ALGO_BACKTRACKING_H

#include "Solution.h"

namespace backtracking {
    class Solution {
    public:
        /**
         * @problem: LC 77: combination
         * @site: https://leetcode.cn/problems/combinations/
         * @methods: backtracking; combination;
         * **/
        vector<vector<int>> combine(int n, int k) {
            vector<vector<int>> result;
            vector<int> temp;

            std::function<void(int, int, int)> backtracking;
            backtracking = [&](int n, int k, int i) {
                if (temp.size() == k) {
                    result.emplace_back(temp);
                    return;
                }
                for (int index = i; index <= n - k + temp.size() + 1; index++) {
                    temp.emplace_back(index);
                    backtracking(n, k, index + 1);
                    temp.pop_back();
                }
            };
            backtracking(n, k, 1);
            return result;
        }

        /**
         * @problem: LC 216: combination sum III
         * @site: https://leetcode.cn/problems/combination-sum-iii/
         * @methods: backtracking; combination;
         * **/
        vector<vector<int>> combinationSum3(int k, int n) {
            vector<vector<int>> result;
            vector<int> temp;

            std::function<void(int, int, int)> backtracking;
            backtracking = [&](int k, int n, int startIndex) {
                if (temp.size() == k) {
                    if (n == 0) {
                        result.emplace_back(temp);
                        return;
                    }
                }
                for (int i = startIndex; i <= 9; ++i) {
                    temp.emplace_back(i);
                    backtracking(k, n - i, i + 1);
                    temp.pop_back();
                }
            };
            backtracking(k, n, 1);
            return result;
        }

        /**
         * @problem: LC 17: phone number letter combination
         * @site: https://leetcode.cn/problems/letter-combinations-of-a-phone-number/description/
         * @methods: backtracking; combination;
         * **/
        vector<string> letterCombinations(string digits) {
            unordered_map<char, pair<int, int>> letterMap = {
                    {'2', {0,  2}},
                    {'3', {3,  5}},
                    {'4', {6,  8}},
                    {'5', {9,  11}},
                    {'6', {12, 14}},
                    {'7', {15, 18}},
                    {'8', {19, 21}},
                    {'9', {22, 25}},
            };

            vector<string> result;
            string temp;

            std::function<void(int)> backtracking;
            backtracking = [&](int currentIndex) {
                if (currentIndex == digits.size()) {
                    if (!temp.empty()) {
                        result.push_back(temp);
                    }
                    return;
                }
                auto ch = digits[currentIndex];
                auto range = letterMap[ch];

                for (int i = range.first; i <= range.second; ++i) {
                    temp.push_back('a' + i);
                    backtracking(currentIndex + 1);
                    temp.pop_back();
                }
            };

            backtracking(0);
            return result;
        }

        /**
         * @problem: LC 39: combination sum
         * @site: https://leetcode.cn/problems/combination-sum/
         * @methods: backtracking; combination;
         * **/
        vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
            vector<vector<int>> result;
            vector<int> temp;
            sort(candidates.begin(), candidates.end());
            int len = candidates.size();
            std::function<void(vector<int> &, int, int)> backtracking;
            backtracking = [&](vector<int> &candidates, int target, int currentIndex) {
                if (currentIndex == len) return;
                if (target < 0) return;
                if (target == 0) {
                    result.emplace_back(temp);
                    return;
                }
                for (int i = currentIndex; i < len && candidates[i] <= target; ++i) {
                    temp.emplace_back(candidates[i]);
                    backtracking(candidates, target - candidates[i], i);
                    temp.pop_back();
                }
            };
            backtracking(candidates, target, 0);
            return result;
        }

        /**
         * @problem: LC 40: combination sum II
         * @site: https://leetcode.cn/problems/combination-sum-ii/description/
         * @methods: backtracking; combination;
         * **/
        vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
            vector<vector<int>> result;
            vector<int> temp;
            sort(candidates.begin(), candidates.end());
            int len = candidates.size();
            std::function<void(vector<int> &, int, int startIndex)> backtracking;
            backtracking = [&](vector<int> &candidates, int target, int startIndex) {
                if (target == 0) {
                    result.push_back(temp);
                    return;
                }
                if (target < 0 || startIndex == len) return;
                int last = -1;
                for (int i = startIndex; i < len && candidates[i] <= target; ++i) {
                    if (last == candidates[i]) continue;
                    temp.emplace_back(candidates[i]);
                    backtracking(candidates, target - candidates[i], i + 1);
                    last = *temp.rbegin();
                    temp.pop_back();
                }
            };
            backtracking(candidates, target, 0);
            return result;
        }

        /**
         * @problem: LC 131: palindrome partitioning
         * @site: https://leetcode.cn/problems/palindrome-partitioning/
         * @methods: backtracking;
         * **/
        vector<vector<string>> partition(string s) {
            vector<vector<string>> result;
            vector<string> temp;

            auto isPalindrome = [](const string &s) -> bool {
                int i = 0, j = s.size() - 1;
                while (i <= j) {
                    if (s[i++] != s[j--]) {
                        return false;
                    }
                }
                return true;
            };
            int len = s.size();
            std::function<void(int)> backtracking;
            backtracking = [&](int startIndex) {
                if (startIndex >= len) {
                    result.emplace_back(temp);
                    return;
                }
                for (int i = startIndex; i < len; ++i) {
                    auto str = s.substr(startIndex, i - startIndex + 1);
                    if (isPalindrome(str)) {
                        temp.emplace_back(str);
                    } else {
                        continue;
                    }
                    backtracking(i + 1);
                    temp.pop_back();
                }
            };
            backtracking(0);
            return result;
        }

        /**
         * @problem: LC 93: restore IP
         * @site: https://leetcode.cn/problems/restore-ip-addresses/description/
         * @methods: backtracking;
         * **/
        vector<string> restoreIpAddresses(string s) {
            vector<vector<string>> result;
            vector<string> temp;
            int len = s.size();

            auto isValid = [](const string &s, int start, int end) {
                if (start > end) return false;
                int tempSeg = 0;
                string temp = "";
                for (int i = start; i <= end; ++i) {
                    tempSeg = tempSeg * 10 + s[i] - '0';
                    temp.push_back(s[i]);
                    if (temp[0] == '0' && temp.size() > 1) {
                        return false;
                    }
                }
                return temp.size() <= 3 && tempSeg <= 255;
            };

            std::function<void(int)> backtrack;
            backtrack = [&](int startIndex) {
                if (temp.size() == 4) {
                    if (startIndex >= len) {
                        result.push_back(temp);
                    }
                    return;
                }

                for (int i = startIndex; i < len; ++i) {
                    auto str = s.substr(startIndex, i - startIndex + 1);
                    if (isValid(s, startIndex, i)) {
                        temp.push_back(str);
                        backtrack(i + 1);
                        temp.pop_back();
                    } else {
                        break;
                    }
                }
            };
            backtrack(0);
            vector<string> IPs;
            for (auto str: result) {
                string tempIP = "";
                for (auto seg: str) {
                    tempIP += (seg + ".");
                }
                tempIP.pop_back();
                IPs.emplace_back(tempIP);
            }
            return IPs;
        }

        /**
         * @problem: LC 78: subsets
         * @site: https://leetcode.cn/problems/subsets/description/
         * @methods: backtracking;
         * **/
        vector<vector<int>> subsets(vector<int> &nums) {
            vector<vector<int>> result{};
            vector<int> temp;
            int len = nums.size();
            std::function<void(int)> backtracking;
            backtracking = [&](int startIndex) {
                result.emplace_back(temp);
                for (int i = startIndex; i < len; ++i) {
                    temp.emplace_back(nums[i]);
                    backtracking(i + 1);
                    temp.pop_back();
                }
            };

            backtracking(0);
            return result;
        }

        /**
         * @problem: LC 78: subsets II
         * @site: https://leetcode.cn/problems/subsets-ii/description/
         * @methods: backtracking;
         * **/
        vector<vector<int>> subsetsWithDup(vector<int> &nums) {
            vector<vector<int>> result;
            vector<int> temp;
            sort(nums.begin(), nums.end());
            int len = nums.size();
            std::function<void(int)> backtracking;
            backtracking = [&](int startIndex) {
                result.emplace_back(temp);

                int last = INT_MAX;
                for (int i = startIndex; i < len; ++i) {
                    if (last == nums[i]) continue;
                    temp.emplace_back(nums[i]);
                    backtracking(i + 1);
                    last = *temp.rbegin();
                    temp.pop_back();
                }
            };

            backtracking(0);
            return result;
        }

        /**
         * @problem: LC 491: nd sequence
         * @site: https://leetcode.cn/problems/non-decreasing-subsequences/description/
         * @methods: backtracking;
         * **/
        vector<vector<int>> findSubsequences(vector<int> &nums) {
            vector<vector<int>> result;
            vector<int> temp;
            int len = nums.size();

            std::function<void(int)> backtracking;
            backtracking = [&](int startIndex) {
                if (temp.size() >= 2) {
                    result.emplace_back(temp);
                }
                int used[201] = {};
                for (int i = startIndex; i < len; ++i) {
                    if (!temp.empty() && nums[i] < temp.back() || used[nums[i] + 100] == 1) {
                        continue;
                    }
                    used[nums[i] + 100] = 1;
                    temp.emplace_back(nums[i]);
                    backtracking(i + 1);
                    temp.pop_back();
                }
            };
            backtracking(0);
            return result;
        }

        /**
         * @problem: LC 46: permutations
         * @site: https://leetcode.cn/problems/permutations/
         * @methods: backtracking;
         * **/
        vector<vector<int>> permute(vector<int> &nums) {
            vector<vector<int>> result;
            vector<int> temp;
            int len = nums.size();
            vector<bool> used(len, false);
            std::function<void()> backtracking;
            backtracking = [&]() {
                if (temp.size() == len) {
                    result.push_back(temp);
                    return;
                }
                for (int i = 0; i < len; ++i) {
                    if (!used[i]) {
                        used[i] = true;
                        temp.emplace_back(nums[i]);
                        backtracking();
                        temp.pop_back();
                        used[i] = false;
                    }
                }
            };
            backtracking();
            return result;
        }

        /**
         * @problem: LC 47: permutations II
         * @site: https://leetcode.cn/problems/permutations-ii/description/
         * @methods: backtracking;
         * **/
        vector<vector<int>> permuteUnique(vector<int> &nums) {
            vector<vector<int>> result;
            vector<int> temp;
            int len = nums.size();
            vector<bool> used(len, false);
            sort(nums.begin(), nums.end());

            std::function<void()> backtracking;
            backtracking = [&]() {
                if (temp.size() == len) {
                    result.emplace_back(temp);
                    return;
                }
                for (int i = 0; i < len; ++i) {
                    if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) {
                        continue;
                    }
                    if (!used[i]) {
                        used[i] = true;
                        temp.emplace_back(nums[i]);
                        backtracking();
                        temp.pop_back();
                        used[i] = false;
                    }
                }
            };
            backtracking();
            return result;
        }

        /**
         * @problem: LC 332: reconstruct itinerary
         * @site: https://leetcode.cn/problems/reconstruct-itinerary/
         * @methods: backtracking;
         * **/
        vector<string> findItinerary(vector<vector<string>>& tickets) {
            vector<string> result = {"JFK"};
            unordered_map<string, map<string, int>> ticketsMap;
            for (auto ticket: tickets) {
                ticketsMap[ticket[0]][ticket[1]]++;
            }

            std::function<bool(string)> backtracking;
            backtracking = [&](const string& current){
                if (result.size() == tickets.size() + 1) {
                    return true;
                }
                for (auto& endPlace: ticketsMap[current]) {
                    if (endPlace.second > 0) {
                        endPlace.second--;
                        result.emplace_back(endPlace.first);
                        if (backtracking(endPlace.first)) return true;
                        result.pop_back();
                        endPlace.second++;
                    }
                }
                return false;
            };
            backtracking("JFK");
            return result;
        }

        /**
         * @problem: LC 51: N queens
         * @site: https://leetcode.cn/problems/n-queens/
         * @methods: backtracking;
         * **/
        vector<vector<string>> solveNQueens(int n) {
            vector<vector<string>> results;
            vector<string> tempSolution(n, string(n, '.'));

            auto isValid = [](const vector<string>& solution, int x, int y, int n){
                vector<int> dx = {1, 1, 1, 0, -1, -1, -1, 0};
                vector<int> dy = {1, 0, -1, -1, -1, 0, 1, 1};
                for (int i = 0; i < 8; ++i) {
                    int curx = x, cury = y;
                    while (curx >= 0 && curx < n && cury >= 0 && cury < n) {
                        if (solution[curx][cury] == 'Q') return false;
                        curx += dx[i];
                        cury += dy[i];
                    }
                }
                return true;
            };

            std::function<void(int)> backtracking;
            backtracking = [&](int queens){
                if (queens == n) {
                    results.emplace_back(tempSolution);
                    return ;
                }

                for (int i = 0; i < n; ++i) {
                    if (isValid(tempSolution, queens, i, n)) {
                        tempSolution[queens][i] = 'Q';
                        backtracking(queens + 1);
                        tempSolution[queens][i] = '.';
                    }
                }
            };
            backtracking(0);
            return results;
        }

        /**
         * @problem: LC 37: sudoku
         * @site: https://leetcode.cn/problems/sudoku-solver/description/
         * @methods: backtracking;
         * **/
        void solveSudoku(vector<vector<char>>& board) {
            vector<vector<char>> valid;
            int n = board.size();

        }
    };

}

#endif //ALGO_BACKTRACKING_H
