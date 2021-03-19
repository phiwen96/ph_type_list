

file(GLOB_RECURSE HEADER_LIST "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB SOURCE_LIST ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library (phore
	${SOURCE_LIST}  ${HEADER_LIST} 
)



ph_precompile (TARGET phore PUBLIC PCH ${std_pch} ${boost_pch})

add_library (ph::phore ALIAS phore)
target_link_libraries (phore PRIVATE ${Boost_LIBRARIES})
target_include_directories (phore PUBLIC ${PROJECT_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})

target_compile_features (phore PUBLIC cxx_std_20)


target_include_directories(phore PRIVATE
    $<BUILD_INTERFACE:${phore_SOURCE_DIR}/include/phore>
    $<INSTALL_INTERFACE:include/phore>
)

target_include_directories(phore PUBLIC
    $<BUILD_INTERFACE:${phore_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)