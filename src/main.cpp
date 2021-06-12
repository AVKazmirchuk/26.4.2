#include "../include/header.h"

int main()
{
    Telephone* phone = new Telephone;

    phone->control();

    delete phone;
}