#include "User.h"

User::User(const std::string& uname, const std::string& pwd)
    : uname_(uname), pwd_(pwd) {}

std::string User::getUsername() const {
    return uname_;
}

std::string User::getPassword() const {
    return pwd_;
}

void User::setPassword(const std::string& newPwd) {
    pwd_ = newPwd;
}

bool User::login(const std::string& uname, const std::string& pwd) const {
    return (uname_ == uname && pwd_ == pwd);
}

void User::changePassword() {
    std::string newPassword;
    std::cout << "请输入新密码: ";
    std::cin >> newPassword;
    setPassword(newPassword);
    std::cout << "密码修改成功!" << std::endl;
}
