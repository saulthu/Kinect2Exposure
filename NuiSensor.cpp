#pragma comment (lib, "Setupapi.lib")

#include "NuiSensor.h"
#include <vector>
#include "Helpers.h"
#include <comdef.h>
#include <codecvt>
#include <iostream>

#define GET_NUISENSOR_RGB_CHANGE_STREAM_SETTING_BYTE_COUNT(Setting) \
    ( \
    sizeof(::NUISENSOR_RGB_CHANGE_STREAM_SETTING) \
    + ( (Setting).NumCommands - 1) * sizeof(::NUISENSOR_RGB_CHANGE_SETTING_CMD) \
    )

#define GET_NUISENSOR_RGB_CHANGE_STREAM_SETTING_REPLY_BYTE_COUNT(Reply) \
    ( \
    sizeof(::NUISENSOR_RGB_CHANGE_STREAM_SETTING_REPLY) \
    + ( (Reply).NumStatus - 1) * sizeof(::NUISENSOR_RGB_CHANGE_STREAM_SETTING_REPLY_STATUS) \
    )

namespace Xbox
{
namespace Kinect
{

NuiSensor::NuiSensor()
{
  TestResult(Internal::Initialize(&_sensor));
}

NuiSensor::~NuiSensor()
{
  Shutdown();
}

void NuiSensor::Shutdown()
{
  if (_sensor) {
    Internal::Shutdown(_sensor);
    _sensor = nullptr;
  }
}

void NuiSensor::ColorChangeCameraSettings(
  const NUISENSOR_RGB_CHANGE_STREAM_SETTING& settings,
  NUISENSOR_RGB_CHANGE_STREAM_SETTING_REPLY* p_reply)
{
  if (!_sensor)
    throw std::runtime_error("Sensor is not connected");

  if (settings.Commands.size() > NUISENSOR_RGB_CHANGE_SETTING_MAX_NUM_CMD)
    throw std::invalid_argument("Commands length is greater than maximum allowed");

  std::vector<BYTE> scratchBuffer(NUISENSOR_SEND_SCRATCH_SPACE_REQUIRED);
  std::vector<BYTE> settingBuffer(NUISENSOR_MAX_USB_COMMAND_SIZE);
  std::vector<BYTE> replyBuffer(NUISENSOR_MAX_USB_RESPONSE_SIZE);

  auto pSettings = reinterpret_cast<::NUISENSOR_RGB_CHANGE_STREAM_SETTING*>(settingBuffer.data());
  auto pReplies = reinterpret_cast<::NUISENSOR_RGB_CHANGE_STREAM_SETTING_REPLY*>(settingBuffer.data());

  pSettings->NumCommands = uint32_t(settings.Commands.size());
  pSettings->SequenceId = settings.SequenceId;

  for (auto i = 0; i < int(settings.Commands.size()); i++) {
    pSettings->Commands[i].Cmd = settings.Commands[i].Cmd;
    pSettings->Commands[i].Arg = settings.Commands[i].Arg;
  }

  pReplies->NumStatus = uint32_t(settings.Commands.size());

  DWORD settingsSize = GET_NUISENSOR_RGB_CHANGE_STREAM_SETTING_BYTE_COUNT(*pSettings);
  DWORD replySize = GET_NUISENSOR_RGB_CHANGE_STREAM_SETTING_REPLY_BYTE_COUNT(*pReplies);

  TestResult(Internal::ColorChangeCameraSettingsSync(
    _sensor,
    scratchBuffer.data(),
    (DWORD)scratchBuffer.size(),
    pSettings,
    settingsSize,
    pReplies,
    replySize));

  auto& reply = *p_reply;
  reply.CommandListStatus = pReplies->CommandListStatus;
  reply.Status.clear();
  reply.Status.resize(pReplies->NumStatus);

  for (auto i = 0; i < int(reply.Status.size()); i++) {
    reply.Status[i].Status = pReplies->Status[i].Status;
    reply.Status[i].Data = pReplies->Status[i].Data;
  }
}

// Convert wide string to string.
inline std::string _ws2s(const std::wstring& wstr)
{
  using convert_typeX = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_typeX, wchar_t> converterX;
  return converterX.to_bytes(wstr);
}

void NuiSensor::TestResult(BOOL success)
{
  if (success)
    return;

  auto hr = HRESULT_FROM_WIN32(Internal::GetLastError());
  _com_error err(hr);
  auto errMsg = err.ErrorMessage();
  //throw std::runtime_error(std::string("NuiSensor: error: ") + _ws2s(errMsg));
  std::cerr << std::string("NuiSensor: error: ") << _ws2s(errMsg) << "\n";
}

}
}
