#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string COURSES_OFFERED_PATH     = "student_output/courses_offered.csv";
const std::string COURSES_NOT_OFFERED_PATH = "student_output/courses_not_offered.csv";

struct Course {
    std::string title;           // 课程标题
    std::string number_of_units; // 学分
    std::string quarter;         // 开课季度
};

/**
 * （学生 TODO）查看主函数（文件底部）如何调用 parse_csv、
 * write_courses_offered 和 write_courses_not_offered。
 * 按需修改这些函数的签名，使其符合预期行为，然后删除本注释！
 */

/**
 * 注意：
 * 我们必须先在上方声明 Course 结构体，再 #include "utils.cpp"，
 * 这样 utils.cpp 里的代码才能识别 Course 类型。
 * 记住：#include 会直接把文件内容复制粘贴过来。
 */
#include "utils.cpp"

/**
 * 该函数应使用 courses.csv 中的记录填充 courses 向量，
 * 其中每一行就是一条记录！
 *
 * 提示：
 * 1) 参考 utils.cpp 提供的 split 函数
 * 2) 每**一行**就是一条记录！（重要，再说一遍 :>）
 * 3) 第一行是列头，直接跳过！
 *
 * @param filename 输入文件名
 * @param courses  用于存放解析结果的向量
 */
void parse_csv(std::string filename, std::vector<Course>& courses) {
    std::ifstream fin(filename);
    if (fin.is_open()) {
        std::string line1;
        std::getline(fin, line1); // 去掉列表头

        std::string line2;
        while (std::getline(fin, line2)) {
            auto cols = split(line2, ',');
            courses.push_back({cols[0], cols[1], cols[2]});
        }
    }
}

/**
 * 该函数有两个要求：
 *
 * 1) 把所有“开课”的课程写入文件
 *    "student_output/courses_offered.csv"
 *    开课定义：Quarter 字段不等于字符串 "null"
 *
 * 2) 写完后，从 all_courses 中**删除**这些已开课的课程。
 *    注意：务必先写文件，再删除元素！
 *
 * 提示：
 * 1) 先记录需要删除哪些课
 * 2) 使用我们提供的 delete_elem_from_vector 函数
 * 3) 记得在输出文件第一行写列头（参考 courses.csv）
 *
 * @param all_courses 解析后的全部课程，函数执行后只剩“未开课”课程
 */
void write_courses_offered(std::vector<Course>& all_courses) {
    std::ofstream fout(COURSES_OFFERED_PATH);
    if (fout.is_open()) {
        std::vector<Course> offered_courses;
        fout << "Title,Number of Units,Quarter\n";
        for (auto& course: all_courses) {
            if (course.quarter != "null") {
                fout << course.title << "," << course.number_of_units << "," << course.quarter << std::endl;
                offered_courses.push_back(course);
            }
        }
        for (auto& course: offered_courses) {
            delete_elem_from_vector(all_courses, course);
        }
    }
}

/**
 * 将“未开课”课程写入文件
 * "student_output/courses_not_offered.csv"。
 *
 * 该函数**总是**在 write_courses_offered 之后调用，
 * 因此 unlisted_courses 里天然只剩未开课课程。
 *
 * 提示：实现与 write_courses_offered 非常相似，但更简短。
 *
 * @param unlisted_courses 未开课课程向量
 */
void write_courses_not_offered(std::vector<Course>& unlisted_courses) {
    std::ofstream fout(COURSES_NOT_OFFERED_PATH);
    if (fout.is_open()) {
        fout << "Title,Number of Units,Quarter\n";
        for (auto& course: unlisted_courses) {
            fout << course.title << "," << course.number_of_units << "," << course.quarter << std::endl;
        }
    }
}

int main() {
  /* 确保你正确定义了 Course 结构体！ */
  static_assert(is_valid_course<Course>, "Course struct 定义不正确！");

  std::vector<Course> courses;
  parse_csv("courses.csv", courses);

  /* 如需调试，可取消下行注释 */
  // print_courses(courses);

  write_courses_offered(courses);

  write_courses_not_offered(courses);

  return run_autograder();
}