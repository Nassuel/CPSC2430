# @file Makefile - Makefile for CPSC2430, Seattle University, Spring 2018
# @author Kevin Lundeen
# @see "Seattle University, CPSC2430, Spring 2018"
# @version 1.26, 06-Jun-2018

# Flags:
CPP_FLAGS = -std=c++11 -Wall -Werror -pedantic -ggdb
LNK_FLAGS = 
LIBS = -lgtest -lpthread

# Projects:
ifeq ($(shell pwd),/home/fac/lundeenk/cpsc2430/testmake)
	SUBMIT = ~lundeenk/submit/test
else
	SUBMIT = ~lundeenk/submit/18sq2430
endif

PROJECTS = tw1 tw2 tw3 tw4 tw5 tw7 tw8 tw9 tw10 lab1 lab2 lab3 lab4 lab5 lab6 p1 p2 p3 p4 p5
WORK = RandomList.cpp lab1.cpp CrowWorld.cpp tw2.cpp lab2.cpp InchWorm.cpp Menagerie.cpp tw3.cpp PQueueLL.h adt/PriorityQueue.h BinaryNode.h lab3.cpp BSeeker.h Huffman.cpp BabyHuffman.cpp ConcordanceApp.h ConcordanceApp.cpp ConcordanceBST.cpp ConcordanceBST.h lab4.cpp SetBST.h lab5.cpp DictBST.h tw7.cpp RPN.h RPN.cpp StackV.h ConcordanceApp4.cpp ConcordanceApp4.h ConcordanceH.cpp ConcordanceH.h DictHash.h SetHash.h tw9.cpp lab6.cpp PQHeap.h NewsFeed.h NewsFeed.cpp tw10.cpp SortOptimal.h

GIVEN = CrowWorld.h InchWorm.h lab1_hints.cpp lab1_test.cpp lab2_test.cpp ListA.h ListLL.h PixelMatrix.h PixelMatrix.cpp QueueL.h RandomList.h RGB.cpp RGB.h Terminal.cpp Terminal.h Tower.cpp Tower.h tw1.cpp tw1_test.cpp tw2_hints.cpp p1.cpp Menagerie2.cpp Menagerie.h InchWorm2.cpp Pacer.cpp Pacer.h Cannon.cpp Cannon.h Cannonball.cpp Cannonball.h tw3_test.cpp RandomList_v2.h RandomList_v2.cpp p1_test.cpp lab3_test.cpp tw4.cpp tw4_test.cpp hanoi.cpp hanoiR.cpp p2.cpp p2_test.cpp Bits.cpp Bits.h Huffman.h BitStreamF.cpp BitStreamF.h tw5.cpp tw5_test.cpp BabyHuffman.h p2key SetLA.h p3.cpp p3_test.cpp DictM.h lab4_test.cpp SetS.h lab5_test.cpp CsvFile.h CsvFile.cpp tw7_test.cpp tw8.cpp Tokens.h Tokens.cpp ConcordanceM.h ConcordanceM.cpp p4.cpp p4_test.cpp lab6_test.cpp p5.cpp p5_test.cpp SortNaive.h SortTimer.h

ADTS = adt/List.h adt/Stack.h adt/Queue.h adt/Critter.h adt/Display.h adt/Printable.h adt/BitStream.h adt/Set.h adt/Dictionary.h adt/Concordance.h
DATA_FILES = data/Cities.txt data/Cousins.txt data/Latitude.txt data/Longitude.txt data/Ulysses.txt data/LND01.csv data/DEC_10_SF2_PCT1_with_ann.csv data/Macbeth.txt
TEST_FILES = test/lab2_input.txt

# make with no argument means just update Makefile from source
default: Makefile
	@touch updated_makefile

# header dependencies for all .o files
hanoi.o : Tower.h adt/Stack.h Terminal.h adt/Display.h
hanoiR.o : hanoi.o
BabyHuffman.o : BabyHuffman.h BinaryNode.h Bits.h adt/BitStream.h PQueueLL.h adt/PriorityQueue.h
Bits.o : adt/BitStream.h
BitStreamF.o : Bits.o BitStreamF.h ListA.h adt/List.h
Cannon.o : Cannon.h adt/Critter.h
Cannonball.o : Cannonball.h adt/Critter.h
ConcordanceBST.o : ConcordanceBST.h adt/Concordance.h DictBST.h adt/Dictionary.h ListA.h adt/List.h
ConcordanceH.o : ConcordanceH.h adt/Concordance.h DictHash.h adt/Dictionary.h ListA.h adt/List.h
ConcordanceApp.o : ConcordanceApp.h ConcordanceBST.h adt/Concordance.h DictBST.h adt/Dictionary.h ListA.h adt/List.h
ConcordanceApp4.o : ConcordanceApp4.h ConcordanceH.h adt/Concordance.h DictHash.h adt/Dictionary.h ListA.h adt/List.h
CrowWorld.o : CrowWorld.h ListA.h adt/List.h
CsvFile.o : CsvFile.h DictM.h adt/Dictionary.h ListA.h adt/List.h
Huffman.o : Huffman.h adt/BitStream.h Bits.h BinaryNode.h PQueueLL.h adt/PriorityQueue.h BitStreamF.o
InchWorm.o : InchWorm.h adt/Critter.h PixelMatrix.o
InchWorm2.o : InchWorm.o
Menagerie.o : Menagerie.h Cannon.h InchWorm.h Cannonball.h Pacer.h ListA.h adt/List.h adt/Critter.h adt/Display.h QueueL.h adt/Queue.h
Menagerie2.o : Menagerie.o
NewsFeed.o : NewsFeed.h DictHash.h adt/Dictionary.h adt/List.h
Pacer.o : Pacer.h adt/Critter.h
PixelMatrix.o : RGB.o PixelMatrix.h
RGB.o : RGB.h ListA.h adt/List.h
RPN.o : RPN.h Tokens.h StackV.h adt/Stack.h adt/Queue.h DictBST.h adt/Dictionary.h
RandomList.o : RandomList.h ListA.h adt/List.h
RandomList_v2.o : RandomList_v2.h ListA.h adt/List.h
Terminal.o : Terminal.h PixelMatrix.o adt/Display.h
Tokens.o : Tokens.h adt/Queue.h
Tower.o : Tower.h adt/Stack.h PixelMatrix.o
lab1.o : CrowWorld.o
lab1_test.o : lab1.o
lab2.o : InchWorm.o Terminal.o 
lab2_test.o : lab2.o
lab3.o : BinaryNode.h QueueL.h adt/Queue.h
lab3_test.o : lab3.o
lab4.o : SetS.h SetBST.h adt/Set.h
lab4_test.o : lab4.o
lab5.o : DictBST.h adt/Dictionary.h
lab5_test.o : lab5.o
lab6.o : PQHeap.h adt/PriorityQueue.h adt/List.h
lab6_test.o : lab6.o
p1.o : Menagerie.h ListA.h adt/List.h QueueL.h adt/Queue.h adt/Critter.h
p1_test.o : p1.o
p2.o : Huffman.o BitStreamF.h ListA.h adt/List.h
p2_test.o : p2.o
p3.o : ConcordanceApp.o
p3_test.o : p3.o
p4.o : ConcordanceApp4.o
p4_test.o : p4.o
p5.o : NewsFeed.o
p5_test.o : p5.o
tw1.o : RandomList.o
tw1_test.o : tw1.o
tw2.o : Tower.o Terminal.o QueueL.h adt/Queue.h
tw3.o : PQueueLL.h adt/PriorityQueue.h
tw3_test.o : tw3.o
tw4.o : BSeeker.h
tw4_test.o : tw4.o
tw5.o : BabyHuffman.h Bits.h adt/BitStream.h BinaryNode.h
tw5_test.o : tw5.o
tw7.o : CsvFile.o
tw7_test.o : CsvFile.o
tw8.o : RPN.o
tw9.o : SetHash.h adt/Set.h
tw10.o : SortTimer.h SortNaive.h SortOptimal.h

# TW1
tw1_prep : ListA.h adt/List.h RandomList.h tw1.cpp tw1_test.cpp
	@touch $@
tw1: tw1_prep tw1.o RandomList.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@
tw1_test: tw1 tw1_test.o RandomList.o 
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@_exe
	valgrind ./$@_exe

# L1
lab1_prep: CrowWorld.h lab1_hints.cpp lab1_test.cpp data/Cities.txt data/Cousins.txt data/Longitude.txt data/Latitude.txt
	@touch $@
lab1: lab1_prep lab1.o CrowWorld.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@
lab1_test: lab1 lab1_test.o CrowWorld.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@_exe
	valgrind ./$@_exe

# L2
lab2_prep: InchWorm.h PixelMatrix.h PixelMatrix.cpp Terminal.h Terminal.cpp RGB.h RGB.cpp lab2_test.cpp test/lab2_input.txt adt/Display.h adt/Critter.h adt/Printable.h
	@touch $@
L2_OBJ = InchWorm.o InchWorm2.o PixelMatrix.o Terminal.o RGB.o
lab2: lab2_prep lab2.o $(L2_OBJ)
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -lncurses -o $@
lab2_test: lab2 lab2_test.o $(L2_OBJ)
	./lab2 < test/lab2_input.txt
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -lncurses -o $@_exe
	valgrind ./$@_exe

# R3
reading_3: ListLL.h $(ADTS) 

# TW2
tw2_prep: Tower.h QueueL.h Tower.cpp tw2_hints.cpp
	@touch $@
tw2: tw2_prep tw2.o Tower.o Terminal.o PixelMatrix.o RGB.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -lncurses -o $@
tw2_test: tw2
	@echo "There is no internal testing for tw2."

# P1
-include p1_make_extra
ifndef P1_EXTRA
    P1_EXTRA = 
endif
p1_prep: InchWorm.h PixelMatrix.h PixelMatrix.cpp Terminal.h Terminal.cpp RGB.h RGB.cpp InchWorm2.cpp Pacer.h Pacer.cpp adt/Display.h Cannon.h Cannon.cpp Cannonball.h Cannonball.cpp Menagerie.h Menagerie2.cpp p1.cpp adt/Printable.h
	@touch $@
P1_CORE = Menagerie.o Menagerie2.o InchWorm.o InchWorm2.o Pacer.o Cannon.o Cannonball.o PixelMatrix.o RGB.o
p1: p1_prep p1.o $(P1_CORE) $(P1_EXTRA) Terminal.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -lncurses -o $@
p1_test: $(P1_CORE) $(P1_EXTRA) Terminal.o p1_test.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -lncurses -o $@_exe
	valgrind ./$@_exe

# TW3
tw3_prep: adt/Queue.h QueueL.h adt/List.h ListLL.h tw3_test.cpp RandomList_v2.cpp RandomList_v2.h ListA.h adt/List.h
	@touch $@
tw3: tw3_prep tw3.o 
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@
tw3_test: tw3 tw3_test.o RandomList_v2.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@_exe
	valgrind ./$@_exe

# L3
lab3_prep: QueueL.h adt/Queue.h
	@touch $@
lab3: lab3_prep lab3.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@
lab3_test: lab3 lab3_test.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@_exe
	valgrind ./$@_exe

# TW4
tw4_prep: tw4.cpp tw4_test.cpp data/Ulysses.txt hanoi.cpp hanoiR.cpp
	@touch $@
tw4: tw4_prep tw4.o 
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@
tw4_test: tw4 tw4_test.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@_exe
	valgrind ./$@_exe
HANOI = Tower.o Terminal.o PixelMatrix.o RGB.o
hanoi : hanoi.o $(HANOI)
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -lncurses -o $@
hanoiR : hanoiR.o $(HANOI)
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -lncurses -o $@

# TW5
tw5_prep: tw5.cpp BabyHuffman.h tw5_test.cpp Bits.h Bits.cpp adt/BitStream.h
	@touch $@
tw5: tw5_prep tw5.o BabyHuffman.o Bits.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@
tw5_test: tw5 tw5_test.o BabyHuffman.o Bits.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@_exe
	valgrind ./$@_exe

# P2
p2_prep: p2.cpp p2_test.cpp Huffman.h data/Ulysses.txt adt/BitStream.h BitStreamF.h BitStreamF.cpp Bits.h Bits.cpp
	@touch $@
P2_OBJ = Huffman.o Bits.o BitStreamF.o
p2: p2_prep p2.o $(P2_OBJ)
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@
p2_test: p2 p2_test.o $(P2_OBJ) p2key
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@_exe
	valgrind ./$@_exe

# L4
lab4_prep: lab4_test.cpp adt/Set.h SetS.h SetLA.h adt/Dictionary.h DictM.h
	@touch $@
lab4: lab4_prep lab4.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@
lab4_test: lab4 lab4_test.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@_exe
	valgrind ./$@_exe

# TW7
tw7_prep: CsvFile.cpp CsvFile.h DictM.h adt/Dictionary.h data/LND01.csv data/DEC_10_SF2_PCT1_with_ann.csv
	@touch $@
tw7: tw7_prep tw7.o CsvFile.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@
tw7_test: tw7_test.o CsvFile.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@_exe
	valgrind ./$@_exe

# L5
lab5_prep: lab5_test.cpp adt/Dictionary.h DictM.h
	@touch $@
lab5: lab5_prep lab5.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@
lab5_test: lab5 lab5_test.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@_exe
	valgrind ./$@_exe

# TW8
tw8_prep: tw8.cpp Tokens.cpp Tokens.h adt/Queue.h adt/Dictionary.h
	@touch $@
tw8: tw8_prep tw8.o RPN.o Tokens.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@

# P3
p3_prep: p3.cpp p3_test.cpp adt/Dictionary.h adt/Set.h DictM.h adt/Concordance.h ConcordanceM.cpp ConcordanceM.h
	@touch $@
P3_OBJ = ConcordanceApp.o ConcordanceBST.o
p3: p3_prep p3.o $(P3_OBJ)
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@
p3_test: p3 p3_test.o $(P3_OBJ)
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@_exe
	valgrind ./$@_exe

# P4
p4_prep: p4.cpp p4_test.cpp adt/Dictionary.h adt/Concordance.h data/Ulysses.txt data/Macbeth.txt
	@touch $@
P4_OBJ = ConcordanceApp4.o ConcordanceH.o
p4: p4_prep p4.o $(P4_OBJ)
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@
p4_test: p4 p4_test.o $(P4_OBJ)
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@_exe
	valgrind ./$@_exe

# TW9
tw9_prep: adt/Set.h
	@touch $@
tw9: tw9_prep tw9.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@

# TW10
tw10_prep: SortTimer.h SortNaive.h
	@touch $@
tw10: tw10_prep tw10.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@

# L6
lab6_prep: lab6_test.cpp
	@touch $@
lab6: lab6_prep lab6.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@
lab6_test: lab6 lab6_test.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@_exe
	valgrind ./$@_exe

# P5
p5_prep: p5.cpp p5_test.cpp adt/Dictionary.h adt/PriorityQueue.h
	@touch $@
p5: p5_prep p5.o NewsFeed.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@
p5_test: p5 p5_test.o NewsFeed.o
	g++ $(LNK_FLAGS) $(filter %.o, $^) $(LIBS) -o $@_exe
	valgrind ./$@_exe

# General Stuff
$(GIVEN) Makefile : % : $(SUBMIT)/files/%
	@if [ `pwd` != "/home/fac/lundeenk/cpsc2430" ];then 	\
		echo "Provide/update $@ (from $<)" ; \
		cp -f $< $@ ; \
    else \
		echo "Doh! You're in dev directory. $< newer than $@." ; \
	fi

SUBMIT_EXTRA ?= 
$(foreach proj, $(PROJECTS), $(proj)_submit) : %_submit: %
	$(SUBMIT)/script/$<_runme $(SUBMIT_EXTRA)

$(WORK) : % :
	@echo "Student-provided file, $@, not found"
	@false

$(ADTS): adt/%.h : $(SUBMIT)/files/adt/%.h
	@if [ `pwd` != "/home/fac/lundeenk/cpsc2430" ];then 	\
		echo "Provide/update $@ (from $<)" ; \
		if [ ! -d "./adt" ];then 	\
			mkdir ./adt; 		\
		fi ; \
		cp -f $< $@ ; \
    else \
		echo "Doh! You're in dev directory. $< newer than $@." ; \
	fi

$(DATA_FILES): data/% : $(SUBMIT)/files/data/%
	@if [ `pwd` != "/home/fac/lundeenk/cpsc2430" ];then 	\
		echo "Provide/update $@ (from $<)" ; \
		if [ ! -d "./data" ];then 	\
			mkdir ./data; 		\
		fi ; \
		cp -f $< $@ ; \
    else \
		echo "Doh! You're in dev directory. $< newer than $@." ; \
	fi

$(TEST_FILES): test/% : $(SUBMIT)/files/test/%
	@if [ `pwd` != "/home/fac/lundeenk/cpsc2430" ];then 	\
		echo "Provide/update $@ (from $<)" ; \
		if [ ! -d "./test" ];then 	\
			mkdir ./test; 		\
		fi ; \
		cp -f $< $@ ; \
    else \
		echo "Doh! You're in dev directory. $< newer than $@." ; \
	fi

%.o: %.cpp
	g++ $(CPP_FLAGS) -c $< -o $@

clean:
	rm -f $(GIVEN) $(ADTS) $(DATA_FILES) $(TEST_FILES)
	rm -f *.o
	rm -f $(PROJECTS)
	rm -f $(foreach proj, $(PROJECTS), $(proj)_prep)
	rm -f $(foreach proj, $(PROJECTS), $(proj)_test)
	rm -f $(foreach proj, $(PROJECTS), $(proj)_test_exe)

# release: cp -ruvi * $CS/files
