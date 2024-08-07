// published by horizonix made by alreadycode!
// thanks for using v2.0-1!

#include <iostream>
#include <windows.h>
#include <thread>
#include <atomic>

std::atomic<bool> autoclickerRunning(false);

bool popEnabled = false;
bool afkEnabled = false;
int popDelay = 20;
int afkDelay = 10000;

void clickMouse() {
    while (true) {
        if (autoclickerRunning) {
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            if (afkEnabled) {
                std::this_thread::sleep_for(std::chrono::milliseconds(afkDelay));
            }
            else if (!popEnabled) {
                std::this_thread::sleep_for(std::chrono::milliseconds(popDelay));
            }
        }
    }
}

void setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void displayStatus() {
    system("cls");
    setConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
    std::cout << "Safeclick V2 - Quickest Autoclicker - No Viruses" << std::endl;
    std::cout << "Made by Alreadycode" << std::endl;
    std::cout << "Press F2 to enable/disable" << std::endl;
    setConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << "AFK Mode (F1): ";
    if (afkEnabled) {
        setConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::cout << "ON" << std::endl;
    }
    else {
        setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << "OFF" << std::endl;
    }
    setConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << "Autoclicker Toggle (F2): ";
    if (autoclickerRunning) {
        setConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::cout << "ON" << std::endl;
    }
    else {
        setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << "OFF" << std::endl;
    }
    setConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << "POP (POWER OVER PERFORMANCE) Mode (F3): ";
    if (popEnabled) {
        setConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::cout << "ON" << std::endl;
    }
    else {
        setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << "OFF" << std::endl;
    }
    setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    std::cout << "Quit (Ctrl+C)";
}

void hotkeyListener() {
    if (!RegisterHotKey(NULL, 3, 0, VK_F1)) {
        return;
    }
    if (!RegisterHotKey(NULL, 1, 0, VK_F2)) {
        return;
    }
    if (!RegisterHotKey(NULL, 2, 0, VK_F3)) {
        return;
    }

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY) {
            if (msg.wParam == 1) {
                autoclickerRunning = !autoclickerRunning;
                displayStatus();
            }
            else if (msg.wParam == 2) {
                if (!popEnabled) {
                    if (afkEnabled) {
                        afkEnabled = false;
                    }
                }
                popEnabled = !popEnabled;
                displayStatus();
            }
            else if (msg.wParam == 3) {
                if (!afkEnabled) {
                    if (popEnabled) {
                        popEnabled = false;
                    }
                }
                afkEnabled = !afkEnabled;
                displayStatus();
            }
        }
    }
    UnregisterHotKey(NULL, 1);
    UnregisterHotKey(NULL, 2);
    UnregisterHotKey(NULL, 3);
}

int main() {
    std::wstring strW = L"Safeclick V2";
    SetConsoleTitle(strW.c_str());
    displayStatus();

    std::thread clickThread(clickMouse);

    hotkeyListener();

    clickThread.join();

    return 0;
}

// made by alreadycode
