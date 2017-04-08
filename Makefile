CC = g++ -MMD -O3
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
CFLAGS = -g -DGL_GLEXT_PROTOTYPES -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED -DOSX -Wno-deprecated-register -Wno-deprecated-declarations -Wno-shift-op-parentheses
INCFLAGS = -I./lib/glm-0.9.7.1 -I/usr/X11/include -I./src/class
LDFLAGS = -framework GLUT -framework OpenGL -L./lib/mac/ \
		-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
		-lGL -lGLU -lm -lstdc++ -lfreeimage
else
CFLAGS = -g -DGL_GLEXT_PROTOTYPES
INCFLAGS = -I./glm-0.9.7.1 -I./include/ -I/usr/X11R6/include -I/sw/include \
		-I/usr/sww/include -I/usr/sww/pkg/Mesa/include
LDFLAGS = -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L./lib/nix/ \
		-L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lGLEW -lglut -lGLU -lGL -lX11 -lfreeimage
endif

CPP_FILES := $(wildcard ./src/private/*/*.cpp)
OBJ_FILES := $(addprefix ./build/,$(notdir $(CPP_FILES:.cpp=.o)))

RM = /bin/rm -f

all: p1s1
p1s1: $(CPP_FILES)
	$(CC) $(CFLAGS) -o ./build/$@ ./src/p1s1.cpp $(CPP_FILES) $(INCFLAGS)
clean:
	$(RM) build/p1s1 *.o *.d *.DSYM
