#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>

void Thread1(HANDLE hEvent) {
    std::cout << "Thread1: Waiting for event...\n";

    // Wait for the event to be signaled
    DWORD dwWaitResult = WaitForSingleObject(hEvent, INFINITE);

    if (dwWaitResult == WAIT_OBJECT_0) {
        std::cout << "Thread1: Event received! Resuming execution...\n";
    }
    else {
        std::cerr << "Thread1: Error waiting for event.\n";
    }
}

void Thread2(HANDLE hEvent) {
    // Delay before signaling the event (e.g., 3 seconds)
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "Thread2: Signaling the event...\n";

    // Signal the event
    SetEvent(hEvent);
}

int main() {
    // Create an event (manual reset, initially unsignaled)
    HANDLE hEvent = CreateEvent(
        NULL,           // Security attributes
        FALSE,          // Auto-reset event (FALSE means it does not reset automatically)
        FALSE,          // Initial state of the event (unsignaled)
        NULL            // Event name (NULL means unnamed)
    );

    if (hEvent == NULL) {
        std::cerr << "Failed to create event!" << std::endl;
        return 1;
    }

    // Create two threads
    std::thread t1(Thread1, hEvent);
    std::thread t2(Thread2, hEvent);

    // Wait for threads to finish
    t1.join();
    t2.join();

    // Close the event handle
    CloseHandle(hEvent);

    return 0;
}

