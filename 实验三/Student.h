#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "Course.h"
#include <set>
#include <memory>

class Student : public User {
private:
    std::string sno_;
    std::string sname_;
    std::set<Course> courses_;

public:
    Student(const std::string& sno, const std::string& sname, const std::string& password);

    std::string getSno() const;
    std::string getSname() const;
    void setSname(const std::string& name);

    bool operator<(const Student& other) const;

    void addCourse(const Course& newCourse);
    const std::set<Course>& getAllCourses() const;
    std::set<Course>& getAllCourses();  // 新增非 const 版本
    bool hasCourse(const std::string& courseName) const;
    bool updateCourseScore(const std::string& cname, const std::string& teacherName, int newScore);

    void showMenu() const override;
    void changePassword() override;
    void showScores() const;
};

#endif // STUDENT_H
