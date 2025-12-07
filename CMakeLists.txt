cmake_minimum_required(VERSION 3.26)
project(POOP_project_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(POOP_project_1 main.cpp
        DataBase.cpp
        DataBase.h
        Statment.cpp
        Statment.h
        TableMK2.cpp
        TableMK2.h
        Slicer.cpp
        Slicer.h
        Select.cpp
        Select.h
        Insert.cpp
        Insert.h
        Condition.cpp
        Condition.h
        Delete.cpp
        Delete.h
        Update.cpp
        Update.h
        Exporter.cpp
        Exporter.h
        ExporterKekec.cpp
        ExporterKekec.h
        ExporterSQL.cpp
        ExporterSQL.h
        Exceptions.h
)
