# Коллоквиум по дискретной математике

Статус репозитория:
[![Build status](https://github.com/VolodyaZAVR/DM-project/workflows/Build/badge.svg)](https://github.com/VolodyaZAVR/DM-project/actions?query=workflow%3ABuild)
[![Test status](https://github.com/VolodyaZAVR/DM-project/workflows/Test/badge.svg)](https://github.com/VolodyaZAVR/DM-project/actions?query=workflow%3ATest)

Это лишь экспериментальная версия оболочки. В ней запросто могут найтись ошибки и недоработки. Обо всех проблемах, пожалуйста, сообщайте лично или через "Issues" на GitHub.

### [Исполняемый файл для Windows (.exe)](https://github.com/VolodyaZAVR/DM-project/raw/master/main.exe)

### Как это работает?

Весь проект разделён на множество заголовочных файлов:

- `main.c` отвечает за запуск интерфейса;

- `config.h` позволяет включить или отключить определённый модуль;

- `template.h` содержит список доступных функций и структур для работы с числами, дробями и многочленами.

В папке `interface/`:

- `interface.h` выводит интерфейс и обеспечивает ввод команд;

- `list.h` выводит справку по доступным модулям;

- `call.h` вызывает функции из директории `call`;

- `system.h` содержит функции для низкоуровневой работы с памятью;

- `numbers.h` содержит функции ввода-вывода чисел, дробей и многочленов;

- `io.h` упрощает печать и ввод символов;

- `locale.h` содержит элементы текстовой части интерфейса;

- `include.h` отвечает за включение в проект модулей, прописанных в `config.h`.

В `interface/call/` содержатся файлы с обёртками для каждого модуля.

В директории `modules/` содержатся сами модули.
