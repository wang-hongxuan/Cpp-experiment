#include "Student.h"
#include "ConsoleUtils.h"
#include <iostream>
#include <algorithm>
#include <windows.h>

Student::Student(const std::string& sno, const std::string& sname)
    : User(sno, "123456"), sno_(sno), sname_(sname) {}

std::string Student::getSno() const {
    return sno_;
}

std::string Student::getSname() const {
    return sname_;
}

void Student::setSname(const std::string& name) {
    sname_ = name;
}

void Student::addCourse(const Course& newCourse) {
    courses_.push_back(newCourse);
}

const std::vector<Course>& Student::getAllCourses() const {
    return courses_;
}

bool Student::hasCourse(const std::string& courseName) const {
    return std::any_of(courses_.begin(), courses_.end(),
        [&courseName](const Course& c) {
            return c.getCourseName() == courseName;
        });
}

bool Student::updateCourseScore(const std::string& courseName, int newScore) {
    auto it = std::find_if(courses_.begin(), courses_.end(),
        [&courseName](const Course& c) {
            return c.getCourseName() == courseName;
        });

    if (it != courses_.end()) {
        return it->setScore(newScore);
    }
    return false;
}

void Student::showMenu() const {
    SetColor(14);
    std::cout <<  sname_ << "同学，你好!" << std::endl;
    SetColor(14);
    std::cout << "1. 查询成绩" << std::endl;
    std::cout << "2. 修改密码" << std::endl;
    std::cout << "3. 退出登录" << std::endl;
    SetColor(7);
}

void Student::changePassword() {
    std::string currentPwd, newPwd, confirmPwd;

    // 验证当前密码
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

    // 获取并确认新密码
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

    // 设置新密码
    setPassword(newPwd);

    // 提示修改成功
    SetColor(10);
    std::cout << "密码修改成功!" << std::endl;
    SetColor(7);
    system("pause");
    system("cls");
}

void Student::showScores() const {
    SetConsoleOutputCP(65001);
    SetColor(14);
    std::cout << "******** " << sname_ << "同学(" << sno_ << ")的成绩单 ********" << std::endl;

    if (courses_.empty()) {
        SetColor(12);
        std::cout << "暂无成绩记录" << std::endl;
    } else {
        SetColor(10);
        for (const auto& course : courses_) {
            std::cout << course.getCourseName() << ": "
                      << course.getScore() << std::endl;
        }
    }
    SetColor(7);
    system("pause");
    system("cls");
}