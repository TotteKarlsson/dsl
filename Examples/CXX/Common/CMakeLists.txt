CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(CommonExamples)

if(${MSVC})
endif(${MSVC})

set(examples 	
	first_step 	
    timer
#    atom_groups 	
#    CF3 
#	ethanol 	
#    euler1 		   
#    euler2 
#	one_atom 	
#    read_from_file 
#    spin_echo 
#	three_atoms 
#    trajectory		
#    vectors
)

#--- Install stuff
foreach(example ${examples})
 add_subdirectory(${example})
endforeach(example)

#install (FILES Readme.txt 			DESTINATION Examples COMPONENT info)
#install (FILES Examples.groupproj 	DESTINATION Examples COMPONENT examples_source)
#install (FILES CMakeLists.txt 		DESTINATION Examples COMPONENT examples_source)
