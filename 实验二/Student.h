//
// Created by wanghongxuan on 25-5-14.
//

#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "Course.h"
#include <vector>

class Student : public User {
private:
    std::string sno_;
    std::string sname_;
    std::vector<Course> courses_;

public:
    Student(const std::string& sno, const std::string& sname);

    std::string getSno() const;
    std::string getSname() const;
    void setSname(const std::string& name);

    void addCourse(const Course& newCourse);
    const std::vector<Course>& getAllCourses() const;
    bool hasCourse(const std::string& courseName) const;
    bool updateCourseScore(const std::string& courseName, int newScore);

    void showMenu() const override;
    void changePassword();
    void showScores() const;
};

#endif // STUDENT_H

