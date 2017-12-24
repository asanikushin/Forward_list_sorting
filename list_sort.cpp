#include <iostream>

#include <cstddef>

struct Node {
    int data;
    Node *next;

    Node() : data(0), next(nullptr) {}

    Node(const int &d_) : data(d_), next(nullptr) {}

    bool operator<(const Node other) const {
        return data < other.data;
    }

    bool operator<(const Node *other) const {
        return data < other->data;
    }
};

Node *merge(Node *first, Node *second) {
    //std::cerr << "start merge\n";
    if (first == nullptr)
        return second;
    if (second == nullptr)
        return first;
    Node *ans;
    if ((*first) < (*second)) {
        ans = first;
        first = first->next;
    } else {
        ans = second;
        second = second->next;
    }
    Node *start = ans;
    //std::cerr << "before while\n";
    while (first != nullptr && second != nullptr) {
        //std::cerr << "! \n";
        if ((*first) < (*second)) {
            ans->next = first;
            first = first->next;
        } else {
            ans->next = second;
            second = second->next;
        }
        ans = ans->next;
    }
    //std::cerr << "after while\n";
    while (first != nullptr) {
        //std::cerr << "! ";
        ans->next = first;
        first = first->next;
        ans = ans->next;
    }
    //std::cerr << "\n";
    while (second != nullptr) {
        //std::cerr << "! ";
        ans->next = second;
        second = second->next;
        ans = ans->next;
    }
    ans->next = nullptr;
    //std::cerr << "\nend\n";
    return start;
}

Node *merge_sort(Node *begin) {
    //std::cerr << "begin merge\n";
    if (begin == nullptr || begin->next == nullptr) {
        return begin;
    }
    Node *center = begin;
    Node *end = begin->next;
    while (end != nullptr) {
        end = end->next;
        if (end != nullptr) {
            end = end->next;
            center = center->next;
        }
    }
    Node *second = center->next;
    center->next = nullptr;
    //std::cerr << "middle merge\n";

    begin = merge_sort(begin);
    second = merge_sort(second);
    begin = merge(begin, second);
    //std::cerr << "end merge\n";
    return begin;
}

int main() {
    int n, x;
    std::cin >> n >> x;
    auto *data = new Node(x);
    auto start = data;
    for (int i = 1; i < n; ++i) {
        std::cin >> x;
        data->next = new Node(x);
        data = data->next;
    }
    Node *ans = merge_sort(start);
    for (auto elem = ans; elem != nullptr; elem = elem->next) {
        std::cout << (elem->data) << " ";
    }
    return 0;
}