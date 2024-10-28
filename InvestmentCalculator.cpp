#include "InvestmentCalculator.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>

using namespace std;

InvestmentCalculator::InvestmentCalculator()
    : m_initialInvestment(0.0), m_monthlyDeposit(0.0), m_annualInterest(0.0), m_years(0) {}

void InvestmentCalculator::run() {
    char continueCalculation;
    do {
        displayInputScreen();
        getUserInput();
        calculateInvestment(false);  // Without monthly deposits
        calculateInvestment(true);   // With monthly deposits
        displayReports();

        cout << "Do you want to do another calculation? (y/n): ";
        cin >> continueCalculation;
    } while (continueCalculation == 'y' || continueCalculation == 'Y');
}

void InvestmentCalculator::displayInputScreen() {
    cout << "********************************\n";
    cout << "********** Data Input **********\n";
    cout << "Initial Investment Amount: $";
    cout << "Monthly Deposit: $";
    cout << "Annual Interest: %";
    cout << "Number of Years: ";
    cout << "********************************\n";
}

void InvestmentCalculator::getUserInput() {
    cout << "Enter Initial Investment Amount: $";
    cin >> m_initialInvestment;
    cout << "Enter Monthly Deposit: $";
    cin >> m_monthlyDeposit;
    cout << "Enter Annual Interest: %";
    cin >> m_annualInterest;
    cout << "Enter Number of Years: ";
    cin >> m_years;

    // Input validation could be added here
}

void InvestmentCalculator::calculateInvestment(bool includeMonthlyDeposit) {
    double balance = m_initialInvestment;
    double monthlyInterestRate = (m_annualInterest / 100) / 12;
    vector<pair<double, double>>& results = 
        includeMonthlyDeposit ? m_resultsWithDeposits : m_resultsWithoutDeposits;

    results.clear();

    for (int year = 1; year <= m_years; ++year) {
        double yearEndBalance = balance;
        double yearEndInterest = 0;

        for (int month = 1; month <= 12; ++month) {
            if (includeMonthlyDeposit) {
                yearEndBalance += m_monthlyDeposit;
            }
            double monthlyInterest = yearEndBalance * monthlyInterestRate;
            yearEndBalance += monthlyInterest;
            yearEndInterest += monthlyInterest;
        }

        results.push_back(make_pair(yearEndBalance, yearEndInterest));
        balance = yearEndBalance;
    }
}

void InvestmentCalculator::displayReports() {
    // Display report without monthly deposits
    cout << "\nBalance and Interest Without Additional Monthly Deposits\n";
    cout << "==============================================================\n";
    cout << "Year\tYear End Balance\tYear End Earned Interest\n";
    cout << "--------------------------------------------------------------\n";
    for (size_t i = 0; i < m_resultsWithoutDeposits.size(); ++i) {
        cout << i + 1 << "\t"
             << formatCurrency(m_resultsWithoutDeposits[i].first) << "\t\t"
             << formatCurrency(m_resultsWithoutDeposits[i].second) << "\n";
    }

    // Display report with monthly deposits
    cout << "\nBalance and Interest With Additional Monthly Deposits\n";
    cout << "==============================================================\n";
    cout << "Year\tYear End Balance\tYear End Earned Interest\n";
    cout << "--------------------------------------------------------------\n";
    for (size_t i = 0; i < m_resultsWithDeposits.size(); ++i) {
        cout << i + 1 << "\t"
             << formatCurrency(m_resultsWithDeposits[i].first) << "\t\t"
             << formatCurrency(m_resultsWithDeposits[i].second) << "\n";
    }
}

string InvestmentCalculator::formatCurrency(double amount) const {
    stringstream ss;
    ss << fixed << setprecision(2) << "$" << amount;
    return ss.str();
}