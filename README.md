# Оглавление

- [Проект: c-rpn (Калькулятор RPN)](#проект-c-rpn-калькулятор-rpn)
- [Complex Numbers Calculator](#complex-numbers-calculator)
- [Операции с Матрицами](#операции-с-матрицами)
- [SpinningCube (mySpinningCube)](#spinningcube-myspinningcube)
- [Игра "Крестики-нолики" на C (tic-tac-toe)](#игра-крестики-нолики-на-c-tic-tac-toe)

---

# Проект: c-rpn (Калькулятор RPN)

Этот проект представляет собой консольный калькулятор, реализующий обратную польскую нотацию (Reverse Polish Notation, RPN) для выполнения арифметических операций. Калькулятор поддерживает базовые арифметические операции и проверки на корректность введенных данных.

## Оглавление

- [Описание проекта](#описание-проекта)
- [Модули проекта](#модули-проекта)
  - [Стек (stack.h)](#стек-stackh)
  - [Обработка выражений RPN (rpn.h)](#обработка-выражений-rpn-rpnh)
  - [Основная программа (main.c)](#основная-программа-mainc)
- [Использование](#использование)
- [Примеры ввода и вывода](#примеры-ввода-и-вывода)

## Описание проекта

Калькулятор RPN — это консольное приложение для вычисления выражений в обратной польской нотации. Калькулятор принимает входные выражения с операндами и операторами, разделенными пробелами, и поддерживает следующие арифметические операции:
- Сложение (`+`)
- Вычитание (`-`)
- Умножение (`*`)
- Деление (`/`)

## Модули проекта

### Стек (stack.h)

Модуль `stack.h` предоставляет структуру стека для хранения операндов, используемых в процессе вычисления RPN.

#### Функции модуля stack.h:

- **`initialize_stack`** — Инициализирует новый стек и возвращает указатель на него.
- **`stack_is_full`** — Проверяет, заполнен ли стек.
- **`stack_push`** — Добавляет элемент на вершину стека. Если стек заполнен, выводит сообщение об ошибке.
- **`stack_is_empty`** — Проверяет, пуст ли стек.
- **`stack_pop`** — Удаляет и возвращает элемент с вершины стека. Если стек пуст, возвращает ошибку `STACK_UNDERFLOW_ERR`.
- **`stack_peek`** — Возвращает значение элемента на вершине стека без удаления.

### Обработка выражений RPN (rpn.h)

Модуль `rpn.h` выполняет обработку строки с выражением в RPN, выполняет арифметические операции и возвращает результат.

#### Функции модуля rpn.h:

- **`is_valid_char`** — Проверяет, является ли символ допустимым для выражения RPN (цифра, оператор или пробел).
- **`check_valid_str`** — Проверяет, содержит ли строка только допустимые символы.
- **`check_decimal_points`** — Проверяет правильность использования десятичных точек.
- **`check_spaces`** — Проверяет корректность пробелов в выражении.
- **`make_operation`** — Выполняет одну из операций (`+`, `-`, `*`, `/`) над двумя верхними элементами стека.
- **`parse_expression`** — Разбирает строку RPN, выполняет операции и возвращает результат.
- **`start_rpn`** — Основной цикл программы для обработки выражений RPN и вывода результата.
- **`menu`** — Выводит инструкции по использованию калькулятора и запускает обработку выражений.

### Основная программа (main.c)

Модуль `main.c` содержит функцию `main`, которая вызывает функцию `menu` для начала работы с калькулятором.

## Использование

1. **Клонируйте репозиторий**:
   ```bash
   git clone https://github.com/totallynotbuzzismaloy/c-rpn.git
   ```
2. **Сборка программы**:
   ```bash
   gcc main.c -o main
   ```
3. **Запуск**:
    ```bash
   ./main
   ```

---

# Complex Numbers Calculator (complex-numbers-calc)

Complex Numbers Calculator — это консольное приложение на языке C, позволяющее выполнять основные арифметические операции с комплексными числами. Программа поддерживает такие операции, как сложение, вычитание, умножение, деление, а также вычисление модуля, аргумента и нахождение комплексного сопряжения.

## Оглавление

- [Описание](#описание)
- [Установка и запуск](#установка-и-запуск)
- [Используемые структуры и функции](#используемые-структуры-и-функции)
  - [Тип Complex](#тип-complex)
  - [Функции для работы с комплексными числами](#функции-для-работы-с-комплексными-числами)
- [Поддерживаемые операции](#поддерживаемые-операции)
- [Дополнительная информация](#дополнительная-информация)

## Описание

Complex Numbers Calculator — это проект на языке C, позволяющий выполнять операции над двумя комплексными числами, которые вводятся пользователем. Поддерживаются следующие операции:

- Сложение
- Вычитание
- Умножение
- Деление
- Вычисление модуля
- Вычисление аргумента
- Нахождение комплексного сопряжения

## Установка и запуск

1. **Клонируйте репозиторий**:
   ```bash
   git clone https://github.com/totallynotbuzzismaloy/complex-numbers-calc.git
   cd complex-numbers-calc
   ```
2. **Сборка программы**:
   ```bash
   gcc main.c -o main -lm
   ```
3. **Запуск**:
   ```bash
   ./main
   ```
   
## Используемые структуры и функции

### Тип Complex

Комплексное число представлено структурой Complex, которая определяет действительную и мнимую часть числа:

```c
typedef struct {
    double real;
    double imag;
} Complex;
```
### Функции для работы с комплексными числами
- **Основные арифметические операции**:

    - **`Complex add(Complex* a, Complex* b)`** — сложение комплексных чисел a и b.
    - **`Complex subtract(Complex* a, Complex* b)`** — вычитание комплексных чисел a и b.
    - **`Complex multiply(Complex* a, Complex* b)`** — умножение комплексных чисел a и b.
    - **`Complex divide(Complex* a, Complex* b)`** — деление комплексного числа a на b.

- **Дополнительные функции**:

    - **`double get_modulus(Complex* a)`** — возвращает модуль комплексного числа a.
    - **`double get_argument(Complex* a)`** — возвращает аргумент комплексного числа a.
    - **`Complex get_conjugate(Complex* a)`** — возвращает комплексное сопряжение для числа a.
    - **`void print_complex(Complex* numb)`** — выводит комплексное число numb в формате real ± imagi.
    - **`void scan_complex_numb(Complex* numb)`** — считывает комплексное число из ввода.
    - **`void scan_operation(char* operation)`** — считывает оператор из ввода и проверяет его на допустимость.

## Поддерживаемые операции

   - `+` — сложение двух комплексных чисел.
   - `—` вычитание второго числа из первого.
   - `*` — умножение двух комплексных чисел.
   - `/` — деление первого числа на второе.
   - `#` — вычисление модуля для каждого числа.
   - `^` — вычисление аргумента для каждого числа.
   - `&` — нахождение комплексного сопряжения для каждого числа.

## Дополнительная информация

- При вводе комплексных чисел формат должен быть следующий: `<действительная часть>` `<мнимая часть>`, например, `3 4` представляет собой комплексное число `3 + 4i`.
- Для ввода операции используйте символы `+, -, *, /, #, ^, &`. Если введённый символ не поддерживается, программа попросит повторить ввод.


---

# Операции с Матрицами (matrix-operations)

Проект на языке C, реализующий основные операции с матрицами. Поддерживаются операции сложения, вычитания, умножения матриц, умножения на скаляр, транспонирования, вычисления определителя, обратной матрицы и следа.

## Содержание
- [Особенности](#особенности)
- [Начало работы](#начало-работы)
- [Использование](#использование)
- [Операции](#операции)

## Особенности
- Сложение и вычитание матриц
- Умножение матриц и умножение матрицы на скаляр
- Транспонирование матрицы
- Вычисление определителя матрицы
- Обратная матрица
- Вычисление следа матрицы

## Начало работы

### Предварительные требования
- Компилятор C (например, GCC)
- git

### **Клонируйте репозиторий**
```bash
git clone https://github.com/totallynotbuzzismaloy/matrix-operations.git
```

### **Компиляция**
Для компиляции программы используйте следующую команду:
```bash
gcc main.c -o main
```

### **Запуск**
```bash
./main
```

## Операции
- `1` - Сложение двух матриц
- `2` - Вычитание одной матрицы из другой
- `3` - Умножение двух матриц
- `4` - Умножение матрицы на скаляр
- `5` - Транспонирование матрицы
- `6` - Вычисление определителя матрицы
- `7` - Нахождение обратной матрицы
- `8` - Вычисление следа матрицы
- `0` - Завершение работы программы

---

# SpinningCube (mySpinningCube)

**SpinningCube** — это консольное приложение на языке C, которое отображает вращающийся куб с ASCII-анимацией. Программа позволяет изменить цвет шрифта и управлять приложением через меню, доступное в консоли.

## Оглавление

1. [Описание](#описание)
2. [Требования](#требования)
3. [Установка](#установка)
4. [Использование](#использование)
5. [Функции](#функции)
6. [Выход из программы](#выход-из-программы)

## Описание

SpinningCube создает эффект вращающегося куба, используя символы ASCII, и предоставляет возможность изменения цвета шрифта. Вращение и отображение куба выполняется в бесконечном цикле, где используются математические вычисления для преобразования координат куба в плоскость экрана.

## Требования

- Компилятор, поддерживающий стандарт языка C (например, GCC).
- Терминал для запуска приложения.

## Установка

1. **Клонируйте репозиторий**:
   ```bash
   git clone https://github.com/totallynotbuzzismaloy/mySpinningCube.git
   ```
2. **Компиляция**:
   ```bash
   gcc main.c -o main -lm
   ```
3. **Запуск**:
   ```bash
   ./main
   ```

## Использование
После запуска программы появится меню с доступными действиями:

   1. **Вращение куба** — выводит вращающийся куб в ASCII-графике.
   2. **Изменение цвета шрифта** — позволяет выбрать один из доступных цветов текста:
       - Зеленый
       - Красный
       - Стандартный цвет терминала
   3. **Выход** — завершает программу.
   
Выберите необходимую операцию, введя соответствующий номер и нажав Enter.

## Функции

### Основные функции

- `calculate_x`, `calculate_y`, `calculate_z` — вычисление координат вершин куба в пространстве.
- `calculate_surface` — расчет видимой поверхности и ее отображение.
- `spin_cube` — основной цикл вращения куба и отрисовка кадров.
- `set_font_colour` — изменение цвета шрифта.
- `read_font_choice` — выбор цвета из доступных опций.
- `reset_font_colour` — сброс цвета шрифта к значению по умолчанию.
- `read_user_choice` — выбор действия из главного меню.

### Дополнительные функции

- `run` — запуск главного цикла приложения и отображение меню.
- `signal_handler` — обработка сигнала SIGINT для корректного выхода из программы.
- `quit` — завершение работы программы.

## Выход из программы

Для выхода из программы выберите опцию "3" в меню или используйте комбинацию клавиш `Ctrl + C`.


---

# Игра "Крестики-нолики" на C (tic-tac-toe)

## Описание проекта

Проект представляет собой классическую игру "Крестики-нолики", разработанную на языке C. Игрок может выбрать один из двух режимов: играть против другого игрока или с ботом, который использует базовый алгоритм для выполнения ходов.

## Структура проекта

Проект состоит из нескольких модулей:

1. **main.c**: Точка входа программы, запускающая игру.
2. **game.h**: Реализует основные функции для работы с игрой, включая меню и запуск различных игровых режимов.
3. **player.h**: Управляет созданием и управлением данными игрока.
4. **field.h**: Содержит функции для работы с игровым полем (отрисовка и установка начального состояния).
5. **game_check.h**: Модуль для проверки текущего состояния игры (выигрыш, ничья или продолжение).
6. **bot_algo.h**: Реализует алгоритм бота, который включает стратегию блокировки и выигрышные ходы.

## Функциональность

### 1. Запуск игры
Функция `run()` запускает игру и предоставляет меню с выбором режима:
- Игрок против игрока
- Игрок против бота
- Выход из игры

### 2. Игровое поле
Поле представляет собой 3x3 сетку, которая отображается с помощью функции `draw_board()` из модуля `field.h`. Все ячейки в начале пустые и заполняются символами игроков ("X" и "O") по ходу игры.

### 3. Игроки
Игроки представлены структурой `Player` из модуля `player.h`. Каждый игрок имеет имя и символ, который используется для заполнения ячеек поля. Игроки создаются и инициализируются с помощью функции `create_player()`.

### 4. Алгоритм бота
Бот использует следующий алгоритм (в `bot_algo.h`):
- Проверка на возможность выиграть ходом.
- Блокировка хода противника, если он может выиграть.
- Заполнение центра поля, если оно пустое.
- Случайный ход, если вышеуказанные действия невозможны.

### 5. Проверка победы
Модуль `game_check.h` предоставляет функции для проверки различных условий:
- Горизонтальные, вертикальные и диагональные победы.
- Наличие свободных ячеек для продолжения игры.
- Объявление ничьей, если все ячейки заполнены, но победителя нет.

## Установка и запуск

1. **Клонируйте репозиторий**:
   ```bash
   git clone https://github.com/totallynotbuzzismaloy/tic-tac-toe.git
   ```
2. **Скомпилируйте проект с помощью любого C-компилятора (например, gcc)**:
   ```bash
   gcc main.c -o main
   ```
3. Запуск
   ```bash
   ./main
   ```
   
## Использование

После запуска программы пользователь увидит меню с выбором режима. Управление осуществляется с помощью ввода чисел:

   - Выберите "1", чтобы играть против другого игрока.
   - Выберите "2", чтобы играть против бота.
   - Выберите "0" для выхода из игры.

Во время игры вводите координаты хода в формате "x y", где x и y - координаты ячейки на игровом поле.

## Примечание

Программа также обрабатывает некорректный ввод, оповещая пользователя о необходимости корректного ввода значений. В случае прерывания программы (например, при нажатии `Ctrl+C`) очищается память.

## Дополнительная информация

- **Символы игроков**: Игрок 1 использует символ "X", а Игрок 2 или бот используют символ "O".
- **Меню игры**: Меню позволяет переключаться между игровыми режимами, а также возвращаться к меню после завершения партии.

