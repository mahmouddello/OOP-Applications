#pragma once
#include <iomanip>
#include "clsScreen.h";
#include "../cpplibs/clsInputValidate.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsMainScreen : protected clsScreen
{
private:
    enum enMainMenuOptions
    {
        eList = 1,
        eFind = 2,
        eUpdate = 3,
        eCalculator = 4,
        eExit = 5
    };

    static short _readMainMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]: ";
        short choice = clsInputValidate::readShortNumberBetween(1, 5, "");
        return choice;
    }
    
    static void _goBackToMainMenu()
    {
        cout << "\nPress any key to go back to main menu..." << endl;
        system("pause > 0");

        showMainMenu();
    }

    static void _showListCurrenciesScreen()
    {
        clsListCurrenciesScreen::showListCurrenciesScreen();
    }

    static void _showFindCurrencyScreen()
    {
        clsFindCurrencyScreen::showFindCurrencyScreen();
    }

    static void _showUpdateCurrencyScreen()
    {
        clsUpdateCurrencyScreen::showUpdateCurrencyScreen();
    }

    static void _showCurrencyCalculatorScreen()
    {
        clsCurrencyCalculatorScreen::showCurrencyCalculatorScreen();
    }

    static void _performMainMenuOption(enMainMenuOptions option)
    {
        system("cls");

        switch (option)
        {
        case eList:
            _showListCurrenciesScreen();
            break;
        case eFind:
            _showFindCurrencyScreen();
            break;
        case eUpdate:
            _showUpdateCurrencyScreen();
            break;
        case eCalculator:
            _showCurrencyCalculatorScreen();
            break;
        case eExit:
            // exit
            break;
        default:
            break;
        }

        if (option != enMainMenuOptions::eExit)
            _goBackToMainMenu();
    }

public:
    static void showMainMenu()
    {
        system("cls");
        _drawScreenHeader("\tCurrency Exchange Program");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator\n";
        cout << setw(37) << left << "" << "\t[5] Exit\n";
        cout << setw(37) << left << "" << "===========================================\n";


        _performMainMenuOption(enMainMenuOptions(_readMainMenuOption()));
    }
};
