#!/bin/bash
set -e

echo "compiling:"
gcc -Wall -Werror -Wextra get_next_line.c exam_main.c -o gnl_yours
gcc -Wall -Werror -Wextra get_next_line_niks.c exam_main.c -o gnl_niks
echo "test with exam_main.c"
./gnl_yours < exam_main.c > yours.txt
./gnl_niks < exam_main.c > mine.txt
if diff yours mine > /dev/null 2>&1
then
	echo "ERRORS, differences found in differences.txt:"
	diff yours.txt mine.txt
	diff yours.txt mine.txt > differences.txt
	exit 1
else
  echo "OK!"
fi
echo "test with biglinelol (big file, long line without newline)"
./gnl_yours < biglinelol > yours.txt
./gnl_niks < biglinelol > mine.txt
if diff yours mine > /dev/null 2>&1
then
	echo "ERRORS, differences found in differences.txt:"
	diff yours.txt mine.txt
	diff yours.txt mine.txt > differences.txt
	exit 1
else
  echo "OK!"
fi
echo "test with empty file"
./gnl_yours < empty_file > yours.txt
./gnl_niks < empty_file > mine.txt
if diff yours mine > /dev/null 2>&1
then
	echo "ERRORS, differences found in differences.txt:"
	diff yours.txt mine.txt
	diff yours.txt mine.txt > differences.txt
	exit 1
else
  echo "OK!"
fi