#include "driver.hpp"

extern "C"
NTSTATUS DriverEntry(
	const PDRIVER_OBJECT DriverObject,
	const PUNICODE_STRING)
{
	AUTO_ENTER_LEAVE();
	// Registrations.
	DriverObject->MajorFunction[IRP_MJ_CREATE] =
		DriverObject->MajorFunction[IRP_MJ_CLOSE] = createCloseRoutine;
	
	// Create device object.
	DriverObject->DriverUnload = unloadRoutine;
	UNICODE_STRING deviceName;
	RtlInitUnicodeString(&deviceName, DRIVER_DEVICE_PATH);
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
		KdPrint((g_CreateDeviceError));
		return createDeviceStatus;
	}

	// Create symbolic link to device object.
	UNICODE_STRING win32Name;
	RtlInitUnicodeString(&win32Name, DRIVER_SYMBOLIC_LINK_PATH);
	const auto createSymLinkStatus = IoCreateSymbolicLink(&win32Name, &deviceName);
	if (STATUS_SUCCESS != createSymLinkStatus)
	{
		DbgPrint((g_CreateSymbolicLinkError));
		IoDeleteDevice(deviceObject);
		return createSymLinkStatus;
	}

	return STATUS_SUCCESS;
}

void unloadRoutine(PDRIVER_OBJECT DriverObject)
{
	AUTO_ENTER_LEAVE();
	UNICODE_STRING win32Name;
	RtlInitUnicodeString(&win32Name, DRIVER_SYMBOLIC_LINK_PATH);
	IoDeleteSymbolicLink(&win32Name);
	IoDeleteDevice(DriverObject->DeviceObject);
}

NTSTATUS createCloseRoutine(PDEVICE_OBJECT, PIRP irp)
{
	AUTO_ENTER_LEAVE();
	irp->IoStatus.Information = 0;
	irp->IoStatus.Status = STATUS_SUCCESS;
	return STATUS_SUCCESS;
}
