add_library(eval_map_lib
        eval_map.c
        eval_map.h
        eval_fill.c
        eval_shape.c
)

target_link_libraries(eval_map_lib
        dataimporter_lib
)