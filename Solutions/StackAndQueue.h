//
// Created by root on 12/7/23.
//

#ifndef ALGO_STACKANDQUEUE_H
#define ALGO_STACKANDQUEUE_H

#include "Solution.h"

namespace stack_and_queue {
    class Solution {
    public:

        /**
        * @problem: LC 23: inplement queue using stacks
        * @site: https://leetcode.cn/problems/implement-queue-using-stacks/
        * @methods: stack; queue;
        * **/
        template<class T>
        class MyQueue {
        private:
            stack<T> _stack_in;
            stack<T> _stack_out;
        public:
            MyQueue() {}

            void push(T x) {
                _stack_in.push(x);
            }

            std::optional<T> pop() {
                if (!this->empty()) {
                    if (_stack_out.empty()) {
                        while (!_stack_in.empty()) {
                            _stack_out.push(_stack_in.top());
                            _stack_in.pop();
                        }
                    }
                    T result = _stack_out.top();
                    _stack_out.pop();
                    return result;
                }
                return std::nullopt;
            }

            std::optional<T> peek() {
                auto result = this->pop();
                if (result.has_value()) {
                    _stack_out.push(result);
                }
                return result;
            }

            bool empty() {
                return _stack_in.empty() && _stack_out.empty();
            }
        };

        /**
        * @problem: LC 225: inplement stack using queues
        * @site: https://leetcode.cn/problems/implement-stack-using-queues/
        * @methods: stack; queue;
        * **/
        template <class T>
        class MyStack {
        private:
            queue<T> _queue_in;

        public:
            MyStack() {}

            void push(T x) {
                _queue_in.push(x);
            }

            std::optional<T> pop() {
                int len = _queue_in.size();
                if (len > 0) {
                    while (len > 1) {
                        auto temp = _queue_in.front();
                        _queue_in.pop();
                        _queue_in.push(temp);
                        len--;
                    }
                    auto result = _queue_in.front();
                    _queue_in.pop();
                    return result;
                }
                return std::nullopt;
            }

            std::optional<T> top() {
                auto result = this->pop();
                if (result.has_value()) {
                    _queue_in.push(result);
                }
                return result;
            }

            bool empty() {
                return _queue_in.empty();
            }
        };

        /**
        * @problem: LC 20: valid parentheses
        * @site: https://leetcode.cn/problems/valid-parentheses/
        * @methods: stack;
        * **/
        bool isValid(const string& s) {
            bool result = true;
            stack<char> container;
            unordered_set<char> leftChars({'(', '[', '{'});
            unordered_map<char, char> matchChars({
                                                         {')', '('}, {']', '['}, {'}', '{'}
                                                 });
            for (auto ch: s) {
                if (container.empty()) {
                    container.push(ch);
                } else if (leftChars.find(container.top()) != leftChars.end()
                           && leftChars.find(ch) != leftChars.end()){
                    container.push(ch);
                } else if (container.top() == matchChars[ch]) {
                    container.pop();
                } else {
                    result = false;
                    break;
                }
            }
            return result && container.empty();
        }

        /**
        * @problem: LC 1047: remove all adjacent duplicates in string
        * @site: https://leetcode.cn/problems/remove-all-adjacent-duplicates-in-string/
        * @methods: stack;
        * **/
        string removeDuplicates(const string& s) {
            string newStr;
            for (auto ch: s) {
                if (newStr.empty()) {
                    newStr.push_back(ch);
                } else if (*newStr.rbegin() == ch) {
                    newStr.pop_back();
                } else {
                    newStr.push_back(ch);
                }
            }
            return newStr;
        }

        /**
        * @problem: LC 150: reverse polish notation
        * @site: https://leetcode.cn/problems/evaluate-reverse-polish-notation/
        * @methods: stack;
        * **/
        int evalRPN(vector<string>& tokens) {
            vector<int> numbers;
            unordered_map<string, std::function<int(int, int)>> operations({
                                                                                   {"+", [](const int& a, const int& b)->int{ return a + b; }},
                                                                                   {"-", [](const int& a, const int& b)->int{ return a - b; }},
                                                                                   {"*", [](const int& a, const int& b)->int{ return a * b; }},
                                                                                   {"/", [](const int& a, const int& b)->int{ return a / b; }},
                                                                           });
            for (const auto& token: tokens) {
                if (operations.find(token) != operations.end()) {
                    auto op = operations[token];
                    auto len = numbers.size();
                    if (len >= 2) {
                        auto temp = op(numbers[len - 2], numbers[len - 1]);
                        numbers.pop_back();
                        numbers.pop_back();
                        numbers.push_back(temp);
                    }
                } else {
                    numbers.push_back(stoi(token));
                }
            }
            assert(numbers.size() == 1);
            return *numbers.begin();
        }

        /**
        * @problem: LC 230: maximum in sliding window
        * @site: https://leetcode.cn/problems/sliding-window-maximum/
        * @methods: queue; decreasing queue;
        * **/
        vector<int> maxSlidingWindow(vector<int>& nums, int k) {
            int len = nums.size();
            if (len < k) return {};

            vector<int> result;

            deque<int> slidingWindow;
            deque<int> indexes;
            for (int i = 0; i < k; ++i) {
                if (slidingWindow.empty()) {
                    slidingWindow.push_back(nums[i]);
                    indexes.push_back(i);
                } else {
                    while (!slidingWindow.empty() && slidingWindow.back() <= nums[i]) {
                        slidingWindow.pop_back();
                        indexes.pop_back();
                    }
                    slidingWindow.push_back(nums[i]);
                    indexes.push_back(i);
                }
            }
            result.push_back(slidingWindow.front());

            for (int i = k; i < len; ++i) {
                if (indexes.front() == i - k) {
                    indexes.pop_front();
                    slidingWindow.pop_front();
                }
                if (slidingWindow.empty()) {
                    slidingWindow.push_back(nums[i]);
                    indexes.push_back(i);
                } else {
                    while (!slidingWindow.empty() && slidingWindow.back() <= nums[i]) {
                        slidingWindow.pop_back();
                        indexes.pop_back();
                    }
                    slidingWindow.push_back(nums[i]);
                    indexes.push_back(i);
                }
                result.push_back(slidingWindow.front());
            }

            return result;
        }

        /**
        * @problem: LC 347: top k frequent elements
        * @site: https://leetcode.cn/problems/top-k-frequent-elements/
        * @methods: queue; decreasing queue;
        * **/
        vector<int> topKFrequent(vector<int>& nums, int k) {
            vector<int> result;

            unordered_map<int, int> numCount;

            for (const auto& num: nums) {
                numCount[num]++;
            }

            auto cmpPair = [](const pair<int, int>& pair1, const pair<int, int>& pair2){
                return pair1.second < pair2.second;
            };

            priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmpPair)> kFrequent(cmpPair);

            for (const auto& count: numCount) {
                kFrequent.emplace(count);
            }

            while (k--) {
                result.push_back(kFrequent.top().first);
                kFrequent.pop();
            }

            return result;
        }
    };
}

#endif //ALGO_STACKANDQUEUE_H
