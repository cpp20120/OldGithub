class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2){

        ListNode* temp1 = list1;   
        ListNode* temp2 = list2;
        ListNode* res = new ListNode(-1);
        ListNode* ans = res;
        

        while(temp1 && temp2){

            if(temp1->val <= temp2->val){
                ListNode* node = new ListNode(temp1->val);
                ans->next = node;
                ans = ans->next;
                temp1 = temp1->next;
            }
            else{
                ListNode* node = new ListNode(temp2->val);
                ans->next = node;
                ans = ans->next;
                temp2 = temp2->next;                
            }
        }

        if(temp1){
            ans->next = temp1;
        }
        if(temp2){
            ans->next = temp2;
        }

        return res->next;
    }
};
