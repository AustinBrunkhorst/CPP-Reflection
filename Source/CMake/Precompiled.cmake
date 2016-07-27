function (set_precompiled_header target header source)
  if (MSVC)
     set_target_properties(${target} PROPERTIES
        COMPILE_FLAGS "/Yu${header}"
    )

     set_source_files_properties(${source} PROPERTIES
        COMPILE_FLAGS "/Yc${header}"
    )
  endif ()
endfunction ()