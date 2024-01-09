SUCCESS='\e[32m'
MENU='\e[33m'
FILE='\e[35m'
NC='\e[0m'
FAILURE='\e[31m'
TESTFILE=("../grep/grep_worker.c" "../grep/grep_worker.h" "../grep/s21_grep.c" "../cat/cat_worker.c" "../cat/s21_cat.c" "grep_tests.sh")
FLAGS=("-e" "-c" "-v" "-s" "-n" "-i" "-o")
REGEXFILE=pattern.txt
REGEX='include'

rm -f basic_result test_result

cd ../grep
make rebuild
cp s21_grep ../tests/s21_grep
cd ../tests

cases=0
success_cases=0

printf "${MENU}----------------------------------------TESTS----------------------------------------${NC}\n"

for flag in "${FLAGS[@]}"
do
  for case in {1..10}
  do
  randomFile=${TESTFILE[ $RANDOM % ${#TESTFILE[@]} ]}
  grep $flag $REGEX $randomFile > basic_result
  ./s21_grep $flag $REGEX $randomFile > test_result
  any_err=$(diff basic_result test_result)
  ((cases++))

  if [ ! "$any_err"  ]; then
    printf "   ${SUCCESS}[SUCCESS] ${NC}Test [$cases] [file: ${FILE}${randomFile}${NC}] for ${MENU} [$case for '$flag'] ${NC}has been ${SUCCESS}passed${NC}\n"
    ((success_cases++))
  else
    printf "   ${FAILURE}[FAIL]    ${NC}Test [$cases] [file: ${FILE}${randomFile}${NC}] for ${MENU} [$case for '$flag'] ${NC}has been ${FAILURE}failed${NC}\n"
    printf "$any_err\n"
  fi
  done
done

printf "${MENU}-----------------Total amount of test cases $cases. Success cases $success_cases / $cases.-----------------${NC}\n"

rm -f s21_grep