#pragma once
#include <ntddk.h>
#include "common.hpp"

void unloadRoutine(PDRIVER_OBJECT DriverObject);
NTSTATUS createCloseRoutine(PDEVICE_OBJECT DeviceObject, PIRP irp);

static const char* const g_CreateDeviceError = "Failed to create device.\r\n";
static const char* const g_CreateSymbolicLinkError = "Failed to create symbolic link to device.\r\n";

#define AUTO_ENTER_LEAVE() AutoEnterLeave autoEnterLeave(__FUNCTION__)
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
