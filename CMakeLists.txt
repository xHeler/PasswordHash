cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Ustawienie kompilatora
set(CMAKE_C_COMPILER gcc)

# Dodanie folderu src do listy źródeł
aux_source_directory(src SRC_FILES)

# Dodanie folderu include do listy nagłówków
include_directories(include)

# Utworzenie wykonywalnego pliku z plików z folderu src
add_executable(MyExecutable ${SRC_FILES})

target_link_libraries(MyExecutable PRIVATE -lcrypto -lssl)