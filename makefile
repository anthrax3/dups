SRC		= src
TEST_SRC	= test
BUILD		= build
BUILD_NUMBER	?= '"dev"'
LIB_PATH = /usr/local/lib
#LT = dylib
LT = a

LIBS		= \
			$(LIB_PATH)/libboost_filesystem-mt.$(LT) \
			$(LIB_PATH)/libboost_system-mt.$(LT) \
			$(LIB_PATH)/libboost_program_options-mt.$(LT)

TEST_LIBS	= 	$(LIB_PATH)/libboost_unit_test_framework-mt.$(LT)

OBJECTS 	=	$(BUILD)/main.o


TEST_OBJECTS	=	$(BUILD)/test_main.o

all	:	build/dups test

$(BUILD)	:
	mkdir $(BUILD)

build/dups	:	$(BUILD) $(OBJECTS)
	clang++ -g -O1 -o $@ -std=c++11 -D BUILD_NUMBER=$(BUILD_NUMBER) -Xclang "-stdlib=libc++" -lc++ $(SRC)/*.cpp -I /usr/local/include $(LIBS)

$(BUILD)/dupstest	:	$(OBJECTS) $(TEST_OBJECTS)
	c++ $^ -o $@ -std=c++11 -lc++ $(LIBS) $(TEST_LIBS)

test: $(BUILD)/dupstest
	./$^

clean:
	-rm -rf $(BUILD)/*


$(BUILD)/%.o : $(SRC)/%.cpp
	clang++ -g -O1 -std=c++11 -Xclang "-stdlib=libc++" -I $(SRC) -I /usr/local/include -c $< -o $@

$(BUILD)/%.o : $(TEST_SRC)/%.cpp
	clang++ -g -O1 -std=c++11 -Xclang "-stdlib=libc++" -I $(SRC) -I /usr/local/include -D MAKEFILE_BUILD -c $< -o $@


