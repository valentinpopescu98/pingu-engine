file(GLOB libraries "${LIB_DIR}/*.so.*")
foreach(library IN LISTS libraries)
    execute_process(
        COMMAND "${PATCHELF}" --set-rpath "$ORIGIN" "${library}"
        RESULT_VARIABLE result
        ERROR_VARIABLE error)
    if(NOT result EQUAL 0)
        message(FATAL_ERROR "Failed to patch ${library}: ${error}")
    endif()
endforeach()
