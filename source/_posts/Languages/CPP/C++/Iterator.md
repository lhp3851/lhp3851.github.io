---
title: Iterator
date: 2023-07-28 16:07:03
tags: Iterator
---


## [C++中迭代器原理、失效和简单实现](https://www.cnblogs.com/wxquare/p/4699429.html)

### 迭代器的种类

根据迭代器所支持的操作，可以把迭代器分为5类。

1. 输入迭代器：是只读迭代器，在每个被遍历的位置上只能读取一次。例如上面find函数参数就是输入迭代器。

2. 输出迭代器：是只写迭代器，在每个被遍历的位置上只能被写一次。

3. 前向迭代器：兼具输入和输出迭代器的能力，但是它可以对同一个位置重复进行读和写。但它不支持operator--，所以只能向前移动。

4. 双向迭代器：很像前向迭代器，只是它向后移动和向前移动同样容易。

5. 随机访问迭代器：有双向迭代器的所有功能。而且，它还提供了“迭代器算术”，即在一步内可以向前或向后跳跃任意位置，  包含指针的所有操作，可进行随机访问，随意移动指定的步数。支持前面四种Iterator的所有操作，并另外支持it + n、it - n、it += n、 it -= n、it1 - it2和it[n]等操作。

### 迭代器的实现

```cpp
#include <iostream>

template<typename T>
struct ListNode {
    T value;
    ListNode* next;
    ListNode() {
        next = 0;
    }
    ListNode(T val, ListNode *p = nullptr) :
            value(val), next(p) {
    }
};

template<typename T>
class List {
private:
    ListNode<T> *m_pHead;
    ListNode<T> *m_pTail;
    int m_nSize;
public:
    List() {
        m_pHead = nullptr;
        m_pTail = nullptr;
        m_nSize = 0;
    }
    //从链表尾部插入元素
    void push_back(T value) {
        if (m_pHead == nullptr) {
            m_pHead = new ListNode<T>(value);
            m_pTail = m_pHead;
        } else {
            m_pTail->next = new ListNode<T>(value);
            m_pTail = m_pTail->next;
        }

    }

    //打印链表元素
    void print(std::ostream &os = std::cout) const {
        for (ListNode<T> *ptr = m_pHead; ptr != m_pTail->next ; ptr = ptr->next)
            std::cout << ptr->value << " ";
        os << std::endl;
    }

    //内置迭代器
    class iterator {
    private:
        ListNode<T> *m_ptr;
    public:
        iterator(ListNode<T>* p = nullptr) :
                m_ptr(p) {
        }

        T operator*() const {
            return m_ptr->value;
        }
        ListNode<T>* operator->() const {
            return m_ptr;
        }
        iterator& operator++() {
            m_ptr = m_ptr->next;
            return *this;
        }
        iterator operator++(int) {
            ListNode<T>* tmp = m_ptr;
            m_ptr = m_ptr->next;
            return iterator(tmp);
        }

        bool operator==(const iterator &arg) const {
            return arg.m_ptr == this->m_ptr;
        }

        bool operator!=(const iterator &arg) const {
            return arg.m_ptr != this->m_ptr;
        }

    };

    //返回链表头部指针
    iterator begin() const {
        return iterator(m_pHead);
    }

    //返回链表尾部指针
    iterator end() const {
        return iterator(m_pTail->next);
    }

    //其它成员函数

};

int main() {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.print();
    for (List<int>::iterator it = l.begin(); it != l.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}
```
