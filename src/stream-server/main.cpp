#include "rtc_base/ssl_adapter.h"

int main() {
    bool result = webrtc::InitializeSSL();
    printf("SSL %s\n", result ? "Initialized!" : "Failed to initialize");
    if (!result) {
        return -1;
    }

    webrtc::CleanupSSL();
    printf("SSL Cleaned up\n");

    return 0;
}