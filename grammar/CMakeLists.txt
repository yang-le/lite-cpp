# set variable pointing to the antlr tool that supports C++
# this is not required if the jar file can be found under PATH environment
set(ANTLR_EXECUTABLE ${CMAKE_SOURCE_DIR}/3rdparty/antlr/antlr-4.7.2-complete.jar)
# add macros to generate ANTLR Cpp code from grammar
find_package(ANTLR REQUIRED)

# Call macro to add lexer and grammar to your build dependencies.
antlr_target(LiteLexer LiteLexer.g4 LEXER
             OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
             PACKAGE litecpp)
antlr_target(LiteParser LiteParser.g4 PARSER LISTENER VISITOR
             OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
             PACKAGE litecpp
             DEPENDS_ANTLR LiteLexer)

# include generated files in project environment
include_directories(${ANTLR_LiteLexer_OUTPUT_DIR})
include_directories(${ANTLR_LiteParser_OUTPUT_DIR})

add_library(lite_static STATIC
                ${ANTLR_LiteLexer_CXX_OUTPUTS}
                ${ANTLR_LiteParser_CXX_OUTPUTS})

target_link_libraries(lite_static antlr4_static)
