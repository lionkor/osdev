#include "kpanic.h"
#include "kprint.h"

void kpanic(const char* why) {
    kperror("KERNEL PANIC");
    kperror(why);
    while (1)
        ;
}
