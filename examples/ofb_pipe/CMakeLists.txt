add_executable(ofb_pipe
        main.c
        ofb.c
        )

target_link_libraries(ofb_pipe PUBLIC ijon)
