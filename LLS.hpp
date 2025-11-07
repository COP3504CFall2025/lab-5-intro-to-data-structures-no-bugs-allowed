#pragma once
#include <stdexcept>

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : virtual public LinkedList<T>, public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() : list(LinkedList<T>()) {}

    LLS(const LLS<T>& other) : list(other) {}
    LLS(const LLS<T>&& other) noexcept : list(std::move(other.list)) {}

    // Insertion
    void push(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T pop() override {

        if (list.getTail() == nullptr) {
            throw std::runtime_error("Attempted to pop on an empty stack.");
        }
        T res = list.getTail()->data;
        list.removeTail();
        return res;
    }

    // Access
    T peek() const override {
        if (list.getTail() == nullptr) {
            throw std::runtime_error("Attempted to peek on an empty stack.");
        }
        return list.getTail()->data;

    }

    //Getters
    std::size_t getSize() const noexcept override {
        return static_cast<std::size_t>(list.getCount());
    }

    LLS<T>& operator=(const LLS<T>&& other) noexcept {

        if (&other == this) {
            return *this;
        }

        list = std::move(other.list);
        return *this;
    }

    LLS<T>& operator=(const LLS<T>& rhs) {

        if (&rhs == this) {
            return *this;
        }
        list = rhs;
        return *this;
    }
};