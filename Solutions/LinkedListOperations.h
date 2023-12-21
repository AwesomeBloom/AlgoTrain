//
// Created by root on 12/7/23.
//

#ifndef ALGO_LINKEDLISTOPERATIONS_H
#define ALGO_LINKEDLISTOPERATIONS_H

#include "Solution.h"

// linked list namespace
namespace linked_list_operations {



    typedef TListNode<int> ListNode;

    class Solution {
    public:
        /**
         * @problem: LC 203: remove linked list elements
         * @site: https://leetcode.cn/problems/remove-linked-list-elements/
         * @methods: linked list; simulation;
         * **/
        ListNode* removeElements(ListNode* head, int val) {
            // drop nullptr
            if (!head) {
                return head;
            }

            auto dummynode = new ListNode(0, head), s = dummynode->next, t = dummynode;
            decltype(head) deletenode = nullptr;
            while (s) {
                if (s->val == val) {
                    t->next = s->next;
                    deletenode = s;
                } else {
                    t = t->next;
                }
                s = s->next;
                if (deletenode != nullptr) {
                    delete deletenode;
                    deletenode = nullptr;
                }
            }
            auto result = dummynode->next;
            delete dummynode;
            return result;
        }

        /**
         * @problem: LC 707: design linked list
         * @site: https://leetcode.cn/problems/design-linked-list/
         * @methods: linked list; simulation;
         * **/
        class MyLinkedList {
        private:
            ListNode *dummyHead, *tail;
            int len;
        public:
            MyLinkedList() : dummyHead(new ListNode(0, nullptr)), len(0){
                tail =  dummyHead->next;
            }

            int get(int index) {
                auto s = dummyHead->next;
                int i = 0;
                if (index < 0 || index >= len) {
                    return -1;
                }
                while (s) {
                    if (i == index) {
                        return s->val;
                    }
                    s = s->next;
                    ++i;
                }
                return -1;
            }

            void addAtHead(int val) {
                auto new_node = new ListNode(val, dummyHead->next);
                if (len == 0) {
                    tail = new_node;
                }
                dummyHead->next = new_node;
                ++len;
            }

            void addAtTail(int val) {
                auto new_node = new ListNode(val, nullptr);
                if (len == 0) {
                    addAtHead(val);
                } else {
                    tail->next = new_node;
                    tail = new_node;
                    ++len;
                }
            }

            void addAtIndex(int index, int val) {
                if (index < 0 || index > len) {
                    return ;
                } else if (index == len){
                    addAtTail(val);
                } else if (index == 0){
                    addAtHead(val);
                } else {
                    int i = 0;
                    auto s = dummyHead->next;
                    while (i < index - 1) {
                        s = s->next;
                        ++i;
                    }
                    auto new_node = new ListNode(val, s->next);
                    s->next = new_node;
                    len++;
                }
            }

            void deleteAtIndex(int index) {
                if (index < 0 || index >= len) {
                    return ;
                } else {
                    int i = 0;
                    auto s = dummyHead, t = dummyHead->next;
                    while (i < index) {
                        s = s->next;
                        t = t->next;
                        ++i;
                    }
                    s->next = t->next;
                    if (t == tail) {
                        tail = s;
                    }
                    --len;
                }
            }
        };

        /**
         * @problem: LC 206: reverse linked list
         * @site: https://leetcode.cn/problems/reverse-linked-list/
         * @methods: linked list; simulation;
         * **/
        ListNode* reverseList(ListNode* head) {
            // need not reverse (length == 0 || length == 1)
            if (head == nullptr || head->next == nullptr) {
                return head;
            }
            auto dummyHead = new ListNode(0, head), s = head, t = head->next;
            while (t != nullptr) {
                head = dummyHead->next;
                dummyHead->next = t;
                s->next = t->next;
                t->next = head;
                t = s->next;
            }
            auto result = dummyHead->next;
            delete dummyHead;
            return result;
        }

        /**
         * @problem: LC 24: swap nodes in pairs
         * @site: https://leetcode.cn/problems/swap-nodes-in-pairs/
         * @methods: linked list; simulation;
         * **/
        ListNode* swapPairs(ListNode* head) {
            if (head == nullptr || head->next == nullptr) {
                return head;
            }

            auto dummyHead = new ListNode(0, head);
            auto s = head, t = head->next, pre = dummyHead;
            while (s != nullptr && t != nullptr) {
                pre->next = t;
                s->next = t->next;
                t->next = s;

                pre = s;
                s = s->next;
                if (s != nullptr) {
                    t = s->next;
                }
            }
            auto result = dummyHead->next;
            delete dummyHead;
            return result;
        }

        /**
         * @problem: LC 19: delete nth node from end
         * @site: https://leetcode.cn/problems/remove-nth-node-from-end-of-list/
         * @methods: linked list; simulation;
         * **/
        ListNode* removeNthFromEnd(ListNode* head, int n) {
            auto dummyHead = new ListNode(0, head);
            auto slow = head, fast = head;

            while (n > 0 && fast != nullptr) {
                fast = fast->next;
                n--;
            }
            if (n > 0) {
                return nullptr;
            }
            auto pre = dummyHead;
            while (fast != nullptr) {
                pre = pre->next;
                slow = slow->next;
                fast = fast->next;
            }

            pre->next = slow->next;

            auto result = dummyHead->next;
            delete dummyHead;
            return result;
        }

        /**
         * @problem: LC interview 02.07: intersection of 2 linked list
         * @site: https://leetcode.cn/problems/intersection-of-two-linked-lists-lcci/
         * @methods: linked list; simulation;
         * **/
        ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
            auto getLength = [](ListNode *head) -> int{
                auto result = 0;
                while (head != nullptr) {
                    result++;
                    head = head->next;
                }
                return result;
            };

            auto lenA = getLength(headA), lenB = getLength(headB);

            if (lenA > lenB) {
                for (int i = 0; i < lenA - lenB; ++i) {
                    headA = headA->next;
                }
            } else {
                for (int i = 0; i < lenB - lenA; ++i) {
                    headB = headB->next;
                }
            }
            decltype(headA) result = nullptr;
            while (headA != nullptr && headB != nullptr) {
                if (headA == headB) {
                    result = headA;
                    break;
                }
                headA = headA->next;
                headB = headB->next;
            }

            return result;
        }

        /**
         * @problem: LC 142: linked list cycle II
         * @site: https://leetcode.cn/problems/linked-list-cycle-ii/
         * @methods: linked list; simulation;
         * **/
        ListNode *detectCycle(ListNode *head) {
            auto dummyHead = new ListNode(0, head);
            auto slow = head, fast = head;
            while (fast != nullptr && fast->next != nullptr) {
                slow = slow->next;
                fast = fast->next->next;
                if (slow == fast) {
                    auto index1 = dummyHead->next, index2 = fast;
                    while (index1 != index2) {
                        index1 = index1->next;
                        index2 = index2->next;
                    }
                    delete dummyHead;
                    return index1;
                }
            }
            delete dummyHead;
            return nullptr;
        }

    };
}

#endif //ALGO_LINKEDLISTOPERATIONS_H
