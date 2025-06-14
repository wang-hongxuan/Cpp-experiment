#include "Course.h"

Course::Course(int cno, std::string cname)
    : cno_(cno), cname_(cname), score_(0) {}

Course::Course() : cno_(0), cname_(""), score_(-1) {}

int Course::getCno() const {
    return cno_;
}

bool Course::setScore(int newScore) {
    if (newScore >= 0 && newScore <= 100) {
        score_ = newScore;
        return true;
    }
    return false;
}

std::string Course::getCourseName() const {
    return cname_;
}

int Course::getScore() const {
    return score_;
}