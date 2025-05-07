cmake_minimum_required(VERSION 3.14)
project(csvParser)

set(CMAKE_CXX_STANDARD 17)

add_executable(csvParser src/main.cpp include/CsvParser.h include/TuplePrinter.h include/TupleReader.h include/CsvParserException.h)