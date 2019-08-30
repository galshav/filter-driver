#pragma once

_Function_class_(DRIVER_UNLOAD) void unloadRoutine(PDRIVER_OBJECT DriverObject);

class AutoEnterLeave
{
public:
	AutoEnterLeave(char* functionName) :
		m_FunctionName(functionName)
	{
		DbgPrint((L"Entering function: %s\r\n", m_FunctionName));
	}

	~AutoEnterLeave()
	{
		DbgPrint((L"Leaving function: %s\r\n", m_FunctionName));
	}

private:
	 char*  m_FunctionName = "";
};

#define AUTO_ENTER_LEAVE() AutoEnterLeave autoEnterLeave(__FUNCTION__)