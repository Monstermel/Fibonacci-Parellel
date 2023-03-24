#!/bin/bash
g++ Fibonacci-Parellel/bm_test.cpp -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark
