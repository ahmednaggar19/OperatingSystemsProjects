cmake_minimum_required(VERSION 3.5)
project(shell)

set(CMAKE_CXX_STANDARD 11)

add_executable(shell
	main.c
	parser/Parser.c
	parser/CommandNormalizer.c
        environment/Environment.c
        environment/Variables.c
	utils/Constants.c
	executers/InteractiveExecuter.c
	executers/CommandExecuter.c
	executers/RegisteredCommands.c
	executers/BatchExecuter.c
	file_handlers/FileReader.c)
