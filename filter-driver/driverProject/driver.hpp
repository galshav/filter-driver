#pragma once

void unloadRoutine(PDRIVER_OBJECT DriverObject);
NTSTATUS createCloseRoutine(PDEVICE_OBJECT DeviceObject, PIRP irp);

#define DRIVER_PREFIX "Filter Driver - "
#define DRIVER_NAME "driver-filter"
#define DRIVER_DEVICE_PATH L"\\Device\\" DRIVER_NAME
#define DRIVER_SYMBOLIC_LINK_PATH L"\\??\\" DRIVER_NAME

static const char* const g_CreateDeviceError = "Failed to create device.\r\n";
static const char* const g_CreateSymbolicLinkError = "Failed to create symbolic link to device.\r\n";

class AutoEnterLeave
{
public:
	AutoEnterLeave() = delete;
	AutoEnterLeave(const AutoEnterLeave& other) = delete;
	AutoEnterLeave(AutoEnterLeave&& other) = delete;
	AutoEnterLeave& operator=(const AutoEnterLeave& other) = delete;
	AutoEnterLeave& operator=(AutoEnterLeave&& other) = delete;
	AutoEnterLeave(char* functionName) :
		m_FunctionName(functionName)
	{
		KdPrint((DRIVER_PREFIX "Entering: %s\r\n", m_FunctionName));
	}

	~AutoEnterLeave()
	{
		KdPrint((DRIVER_PREFIX "Leaving: %s\r\n", m_FunctionName));
	}

private:
	 const char* const m_FunctionName = "";
};
#define AUTO_ENTER_LEAVE() AutoEnterLeave autoEnterLeave(__FUNCTION__)