#include "Teacher.h"
#include "ConsoleUtils.h"
#include <iostream>
#include <algorithm>
#include <windows.h>

Teacher::Teacher(const std::string& tno, const std::string& tname,
                 const std::string& cname, const std::string& username,
                 const std::string& password, std::shared_ptr<StudentDB> db)
    : User(username, password), tno_(tno), tname_(tname), cname_(cname), studentDB(db) {}

std::string Teacher::getTno() const {
    return tno_;
}

std::string Teacher::getTname() const {
    return tname_;
}

std::string Teacher::getCname() const {
    return cname_;
}

void Teacher::inputScore(const std::string& sno, const std::string& sname, int score) {
    // 从全局数据库查找学生
    auto student = studentDB->findStudent(sno);

    if (student) {
        // 学生存在，检查是否已有该课程
        if (student->hasCourse(this->cname_)) {
            // 已有该课程，更新成绩
            if (student->updateCourseScore(this->cname_, score)) {
                SetColor(10);
                std::cout << "成绩更新成功!" << std::endl;
            } else {
                SetColor(12);
                std::cout << "成绩更新失败!" << std::endl;
            }
        } else {
            // 没有该课程，添加新课程
            Course newCourse(0, this->cname_);
            newCourse.setScore(score);
            student->addCourse(newCourse);
            SetColor(10);
            std::cout << "新课程成绩添加成功!" << std::endl;
        }

        // 更新学生姓名（如果需要）
        if (!sname.empty() && student->getSname() != sname) {
            student->setSname(sname);
        }
    } else {
        // 学生不存在，创建新学生并添加到全局数据库
        auto newStudent = std::make_shared<Student>(sno, sname);
        Course newCourse(0, this->cname_);
        newCourse.setScore(score);
        newStudent->addCourse(newCourse);
        studentDB->addStudent(newStudent);

        SetColor(10);
        std::cout << "新学生记录创建成功!" << std::endl;
    }
    SetColor(7);
    system("pause");
    system("cls");
}

void Teacher::showAllStudents() const {
    SetConsoleOutputCP(65001);
    SetColor(14);
    std::cout <<  tname_ << "老师的学生列表 " << std::endl;
    std::cout << "课程: " << cname_ << std::endl;

    const auto& allStudents = studentDB->getAllStudents();
    bool hasStudents = false;

    for (const auto& student : allStudents) {
        for (const auto& course : student->getAllCourses()) {
            if (course.getCourseName() == cname_) {
                SetColor(14);
                std::cout << "学号: " << student->getSno()
                          << ", 姓名: " << student->getSname()
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
    std::cout <<  tname_ << "老师，你好! " ;
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