#include "../include/header.h"

auto PhoneNumber::searchNotDigits(std::string::const_iterator&& cbegin, std::string::const_iterator&& cend)
{
    return find_if(cbegin, cend, [](auto symbol) {return symbol < '0' || symbol > '9'; });
}

bool PhoneNumber::checkFormat(std::string& number)
{
    if (number.size() == fullSize)
    {
        auto position = search(number.cbegin(), number.cend(),
                               prefix.cbegin(), prefix.cend());

        if (position - number.cbegin() == 0)
        {
            if (searchNotDigits(number.cbegin() + prefix.size(), number.cend()) == number.cend()) return true;
        }

        return false;
    }
    else if (number.size() == baseSize)
    {
        if (searchNotDigits(number.cbegin(), number.cend()) == number.cend())
        {
            number.insert(number.cbegin(), prefix.cbegin(), prefix.cend());
            return true;
        }
    }

    return false;
}


void AddressBook::output()
{
    std::cout << "\nAddress Book\n";
    std::cout << "------------\n";

    for (const auto& contact : addressBook)

        std::cout << contact.first << ' ' << contact.second << '\n';
}

void AddressBook::addContact(std::string& number, std::string& name)
{
    addressBook.emplace(number, name);
}

std::string AddressBook::getNumber(std::string& name)
{
    auto position = find_if(addressBook.cbegin(), addressBook.cend(),
                            [&](auto& contact) {return contact.second == name; });

    if (position != addressBook.cend()) return (*position).first;

    return {};
}

std::string AddressBook::getName(std::string& number)
{
    auto position = addressBook.find(number);

    if (position != addressBook.cend()) return (*position).second;

    return {};
}

void Telephone::add()
{
    while (true)
    {
        std::cout << "Number-> ";
        std::cin >> number;
        if (PhoneNumber::checkFormat(number)) break;
        else
        {
            std::cout << "Invalid format!\n";
            continue;
        }
    }

    std::cout << "Name-> ";
    std::cin >> name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    addresses->addContact(number, name);
}

void Telephone::requestNumberOrName()
{
    while (true)
    {
        std::cout << "Number or name-> ";
        std::string tmp;
        std::cin >> tmp;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        //Если в контактах нет имени, значит введен номер

        number = addresses->getNumber(tmp);
        if (!number.empty())
        {
            name = tmp;
            break;
        }
        else if (PhoneNumber::checkFormat(tmp))
        {
            number = tmp;
            name = addresses->getName(tmp);
            break;
        }

        std::cout << "Invalid data!\n";
    }
}

void Telephone::call()
{
    requestNumberOrName();

    std::cout << "CALL: " << number << ' ' << name << "\n\n";
}

void Telephone::sms()
{
    requestNumberOrName();

    std::cout << "Message-> ";
    std::string message;
    std::getline(std::cin, message);

    std::cout << "The message \"" << message << "\" was sent to " << number << ' ' << name << "\n\n";
}

void Telephone::exit()
{
    delete addresses;
}

void Telephone::control()
{
    std::string command;

    while (true)
    {
        addresses->output();

        std::cout << "\nCommand: add, call, sms, exit: ";

        std::getline(std::cin, command);

        if (command == "add") add();
        else if (command == "call") call();
        else if (command == "sms") sms();
        else if (command == "exit")
        {
            exit();
            return;
        }
        else std::cout << "Invalid command!\n";
    }
}