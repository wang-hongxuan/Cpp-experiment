//
// Created by wanghongxuan on 25-5-14.
//

#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "User.h"
#include "Teacher.h"
#include "StudentDB.h"
#include <vector>
#include <memory>

class Administrator : public User {
private:
    static const std::string DEFAULT_USERNAME;
    static const std::string DEFAULT_PASSWORD;
    std::vector<std::shared_ptr<Teacher>> teachers;
    std::shared_ptr<StudentDB> studentDB;

public:
    Administrator(std::shared_ptr<StudentDB> db);
    void createTeacher();
    void createTeacher(const std::string& tno, const std::string& tname,
                      const std::string& cname, const std::string& username,
                      const std::string& password);
    void showAllTeachers() const;
    void showMenu() const override;
    void changePassword() override;
    const std::vector<std::shared_ptr<Teacher>>& getTeachers() const;
};

#endif // ADMINISTRATOR_H
