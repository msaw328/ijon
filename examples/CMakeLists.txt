add_subdirectory(enc_dec_random)
add_subdirectory(ofb_pipe)

add_custom_target(examples DEPENDS
        enc_dec_random
        ofb_pipe
        )
