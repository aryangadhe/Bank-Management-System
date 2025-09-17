#include "Utils.h"
#include <iostream>
#include <conio.h>   // for _getch() on Windows
using namespace std;

namespace Utils {
    string getHiddenPin() {
        string pin;
        char ch;
        while ((ch = _getch()) != '\r') { // Enter key ends input
            if (ch == '\b') { // handle backspace
                if (!pin.empty()) {
                    cout << "\b \b";
                    pin.pop_back();
                }
            } else {
                pin.push_back(ch);
                cout << '*';  // print * instead of digit
            }
        }
        cout << endl;
        return pin;
    }
}