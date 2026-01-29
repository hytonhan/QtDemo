cmake_minimum_required(VERSION 3.16)

project(QtDemo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)




set(PROJECT_SOURCES
        src/main.cpp
        src/ui/mainwindow.cpp
        src/ui/mainwindow.h
        src/ui/mainwindow.ui
)

add_library(QtDemoCore
    src/domain/school.cpp src/domain/school.h
    src/domain/person.cpp src/domain/person.h
    src/domain/school.cpp src/domain/school.h
    src/domain/program.cpp src/domain/program.h
    src/domain/teacher.cpp src/domain/teacher.h
    src/domain/student.cpp src/domain/student.h
    src/domain/worker.cpp src/domain/worker.h
    src/model/programlistmodel.cpp src/model/programlistmodel.h
    src/model/programteacherlistmodel.h src/model/programteacherlistmodel.cpp
    src/model/programstudentlistmodel.h src/model/programstudentlistmodel.cpp
    src/infra/databaseservice.h src/infra/databaseservice.cpp
    src/sql/schema.sql
    src/sql/initial_data.sql
    src/sql/insert_program.sql
    src/sql/fetch_programs.sql
    src/sql/delete_program.sql
    src/sql/insert_teacher.sql
    src/model/teacherlistmodel.h src/model/teacherlistmodel.cpp
    src/sql/fetch_teachers.sql
    src/sql/delete_teacher.sql
    src/sql/delete_program_teacher.sql
    src/sql/insert_student.sql
    src/sql/delete_student.sql
    src/sql/fetch_students.sql
    src/model/programassociationitemlistmodel.h src/model/programassociationitemlistmodel.cpp
    src/model/teacherprogramlistmodel.h src/model/teacherprogramlistmodel.cpp
    src/services/programassociationservice.h src/services/programassociationservice.cpp
    src/services/programteacherassociationservice.h src/services/programteacherassociationservice.cpp
    src/services/programstudentassociationservice.h src/services/programstudentassociationservice.cpp
    src/infra/repositories/programrepository.cpp src/infra/repositories/programrepository.h
    src/infra/repositories/programstudentrepository.cpp src/infra/repositories/programstudentrepository.h
    src/infra/repositories/programteacherrepository.cpp src/infra/repositories/programteacherrepository.h
    src/infra/repositories/schoolrepository.cpp src/infra/repositories/schoolrepository.h
    src/infra/repositories/studentrepository.cpp src/infra/repositories/studentrepository.h
    src/infra/repositories/teacherrepository.cpp src/infra/repositories/teacherrepository.h
    src/infra/databaseservice.cpp src/infra/databaseservice.h
    src/services/programservice.h src/services/programservice.cpp
    src/services/teacherservice.h src/services/teacherservice.cpp
    src/sql/fetch_programstudents.sql
    src/sql/fetch_studentsnotinprogram.sql
    src/sql/fetch_studentprograms.sql
    src/sql/link_programstudent.sql
    src/sql/unlink_programstudent.sql
    src/sql/fetch_programteachers.sql
    src/sql/fetch_teachersnotinprogram.sql
    src/sql/fetch_teacherprograms.sql
    src/sql/link_programteacher.sql
    src/sql/unlink_programteacher.sql
    src/resources.qrc
)

target_link_libraries(QtDemoCore
    PUBLIC
        Qt6::Core
        Qt6::Sql
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtDemo
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/ui/itemdetailsdialog.h src/ui/itemdetailsdialog.cpp src/ui/itemdetailsdialog.ui
        src/ui/confirmremovedialog.h src/ui/confirmremovedialog.cpp src/ui/confirmremovedialog.ui
        src/ui/addprogramdialog.h src/ui/addprogramdialog.cpp src/ui/addprogramdialog.ui
        src/ui/addteacherdialog.h src/ui/addteacherdialog.cpp src/ui/addteacherdialog.ui
        src/ui/additemtoprogramdialog.h src/ui/additemtoprogramdialog.cpp src/ui/additemtoprogramdialog.ui
        src/resources.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QtDemo APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QtDemo SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QtDemo
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QtDemo PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(QtDemo
    PRIVATE
        Qt6::Widgets
        QtDemoCore
)



find_package(Qt6 REQUIRED COMPONENTS Sql)
target_link_libraries(QtDemo PRIVATE Qt6::Sql)

enable_testing()
find_package(Qt6 REQUIRED COMPONENTS Test)   # or Qt5::Test

add_executable(test_teacher tests/domain/test_teacher.cpp)
target_link_libraries(test_teacher PRIVATE Qt6::Test QtDemoCore)
add_test(NAME test_teacher COMMAND test_teacher)

add_executable(test_student tests/domain/test_student.cpp)
target_link_libraries(test_student PRIVATE Qt6::Test QtDemoCore)
add_test(NAME test_student COMMAND test_student)

add_executable(test_person tests/domain/test_person.cpp)
target_link_libraries(test_person PRIVATE Qt6::Test QtDemoCore)
add_test(NAME test_person COMMAND test_person)

add_executable(test_worker tests/domain/test_worker.cpp)
target_link_libraries(test_worker PRIVATE Qt6::Test QtDemoCore)
add_test(NAME test_worker COMMAND test_worker)

add_executable(test_program tests/domain/test_program.cpp)
target_link_libraries(test_program PRIVATE Qt6::Test QtDemoCore)
add_test(NAME test_program COMMAND test_program)

add_executable(test_school tests/domain/test_school.cpp)
target_link_libraries(test_school PRIVATE Qt6::Test QtDemoCore)
add_test(NAME test_school COMMAND test_school)


add_executable(test_teacherservice tests/services/test_teacherservice.cpp
    tests/services/faketeacherrepository.h)
target_link_libraries(test_teacherservice PRIVATE Qt6::Test QtDemoCore)
add_test(NAME test_teacherservice COMMAND test_teacherservice)

add_executable(test_programservice tests/services/test_programservice.cpp
    tests/services/fakeprogramrepository.h)
target_link_libraries(test_programservice PRIVATE Qt6::Test QtDemoCore)
add_test(NAME test_programservice COMMAND test_programservice)

add_executable(test_programstudentassociationservice tests/services/test_programstudentassociationservice.cpp
    tests/services/fakeprogramstudentrepository.h)
target_link_libraries(test_programstudentassociationservice PRIVATE Qt6::Test QtDemoCore)
add_test(NAME test_programstudentassociationservice COMMAND test_programstudentassociationservice)

add_executable(test_programteacherassociationservice tests/services/test_programteacherassociationservice.cpp
    tests/services/fakeprogramteacherrepository.h)
target_link_libraries(test_programteacherassociationservice PRIVATE Qt6::Test QtDemoCore)
add_test(NAME test_programteacherassociationservice COMMAND test_programteacherassociationservice)


add_executable(test_teacherrepository tests/infra/test_teacherrepository.cpp)
target_link_libraries(test_teacherrepository PRIVATE Qt6::Test QtDemoCore)
add_test(NAME test_teacherrepository COMMAND test_teacherrepository)

add_executable(test_programrepository tests/infra/test_programrepository.cpp)
target_link_libraries(test_programrepository PRIVATE Qt6::Test QtDemoCore)
add_test(NAME test_programrepository COMMAND test_programrepository)

add_executable(test_studentrepository tests/infra/test_studentrepository.cpp)
target_link_libraries(test_studentrepository PRIVATE Qt6::Test QtDemoCore)
add_test(NAME test_studentrepository COMMAND test_studentrepository)

add_executable(test_programstudentrepository tests/infra/test_programstudentrepository.cpp)
target_link_libraries(test_programstudentrepository PRIVATE Qt6::Test QtDemoCore)
add_test(NAME test_programstudentrepository COMMAND test_programstudentrepository)

add_executable(test_programteacherrepository tests/infra/test_programteacherrepository.cpp)
target_link_libraries(test_programteacherrepository PRIVATE Qt6::Test QtDemoCore)
add_test(NAME test_programteacherrepository COMMAND test_programteacherrepository)

add_executable(test_databaseservice tests/infra/test_databaseservice.cpp)
target_link_libraries(test_databaseservice PRIVATE Qt6::Test QtDemoCore)
add_test(NAME test_databaseservice COMMAND test_databaseservice)



# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QtDemo)
endif()
set_target_properties(QtDemo PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QtDemo
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtDemo)
endif()
