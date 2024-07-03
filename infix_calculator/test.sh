#!/bin/bash
FAIL=0

# Function to run a single test of the infix_10 program.
testinfix_10() {
  TESTNO=$1
  ESTATUS=$2

  rm -f output.txt
  
  echo "Test $TESTNO: ./infix_10 < input-10-$TESTNO.txt > output.txt"
  ./infix_10 < input-10-$TESTNO.txt > output.txt
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** FAILED - Expected an exit status of $ESTATUS, but got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure output matches expected output.
  if ! diff -q expected-10-$TESTNO.txt output.txt >/dev/null 2>&1 ; then
      echo "**** FAILED - output didn't match expected output."
      FAIL=1
      return 1
  fi

  echo "PASS"
  return 0
}

# Function to run a single test of the infix_32 program.
testinfix_32() {
  TESTNO=$1
  ESTATUS=$2

  rm -f output.txt
  
  echo "Test $TESTNO: ./infix_32 < input-32-$TESTNO.txt > output.txt"
  ./infix_32 < input-32-$TESTNO.txt > output.txt
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** FAILED - Expected an exit status of $ESTATUS, but got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure output matches expected output.
  if ! diff -q expected-32-$TESTNO.txt output.txt >/dev/null 2>&1 ; then
      echo "**** FAILED - output didn't match expected output."
      FAIL=1
      return 1
  fi

  echo "PASS"
  return 0
}

# Function to run a single test of the infix_n program.
testinfix_n() {
  TESTNO=$1
  ESTATUS=$2

  rm -f output.txt
  
  echo "Test $TESTNO: ./infix_n < input-n-$TESTNO.txt > output.txt"
  ./infix_n < input-n-$TESTNO.txt > output.txt
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** FAILED - Expected an exit status of $ESTATUS, but got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure output matches expected output.
  if ! diff -q expected-n-$TESTNO.txt output.txt >/dev/null 2>&1 ; then
      echo "**** FAILED - output didn't match expected output."
      FAIL=1
      return 1
  fi

  echo "PASS"
  return 0
}

# Try to get a fresh compile of the project.
echo "Running make clean"
make clean

echo "Building infix_10 with make"
make infix_10
if [ $? -ne 0 ]; then
    echo "**** Make didn't run succesfully when trying to build your infix_10 program."
    FAIL=1
fi

# Run tests for infix_10
if [ -x infix_10 ] ; then
    testinfix_10 01 0
    testinfix_10 02 0
    testinfix_10 03 0
    testinfix_10 04 0
    testinfix_10 05 0
    testinfix_10 06 0
    testinfix_10 07 0
    testinfix_10 08 0
    testinfix_10 09 0
    testinfix_10 10 0
    testinfix_10 11 0
    testinfix_10 12 100
    testinfix_10 13 102
    testinfix_10 14 101
    testinfix_10 15 0
    testinfix_10 16 100
else
    echo "**** Your infix_10 program couldn't be tested since it didn't compile successfully."
    FAIL=1

fi

echo "Building infix_32 with make"
make infix_32
if [ $? -ne 0 ]; then
    echo "**** Make didn't run succesfully when trying to build your infix_32 program."
    FAIL=1
fi

# Run tests for infix_32
if [ -x infix_32 ] ; then
    testinfix_32 01 0
    testinfix_32 02 0
    testinfix_32 03 0
    testinfix_32 04 0
    testinfix_32 05 0
    testinfix_32 06 0
    testinfix_32 07 0
    testinfix_32 08 102
    testinfix_32 09 100
    testinfix_32 10 100
    testinfix_32 11 102
else
    echo "**** Your infix_32 program couldn't be tested since it didn't compile successfully."
    FAIL=1

fi

echo "Building infix_n with make"
make infix_n
if [ $? -ne 0 ]; then
    echo "**** Make didn't run succesfully when trying to build your infix_n program."
    FAIL=1
fi

# Run tests for infix_n
if [ -x infix_n ] ; then
    testinfix_n 01 0
    testinfix_n 02 0
    testinfix_n 03 100
    testinfix_n 04 0
    testinfix_n 05 101
    testinfix_n 06 0
    testinfix_n 07 0
    testinfix_n 08 102
    testinfix_n 09 102
    testinfix_n 10 0
else
    echo "**** Your infix_n program couldn't be tested since it didn't compile successfully."
    FAIL=1

fi

if [ $FAIL -ne 0 ]; then
  echo "**** There were failing tests"
  exit 1
else 
  echo "Tests successful"
  exit 0
fi
