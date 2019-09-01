#include <Windows.h>
#include <exception>
#include <iostream>
#include "..\driverProject\common.hpp"

enum ReturnCodes
{
	Success = 0,
	Exception = -1,
	UnhandledException = -2,
};

int main(const size_t argc, const char* const* const argv)
{
	try
	{
		const auto hDevice = CreateFileW(
			DRIVER_SYMBOLIC_LINK_PATH,
			GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hDevice)
		{
			std::cout << "Can not open device." << std::endl;
		}

		std::cout << "Handle received: " << hDevice << std::endl;
		return ReturnCodes::Success;
	}

	catch (const std::exception& error)
	{
		std::cout << "Error: " << error.what();
		return ReturnCodes::Exception;
	}

	catch (...)
	{
		std::cout << "Unhandled exception.\r\n";
		return ReturnCodes::UnhandledException;
	}
}
