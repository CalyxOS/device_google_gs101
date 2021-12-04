#
# Copyright (C) 2021 The Calyx Institute
#
# SPDX-License-Identifier: Apache-2.0
#

BUILD_BROKEN_ELF_PREBUILT_PRODUCT_COPY_FILES := true

AB_OTA_PARTITIONS += vendor_dlkm
AB_OTA_PARTITIONS += vendor

# vendor_dlkm.img
BOARD_VENDOR_DLKMIMAGE_FILE_SYSTEM_TYPE := ext4
TARGET_COPY_OUT_VENDOR_DLKM := vendor_dlkm

# vendor.img
BOARD_VENDORIMAGE_FILE_SYSTEM_TYPE := ext4
TARGET_COPY_OUT_VENDOR := vendor
