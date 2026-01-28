cmake_minimum_required(VERSION 3.16)

project(KouluHarkkaTyoQt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


set(PROJECT_SOURCES
        main.cpp
        ui/mainwindow.cpp
        ui/mainwindow.h
        ui/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(KouluHarkkaTyoQt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ui/itemdetailsdialog.h ui/itemdetailsdialog.cpp ui/itemdetailsdialog.ui
        domain/school.cpp domain/school.h
        domain/person.cpp domain/person.h
        domain/school.cpp domain/school.h
        domain/program.cpp domain/program.h
        domain/teacher.cpp domain/teacher.h
        domain/student.cpp domain/student.h
        domain/worker.cpp domain/worker.h
        model/programlistmodel.cpp model/programlistmodel.h
        model/programteacherlistmodel.h model/programteacherlistmodel.cpp
        model/programstudentlistmodel.h model/programstudentlistmodel.cpp
        ui/confirmremovedialog.h ui/confirmremovedialog.cpp ui/confirmremovedialog.ui
        ui/addprogramdialog.h ui/addprogramdialog.cpp ui/addprogramdialog.ui
        infra/databaseservice.h infra/databaseservice.cpp
        sql/schema.sql
        resources.qrc
        sql/initial_data.sql

        sql/insert_program.sql
        sql/fetch_programs.sql
        sql/delete_program.sql
        sql/insert_teacher.sql
        model/teacherlistmodel.h model/teacherlistmodel.cpp
        sql/fetch_teachers.sql
        ui/addteacherdialog.h ui/addteacherdialog.cpp ui/addteacherdialog.ui
        sql/delete_teacher.sql
        sql/delete_program_teacher.sql
        ui/additemtoprogramdialog.h ui/additemtoprogramdialog.cpp ui/additemtoprogramdialog.ui

        sql/insert_student.sql
        sql/delete_student.sql
        sql/fetch_students.sql
        model/programassociationitemlistmodel.h model/programassociationitemlistmodel.cpp

        model/teacherprogramlistmodel.h model/teacherprogramlistmodel.cpp
        services/programassociationservice.h services/programassociationservice.cpp
        services/programteacherassociationservice.h services/programteacherassociationservice.cpp
        services/programstudentassociationservice.h services/programstudentassociationservice.cpp






        infra/repositories/programrepository.cpp infra/repositories/programrepository.h
        infra/repositories/programstudentrepository.cpp infra/repositories/programstudentrepository.h
        infra/repositories/programteacherrepository.cpp infra/repositories/programteacherrepository.h
        infra/repositories/schoolrepository.cpp infra/repositories/schoolrepository.h
        infra/repositories/studentrepository.cpp infra/repositories/studentrepository.h
        infra/repositories/teacherrepository.cpp infra/repositories/teacherrepository.h
        infra/databaseservice.cpp infra/databaseservice.h
        services/programservice.h services/programservice.cpp
        services/teacherservice.h services/teacherservice.cpp
        sql/fetch_programstudents.sql
        sql/fetch_studentsnotinprogram.sql
        sql/fetch_studentprograms.sql
        sql/link_programstudent.sql
        sql/unlink_programstudent.sql
        sql/fetch_programteachers.sql
        sql/fetch_teachersnotinprogram.sql
        sql/fetch_teacherprograms.sql
        sql/link_programteacher.sql
        sql/unlink_programteacher.sql


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET KouluHarkkaTyoQt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(KouluHarkkaTyoQt SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(KouluHarkkaTyoQt
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(KouluHarkkaTyoQt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


find_package(Qt6 REQUIRED COMPONENTS Sql)
target_link_libraries(KouluHarkkaTyoQt PRIVATE Qt6::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.KouluHarkkaTyoQt)
endif()
set_target_properties(KouluHarkkaTyoQt PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS KouluHarkkaTyoQt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(KouluHarkkaTyoQt)
endif()
