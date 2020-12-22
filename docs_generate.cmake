function(docs_generate DOXYGEN_INPUT DOC_SNAPSHOTS_DIR OUTPUT_DIR)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        set(DOXYGEN_IN  ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in)
        set(DOXYGEN_CONF ${CMAKE_SOURCE_DIR}/docs/Doxyfile)

        # 将DOXYGEN_IN配置文件中"DOXYGEN_INPUT"和"OUTPUT_DIR"替换,生成doxygen配置文件
        configure_file(${DOXYGEN_IN} ${DOXYGEN_CONF} @ONLY)

        # 添加自定义目标docs
        add_custom_target(docs ALL
                ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONF}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM)
        add_dependencies(docs ${PROJECT_NAME})

        # 将控件截图拷贝到文档生成目录
        add_custom_command(TARGET docs
                POST_BUILD
                COMMAND cp -r ${DOC_SNAPSHOTS_DIR} ${OUTPUT_DIR}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Copy documentation snapshots"
                VERBATIM)

        #　添加安装选项
        install(DIRECTORY ${OUTPUT_DIR} DESTINATION ${SHARE_INSTALL_PREFIX}/docs/${PROJECT_NAME} )
    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endfunction()