QT += testlib sql network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_funcforserver_test.cpp \
    ../1/server1/functionsforserver.cpp \
    ../1/server1/database.cpp \
    ../1/server1/mytcpserver.cpp \
    ../1/server1/sha1.cpp


HEADERS += \
    ../1/server1/functionsforserver.h \
    ../1/server1/database.h \
    ../1/server1/mytcpserver.h \
    ../1/server1/sha1.h \

