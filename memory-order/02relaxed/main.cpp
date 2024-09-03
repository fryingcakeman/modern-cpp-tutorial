#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>
using namespace std;

atomic<bool> x, y;
atomic<int> z;

void write_x_then_y() {
    x.store(true, memory_order::relaxed);
    y.store(true, memory_order::relaxed);
}

void read_y_then_x() {
    while (!y.load(memory_order::relaxed)) {}
    if (x.load(memory_order::relaxed)) {
        ++z;
    }
}

int main() {
    x = false;
    y = false;
    z = 0;
    thread a(write_x_then_y);
    thread b(read_y_then_x);
    a.join();
    b.join();

    assert(z.load() != 0); // 可能会触发

    return 0;
}
