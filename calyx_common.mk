#
# SPDX-FileCopyrightText: 2021-2024 The LineageOS Project
# SPDX-FileCopyrightText: 2021-2024 The Calyx Institute
# SPDX-License-Identifier: Apache-2.0
#

# Overlays
DEVICE_PACKAGE_OVERLAYS += device/google/gs101/overlay-calyx

# Camera
PRODUCT_PRODUCT_PROPERTIES += \
    ro.vendor.camera.extensions.package=com.google.android.apps.camera.services \
    ro.vendor.camera.extensions.service=com.google.android.apps.camera.services.extensions.service.PixelExtensions

# EUICC
PRODUCT_PACKAGES += \
    EuiccSupportPixelOverlay

# Lineage Health
include hardware/google/pixel/lineage_health/device.mk

# Linker config
PRODUCT_VENDOR_LINKER_CONFIG_FRAGMENTS += \
    device/google/gs101/linker.config.json

# pKVM
PRODUCT_VENDOR_PROPERTIES += \
    persist.device_config.virtualization_framework_native.isolated_compilation_enabled=true

# Tethering
PRODUCT_PACKAGES += \
    TetheringOverlay

# Touch
include hardware/google/pixel/touch/device.mk
