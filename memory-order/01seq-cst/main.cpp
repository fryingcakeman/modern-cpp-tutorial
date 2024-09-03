#include <iostream>
#include <atomic>
#include <cassert>
#include <thread>
using namespace std;

atomic<bool> x, y;
atomic<int> z;

void write_x() {
    x.store(true, memory_order_seq_cst);
}

void write_y() {
    y.store(true, memory_order_seq_cst);
}

void read_x_then_y() {
    while (!x.load(memory_order_seq_cst)) {}
    if (x.load(memory_order_seq_cst)) {
        ++z;
    }
}

void read_y_then_x() {
    while (!y.load(memory_order_seq_cst)) {}
    if (x.load(memory_order_seq_cst)) {
        ++z;
    }
}


int main() {

    x = false;
    y = false;
    z = 0;
    thread a(write_x);
    thread b(write_y);
    thread c(read_x_then_y);
    thread d(read_y_then_x);

    a.join();
    b.join();
    c.join();
    d.join();

    assert(z.load() != 0);

    return 0;
}
