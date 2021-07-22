


set (include_dir "${CMAKE_CURRENT_LIST_DIR}/../include/ph_type_list")
set (src_dir "${CMAKE_CURRENT_LIST_DIR}")

ph_create_modules (

	MODULES 
		"type_list"

	INCLUDE
		"${include_dir}"

	SRC 
		"${src_dir}"
)

file(GLOB_RECURSE HEADER_LIST "${include_dir}/*.hpp")
file(GLOB SOURCE_LIST "${src_dir}/*.cpp")

add_library (ph_type_list
	${SOURCE_LIST}  ${HEADER_LIST} 
)



ph_precompile (TARGET ph_type_list PUBLIC PCH ${std_pch} ${boost_pch})

add_library (ph::type_list ALIAS ph_type_list)
target_link_libraries (ph_type_list PRIVATE ${Boost_LIBRARIES})
target_include_directories (ph_type_list PUBLIC ${PROJECT_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})

target_compile_features (ph_type_list PUBLIC cxx_std_20)


target_include_directories(ph_type_list PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/ph_type_list>
    $<INSTALL_INTERFACE:include/ph_type_list>
)

target_include_directories(ph_type_list PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

else()
    set_target_properties(${PROJECT_NAME}          PROPERTIES FOLDER "dependencies/${PROJECT_NAME}")
endif()