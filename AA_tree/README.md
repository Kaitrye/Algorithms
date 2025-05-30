# AA-Tree

Реализовать контейнер множество с помощью самобалансирующегося AA-дерева.

На вход программе подаются строки, содержащие команды. Каждая строка содержит одну команду. 
* Команда «+ X» означает добавление в множество числа X, по модулю не превышающего 10<sup>9</sup>. 
* Команда «− X» означает изъятие элемента из множества. 
* Команда «? X» означает проверку наличия числа X в множестве.

## Входной файл
В первой строке содержится N (1 ≤ N ≤ 10<sup>6</sup>) — число команд. В последующих строках содержатся команды, по одной в каждой строке.

## Выходной файл
* Для каждой операции «+ X» или «– X» вывести баланс корня дерева после выполнения операции. Если дерево пустое (в нем нет вершин), вывести 0. 
* Для каждой операции «? X» вывести её результат: true, если ключ есть в множестве, false – иначе. 
* Результаты должны быть выведены в том порядке, в котором эти операции встречаются во входном файле. 
* Вывод для каждой операции должен содержаться в отдельной строке.

Имена входного и выходного файла задаются в командной строке.

## Требования к реализации
Программа не должна использовать контейнеры STL (std::vector, std::string и т. д.). 

