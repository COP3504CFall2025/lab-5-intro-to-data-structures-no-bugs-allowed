#pragma once

#include "LinkedList.hpp"
#include <cstddef>
#include <stdexcept>


template <typename T>
class StackInterface{

public:

    virtual void push(const T& item) = 0;

    virtual T pop() = 0;

    virtual T peek() const = 0;

    [[nodiscard]] virtual std::size_t getSize() const noexcept = 0;

    virtual ~StackInterface() {}

};


template <typename T>
class QueueInterface{
public:
    QueueInterface() : LinkedList<T>() {}

    virtual void enqueue(const T& item) = 0;

    virtual T dequeue() = 0;

    virtual T peek() const = 0;

    [[nodiscard]] virtual std::size_t getSize() const noexcept = 0;

    virtual ~QueueInterface() {}

};


template <typename T>
class DequeInterface : public LinkedList<T>{

public:

    DequeInterface() : LinkedList<T>() {}

    void pushFront(const T& item) {
        LinkedList<T>::addHead(item);
    }

    void pushBack(const T& item) {
        LinkedList<T>::addTail(item);
    }

    T popFront() {

        T res = LinkedList<T>::getHead()->data;
        LinkedList<T>::removeHead();
        return res;
    }

    T popBack() {
        T res = LinkedList<T>::getTail()->data;
        LinkedList<T>::removeTail();
        return res;
    }

    const T& front() const {
        return LinkedList<T>::getHead();
    }

    const T& back() const {
        return LinkedList<T>::getTail();
    }

    [[nodiscard]] std::size_t getSize() const noexcept {
        return static_cast<std::size_t>(LinkedList<T>::getCount());
    }


};



