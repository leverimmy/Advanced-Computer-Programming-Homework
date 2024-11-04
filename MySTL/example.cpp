#include <cstdio>
#include <cstring> 
#define N 100010
#define M 500010

using namespace std;

const int inf = 2147483647;

#ifndef LIST_H
#define LIST_H

#include <cstddef>

template <typename T> class list {
public:
    list();
    ~list();
    void push_back(const T& val);
    void push_front(const T& val);
    void pop_back();
    void pop_front();
    T& back();
    T& front();
    bool empty() const;
    size_t size() const;
    void clear();
private:
    struct Node {
        T data;
        Node* nxt;
        Node* pre;
    };
    Node* m_head;
    Node* m_tail;
    size_t m_size;
};

#endif // LIST_H

template <typename T> list<T>::list() {
    m_head = new Node();
    m_tail = new Node();
    m_head->nxt = m_tail;
    m_tail->pre = m_head;
    m_size = 0;
}

template <typename T> list<T>::~list() {
    clear();
    delete m_head;
    delete m_tail;
}

template <typename T> void list<T>::push_back(const T& val) {
    Node* new_node = new Node();
    new_node->data = val;
    new_node->nxt = m_tail;
    new_node->pre = m_tail->pre;
    m_tail->pre->nxt = new_node;
    m_tail->pre = new_node;
    ++m_size;
}

template <typename T> void list<T>::push_front(const T& val) {
    Node* new_node = new Node();
    new_node->data = val;
    new_node->nxt = m_head->nxt;
    new_node->pre = m_head;
    m_head->nxt->pre = new_node;
    m_head->nxt = new_node;
    ++m_size;
}

template <typename T> void list<T>::pop_back() {
    if (m_size == 0) return;
    Node* del_node = m_tail->pre;
    m_tail->pre = del_node->pre;
    del_node->pre->nxt = m_tail;
    delete del_node;
    --m_size;
}

template <typename T> void list<T>::pop_front() {
    if (m_size == 0) return;
    Node* del_node = m_head->nxt;
    m_head->nxt = del_node->nxt;
    del_node->nxt->pre = m_head;
    delete del_node;
    --m_size;
}

template <typename T> T& list<T>::back() {
    return m_tail->pre->data;
}

template <typename T> T& list<T>::front() {
    return m_head->nxt->data;
}

template <typename T> bool list<T>::empty() const {
    return m_size == 0;
}

template <typename T> size_t list<T>::size() const {
    return m_size;
}

template <typename T> void list<T>::clear() {
    while (m_size > 0) {
        pop_back();
    }
}

#ifndef DEQUE_H
#define DEQUE_H

template <typename T> class deque {
public:
    deque();
    ~deque();
    void push_back(const T& val);
    void push_front(const T& val);
    void pop_back();
    void pop_front();
    T& back();
    T& front();
    bool empty() const;
    size_t size() const;
    void clear();

private:
    list<T>* _container;
};

#endif

template <typename T> deque<T>::deque() {
    _container = new list<T>();
}

template <typename T> deque<T>::~deque() {
    _container->clear();
}

template <typename T> void deque<T>::push_back(const T& val) {
    _container->push_back(val);
}

template <typename T> void deque<T>::push_front(const T& val) {
    _container->push_front(val);
}

template <typename T> void deque<T>::pop_back() {
    _container->pop_back();
}

template <typename T> void deque<T>::pop_front() {
    _container->pop_front();
}

template <typename T> T& deque<T>::back() {
    return _container->back();
}

template <typename T> T& deque<T>::front() {
    return _container->front();
}

template <typename T> bool deque<T>::empty() const {
    return _container->empty();
}

template <typename T> size_t deque<T>::size() const {
    return _container->size();
}

template <typename T> void deque<T>::clear() {
    _container->clear();
}

#ifndef QUEUE_H
#define QUEUE_H

template <typename T> class queue {
public:
    queue();
    ~queue();
    void push(const T& val);
    void pop();
    T& front();
    T& back();
    bool empty() const;
    size_t size() const;
    void clear();

private:
    deque<T> _container;
};

#endif // QUEUE_H

template <typename T> queue<T>::queue() {
    _container = deque<T>();
}

template <typename T> queue<T>::~queue() {
    _container.clear();
}

template <typename T> void queue<T>::push(const T& val) {
    _container.push_back(val);
}

template <typename T> void queue<T>::pop() {
    _container.pop_front();
}

template <typename T> T& queue<T>::front() {
    return _container.front();
}

template <typename T> T& queue<T>::back() {
    return _container.back();
}

template <typename T> bool queue<T>::empty() const {
    return _container.empty();
}

template <typename T> size_t queue<T>::size() const {
    return _container.size();
}

template <typename T> void queue<T>::clear() {
    _container.clear();
}

queue <int> q;

int n, m, s, t, cnt;
int dis[N], first[N], vis[N], f[N];

struct Edge {
	int to, next, wt;
} e[M];

void addEdge(int u, int v, int w) {
	cnt++;
	e[cnt].wt = w;
	e[cnt].to = v;
	e[cnt].next = first[u];
	first[u] = cnt;
}

int spfa() {
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++)
		dis[i] = inf;
	dis[s] = 0;
	vis[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		vis[x] = 0;
		for (int i = first[x]; i; i = e[i].next) {
			int y = e[i].to;
			if (dis[y] > dis[x] + e[i].wt) {
				dis[y] = dis[x] + e[i].wt;
				if (!vis[y]) {
					q.push(y);
					vis[y] = 1;
					if (++f[y] > n) {
						return 0;
                    }
				}
			}
		}
	}
	return 1;
}

int main() {
	scanf("%d %d %d", &n, &m, &s);
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		addEdge(u, v, w);
	}
	if (spfa()) {
		for(int i = 1; i <= n; i++)
			printf("%d ", dis[i]);
    } else {
		printf("Fail");
    }
	return 0;
}
