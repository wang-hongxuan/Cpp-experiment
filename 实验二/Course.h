//
// Created by wanghongxuan on 25-5-14.
//


#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
private:
    int cno_;
    std::string cname_;
    int score_;

public:
    Course(int cno, std::string cname);
    Course();

    int getCno() const;
    bool setScore(int newScore);
    std::string getCourseName() const;
    int getScore() const;
};

#endif // COURSE_H