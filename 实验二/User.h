//
// Created by wanghongxuan on 25-5-14.
//

#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

class User {
protected:
    std::string uname_;
    std::string pwd_;

public:
    User(const std::string& uname, const std::string& pwd);
    virtual ~User() = default;

    std::string getUsername() const;
    std::string getPassword() const;
    void setPassword(const std::string& newPwd);

    virtual bool login(const std::string& uname, const std::string& pwd) const;
    virtual void showMenu() const = 0;
    virtual void changePassword() {
        std::string newPassword;
        std::cout << "请输入新密码: ";
        std::cin >> newPassword;
        setPassword(newPassword);
        std::cout << "密码修改成功!" << std::endl;
    }
};

#endif // USER_H