#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "mbed.h"
#pragma GCC diagnostic pop

DigitalIn  startSwitch(dp15);
DigitalIn  reverseSwitch(dp16);

DigitalOut started(dp17);
DigitalOut reversed(dp18);
DigitalOut o1(dp10);
DigitalOut o2(dp11);
DigitalOut o3(dp13);
DigitalOut o4(dp14);

int table[16] = {
    0, 0, 1, 1,
    0, 1, 1, 0,
    1, 1, 0, 0,
    1, 0, 0, 1
};

void Inc(int &ind) {
    ind++;
    if (ind >= 4)
        ind = 0;
}

void Dec(int &ind) {
    ind--;
    if (ind < 0)
        ind = 3;
}

void Out(int ind) {
    if (ind < 0 || ind > 3)
        error("Panic!");
    o1 = table[4 * ind];
    o2 = table[4 * ind + 1];
    o3 = table[4 * ind + 2];
    o4 = table[4 * ind + 3];
}

void Status(bool STARTED, bool REVERSED) {
    started  = STARTED;
    reversed = REVERSED;
}

int main() {
    int ind = 0;
    bool STARTED;
    bool REVERSED;
    while (true) {
        Out(ind);
        STARTED  = startSwitch;
        REVERSED = reverseSwitch;
        Status(STARTED, REVERSED);
        if (REVERSED) {
            Inc(ind);
            Out(ind);
            wait(0.030);
        } else if (STARTED) {
            Dec(ind);
            Out(ind);
            wait(0.300);
        } else {
            wait(0.300);
        }
    }
    error("WTF!?");
    return 0;
}
