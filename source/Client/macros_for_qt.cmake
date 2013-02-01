# includeGuard: Wird dieses Dokument mehrfach in einer Dateistrucktur inkludiert, verhindert der Includeguard unnötige Rechenarbeit und verringert die Bearbeitungszeit
if( NOT MACROS_FOR_QT_CMAKE )
set( MACROS_FOR_QT_CMAKE TRUE )

# Das Macro TO_MOC_OR_NOT_TO_MOC findet automatisch heraus welche Dateien geMOCt werden sollten und stellt diese in eine gemeinsame liste
MACRO( TO_MOC_OR_NOT_TO_MOC _OutputFiles )
  foreach( _current_FILE ${ARGN} )
    get_filename_component( _abs_FILE ${_current_FILE} ABSOLUTE )
    if( EXISTS ${_abs_FILE} )
        file( READ ${_abs_FILE} _contents ) 
        string( FIND "${_contents}" "Q_OBJECT" _MATCH  )
        if( _MATCH GREATER -1 )
            set(${_OutputFiles} ${${_OutputFiles}} ${_current_FILE} )
        endif( _MATCH GREATER -1 )
    endif( EXISTS ${_abs_FILE} )
  endforeach( _current_FILE )
ENDMACRO( TO_MOC_OR_NOT_TO_MOC _NAME )



# QT4_WRAP_UI_MOD(outfiles inputfile ... ) a modified version of QT4_WRAP_UI

MACRO (QT4_WRAP_UI_MOD outfiles ui_generated_path )
  QT4_EXTRACT_OPTIONS(ui_files ui_options ${ARGN})
  FOREACH (it ${ui_files})
    GET_FILENAME_COMPONENT(outfile ${it} NAME_WE)
    GET_FILENAME_COMPONENT(infile ${it} ABSOLUTE)
    SET(outfile ${CMAKE_CURRENT_BINARY_DIR}/${ui_generated_path}/ui_${outfile}.h)
    ADD_CUSTOM_COMMAND(OUTPUT ${outfile}
      COMMAND ${QT_UIC_EXECUTABLE}
      ARGS ${ui_options} -o ${outfile} ${infile}
      MAIN_DEPENDENCY ${infile} VERBATIM)
    SET(${outfiles} ${${outfiles}} ${outfile})
  ENDFOREACH (it)

ENDMACRO (QT4_WRAP_UI_MOD)



# QT4_WRAP_CPP_MOD(outfiles inputfile ... ) a modified version of QT4_WRAP_CPP

MACRO (QT4_WRAP_CPP_MOD outfiles moc_generated_path )
  # get include dirs
  QT4_GET_MOC_FLAGS(moc_flags)
  QT4_EXTRACT_OPTIONS(moc_files moc_options ${ARGN})

  FOREACH (it ${moc_files})
    GET_FILENAME_COMPONENT(it ${it} ABSOLUTE)
    QT4_MAKE_OUTPUT_FILE(${it}  ${moc_generated_path}/moc_ cpp outfile)
    QT4_CREATE_MOC_COMMAND(${it} ${outfile} "${moc_flags}" "${moc_options}")
    SET(${outfiles} ${${outfiles}} ${outfile})
  ENDFOREACH(it)

ENDMACRO (QT4_WRAP_CPP_MOD)



endif( NOT MACROS_FOR_QT_CMAKE )

