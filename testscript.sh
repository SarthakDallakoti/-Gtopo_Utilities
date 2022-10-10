make gtopoEcho
make gtopoComp
make gtopoReduce


echo -e "Task 1 TESTS: gtopoEcho"
echo -e "\n"
echo -e "Checking gtopoEcho for No arguments: "
./gtopoEcho
echo $?
echo -e "\n"
echo -e "Testing gtopoEcho for wrong number of arguments: "
./gtopoEcho wrong.dem
echo $?
echo -e "\n"
echo -e "Testing gtopoEcho for non readable input file:"
./gtopoEcho wrong 10 10 out.dem
echo $?
echo -e "\n"

echo -e "Testing gtopoEcho for bad Dimensions:"
./gtopoEcho dimension.dem a 10 out.dem
echo $?
echo -e "\n"

echo -e "Testing gtopoEcho for Bad CommentLine:"
./gtopoEcho badcomment.dem 2 2 ./testdems/gtopo_reduced_6_6.dem
echo $?
echo -e "\n"

echo -e "Testing gtopoEcho for failed write:"
./gtopoEcho echo.dem 2 2 ./testdems/gtopo_reduced_6_6.dem
echo $?
echo -e "\n"

echo -e "Testing gtopoEcho for successful file copy:"
./gtopoEcho ./testdems/gtopo_reduced_6_6.dem 10 10 Echo.dem
echo $?
echo -e "\n"
echo -e "\n"
echo -e "--------------------------------------------------------------------------------------"

echo -e "Task 2 TESTS: gtopoComp"
echo -e "\n"
echo -e "Checking gtopoComp for No arguments:"
./gtopoComp
echo $?
echo -e "\n"
echo -e "Testing gtopoComp for wrong number of arguments:  "
./gtopoComp   wrong.dem
echo $?
echo -e "\n"
echo -e "Testing gtopoComp for non readable input file:"
./gtopoComp wrong 10 10 out.dem
echo $?
echo -e "\n"

echo -e "Testing gtopoComp for bad Dimensions:"
./gtopoComp gtopo.dem a 10 out.dem
echo -e " "
echo $?
echo -e "\n"

echo -e "Testing gtopoComp for Bad CommentLine: "
./gtopoComp badcomment.dem 2 2 ./testdems/gtopo_reduced_6_6.dem
echo $?
echo -e "\n"

echo -e "Testing gtopoComp for DIFFERENT file comparison:"
./gtopoComp ./testdems/gtopo_reduced_6_6.dem 10 10 ./testdems/gtopo_reduced_6_5.dem
echo $?
echo -e "\n"

echo -e "Testing gtopoComp for successful file comparison:"
./gtopoComp ./testdems/gtopo_reduced_6_6.dem 10 10 ./testdems/gtopo_reduced_6_6.dem
echo $?
echo -e "\n"
echo -e "\n"
echo -e "--------------------------------------------------------------------------------------"

echo -e "Task 3 TESTS"
echo -e " Checking gtopoReduce for No arguments:"
./gtopoReduce
echo $?
echo -e "\n"
echo -e "Testing gtopoReduce for wrong number of arguments:  "
./gtopoReduce   wrong.dem
echo $?
echo -e "\n"
echo -e "Testing gtopoReduce for non readable input file:"
./gtopoReduce wrong 2 2 1 out.dem
echo $?
echo -e "\n"
echo -e "Testing gtopoReduce for non integer reduction factor:"
./gtopoReduce gtopo.dem 2 2 a red.dem
echo $?
echo -e "\n"
echo -e "Testing gtopoReduce for negative reduction factor:"
./gtopoReduce gtopo.dem 2 2 -2 bred.dem
echo $?
echo -e "\n"

echo -e "Testing gtopoReduce for Bad Dimensions:"
./gtopoReduce gtopo.dem 2 a 1 reds.dem
echo $?
echo -e "\n"
echo -e "Testing gtopoReduce for Bad CommentLine:"
./gtopoReduce badcomment.dem 2 2 1 out.dem
echo $?
echo -e "\n"

echo -e "Testing gtopoReduce for failed write:"
./gtopoReduce gtopo.dem 2 2 1 ./testdems/gtopo_reduced_6_6.dem
echo $?
echo -e "\n"
echo -e "Testing gtopoReduce for successful image reduction:"
./gtopoReduce ./testdems/gtopo_reduced_6_6.dem  10 10 3 reduced.dem
echo $?
echo -e "\n"
echo -e "\n"

rm reduced.dem
rm passedecho.dem
