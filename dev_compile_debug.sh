#!/bin/bash
cmake .. -DWITH_DL:BOOL=ON -DWITH_LLVM:BOOL=ON -DWITH_PYTHON_INTERRUPTS:BOOL=ON -DWITH_OPENMP:BOOL=ON -DWITH_ACADO:BOOL=ON -DWITH_OOQP:BOOL=ON -DCMAKE_BUILD_TYPE:STRING=Debug
