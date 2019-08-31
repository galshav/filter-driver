#include <ntddk.h>
#include "driver.hpp"

extern "C"
NTSTATUS DriverEntry(
	const PDRIVER_OBJECT DriverObject,
	const PUNICODE_STRING  RegistryPath)
{
	AUTO_ENTER_LEAVE();
	// Create device object.
	UNREFERENCED_PARAMETER(RegistryPath);
	DriverObject->DriverUnload = unloadRoutine;
	UNICODE_STRING deviceName;
	RtlInitUnicodeString(&deviceName, L"\\Device\\filter-driver");
	PDEVICE_OBJECT deviceObject = nullptr;
	const auto createDeviceStatus = IoCreateDevice(
		DriverObject,
		0,
		&deviceName,
		FILE_DEVICE_UNKNOWN,
		DO_BUFFERED_IO,
		FALSE,
		&deviceObject);

	if (STATUS_SUCCESS != createDeviceStatus)
	{
		DbgPrint(("Failed to create device.\n"));
		return createDeviceStatus;
	}

	// Create symbolic link to device object.
	UNICODE_STRING win32Name;
	RtlInitUnicodeString(&win32Name, L"\\??\\filter-driver");
	const auto createSymLinkStatus = IoCreateSymbolicLink(&win32Name, &deviceName);
	if (STATUS_SUCCESS != createSymLinkStatus)
	{
		DbgPrint(("Failed to create symbolic link to device."));
		IoDeleteDevice(deviceObject);
		return createSymLinkStatus;
	}
	int* ptr = nullptr;
	*ptr = 0;
	return STATUS_SUCCESS;
}

void unloadRoutine(PDRIVER_OBJECT DriverObject)
{
	AUTO_ENTER_LEAVE();
	UNICODE_STRING win32Name;
	RtlInitUnicodeString(&win32Name, L"\\??\\filter-driver");
	IoDeleteSymbolicLink(&win32Name);
	IoDeleteDevice(DriverObject->DeviceObject);
}
