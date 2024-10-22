// CSC1061_Lab9_start
// zyBooks 9.7 LAB: Timeout manager with priority_queue
// Starting code

#include <iostream>
#include <string>
#include <thread>
#include <unordered_set>
#include <vector>
#include "Clocks.h"
#include "TimeoutManager.h"
using namespace std;

void PrintVector(ostream& output, const vector<string>& vec,
    string delimiter = ",");
bool VerifyCallbacks(ostream& testFeedback, const vector<string>& actual,
    const vector<string>& expected);
bool Test1(ostream& testFeedback);
bool Test2(ostream& testFeedback);

int main() {
    bool test1Result = Test1(cout);
    cout << endl;
    bool test2Result = Test2(cout);

    cout << endl;
    cout << "Local test 1: " << (test1Result ? "PASS" : "FAIL") << endl;
    cout << "Local test 2: " << (test2Result ? "PASS" : "FAIL") << endl;

    return 0;
}

bool Test1(ostream& testFeedback) {
    TestClock clock;
    TimeoutManager timeouts(&clock);

    vector<string> actualCallbacks;

    // Test with items:
    // Added at clock time = 0:
    // - item D with delay 500 (callback time is 500)
    // - item A with delay 100 (callback time is 100)
    // Added at clock time = 50
    // - item B with delay 150 (callback time is 200)
    clock.SetTime(0);
    timeouts.AddTimeout([&]() {
        actualCallbacks.push_back("D");
        testFeedback << "Item D's callback" << endl;
        }, 500);
    timeouts.AddTimeout([&]() {
        actualCallbacks.push_back("A");
        testFeedback << "Item A's callback" << endl;
        }, 100);
    clock.SetTime(50);
    timeouts.AddTimeout([&]() {
        actualCallbacks.push_back("B");
        testFeedback << "Item B's callback" << endl;
        }, 150);

    // Do an update with clock time = 100, which should invoke item A's
    // callback
    clock.SetTime(100);
    testFeedback << "Updating with clock time = 100. Item A should show below." << endl;
    timeouts.Update();

    // Verify that only item A's callback was called
    if (!VerifyCallbacks(testFeedback, actualCallbacks, { "A" })) {
        return false;
    }

    // Do another update with a clock time of 150, which shouldn't invoke any
    // callbacks
    clock.SetTime(150);
    testFeedback << "Updating with clock time = 150. No callbacks should show below.";
    testFeedback << endl;
    timeouts.Update();

    // Verify that still only item A's callback has been called
    if (!VerifyCallbacks(testFeedback, actualCallbacks, { "A" })) {
        return false;
    }

    // Add more timeouts at clock time = 300:
    // - item E with delay 500 (callback time is 800)
    // - item C with delay 100 (callback time is 400)
    clock.SetTime(300);
    testFeedback << "Adding timeouts E and C" << endl;
    timeouts.AddTimeout([&]() {
        actualCallbacks.push_back("E");
        testFeedback << "Item E's callback" << endl;
        }, 500);
    timeouts.AddTimeout([&]() {
        actualCallbacks.push_back("C");
        testFeedback << "Item C's callback" << endl;
        }, 100);

    // Verify that adding new timeouts didn't invoke any new callbacks
    if (!VerifyCallbacks(testFeedback, actualCallbacks, { "A" })) {
        return false;
    }

    // Do an update with a clock time of 350, which should invoke item B's
    // callback
    clock.SetTime(350);
    testFeedback << "Updating with clock time = 350. Item B should show below." << endl;
    timeouts.Update();

    // Verify callbacks: A and B called, others not
    if (!VerifyCallbacks(testFeedback, actualCallbacks, { "A", "B" })) {
        return false;
    }

    // Do an update with a clock time of 550, which should invoke item C's
    // callback and item D's callback, in that order
    clock.SetTime(550);
    testFeedback << "Updating with clock time = 550. Item C and D should show below, ";
    testFeedback << "in that order." << endl;
    timeouts.Update();

    // Verify callbacks: A, B, C, and D
    if (!VerifyCallbacks(testFeedback, actualCallbacks, { "A", "B", "C", "D" })) {
        return false;
    }

    // Do another update with a clock time of 700, which shouldn't invoke any
    // callbacks
    clock.SetTime(700);
    testFeedback << "Updating with clock time = 700. No callbacks should show below.";
    testFeedback << endl;
    timeouts.Update();

    // Verify callbacks: again just A, B, C, and D
    if (!VerifyCallbacks(testFeedback, actualCallbacks, { "A", "B", "C", "D" })) {
        return false;
    }

    // Do a final update with time = 900, which should invoke item E's callback
    clock.SetTime(900);
    testFeedback << "Updating with clock time = 900. Item E should show below.";
    testFeedback << endl;
    timeouts.Update();

    // Verify callbacks: A, B, C, D, and E
    if (!VerifyCallbacks(testFeedback, actualCallbacks, { "A","B","C","D","E" })) {
        return false;
    }

    return true;
}

bool Test2(ostream& testFeedback) {
    TestClock clock;
    TimeoutManager timeouts(&clock);

    vector<string> actualCallbacks;

    // At t = 0:
    // - Add item A with delay 800 (callback time is 800)
    clock.SetTime(0);
    testFeedback << "At t=0, adding timeout A with delay = 800" << endl;
    timeouts.AddTimeout([&]() {
        actualCallbacks.push_back("A");
        }, 800);

    // At t = 50:
    // - Add item D with delay 600 (callback time is 650)
    clock.SetTime(50);
    testFeedback << "At t=50, adding timeout D with delay = 600" << endl;
    timeouts.AddTimeout([&]() {
        actualCallbacks.push_back("D");
        }, 600);

    // At t = 100:
    // - Add item C with delay 200 (callback time is 300)
    clock.SetTime(100);
    testFeedback << "At t=100, adding timeout C with delay = 200" << endl;
    timeouts.AddTimeout([&]() {
        actualCallbacks.push_back("C");
        }, 200);

    // At t = 150:
    // - Add item E with delay 250 (callback time is 400)
    clock.SetTime(150);
    testFeedback << "At t=150, adding timeout E with delay = 250" << endl;
    timeouts.AddTimeout([&]() {
        actualCallbacks.push_back("E");
        }, 250);

    // At t = 200:
    // - Add item B with delay 50 (callback time is 250)
    // - Update, then verify that no callback have yet been called
    clock.SetTime(200);
    testFeedback << "At t=200, adding timeout B with delay = 50";
    testFeedback << ", then updating" << endl;
    timeouts.AddTimeout([&]() {
        actualCallbacks.push_back("B");
        }, 50);
    timeouts.Update();
    if (!VerifyCallbacks(testFeedback, actualCallbacks, { })) {
        return false;
    }

    // At t = 400:
    // - Update, then verify that callbacks B, C, and E have been called
    clock.SetTime(400);
    testFeedback << "At t=400, updating" << endl;
    timeouts.Update();
    if (!VerifyCallbacks(testFeedback, actualCallbacks, { "B", "C", "E" })) {
        return false;
    }

    // At t = 450:
    // - Add item F with delay 100 (callback time is 550)
    clock.SetTime(450);
    testFeedback << "At t=450, adding timeout F with delay = 100" << endl;
    timeouts.AddTimeout([&]() {
        actualCallbacks.push_back("F");
        }, 100);

    // At t = 600:
    // - Update, then verify callbacks: B and C from earlier, E and F now
    clock.SetTime(600);
    testFeedback << "At t=600, updating" << endl;
    timeouts.Update();
    if (!VerifyCallbacks(testFeedback, actualCallbacks, { "B", "C", "E", "F" })) {
        return false;
    }

    // At t = 800:
    // - Update, then verify callbacks: B, C, E, F, D, A
    clock.SetTime(800);
    testFeedback << "At t=800, updating" << endl;
    timeouts.Update();
    if (!VerifyCallbacks(testFeedback, actualCallbacks, { "B", "C", "E", "F", "D", "A" })) {
        return false;
    }

    return true;
}

bool VerifyCallbacks(ostream& testFeedback, const vector<string>& actual,
    const vector<string>& expected) {
    // Compare vector sizes first
    bool areEqual = true;
    if (actual.size() == expected.size()) {
        for (int i = 0; areEqual && i < (int)actual.size(); i++) {
            if (actual[i] != expected[i]) {
                areEqual = false;
            }
        }
    }
    else {
        areEqual = false;
    }

    // Print results
    testFeedback << (areEqual ? "PASS" : "FAIL");
    testFeedback << ": Verification of invoked callbacks" << endl;
    testFeedback << "  Expected: { ";
    PrintVector(testFeedback, expected);
    testFeedback << " }" << endl;
    testFeedback << "  Actual:   { ";
    PrintVector(testFeedback, actual);
    testFeedback << " }" << endl;

    return areEqual;
}

// Prints comma-separated vector elements to the output stream
void PrintVector(std::ostream& output, const std::vector<string>& vec,
    std::string delimiter) {
    // Output occurs only if at least one element exists
    if (vec.size() > 0) {
        // Write the first element without delimiter
        output << vec[0];

        // Write each remaining element preceded by the delimiter
        for (int i = 1; i < (int)vec.size(); i++) {
            output << delimiter << vec[i];
        }
    }
}