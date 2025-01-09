SUCCESS=0
FAIL=0
DIFF_RES=""
FLAGS=(-n -e -b -s -t -v -E -T) 
TEST_FILE="cat_file_test.txt"
LOGER="cat_log.txt"
echo "" > cat_log.txt

for var in "${FLAGS[@]}"
do
    TEST="$var $TEST_FILE"
    ./s21_cat $TEST > s21_cat.txt 
    cat $TEST > cat.txt
    if cmp -s s21_cat.txt cat.txt; then
        ((SUCCESS++))
    else
        echo $TEST >> $LOGER
        ((FAIL++))
        rm $LOGER
        echo "FAILURES: $FAIL"
        exit 1
    fi
     rm s21_cat.txt cat.txt
done

echo SUCCESS: $SUCCESS
echo FAIL: $FAIL