# CMakeList.txt: проект CMake для cpp_xmlRes; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (cpp_xmlRes "XMLres.cpp" "XMLres.h" "main.cpp" "Node.h" "Node.cpp" "Iterator.h" "Iterator.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
