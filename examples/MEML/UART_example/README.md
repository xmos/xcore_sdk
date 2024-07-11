# MEML UART example

This example application demonstrates UART loopback on the XK-EVK-XU316.

It effectively makes minimal modifications to the `explorer_board`'s bare metal
example in order for that suite to run on the XK-EVK-XU316. Therefore all the 
other, non UART demos are still running on the board (see the README for those
examples for more detail) but have not been fully tested.

In order for the loopback to work, you must connect Pin 36 on J10 to pin 39 on J16.

## CMake Targets

The following CMake targets are provided:

- meml_uart_example
- run_meml_uart_example
- debug_meml_uart_example

## Deploying the Firmware

See the Programming Guide for information on building and running the application.
