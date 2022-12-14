//
// Created by vshug on 12.12.2022.
//

#ifndef DATA
#define DATA

#include <map>
#include <iostream>
#include "user.h"

class User;

class Data{
private:
    std::map<std::string , User*>* users;

    std::size_t createId(const std::string& email) const;

    bool find(const std::string& email) const;

public:
    Data(){
        users = new std::map<std::string , User*>;
    }
    ~Data(){
        users->clear();
        users = nullptr;
    }

    void addUser(const std::string email, const std::string password, const std::string Name, const std::string Surname);

    void printUserInfo(const std::string& email) const;

    void registration();

};


//////------------------------------IMPLEMENTATION--------------------------//////

void Data::addUser(const std::string email, const std::string password, const std::string Name, const std::string Surname) {
    User* newUser = new User(email, password, Name, Surname);
    users->insert(std::pair<std::string, User*>(email, newUser));
}

void Data::registration() {
    std::cout << "Write your Name , please: \n";
    std::string nName;
    std::getline(std::cin, nName);

    std::cout << "\nWrite your Surname , please: \n";
    std::string nSurName;
    std::getline(std::cin, nSurName);

    bool flag = true;
    std::string nEmail;
    while(flag){
        std::string temp;
        std::cout << "\nCreate a new email , please, do not write @sth.com at the end: \n";
        std::getline(std::cin, temp);
        if(temp.find('@') != std::string::npos){
            continue;
        }
        nEmail = temp + "@sth.com";
        std::cout << nEmail << std::endl;
        if(find(nEmail)){
            std::cout << "Sorry, this email address has already been taken, chose another one, please\n";
        }else{
            flag = false;
        }

    }

    flag = true;
    std::string nPass;
    std::cout << "Create a password(Password can't contain spaces and can't be smaller than 8 letters): \n";
    while(flag){
        std::getline(std::cin, nPass);
        if(nPass.find(' ') != std::string::npos || nPass.length() < 8){
            std::cout << "Something went wrong , try again: \n";
        }
        else{
            flag = false;
        }
    }
    addUser(nEmail, nPass, nName, nSurName);
}

std::size_t Data::createId(const std::string &email) const {
    std::hash<std::string> sHash;

    std::size_t id = sHash(email);

    return id;
}

bool Data::find(const std::string& email) const {
    for(auto it = users->begin(); it != users->end(); ++it){
        if(it->first == email){
            return true;
        }
    }
    return false;

}

void Data::printUserInfo(const std::string& email) const {
    if(!find(email)){
        std::cout << "There is no such a User, with a given email" << std::endl;
        return;
    }
    auto it = users->find(email);

    std::cout << *it->second;
}

#endif
