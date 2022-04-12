project(<micropitcher> VERSION 0.0.1)

set (BaseTargetName micropitcher)

juce_add_plugin("${BaseTargetName}"
    COMPANY_NAME "Evan Snoswell"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT TRUE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Juce
    PLUGIN_CODE mipi
    FORMATS AU VST3
    PRODUCT_NAME "micropitcher"
)

target_sources(${BaseTargetName} PRIVATE
    PluginProcessor.cpp
    PluginEditor.cpp
)

target_compile_definitions(${BaseTargetName}
    PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(${BaseTargetName} PRIVATE
    shared_plugin_helpers
    juce_recommended_config_flags
    juce_recommended_lto_flags
    juce_recommended_warning_flags
)

