#include "system_icon.hpp"

template <>
void SystemIconAsyncWorker<ExtensionTag>::Execute() {
    // Do nothing: see OS-specific files for actual implementation
}

template <>
void SystemIconAsyncWorker<PathTag>::Execute() {
    // Do nothing: see OS-specific files for actual implementation
}
