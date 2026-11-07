# Nutter Programming Language (v1.3)

InShot_20261107_164014837.jpg

[RU] Официальная документация языка программирования Nutter.
[EN] Official documentation for the Nutter programming language.

---

## [RU] РУССКАЯ ВЕРСИЯ

### 1. Общие сведения
* **Название языка:** Nutter (Наттер)
* **Расширение файлов:** `.erno`
* **Парадигма:** Эзотерический текстовый моно-функциональный язык (ЭТМЯ).
* **Философия:** Абсолютный минимализм, скорость и хардкор. Язык создан исключительно для вывода текста. В нём физически невозможно совершить утечку памяти, создать баг или написать говнокод, так как в нём отсутствует любая сложная логика управления данными.

### 2. Архитектура и синтаксис
В языке Nutter v1.3 существует всего три встроенные синтаксические конструкции. Любые другие символы или попытки объявить переменные/циклы вызывают критическую ошибку компиляции.

#### Список команд:
1. `language: [КОД]` — Оператор-переключатель контекста языка.
   * Доступные значения: `RU` (русский) и `EN` (английский).
   * При переключении индексы внутри `erno` начинают отсчитываться для выбранного алфавита заново с единицы (`1`).
   * По умолчанию (если команда не вызвана в начале файла) активен режим `RU`.
2. `erno [X1, X2, X3, ... Xn]` — Оператор вывода строки.
   * `erno` — ключевое слово.
   * `[...]` — контейнер для массива индексов.
   * `X` — целочисленный индекс буквы из активной таблицы символов. Разделитель индексов — запятая.
3. `enter` — Оператор перевода строки.
   * Самостоятельная команда. Не требует скобок и аргументов.
   * Осуществляет перевод каретки вывода на новую строку (`\n`).

### 3. Глобальная таблица символов (Алфавиты)
Символ `0` во всех режимах всегда является **пробелом**. Символ `60` во всех режимах является **восклицательным знаком (`!`)**. Регистр букв при выводе по умолчанию приводится к нижнему.

#### Режим `language: RU` (1–33):
* **0** — пробел
* **1** — А | **10** — И | **19** — С | **28** — Ъ
* **2** — Б | **11** — Й | **20** — Т | **29** — Ы
* **3** — В | **12** — К | **21** — У | **30** — Ь
* **4** — Г | **13** — Л | **22** — Ф | **31** — Э
* **5** — Д | **14** — М | **23** — Х | **32** — Ю
* **6** — Е | **15** — Н | **24** — Ц | **33** — Я
* **7** — Ё | **16** — О | **25** — Ч 
* **8** — Ж | **17** — П | **26** — Ш
* **9** — З | **18** — Р | **27** — Щ

#### Режим `language: EN` (1–26):
* **0** — пробел
* **1** — A | **8** — H  | **15** — O | **22** — V
* **2** — B | **9** — I  | **16** — P | **23** — W
* **3** — C | **10** — J | **17** — Q | **24** — X
* **4** — D | **11** — K | **18** — R | **25** — Y
* **5** — E | **12** — L | **19** — S | **26** — Z
* **6** — F | **13** — M | **20** — T
* **7** — G | **14** — N | **21** — U

### 4. Пример программы (`global_test.erno`)
```text
language: EN
erno [8,5,12,12,15,0,23,15,18,12,4,60]
enter
language: RU
erno [17,18,10,3,6,20,0,15,21,20,6,18,60]
```
**Вывод программы:**
```text
hello world!
привет нутер!
```

---

## [EN] ENGLISH VERSION

### 1. Overview
* **Language Name:** Nutter
* **File Extension:** `.erno`
* **Paradigm:** Esoteric Textual Mono-functional Language (ETML).
* **Philosophy:** Absolute minimalism, extreme speed, and hardcore simplicity. The language is built exclusively for printing text. It is physically impossible to leak memory, cause a bug, or write bad logic because it lacks any complex data management.

### 2. Architecture & Syntax
Nutter v1.3 features exactly three built-in syntax constructs. Any other symbols or attempts to declare variables/loops will trigger a critical compilation error.

#### Command List:
1. `language: [CODE]` — Language context switcher.
   * Supported values: `RU` (Russian) and `EN` (English).
   * Switching resets the token indexes inside `erno` to start from one (`1`) for the selected alphabet.
   * Defaults to `RU` mode if not specified at the beginning of the file.
2. `erno [X1, X2, X3, ... Xn]` — String print operator.
   * `erno` — keyphrase.
   * `[...]` — container for the index array.
   * `X` — integer index of a letter in the active character table. Indexes are comma-separated.
3. `enter` — Line break operator.
   * Standalone command. Requires no brackets or arguments.
   * Moves the output carriage to a new line (`\n`).

### 3. Global Character Table (Alphabets)
The index `0` is always a **whitespace (space)** in all modes. The index `60` is always an **exclamation mark (`!`)** in all modes. Printed output defaults to lowercase.

#### `language: RU` Mode (1–33):
* **0** — Space
* **1** — А | **10** — И | **19** — С | **28** — Ъ
* **2** — Б | **11** — Й | **20** — Т | **29** — Ы
* **3** — В | **12** — К | **21** — У | **30** — Ь
* **4** — Г | **13** — Л | **22** — Ф | **31** — Э
* **5** — Д | **14** — М | **23** — Х | **32** — Ю
* **6** — Е | **15** — Н | **24** — Ц | **33** — Я
* **7** — Ё | **16** — О | **25** — Ч 
* **8** — Ж | **17** — П | **26** — Ш
* **9** — З | **18** — Р | **27** — Щ

#### `language: EN` Mode (1–26):
* **0** — Space
* **1** — A | **8** — H  | **15** — O | **22** — V
* **2** — B | **9** — I  | **16** — P | **23** — W
* **3** — C | **10** — J | **17** — Q | **24** — X
* **4** — D | **11** — K | **18** — R | **25** — Y
* **5** — E | **12** — L | **19** — S | **26** — Z
* **6** — F | **13** — M | **20** — T
* **7** — G | **14** — N | **21** — U

### 4. Code Example (`global_test.erno`)
```text
language: EN
erno [8,5,12,12,15,0,23,15,18,12,4,60]
enter
language: RU
erno [17,18,10,3,6,20,0,15,21,20,6,18,60]
```
**Console Output:**
```text
hello world!
привет нутер!
```
