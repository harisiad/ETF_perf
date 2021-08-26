#ifndef __INVEST_HPP__
#define __INVEST_HPP__

#include <iostream>
#include <vector>
#include <boost/container/vector.hpp>

class Invest
{
    private:
        int32_t _startingMoney;
        int32_t _yearsOfInvestment;
        int32_t _perYearInvestment;

        double _currentMoney;
        double _standardSPRatio;
        double _currentYearWinnings;

        bool _beginWithdrawals;

        boost::container::vector<std::string> _finalUiText;

    public:
        Invest(int32_t, int32_t, int32_t);
        ~Invest();

        boost::container::vector<std::string> run();

    private:
        double calculateInvestmentYear(int);
        void yearlyReport(int);
        void accountYearlyWithdraw();
};

#endif