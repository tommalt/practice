
#include <unordered_map>

using namespace std;

struct List {
	int value;
	List *prev;
	List *next;
};

struct Queue {
	List *head;
	List *tail;
};

int queue_size(Queue *q)
{
	int count = 0;
	List *p = q->head;
	while (p) {
		count++;
		p = p->next;
	}
	return count;
}

void destroy_queue(Queue *q)
{
	List *p;

	if (!q->head)
		return;
	p = q->head;
	while (p) {
		List *next = p->next;
		delete p;
		p = next;
	}
	q->head = q->tail = NULL;
}

void queue_push_front(Queue *q, int x)
{
	List *new_head;

	new_head = new List;
	new_head->value = x;
	new_head->prev = NULL;
	new_head->next = q->head;
	if (q->head) {
		q->head->prev = new_head;
	}
	q->head = new_head;

	if (!q->tail) {
		q->tail = q->head;
	}
}

void queue_pop_back(Queue *q)
{
	List *new_end;

	new_end = q->tail->prev;
	new_end->next = NULL;
	delete q->tail;
	q->tail = new_end;
}

void queue_bubble(Queue *q, List *node)
{
	if (node->prev) {
		node->prev->next = node->next;
	} else {// node is already at head
		return;
	}

	if (node->next) {
		node->next->prev = node->prev;
	} else {// node is tail. reset tail w/o walking entire queue
		q->tail = node->prev;
	}
	node->prev = NULL;
	node->next = q->head;
	q->head->prev = node;
	q->head = node;
}

void print_queue(Queue *q)
{
	List *p;

	for (p = q->head; p; p = p->next) {
		printf("%d ", p->value);
	}
	putchar('\n');
}

class LRU {
	Queue q;
	unordered_map<int, List *> hash;
	int cache_size;
public:

	LRU() {
		q.head = q.tail = NULL;
	}
	~LRU() {
		destroy_queue(&q);
	}

	void set_size(int s) { cache_size = s; }
	void ref(int x) {
		auto ptr = hash.find(x);
		if (ptr == hash.end()) { // not in cache
			if (queue_size(&q) == cache_size) { // cache full
				int removed = q.tail->value;
				queue_push_front(&q, x);
				queue_pop_back(&q);
				hash.erase(removed);
				hash[x] = q.head;
			} else {
				queue_push_front(&q, x);
				hash[x] = q.head;
			}
		} else { // cache hit
			queue_bubble(&q, (*ptr).second);
		}
	}

	void show() {
		print_queue(&q);
	}
};

int main()
{
	LRU cache;

	cache.set_size(3);

	cache.ref(1);
	cache.ref(2);
	cache.ref(3);
	cache.ref(1);
	cache.ref(4);
	cache.ref(5);

	cache.show();
}
