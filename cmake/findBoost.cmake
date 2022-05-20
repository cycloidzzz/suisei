set(BOOST_MINIMUM_VERSION "1.66.0")
find_package(Boost ${BOOST_MINIMUM_VERSION}
COMPONENTS 
    context
    coroutine
    date_time
    thread
    system 
    filesystem 
    unit_test_framework REQUIRED)
add_definitions(-DBOOST_COROUTINES_NO_DEPRECATION_WARNING)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})