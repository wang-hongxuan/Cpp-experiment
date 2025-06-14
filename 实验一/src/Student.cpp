//
// Created by wanghongxuan on 25-4-7.
//

#include "Student.h"


Student::Student(std::string sno, std::string sname) : sno_(sno), sname_(sname){}

std::string Student::getSno() const {
    return sno_;
}

void Student::setSno(std::string newSno) {
    sno_ = newSno;
}

std::string Student::getSname() const {
    return sname_;
}

void Student::setSname(std::string newSname) {
    sname_ = newSname;
}

std::array<Course, 2> Student::getAllCourses() const {
    return courses_;
}

void Student::setAllCourses(const std::array<Course, 2>& newCourses) {
    courses_ = newCourses;
}
Course& Student::getCourse(int index) {
    if (index >= 0 && index < courses_.size()) {
        return courses_[index];
    }
    throw "ERROR";
}
