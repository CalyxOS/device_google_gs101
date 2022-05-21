# ----------------------------
# Add feature flags below
# ----------------------------
FPC_CONFIG_BUILD_VERSION=42
FPC_CONFIG_GOOGLE_CUSTOMIZE=1
FPC_CONFIG_HAL_SHARED_LIB=1
FPC_CONFIG_MAX_NR_TEMPLATES=5
FPC_CONFIG_NO_TU=0
FPC_CONFIG_SENSE_TOUCH_CALIBRATION_PATH=/data/fpc/calibration_sense_touch.dat
FPC_CONFIG_SENSORTEST=1
FPC_CONFIG_TA_FS=1
FPC_DEFECTIVE_PIXEL_LIST_SIZE=5000
FPC_OTP_DECODE_ERRORS_IGNORE=1
FPC_SENSOR_SDK_LOG_LEVEL=3
FPC_TEE_RUNTIME=TRUSTY
LIBFPC_NAME=libfpcmulti_debug.a
FPC_CONFIG_DEBUG=1
FPC_CONFIG_ENGINEERING=1
FPC_CONFIG_GOOGLE_RELEASE=1
FPC_CONFIG_TRUSTY_CLEAN_TA=1

GOOGLE_CONFIG_PERFORMANCE=1

# Enable Suez
$(call soong_config_set,fp_hal_feature,biometric_suez_support,true)

# Must add below method to each project's device.mk to show sensorLocation
#$(call soong_config_set,fp_hal_feature,pixel_product, project_XX)
