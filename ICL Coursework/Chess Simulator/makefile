OBJ = ChessMain.o ChessBoard.o Pieces.o king.o bishop.o rook.o queen.o knight.o pawn.o
EXE = chess

CXX = g++
CXXFLAGS = -Wall -g

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJ:.o=.d)

clean:
	rm -f $(EXE) $(OBJ) $(OBJ:.o=.d)

.PHONY: clean
