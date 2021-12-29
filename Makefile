.PHONY: all clean

# Объектные файлы
OBJS_LIB = trie.o
OBJS_APP = main.o

# Файл библиотеки
# Действует соглашение: файл библиотеки <mylib> имеет имя lib<mylib>.a
MYLIBNAME = libtrie.a
# Файл программы
MYAPPNAME = myapp.out

# Чтобы достичь цели "all", требуется построить библиотеку
all: $(MYLIBNAME) $(MYAPPNAME)

clean:
	$(RM) -f $(OBJS_LIB)
	$(RM) -f $(OBJS_APP)
	$(RM) -f $(OBJS_LIB:.o=.d)
	$(RM) -f $(OBJS_APP:.o=.d)
	$(RM) -f $(MYLIBNAME)
	$(RM) -f $(MYAPPNAME)


# Параметры компиляции
CFLAGS= -std=c11 -pedantic -Wall -Wextra -O1

# Включаемые файлы следует искать в каталоге "include"
INCLUDES+= -I ./include

# Рецепт построения файла библиотеки из имеющихся объектных файлов
# значением переменной $@ будет имя файла библиотеки
# значением переменной $^ будет список (с пробелом в качестве символа-разделителя) зависимостей
#     (с удаленными дубликатами), в данном случае - список объектных файлов
$(MYLIBNAME): $(OBJS_LIB)
	$(AR) -rsc $@ $^

# Рецепт построения объектного файла из исходного текста
# значением переменной $< будет имя первого файла в списке зависимостей, в данном случае - имя исходного файла
%.o: %.c
	gcc -MD $(CFLAGS) $(INCLUDES) -c -o $@ $<

# Включаем всю имеющуюся информацию о зависимостях
# Лидирующий "-" означает, что отсутствие файла .d не является ошибкой
-include $(OBJS_LIB:.o=.d)

$(MYAPPNAME): $(OBJS_APP) $(MYLIBNAME)
	gcc -o $@  $^

-include $(OBJS_APP:.o=.d)