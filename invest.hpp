#ifndef __INVEST_HPP__
#define __INVEST_HPP__

#include <iostream>

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

    public:
        Invest(int32_t, int32_t, int32_t);
        ~Invest();

        void run();

    private:
        double calculateInvestmentYear(int);
        void yearlyReport(int);
        void accountYearlyWithdraw();
};

#endif