//
// Created by wanghongxuan on 25-5-14.
//

#ifndef TEACHER_H
#define TEACHER_H

#include "User.h"
#include "Student.h"
#include "StudentDB.h"
#include <vector>
#include <memory>

class Teacher : public User {
private:
    std::string tno_;
    std::string tname_;
    std::string cname_;
    std::shared_ptr<StudentDB> studentDB;

public:
    Teacher(const std::string& tno, const std::string& tname,
            const std::string& cname, const std::string& username,
            const std::string& password, std::shared_ptr<StudentDB> db);

    std::string getTno() const;
    std::string getTname() const;
    std::string getCname() const;

    void inputScore(const std::string& sno, const std::string& sname, int score);
    void showAllStudents() const;
    void showMenu() const override;
    void changePassword();
};

#endif // TEACHER_H