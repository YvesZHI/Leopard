g++1x:=g++ -std=c++11 -MMD -MP -g
CFLAGS:= -Wall -static-libstdc++
LDLIBS=-lpthread

TARGET:=a.out
SRS:=$(shell find * -type f -name "*.cpp")
OBJDIR:=.obj
OBJ:=$(addprefix $(OBJDIR)/,$(SRS:.cpp=.o))
BIN:=./


.PHONY: install
install: $(BIN) $(BIN)/$(TARGET) $(OBJ)

$(BIN):
	@echo "creating bin directory";
	@mkdir -p $(BIN);

$(BIN)/$(TARGET): $(OBJ)
	$(g++1x) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(OBJ): $(OBJDIR)/%.o: %.cpp
	@if [ ! -d "$(@D)" ]; then\
		echo "creating obj directories"; \
		mkdir -p "$(@D)";\
	fi
	$(g++1x) -c -o $@ $<


-include $(OBJ:.o=.d)


.PHONY: clean
clean:
	@echo "removing bin and obj";
	@rm -rf $(BIN)/$(TARGET);
	@rm -rf $(OBJDIR);
