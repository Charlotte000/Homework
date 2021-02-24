# Task 1.2
Реализовать преобразование Барроуза-Уилера. На вход подаётся строка, на выходе должна получиться строка, преобразованная Барроузом-Уилером, и позиция конца строки в результате преобразования. Реализовать также и обратное преобразование, принимающее преобразованную строку и позицию, и возвращающую исходную строку. Проверить, что исходная строка действительно восстанавливается.  
 - Решение, где в прямом преобразовании явно строится таблица вращений строк («наивный BWT»), оценивается на один балл ниже максимума.  
 - Решение, где в обратном преобразовании не используется построение циклической перестановки, а явно сортируются строки и строится таблица («наивный обратный BWT»), также лишает вас одного балла.  
 - Использование в явном виде символа конца строки также даёт минус балл (поскольку исходная строка, вообще говоря, может содержать любой символ — преобразование Барроуза-Уилера используется и для сжатия бинарных файлов, где может встречаться вообще всё, что угодно).