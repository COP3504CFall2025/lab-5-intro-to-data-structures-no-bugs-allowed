#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : virtual public LinkedList<T>, public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() : list(LinkedList<T>()) {}
    LLDQ(const LLDQ& other) : list(other.list) {}
    LLDQ(LLDQ&& other) noexcept : list(std::move(other.list)) {}

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }
    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {

        if (list.getHead() == nullptr) {
            throw std::runtime_error("Attempted to popFront on empty LLDQ");
        }

        T res = list.getHead();
        list.removeHead();
        return res;
    }
    T popBack() override {
        if (list.getTail() == nullptr) {
            throw std::runtime_error("Attempted to popBack on empty LLDQ");
        }

        T res = list.getTail();
        list.removeTail();
        return res;
    }

    // Element Accessors
    const T& front() const override {
        if (list.getHead() == nullptr) {
            throw std::runtime_error("Attempted to front() on empty LLDQ");
        }

        return list.getHead();
    }
    const T& back() const override {
        if (list.getTail() == nullptr) {
            throw std::runtime_error("Attempted to back() on empty LLDQ");
        }

        return list.getTail();
    }

    // Getter
    [[nodiscard]] std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    LLDQ& operator=(LLDQ&& other) noexcept {

        if (&other == this) {
            return *this;
        }

        this->list = std::move(other.list);

        return *this;
    }

    LLDQ& operator=(const LLDQ&& other) {

        if (&other == this) {
            return *this;
        }

        this->list = other.list;

        return *this;
    }
};






