include $(GNUSTEP_MAKEFILES)/common.make

CC = clang
CXX = clang++

APP_NAME = CatLock

CatLock_HEADERS = 	objc/main.h \
					objc/Params.h \
					objc/XGuiApplication.h \
					objc/XGuiFont.h \
					objc/XGuiLabel.h \
					objc/XGuiWindow.h

CatLock_OBJC_FILES = objc/main.m \
					objc/Params.m \
					objc/XGuiApplication.m \
					objc/XGuiFont.m \
					objc/XGuiLabel.m \
					objc/XGuiWindow.m

# 					objc/helpers.m \
#					obc/helpers.h \

# CatLock_HEADERS = objc/main.h
# CatLock_OBJC_FILES = objc/main.m objc/Params.m
CatLock_RESOURCE_FILES =

CatLock_RESOURCE_FILES =

OBJCFLAGS= -I/usr/local/include -I/usr/local/include/X11 -I/usr/local/include/freetype2

LDFLAGS=  -lX11  -lXext  -lXpm -lImlib2  -lXft


# -include GNUmakefile.preamble

-include GNUmakefile.local

include $(GNUSTEP_MAKEFILES)/application.make

# -include GNUmakefile.postamble



