CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

PROJECT(Admin)

IF(COMMAND CMAKE_POLICY)
	CMAKE_POLICY(SET CMP0005 NEW)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "2")
SET(VERSION_PATCH "1")
#SET(VERSION_SUFFIX "")

SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
IF(VERSION_SUFFIX)
	SET(VERSION "${VERSION}-${VERSION_SUFFIX}")
ENDIF(VERSION_SUFFIX)

# check for Qt4
SET(QT_MIN_VERSION "4.4.0")
SET(QT_USE_QTSQL TRUE)
FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtSql REQUIRED)
#find_package(Qwt REQUIRED)

INCLUDE(${QT_USE_FILE})


#CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/hmi.rc.in ${CMAKE_BINARY_DIR}/hmi.rc)

# set compiler flags
SET(CMAKE_C_FLAGS "-O2 -g -Wall ${CMAKE_C_FLAGS}")
SET(CMAKE_CXX_FLAGS "-O2 -g -fno-exceptions -Wall ${CMAKE_CXX_FLAGS}")

SET(HMI_SOURCES src/Database.cpp
                src/GenericDialog.cpp
                src/GroundZero.cpp
                src/ModelProduit.cpp
                src/ModifierOp.cpp
                src/SupprimerOp.cpp
                src/admin.cpp
                src/ajouteringredient.cpp
                src/ajouterproduit.cpp
                src/delegatebox.cpp
                src/login.cpp
                src/main.cpp
                src/menuajouter.cpp
                src/menuajouterproduit.cpp  
                src/modifierproduit.cpp
                src/parametrage.cpp
                src/supprimer.cpp
                src/supprimeringredient.cpp
                src/supprimerproduit.cpp)

SET(HMI_INCLUDES src/Database.h
                src/GenericDialog.h
                src/GroundZero.h
                src/ModelProduit.h
                src/ModifierOp.h
                src/SupprimerOp.h
                src/admin.h
                src/ajouteringredient.h
                src/ajouterproduit.h
                src/delegatebox.h
                src/login.h
                src/menuajouter.h
                src/menuajouterproduit.h 
                src/modifierproduit.h
                src/parametrage.h
                src/supprimer.h
                src/supprimeringredient.h
                src/supprimerproduit.h)

#SET(qmodbus_SOURCES ${qmodbus_SOURCES} 3rdparty/qextserialport/posix_qextserialport.cpp 3rdparty/qextserialport/qextserialenumerator_unix.cpp)
SET(HMI_SOURCES ${HMI_SOURCES})
ADD_DEFINITIONS(-D_TTY_POSIX_)

SET(HMI_UI forms/parametrage.ui
           forms/ajouteringredient.ui
           forms/supprimerproduit.ui
           forms/menuajouter.ui
           forms/supprimeringredient.ui
           forms/ajouterproduit.ui
           forms/modifierproduit.ui
           forms/supprimer.ui
           forms/menuajouterproduit.ui
           forms/admin.ui
           forms/login.ui)

QT4_WRAP_CPP(HMI_MOC_out ${HMI_INCLUDES})
QT4_WRAP_UI(HMI_UIC_out ${HMI_UI})
#QT4_ADD_RESOURCES(HMI_RCC_out data/HMI.qrc)

#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libmodbus ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libmodbus/src ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qextserialport ${CMAKE_BINARY_DIR})
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${QWT_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR} )
#LINK_LIBRARIES(${QT_LIBRARIES} ${QWT_LIBRARY})
ADD_EXECUTABLE(admin ${HMI_SOURCES} ${HMI_UIC_out} ${HMI_MOC_out} ${HMI_RCC_out})
#target_link_libraries(admin ${QT_LIBRARIES} ${QWT_LIBRARY})
target_link_libraries(admin ${QT_LIBRARIES})
#INSTALL(TARGETS admin RUNTIME DESTINATION bin)


#
# add dist target
#
SET(TMP "admin-${VERSION}")
SET(S ${CMAKE_SOURCE_DIR})



INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Admin")
SET(CPACK_PACKAGE_VENDOR "SimuLabo s.a.r.l - http://simulabo.com")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")

SET(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
IF(VERSION_SUFFIX)
	SET(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}-${VERSION_SUFFIX}")
ENDIF(VERSION_SUFFIX)
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "Admin")
SET(CPACK_STRIP_FILES "bin/admin")
SET(CPACK_PACKAGE_EXECUTABLES "admin" "Admin binary")


SET(CPACK_SOURCE_GENERATOR "TBZ2")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "admin-${VERSION}")
INCLUDE(CPack)