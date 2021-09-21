#
# Copyright (C) 2021 The Calyx Institute
#
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

# Security patch
PRODUCT_PROPERTY_OVERRIDES += \
    ro.vendor.kernel.security_patch=2023-10-05

# Touch
include hardware/google/pixel/touch/device.mk
