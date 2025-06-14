#include <iostream>
#include <windows.h>
#include <string>
#include <memory>
#include <limits>
#include <algorithm>
#include <vector>
#include "User.h"
#include "Administrator.h"
#include "Teacher.h"
#include "Student.h"
#include "ConsoleUtils.h"

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void adminOperations(Administrator& admin) {
    int choice;
    while (true) {
        admin.showMenu();
        SetColor(7);
        cout << "请选择操作: ";
        cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            admin.createTeacher();
        } else if (choice == 2) {
            admin.createStudent();
        } else if (choice == 3) {
            admin.showAllTeachers();
        } else if (choice == 4) {
            admin.showAllStudents();
        } else if (choice == 5) {
            admin.changePassword();
        } else if (choice == 6) {
            system("pause");
            system("cls");
            break;
        } else {
            SetColor(12);
            cout << "无效选项!" << endl;
            SetColor(7);
            system("pause");
            system("cls");
        }
    }
}

void teacherOperations(Teacher& teacher, Administrator& admin) {
    int choice;
    while (true) {
        teacher.showMenu();
        SetColor(7);
        cout << "请选择操作: ";
        cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            auto& students = admin.getAllStudents();
            if (students.empty()) {
                SetColor(12);
                cout << "没有学生记录!" << endl;
                SetColor(7);
                system("pause");
                system("cls");
                continue;
            }

            SetColor(14);
            cout << "******** 学生列表 ********" << endl;

            // 创建临时vector存储学生指针以便修改
            vector<Student*> studentPtrs;
            for (auto& student : students) {
                studentPtrs.push_back(const_cast<Student*>(&student));
            }

            for (auto studentPtr : studentPtrs) {
                SetColor(10);
                cout << "学号: " << studentPtr->getSno()
                     << ", 姓名: " << studentPtr->getSname() << endl;

                int score;
                while (true) {
                    SetColor(10);
                    cout << "请输入" << studentPtr->getSname() << "的成绩: ";
                    SetColor(7);
                    cin >> score;
                    if (score >= 0 && score <= 100) {
                        break;
                    }
                    SetColor(12);
                    cout << "成绩必须在0-100之间!" << endl;
                    SetColor(7);
                    clearInputBuffer();
                }
                clearInputBuffer();

                // 直接修改原始学生对象
                teacher.inputScore(*studentPtr, score);

                // 更新set中的学生信息
                Student modifiedStudent = *studentPtr;
                students.erase(*studentPtr);
                students.insert(modifiedStudent);
            }

            SetColor(10);
            cout << "所有学生成绩录入完成!" << endl;
            SetColor(7);
            system("pause");
            system("cls");
        } else if (choice == 2) {
            teacher.showAllStudents(admin.getAllStudents());
        } else if (choice == 3) {
            teacher.changePassword();
        } else if (choice == 4) {
            break;
        } else {
            SetColor(12);
            cout << "无效选项!" << endl;
            SetColor(7);
            system("pause");
            system("cls");
        }
    }
}

void studentOperations(Student& student) {
    int choice;
    while (true) {
        student.showMenu();
        SetColor(7);
        cout << "请选择操作: ";
        cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            student.showScores();
        } else if (choice == 2) {
            student.changePassword();
        } else if (choice == 3) {
            break;
        } else {
            SetColor(12);
            cout << "无效选项!" << endl;
            SetColor(7);
            system("pause");
            system("cls");
        }
    }
}

void teacherLogin(Administrator& admin) {
    string tno, password;

    SetColor(10);
    cout << "请输入用户名: ";
    SetColor(7);
    getline(cin, tno);

    // 使用指针而不是对象
    const Teacher* foundTeacher = nullptr;
    for (const auto& teacher : admin.getTeachers()) {
        if (teacher.getUsername() == tno) {
            foundTeacher = &teacher;
            break;
        }
    }

    if (!foundTeacher) {
        SetColor(12);
        cout << "用户名错误!" << endl;
        SetColor(7);
        system("pause");
        return;
    }

    SetColor(10);
    cout << "请输入密码: ";
    SetColor(7);
    getline(cin, password);

    if (foundTeacher->login(tno, password)) {
        SetColor(10);
        cout << "登录成功!" << endl;
        SetColor(7);

        // 使用 const_cast 获取可修改的引用
        Teacher& teacherRef = const_cast<Teacher&>(*foundTeacher);
        teacherOperations(teacherRef, admin);

        // 更新教师信息
        admin.updateTeacher(teacherRef);
    } else {
        SetColor(12);
        cout << "密码错误!" << endl;
        SetColor(7);
        system("pause");
    }
}

void studentLogin(Administrator& admin) {
    string sno, password;

    SetColor(10);
    cout << "请输入用户名: ";
    SetColor(7);
    getline(cin, sno);

    // 使用指针而不是迭代器
    const Student* foundStudent = nullptr;
    for (const auto& student : admin.getAllStudents()) {
        if (student.getUsername() == sno) {
            foundStudent = &student;
            break;
        }
    }

    if (!foundStudent) {
        SetColor(12);
        cout << "用户名不存在!" << endl;
        SetColor(7);
        system("pause");
        return;
    }

    SetColor(10);
    cout << "请输入密码: ";
    SetColor(7);
    getline(cin, password);

    if (foundStudent->login(sno, password)) {
        SetColor(10);
        cout << "登录成功!" << endl;
        SetColor(7);

        // 使用 const_cast 获取可修改的引用
        Student& studentRef = const_cast<Student&>(*foundStudent);
        studentOperations(studentRef);

        // 更新学生信息
        admin.updateStudent(studentRef);
    } else {
        SetColor(12);
        cout << "密码错误!" << endl;
        SetColor(7);
        system("pause");
    }
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Administrator admin;

    while (true) {
        system("cls");
        SetColor(14);
        cout << "*******欢迎使用学生成绩查询系统！********" << endl;
        cout << "**              1. 学生                **" << endl;
        cout << "**              2. 教师                **" << endl;
        cout << "**              3. 管理员              **" << endl;
        cout << "**              4. 退出                **" << endl;
        cout << "*****************************************" << endl;

        int choice;
        SetColor(7);
        cout << "请选择操作: ";
        cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            studentLogin(admin);
        }
        else if (choice == 2) {
            teacherLogin(admin);
        }
        else if (choice == 3) {
            string username, password;

            SetColor(10);
            cout << "请输入用户名: ";
            SetColor(7);
            getline(cin, username);
            SetColor(10);
            cout << "请输入密码: ";
            SetColor(7);
            getline(cin, password);

            if (admin.login(username, password)) {
                SetColor(10);
                cout << "登录成功!" << endl;
                SetColor(7);
                adminOperations(admin);
            } else {
                SetColor(12);
                cout << "用户名或密码错误!" << endl;
                SetColor(7);
                system("pause");
            }
        }
        else if (choice == 4) {
            SetColor(14);
            cout << "感谢使用，再见!" << endl;
            SetColor(7);
            break;
        }
        else {
            SetColor(12);
            cout << "无效选项!" << endl;
            SetColor(7);
            system("pause");
        }
    }
    return 0;
}