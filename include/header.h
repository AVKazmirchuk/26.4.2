#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <map>


class PhoneNumber
{
private:

    static const int baseSize = 10;
    static const int fullSize = 12;
    inline static const std::string prefix = "+7";

    static auto searchNotDigits(std::string::const_iterator&& cbegin, std::string::const_iterator&& cend);

public:

    static bool checkFormat(std::string& number);
};

class AddressBook
{
private:

    //Номер, имя

    std::map<std::string, std::string> addressBook;

public:

    void output();


    void addContact(std::string& number, std::string& name);

    std::string getNumber(std::string& name);

    std::string getName(std::string& number);
};

class Telephone
{
private:

    std::string number, name;
    AddressBook* addresses = new AddressBook;

    void add();

    void requestNumberOrName();

    void call();

    void sms();

    void exit();

public:

    void control();
};