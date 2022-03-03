// Copyright (c) 2021 XMOS LIMITED. This Software is subject to the terms of the
// XMOS Public License: Version 1

#ifndef APP_CONF_CHECK_H_
#define APP_CONF_CHECK_H_


#if appconfUSB_ENABLED && appconfSPI_OUTPUT_ENABLED
#error Cannot use both USB and SPI interfaces
#endif

#if appconfI2S_TDM_ENABLED && appconfI2S_AUDIO_SAMPLE_RATE != 3*appconfAUDIO_PIPELINE_SAMPLE_RATE
#error appconfI2S_AUDIO_SAMPLE_RATE must be 48000 to use I2S TDM
#endif


#if OSPREY_BOARD
#if appconfI2C_CTRL_ENABLED
#error I2C device control not currently supported on Osprey
#endif
#if appconfI2S_ENABLED
#error I2S not currently supported on Osprey
#endif
#if appconfSPI_OUTPUT_ENABLED
#error SPI audio output not currently supported on Osprey
#endif
#endif

#if XVF3610_Q60A
#if appconfSPI_OUTPUT_ENABLED
#error SPI audio output not currently supported on XVF3610 board
#endif
#endif

#endif /* APP_CONF_CHECK_H_ */