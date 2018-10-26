#include "KinectExposure.h"
#include "NuiSensor.h"
#include "ReinterpretBytes.h"

void KinectExposure::SetAutoExposure(float exposure_compensation)
{
  Connect();
  SetCommand(Xbox::Kinect::NUISENSOR_RGB_COMMAND_SET_EXPOSURE_MODE, 0u);  // 0 == Fully auto
  SetCommand(Xbox::Kinect::NUISENSOR_RGB_COMMAND_SET_EXPOSURE_COMPENSATION, exposure_compensation);
}

void KinectExposure::SetSemiAutoExposure(float pseudo_exposure_time_ms)
{
  Connect();
  SetCommand(Xbox::Kinect::NUISENSOR_RGB_COMMAND_SET_EXPOSURE_MODE, 3u);  // 3 == Semi-auto
  SetCommand(Xbox::Kinect::NUISENSOR_RGB_COMMAND_SET_EXPOSURE_TIME_MS, pseudo_exposure_time_ms);
}

void KinectExposure::SetManualExposure(float integration_time_ms, float analog_gain)
{
  Connect();
  SetCommand(Xbox::Kinect::NUISENSOR_RGB_COMMAND_SET_EXPOSURE_MODE, 4u);  // 4 == Fully manual
  SetCommand(Xbox::Kinect::NUISENSOR_RGB_COMMAND_SET_INTEGRATION_TIME, integration_time_ms);
  SetCommand(Xbox::Kinect::NUISENSOR_RGB_COMMAND_SET_ANALOG_GAIN, analog_gain);
}

void KinectExposure::SetFloat(Xbox::Kinect::NUISENSOR_RGB_COMMAND_TYPE command, float value)
{
  Connect();
  SetCommand(command, value);
}

void KinectExposure::SetUint(Xbox::Kinect::NUISENSOR_RGB_COMMAND_TYPE command, uint32_t value)
{
  Connect();
  SetCommand(command, value);
}

void KinectExposure::Connect()
{
  {
    auto sensor = _sensor.lock();
    if (sensor)
      return;
    sensor = std::make_shared<Xbox::Kinect::NuiSensor>();
  }
  SetCommand(Xbox::Kinect::NUISENSOR_RGB_COMMAND_SET_ACS, 0u);
  //ws::sleep(500ms);
  //SetCommand(Xbox::Kinect::NUISENSOR_RGB_COMMAND_SET_EXPOSURE_MODE, 3u);
}

uint32_t KinectExposure::GetCommand(Xbox::Kinect::NUISENSOR_RGB_COMMAND_TYPE command)
{
  Connect();
  return SetCommand(command, uint32_t(0));
}

float KinectExposure::GetCommandFloat(Xbox::Kinect::NUISENSOR_RGB_COMMAND_TYPE command)
{
  Connect();
  const auto val = SetCommand(command, uint32_t(0));
  const auto buf = ub_land_value_to_bytes(val);
  return ub_land_bytes_to_float(buf.data(), int(buf.size()));
}

uint32_t KinectExposure::SetCommand(Xbox::Kinect::NUISENSOR_RGB_COMMAND_TYPE command, uint32_t argument)
{
  Xbox::Kinect::NUISENSOR_RGB_CHANGE_STREAM_SETTING setting;
  Xbox::Kinect::NUISENSOR_RGB_CHANGE_STREAM_SETTING_REPLY reply;
  setting.SequenceId = 0;
  setting.Commands.resize(1);
  setting.Commands[0].Cmd = uint32_t(command);
  setting.Commands[0].Arg = argument;
  {
    auto sensor = _sensor.lock();
    sensor->ColorChangeCameraSettings(setting, &reply);
  }
  return reply.Status[0].Data;
}

void KinectExposure::SetCommand(Xbox::Kinect::NUISENSOR_RGB_COMMAND_TYPE command, float argument)
{
  const auto buf = ub_land_value_to_bytes(argument);
  const auto arg = ub_land_bytes_to_int(buf.data(), int(buf.size()));
  SetCommand(command, arg);
}
