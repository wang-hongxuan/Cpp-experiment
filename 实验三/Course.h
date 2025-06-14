#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
private:
    std::string cname_;
    std::string teacherName_;  // 新增：记录教师姓名
    int score_;

public:
    Course(const std::string& cname, const std::string& teacherName);
    std::string getCourseName() const;
    std::string getTeacherName() const;
    bool setScore(int newScore);
    int getScore() const;
    bool operator<(const Course& other) const;
};

#endif // COURSE_H