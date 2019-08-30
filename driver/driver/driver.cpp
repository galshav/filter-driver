#include <ntddk.h>

extern "C"
NTSTATUS DriverEntry(
	const PDRIVER_OBJECT DriverObject,
	const PUNICODE_STRING  RegistryPath)
{
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	//UNICODE_STRING deviceName;
	//RtlInitUnicodeString(&deviceName, L"\\Device\\filter-driver");
	//PDEVICE_OBJECT deviceObject;
	//IoCreateDevice(DriverObject, 0, &deviceName, FILE_DEVICE_UNKNOWN, DO_BUFFERED_IO, FALSE, &deviceObject);

	return STATUS_SUCCESS;
}