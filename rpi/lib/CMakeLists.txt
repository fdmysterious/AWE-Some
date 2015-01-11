project(libcaveavin)

SET(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread")

add_library(
	caveavin
	STATIC
	
	sys/log.c

	core/parser.c
	
	net/function.c
	net/register.c
	net/socket.c
	net/client.c
	net/serverClient.c
	net/server.c

	fcgi/query_parser.c
)
