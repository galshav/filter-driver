#pragma once
#include <ntddk.h>
#include "common.hpp"

// Device dispatch routines.
void unloadRoutine          (PDRIVER_OBJECT DriverObject);
NTSTATUS createCloseRoutine (PDEVICE_OBJECT DeviceObject, PIRP irp);
NTSTATUS ioctlRoutine       (PDEVICE_OBJECT DeviceObject, PIRP irp);

// IOCTL's handlers.
NTSTATUS IOCTLCreateFile (PDEVICE_OBJECT DeviceObject, PIRP irp, PIO_STACK_LOCATION stack);
NTSTATUS IOCTLReadFile   (PDEVICE_OBJECT DeviceObject, PIRP irp, PIO_STACK_LOCATION stack);
NTSTATUS IOCTLCloseFile  (PDEVICE_OBJECT DeviceObject, PIRP irp, PIO_STACK_LOCATION stack);
NTSTATUS IOCTLDefault    (PDEVICE_OBJECT DeviceObject, PIRP irp, PIO_STACK_LOCATION stack);

static const char* const g_CreateDeviceError = "Failed to create device.\r\n";
static const char* const g_CreateSymbolicLinkError = "Failed to create symbolic link to device.\r\n";