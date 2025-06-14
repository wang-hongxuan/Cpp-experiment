#include "Administrator.h"
#include "ConsoleUtils.h"
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <algorithm>

const std::string Administrator::DEFAULT_USERNAME = "root";
const std::string Administrator::DEFAULT_PASSWORD = "root";

Administrator::Administrator()
    : User(DEFAULT_USERNAME, DEFAULT_PASSWORD) {}

void Administrator::createTeacher() {
    std::string tno, tname, cname;

    SetColor(10);
    std::cout << "请输入新增教师的工号: ";
    SetColor(7);
    std::getline(std::cin, tno);

    auto it = std::find_if(teachers.begin(), teachers.end(),
        [&tno](const Teacher& teacher) { return teacher.getTno() == tno; });
    if (it != teachers.end()) {
        SetColor(12);
        std::cout << "工号已存在，教师创建失败!" << std::endl;
        SetColor(7);
        system("pause");
        system("cls");
        return;
    }

    SetColor(10);
    std::cout << "请输入新增教师的姓名: ";
    SetColor(7);
    std::getline(std::cin, tname);

    SetColor(10);
    std::cout << "请输入新增教师所受课程: ";
    SetColor(7);
    std::getline(std::cin, cname);

    createTeacher(tno, tname, cname);

    SetColor(10);
    std::cout << "教师账号创建成功!" << std::endl;
    SetColor(7);
    system("pause");
    system("cls");
}

void Administrator::createTeacher(const std::string& tno, const std::string& tname,
                                const std::string& cname) {
    Teacher teacher(tno, tname, cname, "123456");
    teachers.insert(teacher);
}

void Administrator::createStudent() {
    std::string sno, sname;

    SetColor(10);
    std::cout << "请输入新增学生的学号: ";
    SetColor(7);
    std::getline(std::cin, sno);

    if (findStudent(sno)) {
        SetColor(12);
        std::cout << "学号已存在，学生创建失败!" << std::endl;
        SetColor(7);
        system("pause");
        system("cls");
        return;
    }

    SetColor(10);
    std::cout << "请输入新增学生的姓名: ";
    SetColor(7);
    std::getline(std::cin, sname);

    Student student(sno, sname, "123456");
    students.insert(student);

    SetColor(10);
    std::cout << "学生账号创建成功!" << std::endl;
    SetColor(7);
    system("pause");
    system("cls");
}

std::shared_ptr<Student> Administrator::findStudent(const std::string& sno) const {
    auto it = std::find_if(students.begin(), students.end(),
        [&sno](const Student& s) { return s.getSno() == sno; });

    return (it != students.end()) ? std::make_shared<Student>(*it) : nullptr;
}

void Administrator::showAllStudents() const {
    SetConsoleOutputCP(65001);

    SetColor(14);
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "学号\t\t姓名" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    SetColor(10);
    for (const auto& student : students) {
        std::cout << student.getSno() << "\t"
                  << student.getSname() << std::endl;
    }

    SetColor(14);
    std::cout << "----------------------------------------------" << std::endl;
    SetColor(7);

    std::cout << "\n请按任意键继续...";
    system("pause > nul");
    system("cls");
}

void Administrator::showAllTeachers() const {
    SetConsoleOutputCP(65001);

    SetColor(14);
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "工号\t\t姓名\t\t所授课程" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    SetColor(10);
    for (const auto& teacher : teachers) {
        std::cout << teacher.getTno() << "\t"
                  << teacher.getTname() << "\t\t"
                  << teacher.getCname() << std::endl;
    }

    SetColor(14);
    std::cout << "----------------------------------------------" << std::endl;
    SetColor(7);

    system("pause");
    system("cls");
}

void Administrator::changePassword() {
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

const std::set<Teacher>& Administrator::getTeachers() const {
    return teachers;
}

const std::set<Student>& Administrator::getAllStudents() const {
    return students;
}

std::set<Student>& Administrator::getAllStudents() {
    return students;
}

void Administrator::showMenu() const {
    SetColor(14);
    std::cout << "************** 管理员菜单 ***************" << std::endl;
    std::cout << "**           1. 创建教师账号           **" << std::endl;
    std::cout << "**           2. 创建学生账号           **" << std::endl;
    std::cout << "**           3. 查看所有教师           **" << std::endl;
    std::cout << "**           4. 查看所有学生           **" << std::endl;
    std::cout << "**           5. 修改密码               **" << std::endl;
    std::cout << "**           6. 退出登录               **" << std::endl;
    std::cout << "*****************************************" << std::endl;
    SetColor(7);
}

bool Administrator::updateTeacher(const Teacher& teacher) {
    auto it = teachers.find(teacher);
    if (it != teachers.end()) {
        teachers.erase(it);
        teachers.insert(teacher);
        return true;
    }
    return false;
}

bool Administrator::updateStudent(const Student& student) {
    auto it = students.find(student);
    if (it != students.end()) {
        students.erase(it);
        students.insert(student);
        return true;
    }
    return false;
}