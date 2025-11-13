/*
 * CS106L Assignment 7: Unique Pointer
 * Created by Jacob Roberts-Baca.
 */

#include <functional>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "unique_ptr.h"

/**
 * @brief 单链表节点，通过 unique_ptr 自动管理后继节点。
 * @tparam T 节点中存储的值类型。
 *
 * @note 完成本作业无需修改此结构！
 */
template <typename T>
struct ListNode {
    /** @brief 节点中保存的值。 */
    T value;

    /** @brief 指向下一节点的智能指针，可能为 null。 */
    cs106l::unique_ptr<ListNode<T>> next;

    /**
     * @brief 构造单节点链表，next 初始化为 nullptr。
     * @param value 要存入节点的值。
     */
    ListNode(T value) : value(value), next(nullptr) {
        // 仅用于日志：观察构造函数何时被调用
        std::cout << "Constructing node with value '" << value << "'\n";
    }

    ~ListNode() {
        // 仅用于日志：观察析构函数何时被调用
        std::cout << "Destructing node with value '" << value << "'\n";
    }
};

/**
 * @brief 根据给定值向量创建单链表。
 * @param values 要放入链表的值序列。
 * @return 指向链表头节点的 unique_ptr。
 */
template <typename T>
cs106l::unique_ptr<ListNode<T>> create_list(const std::vector<T>& values) {
    /* 请实现：按向量顺序创建链表，空向量返回 nullptr。
     * 提示：可从尾到头反向构造。
     */
    cs106l::unique_ptr<ListNode<T>> head = nullptr;
    for (auto rit = values.rbegin(); rit != values.rend(); ++rit) {
      auto cur = cs106l::make_unique<ListNode<T>>(*rit);
      cur->next = std::move(head);
      head = std::move(cur);
    }
  return head;
}

/**
 * @brief 对链表中每个元素应用指定函数。
 * @tparam T 链表值类型。
 * @tparam Func 函数类型。
 * @param head 链表头节点。
 * @param func 要应用的函数。
 */
template <typename T, typename Func>
void map_list(const cs106l::unique_ptr<ListNode<T>>& head, const Func& func) {
    /* 请实现：递归遍历链表，对每个值调用 func。 */
    if (head) {
      func(head->value);
      map_list(head->next, func);
    }
}

/**
 * @brief 使用 unique_ptr 管理链表的示例。
 */
void linked_list_example() {
    std::vector<std::string> names{"Jacob", "Fabio", "Keith", "Chris", "Sean"};
    auto head = create_list(names);
    map_list(head, [](const std::string& name) { std::cout << name << "\n"; });
}

#include "autograder/utils.hpp"