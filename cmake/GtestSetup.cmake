#Ref: http://google.github.io/googletest/quickstart-cmake.html
# find_package(GTest)
# if(NOT googletest_FOUND)
#https://cmake.org/cmake/help/latest/module/FetchContent.html
include(FetchContent)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
	FetchContent_Declare(
	googletest
	#version v1.16.0
	URL https://github.com/google/googletest/archive/6910c9d9165801d8827d628cb72eb7ea9dd538c5.zip
	)
	# For Windows: Prevent overriding the parent project's compiler/linker settings
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

	FetchContent_MakeAvailable(googletest)
endif()
# endif()

