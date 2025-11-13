#pragma once
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() : capacity_(1), curr_size_(0), array_(new T[1]) {}
    explicit ABS(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity]) {}
    ABS(const ABS& other) {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[other.capacity_];

        for (int i = 0; i < other.curr_size_l; i++) {
            array_[i] = other.array_[i];
        }
    }

    ABS& operator=(const ABS& rhs) {

        if (&rhs == this) {
            return *this;
        }

        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = new T[rhs.capacity_];

        for (int i = 0; i < rhs.curr_size_l; i++) {
            array_[i] = rhs.array_[i];
        }

        return *this;

    }
    ABS(ABS&& other) noexcept {

        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = other.array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;

    }

    ABS& operator=(ABS&& rhs) noexcept {

        if (&rhs == this) {
            return *this;
        }

        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = rhs.array_;

        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.array_ = nullptr;

        return *this;
    }
    ~ABS() noexcept override {
        capacity_ = 0;
        curr_size_ = 0;
        delete[] array_;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    T getCapacity() {
        return capacity_;
    }

    T getSize() {
        return curr_size_;
    }

    // Push item onto the stack
    void push(const T& data) override {


        if (curr_size_ >= capacity_) {
            if (capacity_ > 0) {
                capacity_ *= scale_factor_;
            } else {
                capacity_ = 2;
            }

            T* tempData = new T[capacity_];

            for (int i = 0; i < curr_size_; i++) {
                tempData[i] = array_[i];
            }

            tempData[curr_size_] = data;
            delete[] array_;
            array_ = tempData;
            tempData = nullptr;
            capacity_ *= scale_factor_;
        } else {

            array_[curr_size_] = data;

        }

        curr_size_++;
        
    }

    T peek() const override {

        if (curr_size_ == 0) {
            throw std::runtime_error("Attempted to peek on empty ABS");
        }

        return array_[curr_size_ - 1];
    }

    T pop() override {

        if (curr_size_ == 0) {
            throw std::runtime_error("Attempted to peek on empty ABS");
        }

        T res = array_[curr_size_ - 1];
        array_[curr_size_ - 1] = 0;
        curr_size_--;
        return res;
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
