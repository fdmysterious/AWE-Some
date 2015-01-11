project(daemon)

SET(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread")

include_directories(
	${RPI_CAVEAVIN_SOURCE_DIR}
)

link_directories(
	${RPI_CAVEAVIN_SOURCE_DIR}
)

add_executable(
	daemon	

	main.c
)

target_link_libraries(
	daemon	
	caveavin
)
