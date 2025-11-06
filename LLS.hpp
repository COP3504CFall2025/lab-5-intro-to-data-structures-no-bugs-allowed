#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() : StackInterface<T>() {}

    // Insertion
    void push(const T& item) override {
        LinkedList<T>::addTail(item);
    }

    // Deletion
    T pop() override {
        T res = LinkedList<T>::getTail()->data;
        LinkedList<T>::removeTail();
        return res;
    }

    // Access
    T peek() const override {
        return LinkedList<T>::getTail()->data;

    }

    //Getters
    std::size_t getSize() const noexcept override {
        return static_cast<std::size_t>(LinkedList<T>::getCount());
    }
};