#pragma once

#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <string>
#include <sstream>

template <typename K, typename V>
class SkipList;

template <typename K, typename V>
class Node {
public:
    Node(uint32_t l, const K& k, const V& v) : level_(l), key_(k), value_(v) {
        forward_ = new Node * [level_];
    }

    ~Node() {
        if (forward_) {
            delete[] forward_;
        }
    }

    const K& key() const { return key_; }
    const V& value() const { return value_; }

    friend class SkipList<K, V>;

private:
    K key_;
    V value_;
    uint32_t level_;
    Node<K, V>** forward_;
};


template <typename K, typename V>
class SkipList {
public:
    explicit SkipList(uint32_t max_level) : max_level_(max_level), level_(0), count_(0) {
        head_ = new Node<K,V>* [max_level_];
        for (uint32_t i = 0; i < max_level_; i++) {
            head_[i] = nullptr;
        }
    }

    ~SkipList() {
        Node<K, V>* ptr = head_[0];
        while (ptr != nullptr) {
            Node<K, V>* next = ptr->forward_[0];
            delete ptr;
            ptr = next;
        }

        delete[] head_;
    }

    bool Insert(const K& key, const V& value) {
        if (Search(key)) return false;

        const uint32_t level = RandomLevel();

        Node<K, V>* node = new Node<K, V>(level, key, value);
        Node<K, V>** ptr = &head_[level - 1];

        for (int i = level - 1; i >= 0; i--, ptr--) {
            while (*ptr && (*ptr)->key_ < key) {
                ptr = &((*ptr)->forward_[i]);
            }

            node->forward_[i] = *ptr;
            *ptr = node;
        }

        count_++;
        if (level_ < level) {
            level_ = level;
        }
        return true;
    }

    Node<K, V>* Search(const K& key) const {
        Node<K,V>** ptr = &head_[level_ - 1];
        for (int level = level_ - 1; level >= 0; level--, ptr--) {
            while (*ptr && (*ptr)->key() < key) {
                ptr = &(*ptr)->forward_[level];
            }

            if (*ptr && (*ptr)->key() == key) {
                return *ptr;
            }
        }

        return nullptr;
    }

    void Remove(const K& key) {
        Node<K, V>* node = nullptr;
        Node<K, V>** ptr = &head_[level_ - 1];
        for (int i = level_ - 1; i >= 0; i--, ptr--) {
            while (*ptr && (*ptr)->key_ < key) {
                ptr = &((*ptr)->forward_[i]);
            }

            if (*ptr && (*ptr)->key_ == key) {
                if (node) assert(node == *ptr);
                node = *ptr;
                *ptr = node->forward_[i];
            }
        }

        if (node) {
            count_--;
            while (level_ >= 1 && head_[level_ - 1] == nullptr) {
                level_--;
            }
            delete node;
        }
    }

    std::string ToString() const {
        std::stringstream ss;
        for (int i = level_ - 1; i >= 0; i--) {
            for (Node<K, V>* ptr = head_[i]; ptr != nullptr; ptr = ptr->forward_[i]) {
                ss << ptr->key() << ":" << ptr->level_ << " ---> ";
            }
            ss << "null\n";
        }
        return ss.str();
    }

    uint32_t Level() const { return level_; }

    uint32_t Size() const { return count_; }

private:
    uint32_t RandomLevel() const {
        uint32_t level = 1;
        const double p = 0.25;
        while ((rand() & 0xffff) < 0xffff * p && level < max_level_) {
            level++;
        }
        return level;
    }

private:
    const uint32_t max_level_;
    uint32_t level_;
    uint32_t count_;
    Node<K, V>** head_;
};
