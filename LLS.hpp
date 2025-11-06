#pragma once
#include <stdexcept>

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

        if (LinkedList<T>::getTail() == nullptr) {
            throw std::runtime_error("Attempted to pop on an empty stack.");
        }
        T res = LinkedList<T>::getTail()->data;
        LinkedList<T>::removeTail();
        return res;
    }

    // Access
    T peek() const override {
        if (LinkedList<T>::getTail() == nullptr) {
            throw std::runtime_error("Attempted to peek on an empty stack.");
        }
        return LinkedList<T>::getTail()->data;

    }

    //Getters
    std::size_t getSize() const noexcept override {
        return static_cast<std::size_t>(LinkedList<T>::getCount());
    }

    LLS<T>& operator=(const LLS<T>&& other) noexcept {

        if (&other == this) {
            return *this;
        }

        LinkedList<T>::operator=(std::move(other));
    }

    LLS<T>& operator=(const LLS<T>& rhs) {

        if (&rhs == this) {
            return *this;
        }

        LinkedList<T>::operator=(rhs);
    }
};