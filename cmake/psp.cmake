################################
# TIC-80 app (PSP)
################################

if(PSP)
    set(TIC80_SRC ${TIC80_SRC}
        ${CMAKE_SOURCE_DIR}/src/system/psp/gu.c
        ${CMAKE_SOURCE_DIR}/src/system/psp/input.c
    )
endif()

if(PSP AND NOT BUILD_PLAYER)
    set(TIC80_SRC ${TIC80_SRC}
        ${CMAKE_SOURCE_DIR}/src/system/psp/main.c
    )

    add_executable(tic80_psp ${TIC80_SRC})

    target_include_directories(tic80_psp PRIVATE
        ${PSPDEV}
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src)

    target_link_libraries(tic80_psp PRIVATE pspdebug pspdisplay pspge pspgu psprtc pspctrl)
    target_link_libraries(tic80_psp PRIVATE tic80studio)

    create_pbp_file(
        TARGET tic80_psp
        ICON_PATH NULL
        BACKGROUND_PATH NULL
        PREVIEW_PATH NULL
        TITLE ${PROJECT_NAME}
        VERSION 01.00
    )
endif()

if(PSP AND BUILD_PLAYER)
    set(TIC80_SRC ${TIC80_SRC}
        ${CMAKE_SOURCE_DIR}/src/system/psp/player.c
    )

    add_executable(tic80_psp_player ${TIC80_SRC})

    target_include_directories(tic80_psp_player PRIVATE
        ${PSPDEV}
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src)

    target_link_libraries(tic80_psp_player PRIVATE pspdisplay pspge pspgu psprtc pspctrl)
    target_link_libraries(tic80_psp_player PRIVATE tic80core)

    create_pbp_file(
        TARGET tic80_psp_player
        ICON_PATH NULL
        BACKGROUND_PATH NULL
        PREVIEW_PATH NULL
        TITLE ${PROJECT_NAME}
        VERSION 01.00
    )
endif()