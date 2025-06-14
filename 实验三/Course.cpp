#include "Course.h"

Course::Course(const std::string& cname, const std::string& teacherName)
    : cname_(cname), teacherName_(teacherName), score_(0) {}

std::string Course::getCourseName() const {
    return cname_;
}

std::string Course::getTeacherName() const {
    return teacherName_;
}

bool Course::setScore(int newScore) {
    if (newScore >= 0 && newScore <= 100) {
        score_ = newScore;
        return true;
    }
    return false;
}

int Course::getScore() const {
    return score_;
}

bool Course::operator<(const Course& other) const {
    if (cname_ != other.cname_)
        return cname_ < other.cname_;
    return teacherName_ < other.teacherName_;
}