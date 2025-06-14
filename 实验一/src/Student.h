//
// Created by wanghongxuan on 25-4-7.
//

#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <array>
#include "Course.h"

class Student {
private:
    std::string sno_;
    std::string sname_;
    std::array<Course, 2> courses_;
public:
    Student(std::string sno, std::string sname);
    std::string getSno() const;
    void setSno(std::string);
    std::string getSname() const;
    void setSname(std::string);
    std::array<Course, 2> getAllCourses() const;
    void setAllCourses(const std::array<Course, 2>&);//常量引用参数
    Course& getCourse(int index);

};

#endif //STUDENT_H
