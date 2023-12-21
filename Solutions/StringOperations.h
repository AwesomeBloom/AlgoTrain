//
// Created by root on 12/7/23.
//

#ifndef ALGO_STRINGOPERATIONS_H
#define ALGO_STRINGOPERATIONS_H

#include "Solution.h"


namespace string_operations {
    class Solution {
    public:

        /**
         * @problem: LC 344: reverse string
         * @site: https://leetcode.cn/problems/reverse-string/
         * @methods: string; double pointers;
         * **/
        void reverseString(vector<char>& s) {
            int len = s.size();
            for (int i = 0, j = len - 1; i < j; ++i, --j) {
                swap(s[i], s[j]);
            }
        }

        /**
         * @problem: LC 344: reverse string
         * @site: https://leetcode.cn/problems/reverse-string/
         * @methods: string; double pointers;
         * **/
        string reverseStr(string s, int k) {
            int len = s.size();
            for (int i = 0; i < len; i += 2 * k) {
                int right = min(len - 1, i + k - 1);
                for (int j = i; j < right; ++j, --right) {
                    swap(s[j], s[right]);
                }
            }
            return s;
        }

        /**
         * @problem: LC LCR 122: replace "blank" (path Encryption)
         * @site: https://leetcode.cn/problems/ti-huan-kong-ge-lcof/
         * @methods: string; double pointers;
         * **/
        string pathEncryption(string path,
                              const string& replacement=" ",
                              const string& method="double pointers") {
            if ("double pointers" == method) {
                // todo double pointers method
            } else {
                // inplace replace
                for (auto &ch: path) {
                    if (ch == '.') {
                        ch = ' ';
                    }
                }
            }
            return path;
        }

        /**
         * @problem: LC 151: reverse words
         * @site: https://leetcode.cn/problems/reverse-words-in-a-string/
         * @methods: string;
         * **/
        string reverseWords(const string& s) {
            string result;
            vector<string> words;
            string temp;
            for (auto ch : s) {
                if (ch != ' ') {
                    temp.push_back(ch);
                } else {
                    if (!temp.empty()) {
                        words.push_back(temp);
                        temp = "";
                    }
                }
            }
            if (!temp.empty()) {
                words.push_back(temp);
            }
            for (auto rit=words.rbegin(); rit != words.rend(); ++rit) {
                if (rit == words.rbegin()) {
                    result += *rit;
                } else {
                    result += (" " + *rit);
                }
            }
            return result;
        }

        string reverseWords_ (string& s) {
            auto removeExtraSpaces = [](string& input) {
                int slow = 0, len = input.size();
                for (int fast = 0; fast < len; ++fast) {
                    if (input[fast] != ' ') {
                        if (slow != 0) {
                            input[slow] = ' ';
                            slow ++;
                        }
                        while (fast < len && input[fast] != ' ') {
                            input[slow] = input[fast];
                            slow ++;
                            fast ++;
                        }
                    }
                }
                input.resize(slow);
            };

            auto reverseSingleWord = [](string& input, const int& left, const int& right) {
                for (int i = left, j = right; i < j; ++i, --j) {
                    swap(input[i], input[j]);
                }
            };

            removeExtraSpaces(s);
            int len = s.size();

            reverseSingleWord(s, 0, len - 1);

            int slow = 0;
            for (int fast = 0; fast < len; ) {
                if (fast < len - 1 && s[fast + 1] == ' ') {
                    reverseSingleWord(s, slow, fast);
                    slow = fast + 2;
                    fast = fast + 2;
                } else {
                    fast ++;
                }
            }
            reverseSingleWord(s, slow, len - 1);
            return s;
        }

        /**
         * @problem: LC LCR 182: left rotate string
         * @site: https://leetcode.cn/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/
         * @methods: string; simulation;
         * **/
        string dynamicPassword(string password, int target) {
            auto reverseString = [](string &input, int left, int right){
                for (int i = left, j = right; i < j; i++, j--) {
                    swap(input[i], input[j]);
                }
            };
            int len = password.size();
            if (target >= len) return password;

            reverseString(password, 0, len - 1);
            reverseString(password, 0, len - target - 1);
            reverseString(password, len - target, len - 1);
            return password;
        }

        /**
         * @problem: LC 28: strstr
         * @site: https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/
         * @methods: string; simulation; double pointers;
         * **/
        int strStr(string haystack, string needle) {
            auto getNextBak = [](const string& s) -> vector<int> {
                int len = s.size();
                vector<int> next(len, 0);

                int j = 0;
                next[0] = j;

                for (int i = 1; i < len; ++i) {
                    while (j > 0 && s[i] != s[j]) {
                        j = next[j - 1];
                    }
                    if (s[i] == s[j]) {
                        j++;
                    }
                    next[i] = j;
                }
                return next;
            };

            int len = haystack.size(), len_n = needle.size();
            if (len == 0 || len_n == 0) return -1;
            auto nextBak = getNextBak(needle);
            int j = -1, jBak = 0;

            for (int i = 0; i < len; ++i) {
                while (jBak > 0 && haystack[i] != needle[jBak]) {
                    jBak = nextBak[jBak - 1];
                }
                if (haystack[i] == needle[jBak]) {
                    jBak++;
                }
                if (jBak == len_n) {
                    return i - len_n + 1;
                }
            }
            return -1;
        }

        /**
         * @problem: LC 459: repeated substring pattern
         * @site: https://leetcode.cn/problems/repeated-substring-pattern/
         * @methods: string; simulation;
         * **/
        bool repeatedSubstringPattern(const string& s) {
            auto result = false;

            auto getNext = [](const string& s) {
                int len = s.size();
                vector<int> next(len, 0);

                int j = 0;
                next[0] = j;

                for (int i = 1; i < len; ++i) {
                    while (j > 0 && s[i] != s[j]) {
                        j = next[j - 1];
                    }
                    if (s[i] == s[j]) {
                        j++;
                    }
                    next[i] = j;
                }

                return next;
            };
            auto len = s.size();
            auto next = getNext(s);
            if (next[len - 1] >= 1) {
                int sufStart = next[len - 1] - 1, preEnd = len - next[len - 1];
                if (s.substr(0, preEnd) == s.substr(sufStart + 1 , len)) {
                    result = true;
                }
            }

            return result;
        }
    };


}

#endif //ALGO_STRINGOPERATIONS_H
