# SRC

set(Executable_Name client)
add_executable(${Executable_Name} client.cc)
target_link_libraries(${Executable_Name} ${CONAN_LIBS})
target_compile_options(${Executable_Name} PRIVATE -Werror 
    -Wall 
    -Wextra 
    # -Wconversion 
    # -Wsign-conversion
    )

set(Executable_Name server)
add_executable(${Executable_Name} server.cc)
target_link_libraries(${Executable_Name} ${CONAN_LIBS})
target_compile_options(${Executable_Name} PRIVATE -Werror 
    -Wall 
    -Wextra 
    # -Wconversion 
    # -Wsign-conversion
    )