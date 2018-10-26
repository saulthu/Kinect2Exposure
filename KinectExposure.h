#pragma once
#include <memory>
#include "NuiSensor.h"
#include "Lockable.h"

namespace Xbox { namespace Kinect { class NuiSensor; } }

class KinectExposure
{
public:
  KinectExposure() = default;

  // Fully automatic exposure setting.
  // Exposure compensation: negative value gives an underexposed image,
  // positive gives an overexposed image.
  void SetAutoExposure(float exposure_compensation = 0);

  // Sets a pseudo-exposure time in ms, value in range [0.0, 640] ms.
  //
  // The actual frame integration time is set to a multiple of fluorescent light period
  // that is shorter than the requested time e.g. requesting 16 ms will set 10 ms
  // in Australia (100Hz), 8.33 ms in USA (120Hz).
  // The gain is automatically set to compensate for the reduced integration time.
  //
  // Requesting less than a single fluorescent light period will set the integration time
  // to the requested value.
  //
  // To set the shortest non-flickering integration period for any country, simply set
  // a pseudo-exposure time of between (10.0, 16.667) ms, which will automatically drop
  // the integration time to 10 or 8.3 ms depending on country, while setting the analog
  // gain control to a brighter value.
  void SetSemiAutoExposure(float pseudo_exposure_time_ms);

  // Manually set true exposure time and analog gain.
  void SetManualExposure(float integration_time_ms, float analog_gain);

  // Use one of the SET commands.
  void SetFloat(Xbox::Kinect::NUISENSOR_RGB_COMMAND_TYPE command, float value);
  void SetUint(Xbox::Kinect::NUISENSOR_RGB_COMMAND_TYPE command, uint32_t value);

  // Use one of the GET commands.
  uint32_t GetCommand(Xbox::Kinect::NUISENSOR_RGB_COMMAND_TYPE command);
  float GetCommandFloat(Xbox::Kinect::NUISENSOR_RGB_COMMAND_TYPE command);

private:
  LockableSharedPtr<Xbox::Kinect::NuiSensor> _sensor;

  void Connect();

  //private Dictionary<NUISENSOR_RGB_COMMAND_TYPE, uint> GetCommands(NUISENSOR_RGB_COMMAND_TYPE[] commands)
  //{
  //  NUISENSOR_RGB_CHANGE_STREAM_SETTING setting;
  //  NUISENSOR_RGB_CHANGE_STREAM_SETTING_REPLY reply;

  //  setting.SequenceId = 0;
  //  setting.Commands = commands.Select(command = > new NUISENSOR_RGB_CHANGE_SETTING_CMD{ Cmd = (uint)command, Arg = 0 }).ToArray();

  //  lock(_sensor)
  //  {
  //    _sensor.ColorChangeCameraSettings(ref setting, out reply);
  //  }

  //  return commands.Zip(reply.Status, (c, r) = > { return Tuple.Create(c, r.Data); }).ToDictionary(t = > t.Item1, t = > t.Item2);
  //}

  uint32_t SetCommand(Xbox::Kinect::NUISENSOR_RGB_COMMAND_TYPE command, uint32_t argument);
  void SetCommand(Xbox::Kinect::NUISENSOR_RGB_COMMAND_TYPE command, float argument);
};
