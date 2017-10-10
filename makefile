OBJ = chessSimulation.o board.o piece.o king.o queen.o castle.o bishop.o knight.o pawn.o

EXE = chessSimulation

CXX = g++
CXXFLAGS = -Wall -g -MMD

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJ:.o=.d)

clean:
	rm -f $(EXE) $(OBJ) $(OBJ:.o=.d) *~ *#

.PHONY: clean