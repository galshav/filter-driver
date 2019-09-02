#pragma once
#include <ntddk.h>

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
		KdPrint((DRIVER_PREFIX "Entering: %ws\r\n", m_FunctionName));
	}

	~AutoEnterLeave()
	{
		KdPrint((DRIVER_PREFIX "Leaving: %ws\r\n", m_FunctionName));
	}

private:
	const char* const m_FunctionName = "";
};