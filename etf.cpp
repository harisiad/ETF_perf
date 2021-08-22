#include <boost/container/vector.hpp>
#include <iostream>
#include "gui.hpp"

int main(int argc, char const *argv[])
{
    int32_t startingMoney = 6000;
    int32_t addedInvestmentMoneyPerYear = 0;
    int32_t yearOfInvest = 0;

    if (argc == 3) {
        yearOfInvest = atoi(argv[1]);
        addedInvestmentMoneyPerYear = atoi(argv[2]);
    }

    (new Gui(
        new Invest(
            startingMoney,
            yearOfInvest,
            addedInvestmentMoneyPerYear
        )
    ))->run();

    return 0;
}
