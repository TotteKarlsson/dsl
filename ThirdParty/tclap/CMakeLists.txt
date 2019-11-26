cmake_minimum_required(VERSION 2.8)
project(TCLAP)

    FILE (GLOB headers *.h)
    install (   
        FILES ${headers} 	 		 	
        DESTINATION include/tclap 
        COMPONENT cxx_headers
    )


