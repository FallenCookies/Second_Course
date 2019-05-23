#include <iostream>
#include "phone_number.h"
#include "test_runner.h"

int main() {
    PhoneNumber p("+5-5-");
    cout<<p.GetInternationalNumber();
    return 0;
}