cmake_minimum_required(VERSION 2.6)
project(PCSC_MonteCarlo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

find_package(Lua REQUIRED)

add_executable( MCMoments_Calculator UserInterface.cpp FunctionLua.cpp
        FunctionLua.h FunctionDiscrete.cpp FunctionDiscrete.h Function.h
        ReadFunction.h ReadLua.cpp ReadLua.h ReadDiscrete.cpp
        ReadDiscrete.h MCSimulator.cpp MCSimulator.h RandomGenerator.cpp
        RandomGenerator.h RandomUniform.cpp RandomUniform.h
        Exception.cpp Exception.h FileNotFoundException.cpp FileNotFoundException.h
        FileFormatException.cpp FileFormatException.h
        MomentComputerManager.cpp MomentComputerManager.h
        DataPointReadingException.cpp DataPointReadingException.h DataPoint.cpp DataPoint.h
        FunctionException.cpp FunctionException.h
        FunctionalityNotAvailableException.cpp FunctionalityNotAvailableException.h
        RandomNormal.cpp RandomNormal.h CriticalException.cpp CriticalException.h ExceptionManager.cpp
        ExceptionManager.h RandomExponential.cpp RandomExponential.h Custom_Util.cpp Custom_Util.h)

include_directories(${LUA_INCLUDE_DIR})
target_link_libraries(MCMoments_Calculator ${LUA_LIBRARIES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Test_Suite")


add_executable(Test_Suite Test_Suite.cpp FunctionLua.cpp
        FunctionLua.h FunctionDiscrete.cpp FunctionDiscrete.h Function.h
        ReadFunction.h ReadLua.cpp ReadLua.h ReadDiscrete.cpp
        ReadDiscrete.h MCSimulator.cpp MCSimulator.h RandomGenerator.cpp
        RandomGenerator.h RandomUniform.cpp RandomUniform.h
        Exception.cpp Exception.h FileNotFoundException.cpp FileNotFoundException.h
        FileFormatException.cpp FileFormatException.h
        MomentComputerManager.cpp MomentComputerManager.h
        DataPointReadingException.cpp DataPointReadingException.h DataPoint.cpp DataPoint.h
        FunctionException.cpp FunctionException.h
        FunctionalityNotAvailableException.cpp FunctionalityNotAvailableException.h
        RandomNormal.cpp RandomNormal.h CriticalException.cpp CriticalException.h ExceptionManager.cpp
        ExceptionManager.h RandomExponential.cpp RandomExponential.h Custom_Util.cpp Custom_Util.h)


include_directories(${LUA_INCLUDE_DIR})
target_link_libraries(Test_Suite ${LUA_LIBRARIES})



