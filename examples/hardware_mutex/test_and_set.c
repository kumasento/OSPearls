#define bool int
#define true 1
#define false 0

int main() {
    bool lock = true;
    bool val = __sync_lock_test_and_set(&lock, true);

    return 0;
}
