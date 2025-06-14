#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include "User.h"
#include "Administrator.h"
#include "Teacher.h"
#include "Student.h"
#include "StudentDB.h"
#include "ConsoleUtils.h"

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void adminOperations(shared_ptr<Administrator> admin) {
    int choice;
    while (true) {
        admin->showMenu();
        SetColor(7);
        cout << "请选择操作: ";
        cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            admin->createTeacher();
        } else if (choice == 2) {
            admin->showAllTeachers();
        } else if (choice == 3) {
            admin->changePassword();
        } else if (choice == 4) {
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

void teacherOperations(shared_ptr<Teacher> teacher) {
    int choice;
    while (true) {
        teacher->showMenu();
        SetColor(7);
        cout << "请选择操作: ";
        SetColor(7);
        cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            string sno, sname;
            int score;

            SetColor(10);
            cout << "学号: ";
            SetColor(7);
            getline(cin, sno);

            SetColor(10);
            cout << "姓名: ";
            SetColor(7);
            getline(cin, sname);

            while (true) {
                SetColor(10);
                cout << "成绩: ";
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

            teacher->inputScore(sno, sname, score);
        } else if (choice == 2) {
            teacher->showAllStudents();
        } else if (choice == 3) {
            teacher->changePassword();
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

void studentOperations(shared_ptr<Student> student) {
    int choice;
    while (true) {
        student->showMenu();
        SetColor(7);
        cout << "请选择操作: ";
        SetColor(7);
        cin >> choice;
        clearInputBuffer();

        if (choice == 1) {
            student->showScores();
        } else if (choice == 2) {
            student->changePassword();
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

void teacherLogin(shared_ptr<Administrator> admin) {
    string username, password;

    SetColor(10);
    cout << "请输入用户名: ";
    SetColor(7);
    getline(cin, username);

    SetColor(10);
    cout << "请输入密码: ";
    SetColor(7);
    getline(cin, password);

    bool loggedIn = false;
    for (auto& teacher : admin->getTeachers()) {
        if (teacher->login(username, password)) {
            SetColor(10);
            cout << "登录成功!" << endl;
            SetColor(7);
            teacherOperations(teacher);
            loggedIn = true;
            break;
        }
    }

    if (!loggedIn) {
        SetColor(12);
        cout << "用户名或密码错误!" << endl;
        SetColor(7);
        system("pause");
    }
}

void studentLogin(shared_ptr<StudentDB> studentDB) {
    string username, password;

    SetColor(10);
    cout << "请输入用户名: ";
    SetColor(7);
    getline(cin, username);

    SetColor(10);
    cout << "请输入密码: ";
    SetColor(7);
    getline(cin, password);

    auto student = studentDB->findStudent(username);
    if (student && student->login(username, password)) {
        SetColor(10);
        cout << "登录成功!" << endl;
        SetColor(7);
        studentOperations(student);
    } else {
        SetColor(12);
        cout << "用户名或密码错误!" << endl;
        SetColor(7);
        system("pause");
    }
}

int main() {
    // 设置控制台编码为UTF-8
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // 创建全局学生数据库
    auto studentDB = make_shared<StudentDB>();

    // 创建管理员
    auto admin = make_shared<Administrator>(studentDB);

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
            studentLogin(studentDB);
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

            if (admin->login(username, password)) {
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