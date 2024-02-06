project("FirstLab")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

set(source
    main.cpp
    Duration.cpp
)

set(heaers
    Duration.h
)

add_executable(FirstLab ${source} ${heaers})
