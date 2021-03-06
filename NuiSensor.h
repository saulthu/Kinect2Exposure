// Conversion from the original C++/CLI implementation.

#pragma once
#include <vector>
typedef struct _NUISENSOR_HANDLE *NUISENSOR_HANDLE, **PNUISENSOR_HANDLE;

//using namespace System;
//using namespace System::Runtime::InteropServices;

namespace Xbox
{
namespace Kinect
{

enum NUISENSOR_RGB_COMMAND_TYPE
{
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_MODE = 0,
  NUISENSOR_RGB_COMMAND_SET_INTEGRATION_TIME = 1,
  NUISENSOR_RGB_COMMAND_GET_INTEGRATION_TIME = 2,

  NUISENSOR_RGB_COMMAND_SET_WHITE_BALANCE_MODE = 10,
  NUISENSOR_RGB_COMMAND_SET_RED_CHANNEL_GAIN = 11,
  NUISENSOR_RGB_COMMAND_SET_GREEN_CHANNEL_GAIN = 12,
  NUISENSOR_RGB_COMMAND_SET_BLUE_CHANNEL_GAIN = 13,
  NUISENSOR_RGB_COMMAND_GET_RED_CHANNEL_GAIN = 14,
  NUISENSOR_RGB_COMMAND_GET_GREEN_CHANNEL_GAIN = 15,
  NUISENSOR_RGB_COMMAND_GET_BLUE_CHANNEL_GAIN = 16,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_TIME_MS = 17,
  NUISENSOR_RGB_COMMAND_GET_EXPOSURE_TIME_MS = 18,
  NUISENSOR_RGB_COMMAND_SET_DIGITAL_GAIN = 19,
  NUISENSOR_RGB_COMMAND_GET_DIGITAL_GAIN = 20,
  NUISENSOR_RGB_COMMAND_SET_ANALOG_GAIN = 21,
  NUISENSOR_RGB_COMMAND_GET_ANALOG_GAIN = 22,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_COMPENSATION = 23,
  NUISENSOR_RGB_COMMAND_GET_EXPOSURE_COMPENSATION = 24,
  NUISENSOR_RGB_COMMAND_SET_ACS = 25,
  NUISENSOR_RGB_COMMAND_GET_ACS = 26,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_MODE = 27,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONES = 28,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_0_WEIGHT = 29,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_1_WEIGHT = 30,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_2_WEIGHT = 31,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_3_WEIGHT = 32,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_4_WEIGHT = 33,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_5_WEIGHT = 34,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_6_WEIGHT = 35,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_7_WEIGHT = 36,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_8_WEIGHT = 37,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_9_WEIGHT = 38,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_10_WEIGHT = 39,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_11_WEIGHT = 40,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_12_WEIGHT = 41,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_13_WEIGHT = 42,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_14_WEIGHT = 43,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_15_WEIGHT = 44,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_16_WEIGHT = 45,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_17_WEIGHT = 46,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_18_WEIGHT = 47,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_19_WEIGHT = 48,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_20_WEIGHT = 49,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_21_WEIGHT = 50,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_22_WEIGHT = 51,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_23_WEIGHT = 52,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_24_WEIGHT = 53,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_25_WEIGHT = 54,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_26_WEIGHT = 55,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_27_WEIGHT = 56,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_28_WEIGHT = 57,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_29_WEIGHT = 58,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_30_WEIGHT = 59,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_31_WEIGHT = 60,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_32_WEIGHT = 61,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_33_WEIGHT = 62,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_34_WEIGHT = 63,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_35_WEIGHT = 64,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_36_WEIGHT = 65,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_37_WEIGHT = 66,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_38_WEIGHT = 67,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_39_WEIGHT = 68,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_40_WEIGHT = 69,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_41_WEIGHT = 70,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_42_WEIGHT = 71,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_43_WEIGHT = 72,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_44_WEIGHT = 73,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_45_WEIGHT = 74,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_46_WEIGHT = 75,
  NUISENSOR_RGB_COMMAND_SET_EXPOSURE_METERING_ZONE_47_WEIGHT = 76,
  NUISENSOR_RGB_COMMAND_SET_MAX_ANALOG_GAIN_CAP = 77,
  NUISENSOR_RGB_COMMAND_SET_MAX_DIGITAL_GAIN_CAP = 78,
  NUISENSOR_RGB_COMMAND_SET_FLICKER_FREE_FREQUENCY = 79,
  NUISENSOR_RGB_COMMAND_GET_EXPOSURE_MODE = 80,
  NUISENSOR_RGB_COMMAND_GET_WHITE_BALANCE_MODE = 81,
  NUISENSOR_RGB_COMMAND_SET_FRAME_RATE = 82,
  NUISENSOR_RGB_COMMAND_GET_FRAME_RATE = 83,

  // This range is reserved.  Do not re-use.
  NUISENSOR_RGB_COMMAND_RESERVED_BASE = 400,
  NUISENSOR_RGB_COMMAND_RESERVED_END = NUISENSOR_RGB_COMMAND_RESERVED_BASE + 200,
  // End of reserved region

};

struct NUISENSOR_RGB_CHANGE_SETTING_CMD
{
  uint32_t Cmd;
  uint32_t Arg;
};

struct NUISENSOR_RGB_CHANGE_STREAM_SETTING
{
  uint32_t SequenceId;
  std::vector<NUISENSOR_RGB_CHANGE_SETTING_CMD> Commands;
};

struct NUISENSOR_RGB_CHANGE_STREAM_SETTING_REPLY_STATUS
{
  uint32_t Status;
  uint32_t Data;
};

struct NUISENSOR_RGB_CHANGE_STREAM_SETTING_REPLY
{
  uint32_t CommandListStatus;
  std::vector<NUISENSOR_RGB_CHANGE_STREAM_SETTING_REPLY_STATUS> Status;
};


class NuiSensor
{
public:
  NuiSensor();
  ~NuiSensor();

  void Shutdown();

  void ColorChangeCameraSettings(const NUISENSOR_RGB_CHANGE_STREAM_SETTING& settings, NUISENSOR_RGB_CHANGE_STREAM_SETTING_REPLY* p_reply);

private:
  void TestResult(int success);

  NUISENSOR_HANDLE _sensor = nullptr;
};

}
}
