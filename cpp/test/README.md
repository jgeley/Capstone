g++ -Wall -g -std=gnu++0x  `pkg-config --cflags --libs Qt5Widgets opencv` -fPIC -L/usr/local/lib -lopenbr -isystem /home/pi/googletest/googletest/include -isystem ../ -pthread unitTests.cc ../openBr.o libgtest.a -o my_test

to compile tests


output: 

[==========] Running 5 tests from 2 test cases.
[----------] Global test environment set-up.
[----------] 3 tests from GET_TEMPLATE_LIST
[ RUN      ] GET_TEMPLATE_LIST.TEST_EMPTY
[       OK ] GET_TEMPLATE_LIST.TEST_EMPTY (0 ms)
[ RUN      ] GET_TEMPLATE_LIST.TEST_WITH_ONLY_GALS
[       OK ] GET_TEMPLATE_LIST.TEST_WITH_ONLY_GALS (0 ms)
[ RUN      ] GET_TEMPLATE_LIST.TEST_WITH_SOME_GALS
[       OK ] GET_TEMPLATE_LIST.TEST_WITH_SOME_GALS (0 ms)
[----------] 3 tests from GET_TEMPLATE_LIST (1 ms total)

[----------] 2 tests from GET_MATCH
[ RUN      ] GET_MATCH.TEST_NO_MATCH
Loading /usr/local/share/openbr/models/algorithms/FaceRecognition
[       OK ] GET_MATCH.TEST_NO_MATCH (2246 ms)
[ RUN      ] GET_MATCH.TEST__MATCH
[       OK ] GET_MATCH.TEST__MATCH (1 ms)
[----------] 2 tests from GET_MATCH (2248 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 2 test cases ran. (2250 ms total)
[  PASSED  ] 5 tests.

