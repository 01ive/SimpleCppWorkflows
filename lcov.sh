#!/usr/bin/bash
cd build
lcov --capture --directory $1 --output-file coverage.info
genhtml coverage.info --output-directory html_coverage
