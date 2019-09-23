#!/bin/bash

cd build/ && cmake .. && make && cd .. && bash performance.sh
