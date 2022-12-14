//
// Created by vshug on 12.12.2022.
//

#ifndef DATA
#define DATA

#include <map>
#include <iostream>
#include "user.h"
#include <conio.h>

class User;

class Data{
private:
    std::map<std::string , User*>* users;

    std::size_t createId(const std::string& email) const;

    bool find_bool(const std::string& email) const;

    User* getUser(const std::string& email) const;

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
    void login() const;

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
        if(find_bool(nEmail)){
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

void Data::login() const {
    std::string loginEmail;
    bool flag = true;
    int statusint = 0;
    while(flag){
        if(statusint >= 1){
            std::cout << "Press Escape to exit or Enter to cont.\n";
            char status;
            status = getch();
            if(status == 27)
                return;
        }
        std::cout << "Email: ";
        
        std::getline(std::cin, loginEmail);
        std::cout << std::endl;
    
        if(!find_bool(loginEmail)){
            std::cout << "Invalid email, try again.\n";
            statusint++;
        }
        else{
            flag = false;
        }
    }
    std::string loginPassword;
    flag = true;
    statusint = 0;
    while(flag){
        if(statusint >= 1){
            std::cout << "Press Escape to exit or Enter to cont.\n";
            char status;
            status = getch();
            if(status == 27)
                return;
        }
        std::cout << "Password: ";
        std::getline(std::cin, loginPassword);
        std::cout << std::endl;
    
        if(getUser(loginEmail)->getPass() != loginPassword){
            std::cout << "Invalid password, try again.\n";
            statusint++;
        }
        else{
            flag = false;
        }
    }
}

std::size_t Data::createId(const std::string &email) const {
    std::hash<std::string> sHash;

    std::size_t id = sHash(email);

    return id;
}

bool Data::find_bool(const std::string& email) const {
    for(auto it = users->begin(); it != users->end(); ++it){
        if(it->first == email){
            return true;
        }
    }
    return false;

}

User* Data::getUser(const std::string& email) const{
    if(!find_bool(email)){
        std::cout << "There is no such a User, with a given email" << std::endl;
        return nullptr;
    }
    auto it = users->find(email);
    return it->second;
}

void Data::printUserInfo(const std::string& email) const {
    if(!find_bool(email)){
        std::cout << "There is no such a User, with a given email" << std::endl;
        return;
    }
    auto it = users->find(email);

    std::cout << *it->second;
}

#endif
