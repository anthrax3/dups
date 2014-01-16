SRC		= src
TEST_SRC	= test
BUILD		= build
BUILD_TEST	= $(BUILD)/test
BUILD_NUMBER	?= dev
LIB_PATH = /usr/local/lib
#LT = dylib
LT = a

LIBS		= \
			$(LIB_PATH)/libboost_filesystem-mt.$(LT) 	\
			$(LIB_PATH)/libboost_system-mt.$(LT) 		\
			$(LIB_PATH)/libboost_program_options-mt.$(LT)	\
			$(LIB_PATH)/libboost_regex-mt.$(LT)

TEST_LIBS	= 	$(LIB_PATH)/libboost_unit_test_framework-mt.$(LT)

OBJECTS 	=	


TEST_OBJECTS	=	$(BUILD_TEST)/test_main.o		\
			$(BUILD_TEST)/bucket_tests.o		\
			$(BUILD_TEST)/match_tests.o		\
			$(BUILD_TEST)/text_scanner_tests.o	\
			$(BUILD_TEST)/duplicate_text_finder_tests.o

all		:	build/dups test

$(BUILD)	:
	-mkdir $@

$(BUILD_TEST)		:	$(BUILD)
	-mkdir $@

$(BUILD)/dups		:	$(BUILD) $(OBJECTS) $(BUILD)/main.o
	clang++ -g -O1 -o $@ -std=c++11 -D BUILD_NUMBER='"$(BUILD_NUMBER)"' -Xclang "-stdlib=libc++" -lc++ $(SRC)/*.cpp -I /usr/local/include $(LIBS)

$(BUILD)/dupstest	:	$(OBJECTS) $(TEST_OBJECTS)
	clang++ $^ -o $@ -std=c++11 -lc++ $(LIBS) $(TEST_LIBS)

test			:	$(BUILD_TEST) $(BUILD)/dupstest
	./$(BUILD)/dupstest

ci-test: results.xml

results.xml	: $(BUILD)/dupstest
	./$^ --log_format=XML --log_sink=results.xml --log_level=all --report_level=no

ci-build:	ci-test dmg

dist	:
	-mkdir dist

dmg:	dups-install-0.0.$(BUILD_NUMBER).dmg

dups-install-0.0.$(BUILD_NUMBER).dmg : $(BUILD)/dups dist/README.html
	ln -s /usr/local/bin dist/bin
	cp $(BUILD)/dups dist
	hdiutil create tmp.dmg -ov -volname "dups - duplicate finder" -fs HFS+ -srcfolder "dist" 
	hdiutil convert tmp.dmg -format UDZO -o dups-install-0.0.$(BUILD_NUMBER).dmg
	-rm tmp.dmg

dist/README.html	:	dist	README.md
	markdown README.md > dist/README.html

clean:
	-rm -rf $(BUILD)/*
	-rm dups-install*.dmg
	-rm tmp.dmg
	-rm -rf dist


$(BUILD)/%.o : $(SRC)/%.cpp	$(BUILD)
	clang++ -g -O1 -std=c++11 -Xclang "-stdlib=libc++" -I $(SRC) -I /usr/local/include -c $< -o $@

$(BUILD)/%.o : $(SRC)/%.c	$(BUILD)
	clang -g -O1 -I $(SRC) -I /usr/local/include -c $< -o $@

$(BUILD_TEST)/%.o : $(TEST_SRC)/%.cpp	$(BUILD_TEST)
	clang++ -g -O1 -std=c++11 -Xclang "-stdlib=libc++" -I $(SRC) -I /usr/local/include -D MAKEFILE_BUILD -c $< -o $@


