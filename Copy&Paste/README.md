# Copy & Paste

Для автоматического редактирования большого количества текстовых файлов нужен текстовый редактор, который поддерживает небольшое количество действий:
* переместить курсор на строчку вниз (Down),
* переместить курсор на строчку вверх (Up),
* зажать клавишу Shift (Shift),
* вырезать строки (текущую строку) в буфер обмена (Ctrl+X),
* вставить строки из буфера перед текущей строкой (Ctrl+V).

Операции `Up` и `Down` при зажатой клавише `Shift` выделяют строки в текстовом редакторе. Если курсор находится на строке N, то после операций `Shift, Down, Down` выделенными окажутся строки N и N+1.

Операция `Ctrl+X` вырезает выделенные строки из файла в буфер. Операция `Ctrl+V` копирует строки из буфера, заменяя выделенные строки в файле.

Операции `Ctrl+X` и `Ctrl+V` сбрасывают выделение после исполнения и отпускают клавишу `Shift`. 

Если при исполнении `Ctrl+X` в файле не выделена ни одна строка, то вырезается в буфер обмена текущая строка.

Операция `Ctrl+X` перезаписывает буфер, если в нём уже было какое-то значение. 

Операция `Ctrl+V` не очищает буфер и может быть использована несколько раз подряд. 

Операция `Ctrl+V` при пустом буфере ничего не делает. 

Изначально буфер редактора пустой.

Изначально (при открытии файла) курсор находится на первой (начальной) строке.

Операции `Up` с курсором на первой строке и `Down` с курсором на последней строке должны игнорироваться.

Любой текстовый файл заканчивается переводом строки. Поэтому последняя строка любого файла является пустой и операция `Ctrl+X` на этой пустой строке ничего не должна делать.

Напишите программу, которая применяет заданный набор команд к заданному текстовому файлу.

Имена входного тестового файла, файла с командами и выходного файла заданы в командной строке.

## Пример
Вызов программы `copypaste text1.txt commands1.txt output.txt`

Если файл `text1.txt` содержит текст:
```
My
program
is
awful
bad
poor
wrong
awesome

```

Файл `commands1.txt` команды:
```
Down
Down
Down
Shift
Down
Down
Down
Down
Ctrl+X
```

То содержимое файла `output.txt` должно получиться:
```
My
program
is
awesome
```


Формат ввода
Других пустых строк в файле быть не может.

После этого и до окончания ввода программе подаются команды Down, Up, Ctrl+X, Ctrl+V.

Формат вывода
Выведите получившийся файл построчно.

### Формат входного файла
Входной файл это набор строк, разделённых переносом строки. 
Длина каждой строки не превышает 1000 символов. 
Последняя строка в файле является пустой. 

### Формат файла команд
Файл с командами это набор строк, в каждой из которых указана отдельная команда `Down`, `Up`, `Shift`, `Ctrl+X`, `Ctrl+V`.

### Выход
В выходной файл запишите результат редактирования входного файла.

## Требования к реализации
Программа не должна использовать контейнеры STL (std::vector, std::string и т. д.). 
