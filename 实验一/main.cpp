#include <iostream>
#include<windows.h>
#include <string>
#include <array>
#include <vector>
#include <memory>
#include <algorithm>
#include "src/Student.h"
#include "src/Course.h"
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.


void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    std::vector<std::unique_ptr<Student>> students;
    std::string choice;

    while (true) {
        //Sleep(100000);
        //system("cls");
        SetColor(7);
        std::cout << "********欢迎使用学生成绩管理查询系统！********" << std::endl;
        std::cout << "**               1. 学 生                   **" << std::endl;
        std::cout << "**               2. 教 师                   **" << std::endl;
        std::cout << "**               3. 退 出                   **" << std::endl;
        std::cout << "**********************************************" << std::endl;

        SetColor(1);
        std::cout << "请选择操作(1 or 2 or 3)：" ;
        std::cin >> choice;

        if (choice == "2") {
            SetColor(6);
            std::cout << "你是老师" << std::endl;
            std::cout<<std::endl;
            std::string sno, sname;
            SetColor(2);
            std::cout << "学号：";
            SetColor(7);
            std::cin >> sno;
            SetColor(2);
            std::cout << "姓名：";
            SetColor(7);
            std::cin >> sname;


            auto it = std::find_if(students.begin(), students.end(),
            [&sno](const std::unique_ptr<Student>& stu) {
                    return stu->getSno() == sno;
                });//指定的迭代器范围内查找第一个满足特定条件的元素

            if (it != students.end()) {
                SetColor(3);
                std::cout << "该学生已存在，将更新成绩..." << std::endl;
                SetColor(7);

                for (int i = 0; i < 2; ++i) {
                    auto& course = (*it)->getCourse(i);
                    int score;
                    while (true) {
                        SetColor(2);
                        std::cout << course.GetCno() << " " << course.getCourseName() << " : ";
                        SetColor(7);
                        std::cin >> score;
                        if (course.setScore(score)) {
                            break;
                        }
                        else {
                            std::cout << "输入数据有误，请重新输入！" << std::endl;
                        }
                    }
                }
            }
            else {

                auto stu = std::unique_ptr<Student>(new Student(sno, sname));

                Course c1(62698, "C++程序设计总评成绩");
                Course c2(62540, "数据库与应用A总评成绩");

                // C++11初始化列表
                std::array<Course, 2> courses = {c1, c2};
                stu->setAllCourses(courses);

                // 录入成绩
                for (int i = 0; i < 2; ++i) {
                    auto& course = stu->getCourse(i);
                    int score;
                    while (true) {
                        SetColor(2);
                        std::cout << course.GetCno() << " " << course.getCourseName() << " : ";
                        SetColor(7);
                        std::cin >> score;
                        if (course.setScore(score)) {
                            break;
                        } else {
                            SetColor(4);
                            std::cout << "输入数据有误，请重新输入！" << std::endl;
                            SetColor(2);
                        }
                    }
                }

                // C++11移动语义
                students.push_back(std::move(stu));
            }
            SetColor(3);
            std::cout << "学生成绩操作成功！请继续！" << std::endl;
            //Sleep(150);
            //system("cls");
            SetColor(7);
            std::cout << std::endl;
        }
        else if (choice == "1") {
            SetColor(6);
            std::cout<<"你是学生"<<std::endl;
            std::cout<<std::endl;
            std::string sno;
            SetColor(2);
            std::cout << "学号：";
            SetColor(7);
            std::cin >> sno;

            bool found = false;
            for (const auto& stu : students) {
                if (stu->getSno() == sno) {
                    auto courses = stu->getAllCourses();
                    SetColor(2);
                    std::cout <<"姓名：" ;
                    SetColor(7);
                    std::cout<< stu->getSname() << std::endl;
                    for (const auto& course : courses) {
                        SetColor(2);
                        std::cout << course.getCourseName() << "：" ;
                        SetColor(7);
                        std::cout<< course.getScore() << std::endl;
                    }
                    std::cout << "请继续"<<std::endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                SetColor(4);
                std::cout << "查询不到该学生。" << std::endl;
                SetColor(7);
            }
            //Sleep(150);
            //system("cls");
            std::cout << std::endl;
        } else if (choice == "3") {
            SetColor(6);
            std::cout << "程序已退出！" << std::endl;

            SetColor(7);
            break;
        } else {
            SetColor(4);
            std::cout << "无效选项，请重新输入。" << std::endl;
            std::cout << std::endl;
            SetColor(7);
        }

    }

    return 0;
}
// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.