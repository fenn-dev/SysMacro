#include <sysmacro.hpp>
#include <iostream>

static_assert(CURRENT_OS != OS_UNDEFINED, "Test Failed: OS detected as undefined!");
static_assert(CURRENT_ARCH != ARCH_UNDEFINED, "Test Failed: Architecture detected as undefined!");

int main() {
    std::cout << "--- SysMacro Verification ---\n";
    std::cout << "Target OS ID:   " << CURRENT_OS   << " (" << get_os_name()   << ")\n";
    std::cout << "Target Arch ID: " << CURRENT_ARCH << " (" << get_arch_name() << ")\n";
    return 0;
}