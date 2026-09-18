/*
 * SPDX-FileCopyrightText: The Calyx Institute
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/strings.h>
#include <aidl/android/hardware/usb/BnUsb.h>
#include <dlfcn.h>
#include <mutex>
#include <string>

#define USB_DATA_PATH "/sys/devices/platform/11110000.usb/usb_data_enabled"

using aidl::android::hardware::usb::BnUsb;
using ndk::ScopedAStatus;

static std::mutex gUsbStateMutex;
static bool gUsbDataEnabled = false;

static void SynchronizeUsbDataState() {
    std::lock_guard<std::mutex> lock(gUsbStateMutex);

    std::string state;
    if (!android::base::ReadFileToString(USB_DATA_PATH, &state)) {
        LOG(ERROR) << "libusb_policy_bridge: Failed to read " << USB_DATA_PATH;
        return;
    }

    state = android::base::Trim(state);
    if (state == "enabled" || state == "1") {
        gUsbDataEnabled = true;
    } else if (state == "disabled" || state == "0") {
        gUsbDataEnabled = false;
    } else {
        LOG(ERROR) << "libusb_policy_bridge: Unknown usb_data_enabled state: " << state;
        return;
    }

    LOG(INFO) << "libusb_policy_bridge: Current usb_data_enabled state = " << gUsbDataEnabled;
}

typedef ScopedAStatus (*QueryPortStatusFn)(void* instance, int64_t transactionId);
typedef ScopedAStatus (*EnableUsbDataFn)(void* instance, const std::string& portName, bool enable, int64_t transactionId);

ScopedAStatus _ZN4aidl7android8hardware3usb5BnUsb15queryPortStatusEl(
        void* instance, int64_t transactionId) {

    SynchronizeUsbDataState();

    static QueryPortStatusFn orig_queryPortStatus = nullptr;
    if (!orig_queryPortStatus) {
        orig_queryPortStatus = reinterpret_cast<QueryPortStatusFn>(
            dlsym(RTLD_NEXT, "_ZN4aidl7android8hardware3usb5BnUsb15queryPortStatusEl"));
    }

    if (orig_queryPortStatus) {
        return orig_queryPortStatus(instance, transactionId);
    }

    return ScopedAStatus::fromStatus(STATUS_UNKNOWN_ERROR);
}

ScopedAStatus _ZN4aidl7android8hardware3usb5BnUsb13enableUsbDataERKNSt3__112basic_stringIcNS4_11char_traitsIcEENS4_9allocatorIcEEEEbl(
        void* instance, const std::string& portName, bool enable, int64_t transactionId) {

    if (enable) {
        LOG(INFO) << "libusb_policy_bridge: Starting enable_usb_data service via init property";
        android::base::SetProperty("ctl.start", "enable_usb_data");
    } else {
        LOG(INFO) << "libusb_policy_bridge: Writing 0 to " << USB_DATA_PATH;
        android::base::WriteStringToFile("0", USB_DATA_PATH);
    }

    static EnableUsbDataFn orig_enableUsbData = nullptr;
    if (!orig_enableUsbData) {
        orig_enableUsbData = reinterpret_cast<EnableUsbDataFn>(
            dlsym(RTLD_NEXT, "_ZN4aidl7android8hardware3usb5BnUsb13enableUsbDataERKNSt3__112basic_stringIcNS4_11char_traitsIcEENS4_9allocatorIcEEEEbl"));
    }

    if (orig_enableUsbData) {
        ScopedAStatus status = orig_enableUsbData(instance, portName, enable, transactionId);
        SynchronizeUsbDataState();
        return status;
    }

    return ScopedAStatus::fromStatus(STATUS_UNKNOWN_ERROR);
}
