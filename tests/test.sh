#/bin/bash

CASE1='49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d'
CASE2='77'
CASE3='7796'

EXPECT1='SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t'
EXPECT2='dw=='
EXPECT3='d5Y='

TEST1=$(./hex2base64 $CASE1)
if [[ $TEST1 == $EXPECT1 ]]; then
	echo test 1 passed
else
	echo test 1 failed expected $TEST1 to equal $EXPECT1
	exit 1
fi

TEST2=$(./hex2base64 $CASE2)
if [[ $TEST2 == $EXPECT2 ]]; then
	echo test 2 passed
else
	echo test 2 failed expected $TEST2 to equal $EXPECT2
	exit 1
fi

TEST3=$(./hex2base64 $CASE3)
if [[ $TEST3 == $EXPECT3 ]]; then
	echo test 3 passed
else
	echo test 3 failed expected $TEST3 to equal $EXPECT3
	exit 1
fi

echo all tests pass
