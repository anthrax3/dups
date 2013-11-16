SRC		= src
TEST_SRC	= test
BUILD		= build
BUILD_TEST	= $(BUILD)/test
BUILD_NUMBER	?= '"dev"'
LIB_PATH = /usr/local/lib
#LT = dylib
LT = a

LIBS		= \
			$(LIB_PATH)/libboost_filesystem-mt.$(LT) \
			$(LIB_PATH)/libboost_system-mt.$(LT) \
			$(LIB_PATH)/libboost_program_options-mt.$(LT)

TEST_LIBS	= 	$(LIB_PATH)/libboost_unit_test_framework-mt.$(LT)

OBJECTS 	=	


TEST_OBJECTS	=	$(BUILD_TEST)/test_main.o	\
			$(BUILD_TEST)/bucket_tests.o	\
			$(BUILD_TEST)/match_tests.o

all		:	build/dups test

$(BUILD)	:
	-mkdir $@

$(BUILD_TEST)		:	$(BUILD)
	-mkdir $@

$(BUILD)/dups		:	$(BUILD) $(OBJECTS) $(BUILD)/main.o
	clang++ -g -O1 -o $@ -std=c++11 -D BUILD_NUMBER=$(BUILD_NUMBER) -Xclang "-stdlib=libc++" -lc++ $(SRC)/*.cpp -I /usr/local/include $(LIBS)

$(BUILD)/dupstest	:	$(OBJECTS) $(TEST_OBJECTS)
	clang++ $^ -o $@ -std=c++11 -lc++ $(LIBS) $(TEST_LIBS)

test			:	$(BUILD_TEST) $(BUILD)/dupstest
	./$(BUILD)/dupstest

clean:
	-rm -rf $(BUILD)/*


$(BUILD)/%.o : $(SRC)/%.cpp
	clang++ -g -O1 -std=c++11 -Xclang "-stdlib=libc++" -I $(SRC) -I /usr/local/include -c $< -o $@

$(BUILD_TEST)/%.o : $(TEST_SRC)/%.cpp
	clang++ -g -O1 -std=c++11 -Xclang "-stdlib=libc++" -I $(SRC) -I /usr/local/include -D MAKEFILE_BUILD -c $< -o $@


