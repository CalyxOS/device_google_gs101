/*
 * SPDX-FileCopyrightText: The Calyx Institute
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <aidl/android/hardware/usb/IUsb.h>
#include <string>

using aidl::android::hardware::usb::IUsb;

namespace {
constexpr bool kDebug = true;
constexpr char kServiceInstance[] = "android.hardware.usb.IUsb/default";
constexpr char kDefaultPortName[] = "otg_default";
}  // anonymous namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        if (kDebug) {
            LOG(ERROR) << "usage: usb_data_sync <0|1> [portName]";
        }
        return 1;
    }

    bool enable = std::atoi(argv[1]) != 0;
    std::string portName = (argc >= 3) ? argv[2] : kDefaultPortName;

    ABinderProcess_startThreadPool();

    ndk::SpAIBinder binder(AServiceManager_waitForService(kServiceInstance));
    if (binder.get() == nullptr) {
        if (kDebug) {
            LOG(ERROR) << "Failed to get binder for " << kServiceInstance;
        }
        return 1;
    }

    std::shared_ptr<IUsb> usb = IUsb::fromBinder(binder);
    if (usb == nullptr) {
        if (kDebug) {
            LOG(ERROR) << "Failed to cast binder to IUsb";
        }
        return 1;
    }

    if (kDebug) {
        LOG(INFO) << "Requesting enableUsbData(portName=" << portName << ", enable=" << enable << ")";
    }

    ndk::ScopedAStatus status = usb->enableUsbData(portName, enable, /*transactionId=*/0);
    if (!status.isOk()) {
        if (kDebug) {
            LOG(ERROR) << "enableUsbData transaction failed: " << status.getDescription();
        }
        return 1;
    }

    return 0;
}
