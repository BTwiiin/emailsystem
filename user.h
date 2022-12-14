#ifndef USER
#define USER

#include <iostream>
#include <string>
#include <ostream>



class User{
private:

    std::string email;
    std::string password;
    std::string id;
    std::string name;
    std::string surname;
    int registered = 0;

    std::size_t createId(const std::string& email) const;

public:

    User(const std::string email, const std::string password, const std::string Name, const std::string Surname){
        this->email = email;
        this->name = Name;
        this->surname = Surname;
        this->password = password;
        this->id = createId(email);

    }


    ///---------------GETTERS---------------///
    std::string getName() const{
        return name;
    }
    std::string getSurname() const{
        return surname;
    }
    std::string getEmail() const{
        return email;
    }

    std::string getPass() const{
        return password;
    }
    

    friend std::ostream& operator<<(std::ostream&, const User&);

};

std::size_t User::createId(const std::string &email) const {
    std::hash<std::string> sHash;

    std::size_t id = sHash(email);

    return id;
}

std::ostream& operator<<(std::ostream& os, const User& user){
    os << "User Name: " << user.name << std::endl
    << "User Surname: " << user.surname << std::endl
    << "User email: " << user.email << std::endl
    << "User ID: " << user.id << std::endl;
    return os;
}

#endif

