#include "Student.h"
#include <algorithm>
#include "ConsoleUtils.h"
#include <iostream>
#include <windows.h>

Student::Student(const std::string& sno, const std::string& sname, const std::string& password)
    : User(sno, password), sno_(sno), sname_(sname) {}

std::string Student::getSno() const {
    return sno_;
}

std::string Student::getSname() const {
    return sname_;
}

void Student::setSname(const std::string& name) {
    sname_ = name;
}

bool Student::operator<(const Student& other) const {
    return sno_ < other.sno_;
}

void Student::addCourse(const Course& newCourse) {
    courses_.insert(newCourse);
}

const std::set<Course>& Student::getAllCourses() const {
    return courses_;
}

std::set<Course>& Student::getAllCourses() {
    return courses_;
}

bool Student::hasCourse(const std::string& courseName) const {
    return std::any_of(courses_.begin(), courses_.end(),
        [&courseName](const Course& c) {
            return c.getCourseName() == courseName;
        });
}

bool Student::updateCourseScore(const std::string& cname, const std::string& teacherName, int newScore) {
    auto it = std::find_if(courses_.begin(), courses_.end(),
        [&cname, &teacherName](const Course& c) {
            return c.getCourseName() == cname && c.getTeacherName() == teacherName;
        });

    if (it != courses_.end()) {
        Course modified = *it;
        modified.setScore(newScore);
        courses_.erase(it);
        courses_.insert(modified);
        return true;
    }
    return false;
}

void Student::showMenu() const {
    SetColor(14);
    std::cout << sname_ << "同学，你好!" << std::endl;
    SetColor(14);
    std::cout << "1. 查询成绩" << std::endl;
    std::cout << "2. 修改密码" << std::endl;
    std::cout << "3. 退出登录" << std::endl;
    SetColor(7);
}

void Student::changePassword() {
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
            std::cout << course.getCourseName() << " (" << course.getTeacherName() << "): "
                      << course.getScore() << std::endl;
        }
    }
    SetColor(7);
    system("pause");
    system("cls");
}