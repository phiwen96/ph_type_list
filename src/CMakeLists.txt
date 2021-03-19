

file(GLOB_RECURSE HEADER_LIST "${phore_SOURCE_DIR}/include/*.hpp")
file(GLOB SOURCE_LIST ${phore_SOURCE_DIR}/src/*.cpp)

add_library (phore
	${SOURCE_LIST}  ${HEADER_LIST} 
)

add_library (ph::phore ALIAS phore)

target_include_directories (phore PUBLIC ${const_str_SOURCE_DIR}/include)

target_compile_features (phore PUBLIC cxx_std_20)


target_include_directories(phore PRIVATE
    $<BUILD_INTERFACE:${phore_SOURCE_DIR}/include/phore>
    $<INSTALL_INTERFACE:include/phore>
)

target_include_directories(phore PUBLIC
    $<BUILD_INTERFACE:${phore_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)