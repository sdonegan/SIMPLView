# --------------------------------------------------------------------
# create Resource files for the various license files that are used and 
# also create a header file that lists all the License Files
set(LICENSE_FILES ${PROJECT_SOURCE_DIR}/License/Boost.license
             #     ${PROJECT_SOURCE_DIR}/License/ITK.license
                  ${PROJECT_SOURCE_DIR}/License/MXA.license
                  ${PROJECT_SOURCE_DIR}/License/Qt.license
             #     ${PROJECT_SOURCE_DIR}/License/tiff.license 
                   ${PROJECT_SOURCE_DIR}/License/Qwt.license
                   ${PROJECT_SOURCE_DIR}/License/HDF5.license
             )
set(QRC_LICENSE_FILES "")
set(LICENSE_HEADER_FILE  ${PROJECT_BINARY_DIR}/AIM/License/${PROJECT_NAME}LicenseFiles.h)
file(WRITE ${LICENSE_HEADER_FILE} "#ifndef _LICENSE_FILES_H_\n")
file(APPEND ${LICENSE_HEADER_FILE} "#define _LICENSE_FILES_H_\n")
file(APPEND ${LICENSE_HEADER_FILE} "namespace ${PROJECT_PREFIX} {\n")
file(APPEND ${LICENSE_HEADER_FILE} "  QStringList LicenseList = (QStringList()  ")
foreach(lf ${LICENSE_FILES})
    get_filename_component(cmp_text_file_name ${lf} NAME)
    get_filename_component(lf_fn ${lf} NAME_WE)
    # Copy the text file into the Build Directory
    configure_file("${lf}" ${PROJECT_BINARY_DIR}/AIM/License/${cmp_text_file_name}   COPYONLY )
        
    # create the Qt Resource File
    configure_file(${CMP_CONFIGURED_FILES_SOURCE_DIR}/QtResourceFile.qrc.in 
                   ${PROJECT_BINARY_DIR}/AIM/License/${lf_fn}.qrc)
                   
    set(QRC_LICENSE_FILES ${QRC_LICENSE_FILES} ${PROJECT_BINARY_DIR}/AIM/License/${lf_fn}.qrc)
    file(APPEND ${LICENSE_HEADER_FILE} " << \":/${cmp_text_file_name}\"")
    
endforeach(lf ${LICENSE_FILES})
file(APPEND ${LICENSE_HEADER_FILE}  ");\n")
file(APPEND ${LICENSE_HEADER_FILE}  "}\n#endif /* _LICENSE_FILES_H_ */ \n")

