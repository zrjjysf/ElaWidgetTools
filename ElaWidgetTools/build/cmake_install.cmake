# Install script for directory: /home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/lib/libElaWidgetTools.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/lib/libElaWidgetTools.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/lib/libElaWidgetTools.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/lib" TYPE SHARED_LIBRARY FILES "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/build/libElaWidgetTools.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/lib/libElaWidgetTools.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/lib/libElaWidgetTools.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/lib/libElaWidgetTools.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/include" TYPE FILE FILES
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaAcrylicUrlCard.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaActionCommander.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaAppBar.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaApplication.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaBreadcrumbBar.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaCalendar.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaCalendarPicker.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaCheckBox.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaColorDialog.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaComboBox.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaContentDialog.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaDef.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaDialog.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaDockWidget.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaDoubleSpinBox.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaDrawerArea.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaDxgiManager.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaEventBus.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaExponentialBlur.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaFlowLayout.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaIcon.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaIconButton.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaImageCard.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaInteractiveCard.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaKeyBinder.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaLCDNumber.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaLineEdit.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaListView.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaLog.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaMenu.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaMenuBar.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaMessageBar.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaMessageButton.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaMultiSelectComboBox.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaNavigationBar.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaPivot.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaPlainTextEdit.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaPopularCard.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaProgressBar.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaProgressRing.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaPromotionCard.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaPromotionView.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaProperty.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaPushButton.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaRadioButton.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaReminderCard.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaRoller.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaRollerPicker.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaScrollArea.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaScrollBar.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaScrollPage.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaScrollPageArea.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaSingleton.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaSlider.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaSpinBox.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaStatusBar.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaSuggestBox.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaTabBar.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaTabWidget.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaTableView.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaText.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaTheme.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaToggleButton.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaToggleSwitch.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaToolBar.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaToolButton.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaToolTip.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaTreeView.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaWidget.h"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/ElaWindow.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/lib/cmake/ElaWidgetToolsTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/lib/cmake/ElaWidgetToolsTargets.cmake"
         "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/build/CMakeFiles/Export/0a725064e637b157163c54398f042a49/ElaWidgetToolsTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/lib/cmake/ElaWidgetToolsTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/lib/cmake/ElaWidgetToolsTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/lib/cmake" TYPE FILE FILES "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/build/CMakeFiles/Export/0a725064e637b157163c54398f042a49/ElaWidgetToolsTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/lib/cmake" TYPE FILE FILES "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/build/CMakeFiles/Export/0a725064e637b157163c54398f042a49/ElaWidgetToolsTargets-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/ElaWidgetTools/lib/cmake" TYPE FILE FILES
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/build/ElaWidgetToolsConfig.cmake"
    "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/build/ElaWidgetToolsConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
  file(WRITE "/home/jojoc/development/binanceShell/ElaWidgetTools/ElaWidgetTools/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
