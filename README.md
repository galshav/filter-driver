The filter playground project

Deplyments setps:
1. Create the service in the machine:
	In elevated command line enter: "sc create DRIVER_NAME binPath= DRIVER_SYS_PATH type= kernel"
	
2. Run the driver:
	sc start DRIVER_NAME
	
3. Stop the driver:
	sc stop DRIVER_NAME