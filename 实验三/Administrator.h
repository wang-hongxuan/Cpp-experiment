#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "User.h"
#include "Teacher.h"
#include "Student.h"
#include <set>
#include <memory>

class Administrator : public User {
private:
    static const std::string DEFAULT_USERNAME;
    static const std::string DEFAULT_PASSWORD;
    std::set<Teacher> teachers;
    std::set<Student> students;

public:
    Administrator();
    void createTeacher();
    void createTeacher(const std::string& tno, const std::string& tname,
                     const std::string& cname);
    void createStudent();
    void showAllTeachers() const;
    void showAllStudents() const;
    void showMenu() const override;
    void changePassword() override;
    const std::set<Teacher>& getTeachers() const;
    std::shared_ptr<Student> findStudent(const std::string& sno) const;
    std::shared_ptr<Student> getAllStudents();
    const std::set<Student>& getAllStudents() const;

    bool updateTeacher(const Teacher& teacher);
    bool updateStudent(const Student& student);
};

#endif // ADMINISTRATOR_H