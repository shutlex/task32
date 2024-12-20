#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>

void Thread1(HANDLE hEvent) {
    std::cout << "Thread1: Waiting for event...\n";
    DWORD dwWaitResult = WaitForSingleObject(hEvent, INFINITE);

    if (dwWaitResult == WAIT_OBJECT_0) {
        std::cout << "Thread1: Event received! Resuming execution...\n";
    }
    else {
        std::cerr << "Thread1: Error waiting for event.\n";
    }
}

void Thread2(HANDLE hEvent) {
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "Thread2: Signaling the event...\n";

    SetEvent(hEvent);
}

int main() {
    HANDLE hEvent = CreateEvent(
        NULL,          
        FALSE,         
        FALSE,          
        NULL            
    );

    if (hEvent == NULL) {
        std::cerr << "Failed to create event!" << std::endl;
        return 1;
    }

    std::thread t1(Thread1, hEvent);
    std::thread t2(Thread2, hEvent);

    t1.join();
    t2.join();

    CloseHandle(hEvent);

    return 0;
}

