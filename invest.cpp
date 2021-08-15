#include "invest.hpp"
#include "gui.hpp"

Invest::Invest(
    int32_t startingMoney,
    int32_t yearsOfInvestement,
    int32_t perYearInvestment
):
_standardSPRatio{0.06},
_currentMoney{0},
_currentYearWinnings{0},
_beginWithdrawals{false}
{
    if (startingMoney > 0) {
        _startingMoney = startingMoney;
    }

    if (yearsOfInvestement > 0) {
        _yearsOfInvestment = yearsOfInvestement;
    }

    if (perYearInvestment > 0) {
        _perYearInvestment = perYearInvestment;
    }
}

void Invest::run()
{
    Gui window();
    std::cout << "Running..." << std::endl;
    for (int currentYear = 1; currentYear <= _yearsOfInvestment; currentYear++) {
        _currentMoney = calculateInvestmentYear(currentYear);

        yearlyReport(currentYear);
    }
}

double Invest::calculateInvestmentYear(int currentYear)
{
    double result = _currentMoney;

    if (currentYear == 1) {
        result = _startingMoney;
    }

    result += (_perYearInvestment > 0 && currentYear > 1) ? _perYearInvestment : 0;
    _currentYearWinnings = (result * _standardSPRatio);

    if (!_beginWithdrawals) _beginWithdrawals = _currentYearWinnings > 12000;
    else accountYearlyWithdraw();

    result += _currentYearWinnings;

    return result;
}

void Invest::yearlyReport(int currentYear)
{
    std::cout << "*************************" << std::endl;
    std::cout << "Current Year: " << currentYear << std::endl;
    std::cout << "Current Money: " << _currentMoney << std::endl;
    std::cout << "Current Year Winnings: " << _currentYearWinnings << std::endl;
}

void Invest::accountYearlyWithdraw()
{
    _currentYearWinnings -= 12000;
    _perYearInvestment = 0;
}