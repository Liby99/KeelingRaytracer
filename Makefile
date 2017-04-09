CC = @ g++ -MMD -O3
LD = @ ld -r
MKDIR = @ mkdir -p
ECHO = @ echo
RM = @ /bin/rm -rf

ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'), Mac)
CFLAGS = -g -DGL_GLEXT_PROTOTYPES -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED -DOSX -Wno-deprecated-register -Wno-deprecated-declarations -Wno-shift-op-parentheses
INCFLAGS = -I./lib/glm-0.9.7.1 -I/usr/X11/include -I./src/class
endif

BUILD_DIRECTORY := ./build/

CPP_DIRECTORY := ./src/private/
OBJ_DIRECTORY := ./build/bin/
DIRECTORIES := $(sort $(dir $(OBJ_FILES)))
CPP_FILES := $(wildcard $(CPP_DIRECTORY)*/*.cpp)
OBJ_FILES := $(patsubst $(CPP_DIRECTORY)%.cpp, $(OBJ_DIRECTORY)%.o, $(CPP_FILES))

TEST_DIRECTORY := ./test/
BUILD_TEST_DIRECTORY := ./build/test/
TEST_CPP_FILES := $(wildcard $(TEST_DIRECTORY)*.cpp)
TESTS := $(basename $(notdir $(TEST_CPP_FILES)))
TEST_OBJ_FILES := $(addprefix $(BUILD_TEST_DIRECTORY), $(TESTS))

RAYTRACER := ./build/raytracer.o

all: $(TEST_OBJ_FILES) cleanCache

$(TESTS): $(patsubst $(TEST_DIRECTORY)%.cpp, $(BUILD_TEST_DIRECTORY)%, $@)
	
$(TEST_OBJ_FILES): $(RAYTRACER) | $(BUILD_TEST_DIRECTORY)
	$(ECHO) "Building Test File $@"
	$(CC) $(CFLAGS) $(TEST_DIRECTORY)$(basename $(notdir $@)).cpp $(RAYTRACER) -o $@ $(INCFLAGS)
	
$(RAYTRACER): $(OBJ_FILES)
	$(ECHO) "Linking Raytracer"
	$(LD) $(OBJ_FILES) -o $(RAYTRACER)
	
$(BUILD_TEST_DIRECTORY):
	$(ECHO) "Creating Testing Directories"
	$(MKDIR) $@
	
$(DIRECTORIES):
	$(ECHO) "Creating Directories"
	$(MKDIR) $@
	
$(OBJ_DIRECTORY)%.o: $(CPP_DIRECTORY)%.cpp | $(DIRECTORIES)
	$(ECHO) "Building $@"
	$(CC) $(CFLAGS) -c $< -o $@ $(INCFLAGS)
	
cleanCache:
	$(RM) $(BUILD_TEST_DIRECTORY)*.dSYM $(BUILD_TEST_DIRECTORY)*.d *.d

clean:
	$(RM) $(RAYTRACER) $(addprefix $(BUILD_DIRECTORY), $(TESTS)) $(addprefix $(BUILD_DIRECTORY), $(addsuffix .dSYM, $(TESTS))) $(OBJ_FILES) $(OBJ_FILES:.o=.d)
