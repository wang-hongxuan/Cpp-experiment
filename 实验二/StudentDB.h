//
// Created by wanghongxuan on 25-5-20.
//

#ifndef STUDENTDB_H
#define STUDENTDB_H

#include "Student.h"
#include <vector>
#include <memory>
#include <mutex>

class StudentDB {
private:
    std::vector<std::shared_ptr<Student>> allStudents;
    mutable std::mutex mtx;

public:
    void addStudent(const std::shared_ptr<Student>& student);
    std::shared_ptr<Student> findStudent(const std::string& sno) const;
    const std::vector<std::shared_ptr<Student>>& getAllStudents() const;
};

#endif // STUDENTDB_H