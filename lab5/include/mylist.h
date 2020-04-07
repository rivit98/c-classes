#pragma once

#include <iostream>
#include <memory>
#include <utility>

template<class T>
class MyList{
protected:
    class Node;
    using Ptr = std::unique_ptr<Node>;

    class Node{
    public:
        Ptr next;
        T val;
    public:
        explicit Node(T val = 0, Node *next = nullptr);

        ~Node() = default;
        T& getValue();
        Node *getNext();
    };

    Ptr head;
    size_t m_size;

public:
    MyList();
    ~MyList() = default;

	MyList(const MyList& other) = delete;
	MyList& operator=(const MyList& other) = delete;

    std::size_t size() const;
    void push_front(T val);
    T pop_front();
    T& front() const;
    void remove(T element);

    // so much code duplicated, inheritance will be better
    class MyListIterator: public std::iterator<std::forward_iterator_tag, T>{
    protected:
        Node *iter_node;
    public:
        explicit MyListIterator(Node *start = nullptr) : iter_node(start) {}
        MyListIterator& operator++();
        MyListIterator operator++(int);
        bool operator==(const MyListIterator& other) const { return iter_node == other.iter_node; }
        bool operator!=(const MyListIterator& other) const { return !(*this == other); }

        T& operator*() { return static_cast<Node*>(this->iter_node)->val; }
        Node* operator->() const { return iter_node; }
    };

    class MyListIteratorConst: public std::iterator<std::forward_iterator_tag, T, T, T*, T>{
    protected:
        Node *iter_node;
    public:
        explicit MyListIteratorConst(Node *start = nullptr) : iter_node(start) {}
        MyListIteratorConst& operator++();
        MyListIteratorConst operator++(int);
        bool operator==(const MyListIteratorConst& other) const { return iter_node == other.iter_node; }
        bool operator!=(const MyListIteratorConst& other) const { return !(*this == other); }

        T const& operator*() const { return static_cast<Node*>(this->iter_node)->val; }
        Node* operator->() const { return iter_node; }
    };

    using value_type = T;
    typedef MyListIterator iterator;
    typedef MyListIteratorConst const_iterator;

    iterator begin() { return iterator(head.get()); }
    iterator end() { return iterator(); }
    const_iterator begin() const { return const_iterator(head.get()); }
    const_iterator end() const { return const_iterator(); }
};

template<class T>
typename MyList<T>::MyListIterator& MyList<T>::MyListIterator::operator++() {
    iter_node = iter_node->next.get();
    return *this;
}

template<class T>
typename MyList<T>::MyListIterator MyList<T>::MyListIterator::operator++(int) {
    MyListIterator tmp(*this);
    iter_node = iter_node->next.get();
    return tmp;
}

template<class T>
typename MyList<T>::MyListIteratorConst& MyList<T>::MyListIteratorConst::operator++() {
    iter_node = iter_node->next.get();
    return *this;
}

template<class T>
typename MyList<T>::MyListIteratorConst MyList<T>::MyListIteratorConst::operator++(int) {
    MyListIteratorConst tmp(*this);
    iter_node = iter_node->next.get();
    return tmp;
}

template<class T>
MyList<T>::Node::Node(T val, Node *next) :
    next(next),
    val(val) {

};

template<class T>
T& MyList<T>::Node::getValue(){
    return val;
}

template<class T>
typename MyList<T>::Node *MyList<T>::Node::getNext(){
    return next.get();
}

template<class T>
MyList<T>::MyList():
    head(nullptr),
    m_size(0) {

};

template<class T>
size_t MyList<T>::size() const{
    return m_size;
}

template<class T>
void MyList<T>::push_front(T val){
    head = std::make_unique<Node>(val, head.release());
    m_size++;
}

template<class T>
T MyList<T>::pop_front(){
    if(m_size <= 0){
        throw std::out_of_range("List has no elements!");
    }

    m_size--;
    T ret_val = head.get()->getValue();
    head = std::move(head->next);
    return ret_val;
}

template<class T>
T& MyList<T>::front() const{
    return head->getValue();
}

// TODO: refactor this later
template<class T>
void MyList<T>::remove(T element){
    Node *iter = head.get();
    Node *prev = nullptr;

    while(iter != nullptr){
        if(iter->getValue() == element){
            if(prev != nullptr){
                prev->next = std::move(iter->next);
                iter = prev->getNext();
                m_size--;
            }else{
                pop_front();
                iter = head.get();
            }
        }else{
            prev = iter;
            iter = iter->getNext();
        }
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyList<T>& list) {
    for(auto element : list){
        os << element;
    }
    return os;
}