# Имя исполняемого файла
TARGET = client

# Компилятор и флаги компиляции
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Исходные файлы
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

# Правило по умолчанию
all: $(TARGET)

# Линковка
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

# Компиляция исходников в объектные файлы
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
