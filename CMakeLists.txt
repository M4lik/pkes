cmake_minimum_required(VERSION 3.8)
project(Ex4)

set(CMAKE_CXX_STANDARD 11)

add_executable(Ex4
        everytime.h
        Ex4.ino
        IMURegisters.h
        MotorControl.cpp
        MotorControl.h
        Odometry.cpp
        Odometry.h
        PID.cpp
        PID.h WallFollow.cpp WallFollow.h Distance.cpp Distance.h)
