CXX = g++
TARGET = myproject
PROJ = C++_1.cpp
PREPROC = project.i
ASS = project.s
OBJ = project.o
# Флаги # - Предупреждения - Отладочная информация
CXXFLAGS = -Wall -g

#Будут удалены промежуточные файлы после компиляции
.INTERMEDIATE: $(TARGET) $(PREPROC) $(ASS) $(OBJ)

# Цель по умолчанию
all: $(TARGET)



# Линковка
$(TARGET): $(OBJ)
	@echo "Создание исполняемого файла..."
	$(CXX) $(OBJ) -o $(TARGET)

# Ассемблирование
$(OBJ): $(ASS)
	@echo "Ассемблирование..."
	$(CXX) -c $(ASS) -o $(OBJ)

# Компиляция
$(ASS): $(PREPROC)
	@echo "Компиляция в ассемблер..."
	$(CXX) -S $(PREPROC) -o $(ASS)

# Препроцессинг
$(PREPROC): $(PROJ)
	@echo "Препроцессинг, сборка директорий..."
	$(CXX) -E $(PROJ) -o $(PREPROC)

distclean: clean
	rm -f $(TARGET) $(PREPROC) $(ASS) $(OBJ)

# Запуск
run: $(TARGET)
	./$(TARGET)

# Объявление файловых целей (чтобы make не искал файлы с такими именами)
.PHONY: all clean

