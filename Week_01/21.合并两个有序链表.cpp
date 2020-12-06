/*
 * @lc app=leetcode.cn id=21 lang=cpp
 *
 * [21] 合并两个有序链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
       ListNode* head = new ListNode(0), *list = head;

       while(l1 && l2){
           if(l1->val < l2->val){
               list->next = l1;
               l1 = l1->next;
           }
           else{
               list->next = l2;
               l2 = l2->next;
           }
           // list always points to the back
           list = list->next;
       }

       list->next = !l1 ? l2 : l1;
       return head->next;
    }
};
// @lc code=end

