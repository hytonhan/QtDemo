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
        src/main.cpp
        src/ui/mainwindow.cpp
        src/ui/mainwindow.h
        src/ui/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(KouluHarkkaTyoQt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/ui/itemdetailsdialog.h src/ui/itemdetailsdialog.cpp src/ui/itemdetailsdialog.ui
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
        src/ui/confirmremovedialog.h src/ui/confirmremovedialog.cpp src/ui/confirmremovedialog.ui
        src/ui/addprogramdialog.h src/ui/addprogramdialog.cpp src/ui/addprogramdialog.ui
        src/infra/databaseservice.h src/infra/databaseservice.cpp
        src/sql/schema.sql
        src/resources.qrc
        src/sql/initial_data.sql

        src/sql/insert_program.sql
        src/sql/fetch_programs.sql
        src/sql/delete_program.sql
        src/sql/insert_teacher.sql
        src/model/teacherlistmodel.h src/model/teacherlistmodel.cpp
        src/sql/fetch_teachers.sql
        src/ui/addteacherdialog.h src/ui/addteacherdialog.cpp src/ui/addteacherdialog.ui
        src/sql/delete_teacher.sql
        src/sql/delete_program_teacher.sql
        src/ui/additemtoprogramdialog.h src/ui/additemtoprogramdialog.cpp src/ui/additemtoprogramdialog.ui

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
