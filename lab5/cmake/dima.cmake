#common functions used in project configuration/generation

function(find_or_download_and_compile_gtest)
	find_package(Git)
	if(GIT_FOUND)
		message("git found: ${GIT_EXECUTABLE}")
	else()
		message(FATAL_ERROR, "Nie znaleziono GITa! Pobierz go i dodaj do zmiennej srodowiskowej aby kontynuowac!")
	endif()
	
	enable_testing()
	find_package(GTest)
	if(GTEST_FOUND)
		message("gtest found: includes: ${GTEST_INCLUDE_DIRS}, libs: ${GTEST_LIBRARIES}")
		include_directories("${GTEST_INCLUDE_DIRS}")
	else()
		message("Nie znaleziono GTesta, bedzie proba pobrania go wg kodu od p. Dimy:")
		############### Download and unpack googletest at configure time
		configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
		execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
				RESULT_VARIABLE result
				WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)

		if(result)
			message(FATAL_ERROR "CMake step for googletest failed: ${result}")
		endif()
		execute_process(COMMAND ${CMAKE_COMMAND} --build .
				RESULT_VARIABLE result
				WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
		if(result)
			message(FATAL_ERROR "Build step for googletest failed: ${result}")
		endif()

		# Prevent overriding the parent project's compiler/linker
		# settings on Windows
		set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

		# Add googletest directly to our build. This defines
		# the gtest and gtest_main targets.
		add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
				${CMAKE_CURRENT_BINARY_DIR}/googletest-build
				EXCLUDE_FROM_ALL)

		message("Kod od p. Dimy wykonano")
	endif()
	
endfunction()
