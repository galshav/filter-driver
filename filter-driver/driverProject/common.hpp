#pragma once
#define DRIVER_PREFIX "Filter Driver - "
#define DRIVER_NAME "filter-driver"
#define DRIVER_DEVICE_PATH L"\\Device\\" DRIVER_NAME
#define DRIVER_SYMBOLIC_LINK_PATH L"\\??\\" DRIVER_NAME

// IOCTL's codes.
#define IOCTL_CREATE_FILE CTL_CODE (0x8000, 0x0800, METHOD_BUFFERED, FILE_READ_DATA)
#define IOCTL_READ_FILE CTL_CODE   (0x8000, 0x0801, METHOD_BUFFERED, FILE_READ_DATA)
#define IOCTL_CLOSE_FILE CTL_CODE  (0x8000, 0x0802, METHOD_BUFFERED, FILE_READ_DATA)

// Requests information.
typedef struct _CreateFileRequest
{
	const wchar_t* Path;
} CreateFileRequest, *PCreateFileRequest;