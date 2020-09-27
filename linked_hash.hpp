#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <string>
static const int HASH_SIZE = 1024;
struct linked_node {
    std::string key;
    std::string value;
    struct linked_node *next = nullptr;
};
class linked_hash {
public:
    virtual ~linked_hash() {
        for (int i = 0;i < HASH_SIZE;i++) {
            linked_node *node = nodes_[i];
            while (node) {
                linked_node *tmp = node;
                node = node->next;
                free(tmp);
            }
            node = nullptr;
        }
    }
public:
    bool lookup(const char *key, std::string &value) {
        uint32_t index = hash(key);
        linked_node *p = nodes_[index];
        for (;p;p = p->next) {
            if (0 == p->key.compare(key)) {
                value = p->value;
                return true;
            }
        }
        return false;
    }
    bool lookup(const char *key) {
        uint32_t index = hash(key);
        linked_node *p = nodes_[index];
        for (;p;p = p->next) {
            if (0 == p->key.compare(key)) {
                return true;
            }
        }
        return false;
    }
    bool install(const std::string &key, const std::string &value) {
        if (lookup(key.c_str())) {
            return false;
        }
        linked_node *node = (linked_node *)malloc(sizeof(linked_node));
        if (!node) {
            return false;
        }
        node->key = key;
        node->value = value;
        uint32_t index = hash(key.c_str());
        node->next = nodes_[index];
        nodes_[index] = node;
        return true;
    }
private:
    uint32_t hash(const char *key) {
        uint32_t val = 0;
        for (;*key;key++) {
            val = val * 33 + *key;
        }
        return val % HASH_SIZE;
    }
private:
    linked_node *nodes_[HASH_SIZE] = { 0 };
};