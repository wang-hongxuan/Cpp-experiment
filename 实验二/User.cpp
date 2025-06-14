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
    uname_ = newPwd;
}

bool User::login(const std::string& uname, const std::string& pwd) const {
    return (uname_ == uname && pwd_ == pwd);
}

