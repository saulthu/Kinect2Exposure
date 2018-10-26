# Kinect2Exposure
Provides manual control over Kinect2 exposure on Windows

This is a C++ conversion of the library released by Microsoft here: https://github.com/Microsoft/MixedRealityCompanionKit/tree/master/KinectIPD/NuiSensor which was originally in C, C++, C++/CLI.

The included NuiSensorLib.lib is a pre-compiled library for Windows that can directly connect to Kinect2 cameras, without going through the KinectService.exe camera proxy. Interestingly, this _potentially_ allows connection to multiple Kinect2 devices on Windows.

To use this wrapper for exposure control, first connect to a Kinect2 camera using the usual Microsoft Kinect2 SDK. Then create an instance of KinectExposure and call any of:

```
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
```
