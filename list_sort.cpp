#include <iostream>

#include <cstddef>

struct Node {
    int data;
    Node *next;

    Node() : data(0), next(nullptr) {}

    Node(int d_) : data(d_), next(nullptr) {}

    bool operator<(const Node &other) const {
        return data < other.data;
    }
};

Node *merge(Node *first, Node *second) {
    if (first == nullptr)
        return second;
    if (second == nullptr)
        return first;
    Node *ans;
    if (*first < *second) {
        ans = first;
        first = first->next;
    } else {
        ans = second;
        second = second->next;
    }
    Node *start = ans;
    while (first != nullptr && second != nullptr) {
        if (*first < *second) {
            ans->next = first;
            first = first->next;
        } else {
            ans->next = second;
            second = second->next;
        }
        ans = ans->next;
    }
    while (first != nullptr) {
        ans->next = first;
        first = first->next;
        ans = ans->next;
    }
    while (second != nullptr) {
        ans->next = second;
        second = second->next;
        ans = ans->next;
    }
    ans->next = nullptr;
    return start;
}

Node *merge_sort(Node *begin) {
    if (begin == nullptr || begin->next == nullptr) {
        return begin;
    }
    Node *center = begin;
    Node *end = begin->next;
    while (end != nullptr && end->next != nullptr) {
        end = end->next;
        end = end->next;
        center = center->next;
    }
    Node *second = center->next;
    center->next = nullptr;

    begin = merge_sort(begin);
    second = merge_sort(second);
    begin = merge(begin, second);
    return begin;
}

void clear(Node *current) {
    while (current != nullptr) {
        auto next = current->next;
        delete current;
        current = next;
    }
}

int main() {
    int n, x;
    std::cin >> n >> x;
    auto data = new Node(x);
    auto start = data;
    for (int i = 1; i < n; ++i) {
        std::cin >> x;
        data->next = new Node(x);
        data = data->next;
    }
    Node *ans = merge_sort(start);
    for (auto elem = ans; elem != nullptr; elem = elem->next) {
        std::cout << elem->data << " ";
    }
    clear(ans);
    std::cout << "\n";

    return 0;
}
