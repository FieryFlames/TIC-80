################################
# TIC-80 app (PSP)
################################

if(PSP)
    set(TIC80_SRC ${TIC80_SRC}
        ${CMAKE_SOURCE_DIR}/src/system/psp/main.c
    )

    add_executable(tic80_psp ${TIC80_SRC})

    target_include_directories(tic80_psp PRIVATE
        ${PSPDEV}
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src)

    target_link_libraries(tic80_psp PRIVATE pspdebug pspdisplay pspge)

    create_pbp_file(
        TARGET tic80_psp
        ICON_PATH ${CMAKE_SOURCE_DIR}/build/cart.png
        BACKGROUND_PATH NULL
        PREVIEW_PATH NULL
        TITLE ${PROJECT_NAME}
        VERSION 01.00
    )
    #target_link_directories(tic80_n3ds PRIVATE ${DEVKITPRO}/libctru/lib ${DEVKITPRO}/portlibs/3ds/lib)
    #target_link_libraries(tic80_n3ds tic80studio png citro3d)

    #add_custom_command(TARGET tic80_n3ds
    #       POST_BUILD
    #           COMMAND ${CMAKE_SOURCE_DIR}/build/n3ds/elf_to_3dsx.sh
    #       WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build
    #)
endif()