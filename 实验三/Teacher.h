#ifndef TEACHER_H
#define TEACHER_H
#include "User.h"
#include "Student.h"
#include <set>

class Teacher : public User {
private:
    std::string tno_;
    std::string tname_;
    std::string cname_;

public:
    Teacher(const std::string& tno, const std::string& tname,
            const std::string& cname, const std::string& password);

    std::string getTno() const;
    std::string getTname() const;
    std::string getCname() const;
    bool operator<(const Teacher& other) const;

    void inputScore(Student& student, int score);
    void showAllStudents(const std::set<Student>& students) const;
    void showMenu() const override;
    void changePassword() override;
};

#endif // TEACHER_H