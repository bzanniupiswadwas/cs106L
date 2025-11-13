TEMPLATE = app

CONFIG += no_include_pwd
CONFIG += console
CONFIG -= app_bundle

# 👉 使用具体文件名，避免通配符
SOURCES += src/main.cpp

# 如果有头文件，也列出
HEADERS += src/main.h

# 编译器选项
QMAKE_CXXFLAGS += -std=c++17 \
    -Wall \
    -Wextra \
    -Wreturn-type \
    -Werror=return-type \
    -Wunreachable-code \

# 资源复制函数（保持不变）
defineTest(copyToDestdir) {
    files = $$1
    for(FILE, files) {
        DDIR = $$OUT_PWD
        !win32 {
            copyResources.commands += cp -r '"'$$FILE'"' '"'$$DDIR'"' $$escape_expand(\\n\\t)
        }
        win32 {
            copyResources.commands += xcopy '"'$$FILE'"' '"'$$DDIR'"' /e /y $$escape_expand(\\n\\t)
        }
    }
    export(copyResources.commands)
}

macx {
    cache()
    QMAKE_MAC_SDK = macosx
}
