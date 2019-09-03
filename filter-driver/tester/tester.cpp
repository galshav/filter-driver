#include <Windows.h>
#include <exception>
#include <iostream>
#include "..\driverProject\common.hpp"

enum ReturnCodes
{
	Success			   =  0,
	Exception		   = -1,
	UnhandledException = -2,
};

void PrintUsage(const wchar_t* applicationName)
{
	std::wcout << "Usage: " << applicationName << " " << "FILE_PATH" << std::endl;
}

int wmain(const size_t argc, const wchar_t*const * const argv)
{
	argc;

	try
	{
		if (2 != argc)
		{
			PrintUsage(argv[0]);
			throw std::invalid_argument("Invalid number of arguments.");
		}

		const auto hDevice = CreateFileW(
			DRIVER_SYMBOLIC_LINK_PATH,
			GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);

		if (INVALID_HANDLE_VALUE == hDevice)
		{
			throw std::exception("Can not open device.");
		}

		std::cout << "Handle received: " << hDevice << std::endl;
		HANDLE outBuffer[1] = { 0 };
		CreateFileRequest request;
		request.Path = argv[1];
		DWORD bytesReturned = 0;
		const auto ioctlStatus = DeviceIoControl(
			hDevice,
			(DWORD)IOCTL_CREATE_FILE,
			&request,
			sizeof(request),
			outBuffer,
			sizeof(outBuffer),
			&bytesReturned,
			nullptr);

		if (FALSE == ioctlStatus)
		{
			CloseHandle(hDevice);
			throw std::exception("Can not send ioctl.");
		}

		CloseHandle(hDevice);
		std::cout << "Handle closed." << std::endl;
		return ReturnCodes::Success;
	}

	catch (const std::exception& error)
	{
		std::cout << "Error: " << error.what() <<std::endl;
		return ReturnCodes::Exception;
	}

	catch (...)
	{
		std::cout << "Unhandled exception." << std::endl;
		return ReturnCodes::UnhandledException;
	}
}