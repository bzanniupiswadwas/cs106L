/*
 * CS106L 作业 2：Marriage Pact（婚姻契约）
 * 由 Haven Whitney 创建，Fabio Ibanez 与 Jacob Roberts-Baca 修改。
 *
 * 欢迎参加 CS106L 第二次作业！请在本文件中完成所有“学生 TODO”部分。
 * 你不需要修改任何其他文件。
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <random>
#include <sstream>

std::string kYourName = "Boven Ding"; 

/**
 * 读取指定文件，返回包含所有报名者姓名的集合。
 *
 * @param filename 要读取的文件名。
 *                 文件每行是一个报名者的姓名。
 * @return         包含文件中所有姓名的集合。
 *
 * @备注 如需使用 std::unordered_set，可随意修改本函数及下方函数的返回类型；
 *      同时记得在 utils.h 中也做对应修改。
 */
std::set<std::string> get_applicants(std::string filename) {
    std::ifstream fin(filename);
    std::set<std::string> set;
    if (fin.is_open()) {
        std::string name;
        while (std::getline(fin, name)) {
            set.insert(name);
        }
    }
    return set;
}
/*
std::unordered_set<std::string> get_applicants(std::string filename) {
    std::ifstream fin(filename);
    std::unordered_set<std::string> set;
    if (fin.is_open()) {
        std::string name;
        while (std::getline(fin, name)) {
            set.insert(name);
        }
    }
    return set;
}
*/

/**
 * 根据给定姓名，从学生集合中找出 initials 相同的名字，返回指向这些名字的指针队列。
 *
 * @param name     目标姓名，返回队列中名字的 initials 应与此相同。
 * @param students 学生姓名集合。
 * @return         包含指向匹配姓名的指针的队列。
 */
static std::string get_initial(const std::string& name) {
    std::string res;
    std::string word;
    std::istringstream iss(name);
    while (iss >> word) {
        if (!word.empty()) {
            res += word[0];
        }
    }
    return res;
}

std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
    std::queue<const std::string*> queue;
    const std::string target_initial = get_initial(name);
    for (const auto& s: students) {
        if (get_initial(s) == target_initial) {
            queue.push(&s);
        }
    }
    return queue;
}

/**
 * 从可能匹配的指针队列中，选出“唯一真命”！
 *
 * 实现方式随意，但建议比简单 pop() 稍微有趣一点。
 *
 * @param matches 可能匹配的队列。
 * @return        你的真命天子/天女。
 *                若队列为空，返回 "NO MATCHES FOUND."。
 */
std::string get_match(std::queue<const std::string*>& matches) {
    if (matches.empty()) {return "NO MATCHES FOUND.";}
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<std::size_t> dist(0, matches.size() - 1);
    std::size_t target_index = dist(rng);

    const std::string* target = nullptr;
    for (std::size_t i = 0; i <= target_index; ++i) {
        target = matches.front();
        matches.pop();
        if (i != target_index) {
            matches.push(target);
        }
    }
    return *target;
}

/* #### 请勿删除此行！ #### */
#include "autograder/utils.hpp"