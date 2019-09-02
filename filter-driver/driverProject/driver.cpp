#include "driver.hpp"
#include "AutoEnterLeave.hpp"

extern "C"
NTSTATUS DriverEntry(
	const PDRIVER_OBJECT DriverObject,
	const PUNICODE_STRING)
{
	AUTO_ENTER_LEAVE();
	// Registrations.
	DriverObject->MajorFunction[IRP_MJ_CREATE] = createCloseRoutine;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = createCloseRoutine;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = ioctlRoutine;
	
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
		KdPrint((g_CreateSymbolicLinkError));
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
	NTSTATUS status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;
	irp->IoStatus.Status = status;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return status;
}

NTSTATUS ioctlRoutine(PDEVICE_OBJECT DeviceObject, PIRP irp)
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	const auto stack = IoGetCurrentIrpStackLocation(irp);
	switch (stack->Parameters.DeviceIoControl.IoControlCode)
	{
	case IOCTL_CREATE_FILE:
		status = IOCTLCreateFile(DeviceObject, irp, stack);
		break;

	case IOCTL_READ_FILE:
		status = IOCTLReadFile(DeviceObject, irp, stack);
		break;

	case IOCTL_CLOSE_FILE:
		status = IOCTLCloseFile(DeviceObject, irp, stack);
		break;

	default:
		status = IOCTLDefault(DeviceObject, irp, stack);
		break;
	}

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return status;
}

NTSTATUS IOCTLCreateFile(PDEVICE_OBJECT DeviceObject, PIRP irp, PIO_STACK_LOCATION stack)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(irp);
	UNREFERENCED_PARAMETER(stack);
	return NTSTATUS();
}

NTSTATUS IOCTLReadFile(PDEVICE_OBJECT DeviceObject, PIRP irp, PIO_STACK_LOCATION stack)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(irp);
	UNREFERENCED_PARAMETER(stack);
	return NTSTATUS();
}

NTSTATUS IOCTLCloseFile(PDEVICE_OBJECT DeviceObject, PIRP irp, PIO_STACK_LOCATION stack)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(irp);
	UNREFERENCED_PARAMETER(stack);
	return NTSTATUS();
}

NTSTATUS IOCTLDefault(PDEVICE_OBJECT, PIRP irp, PIO_STACK_LOCATION)
{
	NTSTATUS status = STATUS_NOT_IMPLEMENTED;
	irp->IoStatus.Status = status;
	irp->IoStatus.Information = 0;
	return status;
}