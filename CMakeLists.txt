cmake_minimum_required(VERSION 3.15)
project(run)

set(CMAKE_CXX_STANDARD 14)


include_directories(.)
include_directories(Others)
include_directories(qhull)
include_directories(QuadProg)
include_directories(structure)
include_directories(UH)


if (EMSCRIPTEN)
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY")
    set(CMAKE_EXECUTABLE_SUFFIX ".js")
endif ()

add_executable(run
        Others/lp.cpp
        Others/lp.h
        Others/operation.cpp
        Others/operation.h
        Others/pruning.cpp
        Others/pruning.h
        input/car.txt
        output/ext_pt.txt
        output/hyperplane_data.txt
        output/point.txt
        output/top.txt
        qhull/geom.cpp
        qhull/geom.h
        qhull/geom2.cpp
        qhull/global.cpp
        qhull/io.cpp
        qhull/io.h
        qhull/libqhull.cpp
        qhull/libqhull.h
        qhull/mem.cpp
        qhull/mem.h
        qhull/merge.cpp
        qhull/merge.h
        qhull/poly.cpp
        qhull/poly.h
        qhull/poly2.cpp
        qhull/qhull_a.h
        qhull/qhull_build.cpp
        qhull/qhull_build.h
        qhull/qset.cpp
        qhull/qset.h
        qhull/random.cpp
        qhull/random.h
        qhull/rboxlib.cpp
        qhull/stat.cpp
        qhull/stat.h
        qhull/user.cpp
        qhull/user.h
        qhull/usermem.cpp
        qhull/userprintf.cpp
        qhull/userprintf_rbox.cpp
        QuadProg/Array.cc
        QuadProg/Array.hh
        QuadProg/QuadProg++.cc
        QuadProg/QuadProg++.hh
        structure/data_struct.h
        structure/data_utility.cpp
        structure/data_utility.h
        structure/define.h
        structure/hyperplane.cpp
        structure/hyperplane.h
        structure/Partition.cpp
        structure/Partition.h
        structure/point_set.cpp
        structure/point_set.h
        structure/point_t.cpp
        structure/point_t.h
        structure/rtree.cpp
        structure/rtree.h
        web.cpp
        structure/hyperplane_set.cpp
        structure/hyperplane_set.h
        structure/u_vector.cpp
        structure/u_vector.h
        PreferenceLearning/preferenceLearning.cpp
        PreferenceLearning/preferenceLearning.h
        structure/s_node.cpp
        structure/s_node.h
        structure/cluster_t.cpp
        structure/cluster_t.h
        structure/choose_item.cpp
        structure/choose_item.h)

set_target_properties(run PROPERTIES
    COMPILE_FLAGS "--bind"
    LINK_FLAGS "--bind"
    RUNTIME_OUTPUT_DIRECTORY "../react-app/public"
)
target_compile_options(run PRIVATE "-sALLOW_MEMORY_GROWTH=1")

link_directories(emlib)
#target_link_libraries(run glpk)
