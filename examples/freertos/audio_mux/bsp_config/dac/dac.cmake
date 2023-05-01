
## Create custom board targets for dacs
add_library(xcore_iot_example_audio_mux_board_support_dac_aic3204 INTERFACE)
target_sources(xcore_iot_example_audio_mux_board_support_dac_aic3204
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/aic3204/aic3204.c
)
target_include_directories(xcore_iot_example_audio_mux_board_support_dac_aic3204
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/aic3204
)
target_compile_definitions(xcore_iot_example_audio_mux_board_support_dac_aic3204
    INTERFACE
        AIC3204=1
)

## Create an alias
add_library(xcore_iot::example::audio_mux::dac::aic3204 ALIAS xcore_iot_example_audio_mux_board_support_dac_aic3204)
