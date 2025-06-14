#include "Administrator.h"
#include "ConsoleUtils.h"
#include <iostream>
#include <windows.h>
#include <limits>

const std::string Administrator::DEFAULT_USERNAME = "root";
const std::string Administrator::DEFAULT_PASSWORD = "root";

Administrator::Administrator(std::shared_ptr<StudentDB> db)
    : User(DEFAULT_USERNAME, DEFAULT_PASSWORD), studentDB(db) {}

void Administrator::createTeacher() {
    std::string tno, tname, cname;
    SetColor(10);
    std::cout << "请输入新增教师的工号: ";
    SetColor(7);
    std::getline(std::cin, tno);

    SetColor(10);
    std::cout << "请输入新增教师的姓名: ";
    SetColor(7);
    std::getline(std::cin, tname);

    SetColor(10);
    std::cout << "请输入新增教师所受课程: ";
    SetColor(7);
    std::getline(std::cin, cname);

    auto teacher = std::make_shared<Teacher>(tno, tname, cname, tno, "123456", studentDB);
    teachers.push_back(teacher);

    SetColor(10);
    std::cout << "教师账号创建成功!" << std::endl;
    SetColor(7);
}

void Administrator::createTeacher(const std::string& tno, const std::string& tname,
                                const std::string& cname, const std::string& username,
                                const std::string& password) {
    auto teacher = std::make_shared<Teacher>(tno, tname, cname, username, password, studentDB);
    teachers.push_back(teacher);
}

void Administrator::showAllTeachers() const {
    SetColor(11);
    std::cout << "*************** 教师列表 ***************" << std::endl;
    for (const auto& teacher : teachers) {
        SetColor(10);
        std::cout << "工号: " << teacher->getTno()
                  << ", 姓名: " << teacher->getTname()
                  << ", 课程: " << teacher->getCname() << std::endl;
    }
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

void Administrator::showMenu() const {
    SetColor(14);
    std::cout << "************** 管理员菜单 ***************" << std::endl;
    std::cout << "**           1. 创建教师账号           **" << std::endl;
    std::cout << "**           2. 查看所有教师           **" << std::endl;
    std::cout << "**           3. 修改密码               **" << std::endl;
    std::cout << "**           4. 退出登录               **" << std::endl;
    std::cout << "*****************************************" << std::endl;
    SetColor(7);
}
const std::vector<std::shared_ptr<Teacher>>& Administrator::getTeachers() const {
    return teachers;
}