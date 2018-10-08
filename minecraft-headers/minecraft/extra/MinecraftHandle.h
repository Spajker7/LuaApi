#pragma once

#include <dlfcn.h>
#include <string.h>

namespace {
void* MinecraftHandle() {
    static void* handle = dlopen(NULL, RTLD_LAZY);
    return handle;
}
}
