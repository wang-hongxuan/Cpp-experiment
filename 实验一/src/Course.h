
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
    int GetCno() const;
    bool setScore(int);
    //void setSno(std::string);
    std::string getCourseName() const;
    int getScore() const;
};


#endif //COURSE_H
