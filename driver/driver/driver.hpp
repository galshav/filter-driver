#pragma once

_Function_class_(DRIVER_UNLOAD) void unloadRoutine(PDRIVER_OBJECT DriverObject);

#define DRIVER_PREFIX "Filter Driver - "
class AutoEnterLeave
{
public:
	AutoEnterLeave() = delete;
	AutoEnterLeave(char* functionName) :
		m_FunctionName(functionName)
	{
		DbgPrint(DRIVER_PREFIX "Entering: %s\r\n", m_FunctionName);
	}

	~AutoEnterLeave()
	{
		DbgPrint(DRIVER_PREFIX "Leaving: %s\r\n", m_FunctionName);
	}

private:
	 char*  m_FunctionName = "";
};
#define AUTO_ENTER_LEAVE() AutoEnterLeave autoEnterLeave(__FUNCTION__)