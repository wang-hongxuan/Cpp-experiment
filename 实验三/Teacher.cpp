#include "Teacher.h"
#include "ConsoleUtils.h"
#include <iostream>
#include <windows.h>

Teacher::Teacher(const std::string& tno, const std::string& tname,
                 const std::string& cname, const std::string& password)
    : User(tno, password), tno_(tno), tname_(tname), cname_(cname) {}

std::string Teacher::getTno() const {
    return tno_;
}

std::string Teacher::getTname() const {
    return tname_;
}

std::string Teacher::getCname() const {
    return cname_;
}

bool Teacher::operator<(const Teacher& other) const {
    return tno_ < other.tno_;
}

void Teacher::inputScore(Student& student, int score) {
    Course targetCourse(cname_, tname_);
    auto& courses = student.getAllCourses();  // 使用非 const 引用
    auto it = courses.find(targetCourse);

    if (it != courses.end()) {
        // 更新已有课程成绩
        Course modified = *it;
        modified.setScore(score);
        courses.erase(it);
        courses.insert(modified);
        SetColor(10);
        std::cout << "成绩更新成功!" << std::endl;
    } else {
        // 添加新课程
        Course newCourse(cname_, tname_);
        newCourse.setScore(score);
        courses.insert(newCourse);
        SetColor(10);
        std::cout << "新课程成绩添加成功!" << std::endl;
    }
    SetColor(7);
}

void Teacher::showAllStudents(const std::set<Student>& students) const {
    SetConsoleOutputCP(65001);
    SetColor(14);
    std::cout << tname_ << "老师的学生列表 " << std::endl;
    std::cout << "课程: " << cname_ << std::endl;

    bool hasStudents = false;

    for (const auto& student : students) {
        for (const auto& course : student.getAllCourses()) {
            if (course.getCourseName() == cname_) {
                SetColor(14);
                std::cout << "学号: " << student.getSno()
                          << ", 姓名: " << student.getSname()
                          << ", 成绩: " << course.getScore() << std::endl;
                hasStudents = true;
                break;
            }
        }
    }

    if (!hasStudents) {
        SetColor(12);
        std::cout << "暂无学生记录" << std::endl;
    }
    SetColor(7);
    system("pause");
    system("cls");
}

void Teacher::showMenu() const {
    SetConsoleOutputCP(65001);
    SetColor(14);
    std::cout << tname_ << "老师，你好! ";
    std::cout << "当前课程: " << cname_ << std::endl;
    SetColor(14);
    std::cout << "1. 录入/更新学生成绩" << std::endl;
    std::cout << "2. 查看所有学生成绩" << std::endl;
    std::cout << "3. 修改密码" << std::endl;
    std::cout << "4. 退出登录" << std::endl;
    SetColor(7);
}

void Teacher::changePassword() {
    std::string currentPwd, newPwd, confirmPwd;

    SetColor(10);
    std::cout << "请输入当前密码: ";
    SetColor(7);
    std::cin >> currentPwd;

    if (currentPwd != pwd_) {
        SetColor(12);
        std::cout << "当前密码错误!" << std::endl;
        SetColor(7);
        return;
    }

    while (true) {
        SetColor(10);
        std::cout << "请输入新密码: ";
        SetColor(7);
        std::cin >> newPwd;

        SetColor(10);
        std::cout << "请确认新密码: ";
        SetColor(7);
        std::cin >> confirmPwd;

        if (newPwd == confirmPwd) {
            break;
        }

        SetColor(12);
        std::cout << "两次输入的密码不一致，请重新输入!" << std::endl;
        SetColor(7);
    }

    setPassword(newPwd);

    SetColor(10);
    std::cout << "密码修改成功!" << std::endl;
    SetColor(7);
    system("pause");
    system("cls");
}