CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(DBExamples)

set(examples 	
example_1 	
)

#--- Install stuff
foreach(example ${examples})
 add_subdirectory(${example})
endforeach(example)

