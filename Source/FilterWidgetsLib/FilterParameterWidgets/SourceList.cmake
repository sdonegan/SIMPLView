
set(FilterWidgetsLib_ParameterWidgets_HDRS "")
set(FilterWidgetsLib_ParameterWidgets_SRCS "")
set(FilterWidgetsLib_ParameterWidgets_UIS "")


set(DREAM3D_PARAMETER_WIDGETS
      StringWidget
      IntWidget
      DoubleWidget
      InputFileWidget
      InputPathWidget
      OutputFileWidget
      OutputPathWidget
      BooleanWidget
      ChoiceWidget
      IntVec3Widget
      FloatVec3Widget
      AxisAngleWidget
	  UnknownWidget
#      VolumeVertexArrayNameSelectionWidget
#      VolumeEdgeArrayNameSelectionWidget
#      VolumeFaceArrayNameSelectionWidget
#      VolumeCellArrayNameSelectionWidget
#      VolumeFeatureArrayNameSelectionWidget
#      VolumeEnsembleArrayNameSelectionWidget
#      SurfaceVertexArrayNameSelectionWidget
#      SurfaceFaceArrayNameSelectionWidget
#      SurfaceEdgeArrayNameSelectionWidget
#      SurfaceFeatureArrayNameSelectionWidget
#      SurfaceEnsembleArrayNameSelectionWidget
#      EdgeVertexArrayNameSelectionWidget
#      EdgeEdgeArrayNameSelectionWidget
#      EdgeFeatureArrayNameSelectionWidget
#      EdgeEnsembleArrayNameSelectionWidget
#      VertexVertexArrayNameSelectionWidget
#      VertexFeatureArrayNameSelectionWidget
#      VertexEnsembleArrayNameSelectionWidget
#      ArraySelectionWidget
#      CellArrayComparisonSelectionWidget
#      FeatureArrayComparisonSelectionWidget
#      EnsembleArrayComparisonSelectionWidget
#      VertexArrayComparisonSelectionWidget
#      FaceArrayComparisonSelectionWidget
#      EdgeArrayComparisonSelectionWidget
#      CustomWidget
)

set(REGISTER_KNOWN_WIDGETS ${FilterWidgetsLib_BINARY_DIR}/FilterWidgetManager_RegisterWidgets.cpp)
set(FILTER_WIDGET_HEADERS ${FilterWidgetsLib_BINARY_DIR}/FilterWidgetHeaders.h)
file(WRITE ${REGISTER_KNOWN_WIDGETS}  "/* This file is automatically generated. DO NOT EDIT this file. It will be over written */\n")
file(WRITE ${FILTER_WIDGET_HEADERS}  "/* This file is automatically generated. DO NOT EDIT this file. It will be over written */\n")

foreach(FPW ${DREAM3D_PARAMETER_WIDGETS})
  set(FilterWidgetsLib_ParameterWidgets_HDRS ${FilterWidgetsLib_ParameterWidgets_HDRS}
    ${FilterWidgetsLib_SOURCE_DIR}/FilterParameterWidgets/${FPW}.h
    )
  set(FilterWidgetsLib_ParameterWidgets_SRCS ${FilterWidgetsLib_ParameterWidgets_SRCS}
    ${FilterWidgetsLib_SOURCE_DIR}/FilterParameterWidgets/${FPW}.cpp
    )
  set(FilterWidgetsLib_ParameterWidgets_UIS ${FilterWidgetsLib_ParameterWidgets_UIS}
    ${FilterWidgetsLib_SOURCE_DIR}/FilterParameterWidgets/UI_Files/${FPW}.ui
    )

  file(APPEND  ${REGISTER_KNOWN_WIDGETS} "{\n")
  file(APPEND  ${REGISTER_KNOWN_WIDGETS} "  QFilterWidgetFactory<${FPW}>::Pointer factory = QFilterWidgetFactory<${FPW}>::New();\n")
  file(APPEND  ${REGISTER_KNOWN_WIDGETS} "  idManager->addFilterWidgetFactory( \"${FPW}\", factory );\n")
  file(APPEND  ${REGISTER_KNOWN_WIDGETS} "}\n")
  file(APPEND  ${FILTER_WIDGET_HEADERS} "#include \"FilterWidgetsLib/FilterParameterWidgets/${FPW}.h\"\n")
endforeach()



cmp_IDE_SOURCE_PROPERTIES( "FilterWidgetsLib/FilterParameterWidgets" "${FilterWidgetsLib_ParameterWidgets_HDRS}" "${FilterWidgetsLib_ParameterWidgets_SRCS}" "0")

cmp_IDE_GENERATED_PROPERTIES("FilterWidgetsLib/FilterParameterWidgets/UI_Files" "${FilterWidgetsLib_ParameterWidgets_UIS}" "")

# --------------------------------------------------------------------
# and finally this will run moc:
QT4_WRAP_CPP( FilterWidgetsLib_ParameterWidgets_Generated_MOC_SRCS ${FilterWidgetsLib_ParameterWidgets_HDRS} )

# These generated moc files will be #include in the FilterWidget source file that
# are generated so we need to tell the build system to NOT compile these files
set_source_files_properties( ${FilterWidgetsLib_ParameterWidgets_Generated_MOC_SRCS} PROPERTIES HEADER_FILE_ONLY TRUE)

# -- Run MOC and UIC on the necessary files
# QT4_ADD_RESOURCES( FilterWidgetsLib_Generated_RC_SRCS "${DREAM3DProj_SOURCE_DIR}/Documentation/Filters/Generated_FilterDocs.qrc"  )

# --------------------------------------------------------------------
# Continue on with our Qt4 section
QT4_WRAP_UI( FilterWidgetsLib_ParameterWidgets_Generated_UI_HDRS ${FilterWidgetsLib_ParameterWidgets_UIS} )

# --------------------------------------------------------------------
#-- Put the Qt generated files into their own group for IDEs
cmp_IDE_SOURCE_PROPERTIES( "Generated/Qt_Moc" "" "${FilterWidgetsLib_ParameterWidgets_Generated_MOC_SRCS}" "0")
cmp_IDE_SOURCE_PROPERTIES( "Generated/Qt_Uic" "${FilterWidgetsLib_ParameterWidgets_Generated_UI_HDRS}" "" "0")
#cmp_IDE_SOURCE_PROPERTIES( "Generated/Qt_Qrc" "${FilterWidgetsLib_Generated_RC_SRCS}" "" "0")




