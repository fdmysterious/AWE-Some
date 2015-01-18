project(fcgi_simple_response)

SET(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread")

include_directories(
	${RPI_CAVEAVIN_SOURCE_DIR}
)

link_directories(
	${RPI_CAVEAVIN_SOURCE_DIR}
)

add_executable(
	fcgi_handler

	main.c
)

target_link_libraries(
	fcgi_handler
	caveavin
	fcgi
)
