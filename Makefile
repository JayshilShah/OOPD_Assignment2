CXX = g++
CXXFLAGS = -std=c++11 -Wall
SOURCES = Library.cpp
EXECUTABLE = track_of_library_items

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(EXECUTABLE)