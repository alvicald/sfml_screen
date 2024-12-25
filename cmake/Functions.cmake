function(get_library_list LIB_DIRECTORY MASK LIBRARY_NAME_LIST)
	file(GLOB LIB_FILES "${LIB_DIRECTORY}/${MASK}")
	set(RESULT_LIST)

	foreach(file ${LIB_FILES})
		get_filename_component(file_name ${file} NAME)
		list(APPEND RESULT_LIST ${file_name})
	endforeach()

	set(${LIBRARY_NAME_LIST} ${RESULT_LIST} PARENT_SCOPE)
endfunction()
