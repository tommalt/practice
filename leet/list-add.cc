#include <stdio.h>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		int a, b, s, rem;
		a = b = 0;
		s = rem = 0;
		ListNode *ret, *end;
		ret = end = NULL;
		for (;;) {
			a = l1 ? l1->val : 0;
			b = l2 ? l2->val : 0;
			s = rem + a + b;
			rem = s / 10;
			s = s % 10;
			if (!ret) {
				ret = new ListNode(0);
				end = ret;
				end->val = s;
			} else {
				end->next = new ListNode(0);
				end->next->val = s;
				end = end->next;
			}
			l1 = l1 ? l1->next : l1;
			l2 = l2 ? l2->next : l2;
			if (!l1 && !l2 && (rem == 0)) {
				break;
			}
		}
		return ret;
	}
};

int main()
{
	Solution s;

	ListNode *a, *b, *end;

	a = b = NULL;

	a = new ListNode(2);
	end = a;
	end->next = new ListNode(4);
	end = end->next;
	end->next = new ListNode(3);

	b = new ListNode(5);
	end = b;
	end->next = new ListNode(6);
	end = end->next;
	end->next = new ListNode(4);

	ListNode *res = s.addTwoNumbers(a, b);

	while (res) {
		printf("%d", res->val);
		res = res->next;
	}
	putchar('\n');
}
