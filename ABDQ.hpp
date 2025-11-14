#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() : data_(new T[4]), capacity_(4), size_(0), front_(0), back_(0) {}
    explicit ABDQ(std::size_t capacity) : data_(new T[capacity]), capacity_(capacity), size_(0), front_(0), back_(0) {}
    ABDQ(const ABDQ& other) {

        data_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        for (long long i = 0; i < other.capacity_; i++) {
            data_[i] = other.data_[i];
        }

    }

    ABDQ(ABDQ&& other) noexcept {

        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }
    ABDQ& operator=(const ABDQ& other) {

        if (&other == this) {
            return *this;
        }

        delete[] data_;

        data_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        for (long long i = 0; i < other.capacity_; i++) {
            data_[i] = other.data_[i];
        }

        return *this;
    }

    ABDQ& operator=(ABDQ&& other) noexcept {

        if (&other == this) {
            return *this;
        }

        delete[] data_;

        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;

        return *this;

    }

    ~ABDQ() override {

        delete[] data_;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = nullptr;
    }

    // Insertion
    void pushFront(const T& item) override {

        if (size_ == capacity_) {
            ensureCapacity();
        }

        if (front_ - back_ == 1 || back_ - front_ == capacity_ - 1) {
            throw std::runtime_error("Tried to pushfront on full ABDQ");
        }

        if (size_ == 0) {
            data_[0] = item;
            size_++;
            return;
        }

        if (front_ == 0) {
            front_ = capacity_ - 1;
        } else {
            front_--;
        }

        data_[front_] = item;
        size_++;
    }

    void pushBack(const T& item) override {

        if (size_ == capacity_) {
            ensureCapacity();
        }

        if (front_ - back_ == 1 || back_ - front_ == capacity_ - 1) {
            throw std::runtime_error("Tried to pushfront on full ABDQ");
        }

        if (size_ == 0) {
            data_[0] = item;
            size_++;
            return;
        }

        if (back_ == capacity_ - 1) {
            back_= 0;
        } else {
            back_++;
        }

        data_[back_] = item;
        size_++;
    }

    // Deletion
    T popFront() override {

        if (size_ == 0) {
            throw std::runtime_error("Attempted to popFront on an empty ABDQ");
        }

        T res = data_[front_];
        data_[front_] = 0;

        if (front_ == capacity_ - 1) {
            front_ = 0;
        } else {
            front_++;
        }

        size_--;

        if (size_ <= capacity_ / 2) {
            shrinkIfNeeded();
        }
        return res;
    }

    T popBack() override {

        if (size_ == 0) {
            throw std::runtime_error("Attempted to popFront on an empty ABDQ");
        }


        T res = data_[back_];
        data_[back_] = 0;

        if (back_ == 0) {
            back_ = capacity_ - 1;
        } else {
            back_--;
        }

        size_--;

        if (size_ <= capacity_ / 2) {
            shrinkIfNeeded();
        }

        return res;

    }

    // Access
    const T& front() const override {
        if (size_ == 0) {
            throw std::runtime_error("Attempted ro front() on an empty ABDQ");
        }

        return data_[front_];
    }

    const T& back() const override {
        if (size_ == 0) {
            throw std::runtime_error("Attempted ro front() on an empty ABDQ");
        }

        return data_[back_];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

    void ensureCapacity() {

        T* newData = new T[capacity_ * 2];

        for (long long i = 0; i < capacity_; i++) {
            newData[i] = data_[i];
        }

        data_ = newData;
        capacity_ *= 2;
        delete[] data_;

    }

    void shrinkIfNeeded() {

        T* newData = new T[capacity_/2];

        int currIndex = front_;
        for (long long i = 0; i < size_; i++) {

            newData[i] = data_[currIndex];

            if (currIndex == capacity_ - 1) {
                currIndex = 0;
            } else {
                currIndex++;
            }
        }

        capacity_ /= 2;
        delete[] data_;
        data_ = newData;
        front_ = 0;
        back_ = capacity_ - 1;

    }

    void display() {

        for (long long i = 0; i < capacity_; i++) {
            std::cout << data_[i] << " | ";
        }

        std::cout << "\n";
    }

};
