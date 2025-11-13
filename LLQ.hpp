#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : virtual public LinkedList<T>, public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() : list(LinkedList<T>()) {}

    LLQ(const LLQ& other) : list(other.list) {}
    LLQ(LLQ&& other) noexcept : list(std::move(other.list)) {}

    // Insertion
    void enqueue(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T dequeue() override {

        if (list.getHead() == nullptr) {
            throw std::runtime_error("Attempted to dequeue empty queue");
        }

        T res = list.getHead()->data;

        list.removeHead();
        return res;
    }

    // Access
    T peek() const override {
        if (list.getHead() != nullptr) {
            return list.getHead()->data;
        }

        throw std::runtime_error("Attempted to peek at nullptr");
    }

    // Getter
    [[nodiscard]] std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    LLQ& operator=(LLQ&& other) noexcept {

        if (&other == this) {
            return *this;
        }

        list = std::move(other.list);
        return *this;

    }

    LLQ& operator=(const LLQ& other) {

        if (&other == this) {
            return *this;
        }

        this->list = other.list;

        return *this;
    }

};