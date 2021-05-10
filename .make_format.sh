#!/usr/bin/env bash
# Скрипт вызывает clang-format для всех файлов *.cpp и *.h
filepaths=$(find . -type f \( -name "*.c" -or -name "*.h" \))
for filepath in $filepaths; do
    echo "Formatting ${filepath}..."
    clang-format -style=file -i "${filepath}"
done
