#!/bin/bash

# Script to generate gcov coverage report for the FSM module.
# Usage: ./04-design-patterns/fsm/run_coverage.sh

# Exit on any error
set -e

# Identify the project root directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
PROJECT_ROOT="$( cd "$SCRIPT_DIR/../.." &> /dev/null && pwd )"
BUILD_DIR="$PROJECT_ROOT/build"

echo "--- Building project ---"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake ..
make fsm

echo ""
echo "--- Running FSM tests ---"
./04-design-patterns/fsm

echo ""
echo "--- Generating coverage report for fsm.c ---"
# Navigate to where CMake stores the object and coverage files
OBJ_DIR="$BUILD_DIR/04-design-patterns/CMakeFiles/fsm.dir/fsm"
cd "$OBJ_DIR"

# Run gcov on the fsm.c object file
gcov fsm.c.gcno

echo ""
echo "Done! You can find the detailed report at:"
echo "$OBJ_DIR/fsm.c.gcov"
echo ""
echo "Summary from the report:"
head -n 5 "fsm.c.gcov"
