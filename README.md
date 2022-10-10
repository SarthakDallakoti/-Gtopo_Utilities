# -Gtopo_Utilities

This file contains information regarding how to run the program.

1. To make executables: Open terminal in the directory where all the .c files are and type make.
2. After that you can type ./testscript.sh to see all the test and their output.
	For the first time use: chmod u+x testscript.sh
	Then type:./testscript.sh
   If you would like to test a particular test then the you need to use following command:

   	Usage: ./gtopoEcho inputFile width height outputFile
	Usage: ./gtopoComp firstFile width height secondFile
	Usage: ./gtopoReduce input width height reduction_factor output

3. You can file useful gtopo Images in following directory: assignment_1/gtopoImages

4. You can also delete the .o file by using make clean command.

(FYI: This piece of work was submitted to University of Leeds)
