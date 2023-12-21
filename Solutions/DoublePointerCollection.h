//
// Created by root on 12/7/23.
//

#ifndef ALGO_DOUBLEPOINTERCOLLECTION_H
#define ALGO_DOUBLEPOINTERCOLLECTION_H

#include "Solution.h"

namespace double_pointer_collection {
    class Solution {
    public:

        /**
         * @problem: LC 27: remove elements
         * @site: https://leetcode.cn/problems/remove-element/
         * @methods: double pointers;
         * **/
        int removeElement(vector<int>& nums,
                          int val,
                          bool optimize=false) {
            int len = nums.size();

            if (optimize) {
                int left = 0, right = len - 1;
                while (left <= right) {
                    while (left <= right && nums[right] == val) {
                        right --;
                    }
                    while (left <= right && nums[left] != val) {
                        left ++;
                    }
                    nums[left++] = nums[right--];
                }
                return left;
            } else {
                int left = 0;
                for (int right = 0; right < len; ++right) {
                    if (nums[right] != val) {
                        nums[left] = nums[right];
                        ++left;
                    }
                }
                return left;
            }
        }

        /**
        * @problem: LC 344: reverse string
        * @site: https://leetcode.cn/problems/reverse-string/
        * @methods: double pointers;
        * **/
        void reverseString(vector<char>& s) {
            int len = s.size();
            int left = 0, right = len - 1;
            while (left <= right) {
                swap(s[left++], s[right--]);
            }
        }

        /**
        * @problem: KM 54: replace number
        * @site: https://kamacoder.com/problempage.php?pid=1064
        * @methods: double pointers;
        * **/
        void replaceNumber(string& s,
                           const string& replacement="number") {
            int len = s.size(), lenReplacement = replacement.size(), numCnt = 0;

            for (const auto &ch: s) {
                if (ch >= '0' && ch <= '9') {
                    ++numCnt;
                }
            }

            int newLen = len + numCnt * (lenReplacement - 1);
            s.resize(len + numCnt * (lenReplacement - 1));
            int j = len - 1, i = newLen - 1;
            while (j >= 0){
                if (s[j] >= '0' && s[j] <= '9') {
                    int t = lenReplacement - 1;
                    while (t >= 0) {
                        s[i--] = replacement[t--];
                    }
                    j--;
                } else {
                    s[i--] = s[j--];
                }
            }
        }

        /**
        * @problem: LC 151: reverse words in a string
        * @site: https://leetcode.cn/problems/reverse-words-in-a-string/
        * @methods: double pointers;
        * **/
        string reverseWords(string& s) {
            auto reverseStr = [](string& s, const int& left, const int& right){
                int _left = left, _right = right;
                while (_left <= _right) {
                    swap(s[_left++], s[_right--]);
                }
            };

            auto stripChar = [](string& s, const char& target=' ') {
                int slow = 0, len = s.size();
                for (int fast = 0; fast < len; ++fast) {
                    if (s[fast] != ' ') {
                        if (slow != 0) {
                            s[slow] = ' ';
                            slow ++;
                        }
                        while (fast < len && s[fast] != ' ') {
                            s[slow] = s[fast];
                            slow ++;
                            fast ++;
                        }
                    }
                }
                s.resize(slow);
            };

            stripChar(s);
            int len = s.size();

            reverseStr(s, 0, len - 1);

            int left = 0;
            for (int right = 0; right < len; ) {
                if (right < len - 1 && s[right + 1] == ' ') {
                    reverseStr(s, left, right);
                    left = right + 2;
                    right = right + 2;
                } else {
                    right ++;
                }
            }
            reverseStr(s, left, len - 1);

            return s;
        }
    };
}


#endif //ALGO_DOUBLEPOINTERCOLLECTION_H
