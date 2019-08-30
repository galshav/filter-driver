#include <ntddk.h>

extern "C"
NTSTATUS DriverEntry(
	const PDRIVER_OBJECT DriverObject,
	const PUNICODE_STRING  RegistryPath)
{
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	return STATUS_SUCCESS;
}