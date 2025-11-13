#pragma once

#include <cstddef>
#include <utility>

namespace cs106l {

/**
 * @brief 管理单个对象的智能指针，离开作用域时自动释放。
 * @tparam T 被管理对象的类型。
 * @note 这是 std::unique_ptr 的简化版。
 */
template <typename T>
class unique_ptr {
private:
    /* 请实现：unique_ptr 需要记录什么数据成员？ */
    // T* ???
    T* uptr;

public:
    /**
     * @brief 用裸指针构造 unique_ptr。
     * @param ptr 要管理的裸指针。
     * @note 建议尽量使用 make_unique() 而不是直接调用本构造函数。
     */
    unique_ptr(T *ptr) {
        /* 请实现 */
        uptr = ptr;
    }

    /**
     * @brief 从 nullptr 构造 unique_ptr。
     */
    unique_ptr(std::nullptr_t) {
        /* 请实现 */
        uptr = nullptr;
    }

    /**
     * @brief 默认构造空 unique_ptr。
     * @note 默认情况下 unique_ptr 指向 nullptr。
     */
    unique_ptr() : unique_ptr(nullptr) {}

    /**
     * @brief 解引用，返回对象引用。
     * @return 被管理对象的引用。
     */
    T& operator*() {
        /* 请实现 */
        if (uptr == nullptr) {
            throw std::runtime_error("Dereferencing a nullptr unique_ptr");
        } else {
            return *uptr;
        }
    }

    /**
     * @brief 解引用，返回常量对象引用。
     * @return 被管理对象的 const 引用。
     */
    const T& operator*() const {
        /* 请实现 */
        if (uptr == nullptr) {
            throw std::runtime_error("Dereferencing a nullptr unique_ptr");
        } else {
            return *uptr;
        }
    }

    /**
     * @brief 箭头运算符，返回裸指针。
     * @return 被管理对象的指针。
     */
    T* operator->() {
        /* 请实现 */
        return uptr;
    }

    /**
     * @brief 箭头运算符，返回常量裸指针。
     * @return 被管理对象的 const 指针。
     */
    const T* operator->() const {
        /* 请实现 */
        return uptr;
    }

    /**
     * @brief 布尔转换，判断指针是否非空。
     * @return 若非空返回 true，否则返回 false。
     */
    operator bool() const {
        /* 请实现 */
        return uptr != nullptr;
    }

    /* 请实现以下函数：
     * - 析构函数
     * - 删除拷贝构造函数
     * - 删除拷贝赋值运算符
     * - 移动构造函数
     * - 移动赋值运算符
     */
    ~unique_ptr() {
      if (uptr != nullptr) {
        delete uptr;
        uptr = nullptr;
      }
    }

    unique_ptr(const unique_ptr<T>&) = delete;

    unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;

    unique_ptr(unique_ptr<T>&& other) noexcept {
      uptr = other.uptr;
      other.uptr = nullptr;
    }

    unique_ptr<T>& operator=(unique_ptr<T>&& other) noexcept {
      if (this != &other) {
        if (uptr != nullptr) {
          delete uptr;
        }
        uptr = other.uptr;
        other.uptr = nullptr;
      }
      return *this;
    }
};

/**
 * @brief 创建并管理一个动态对象。
 * @example auto ptr = make_unique<int>(5);
 * @tparam T 要创建的对象类型。
 * @tparam Args 构造参数的类型的可变参数模板。
 * @param args 传给 T 构造函数的参数。
 */
template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}