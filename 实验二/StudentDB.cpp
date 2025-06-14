#include "StudentDB.h"
#include <algorithm>
void StudentDB::addStudent(const std::shared_ptr<Student>& student) {
    std::lock_guard<std::mutex> lock(mtx);
    allStudents.push_back(student);
}

std::shared_ptr<Student> StudentDB::findStudent(const std::string& sno) const {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = std::find_if(allStudents.begin(), allStudents.end(),
        [&sno](const std::shared_ptr<Student>& s) {
            return s->getSno() == sno;
        });
    
    return (it != allStudents.end()) ? *it : nullptr;
}

const std::vector<std::shared_ptr<Student>>& StudentDB::getAllStudents() const {
    std::lock_guard<std::mutex> lock(mtx);
    return allStudents;
}