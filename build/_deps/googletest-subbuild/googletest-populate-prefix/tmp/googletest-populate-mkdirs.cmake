# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/vayu-cpp-coding-exercise/osm_routing/build/_deps/googletest-src"
  "E:/vayu-cpp-coding-exercise/osm_routing/build/_deps/googletest-build"
  "E:/vayu-cpp-coding-exercise/osm_routing/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "E:/vayu-cpp-coding-exercise/osm_routing/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "E:/vayu-cpp-coding-exercise/osm_routing/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "E:/vayu-cpp-coding-exercise/osm_routing/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "E:/vayu-cpp-coding-exercise/osm_routing/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/vayu-cpp-coding-exercise/osm_routing/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/vayu-cpp-coding-exercise/osm_routing/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
