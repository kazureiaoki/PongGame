# Pong Game — Тестове завдання Junior C++ Developer

Класична гра **Pong** з AI-противником, реалізована на **C++17** з використанням бібліотеки **SFML 3.0.2**.

---

## 📋 Функціонал

- ✅ Гра "Гравець проти AI"
- ✅ Фізика м'яча з відскоками під різними кутами (залежно від місця удару ракеткою)
- ✅ AI-противник з реалістичною поведінкою (dead-zone для уникнення ідеальної точності)
- ✅ Система рахунку (гра до 5 очок)
- ✅ Екран Game Over з визначенням переможця
- ✅ Рестарт гри (клавіша **R**)
- ✅ Вихід з гри (клавіша **ESC**)
- ✅ Пауза після голу з видимим м'ячем (1 секунда)
- ✅ Рандомний кут м'яча після кожного голу (-45° до +45°)

---

## 🛠 Технології

- **C++17** (ООП, наслідування, поліморфізм, STL, smart pointers)
- **SFML 3.0.2** (графіка, вікна, події) — через Git Submodule
- **CMake 3.21+** (система збірки)
- **Visual Studio 2022** (MSVC компілятор)

---

## 🏗 Архітектура проєкту

### Структура файлів

```
PongGame/
├── src/
│   ├── include/
│   │   ├── GameObject.h          # Базовий абстрактний клас для всіх ігрових об'єктів
│   │   ├── Ball.h                # Клас м'яча (наслідує GameObject)
│   │   ├── Paddle.h              # Клас ракетки (наслідує GameObject)
│   │   ├── Game.h                # Головний клас гри (композиція)
│   │   ├── TextObject.h          # Базовий клас для текстових елементів
│   │   ├── ScoreText.h           # Рахунок (наслідує TextObject)
│   │   ├── GameOverText.h        # Game Over повідомлення
│   │   ├── RestartHintText.h     # Підказка рестарту
│   │   └── Constants.h           # Всі константи гри
│   ├── Ball.cpp
│   ├── Paddle.cpp
│   ├── Game.cpp
│   ├── TextObject.cpp
│   ├── ScoreText.cpp
│   ├── GameOverText.cpp
│   ├── RestartHintText.cpp
│   └── PongGame.cpp              # Точка входу (main)
├── Fonts/
│   └── CaesarDressing-Regular.ttf
├── external/
│   └── SFML/                     # SFML як Git Submodule
└── CMakeLists.txt

```

### Ієрархія класів

```
GameObject (abstract)
├── Paddle
├── Ball
└── TextObject
    ├── ScoreText
    ├── GameOverText
    └── RestartHintText
```

---

## ✅ Відповідність вимогам ТЗ

### 1. Знання C++ (не C)

| Вимога | Реалізація | Файл |
|--------|-----------|------|
| **Класи з конструкторами** | `Game()`, `Ball()`, `Paddle()` | `Game.h`, `Ball.cpp` |
| **Member Initializer List** | Ініціалізація полів через `:` | `Game.cpp:34-40` |
| **const-correctness** | `sf::FloatRect getBounds() const` | `Ball.h:32` |
| **namespace** | `using namespace PongConstants` | `Game.cpp:10`, `Ball.cpp:7` |
| **enum class** | `enum class LaunchDirection`, `FieldCollision` | `Game.h:29`, `Ball.h:7` |
| **constexpr** | `constexpr float PADDLE_WIDTH = 20.0f` | `Constants.h:7-52` |
| **override** | `void update(float dt) override`... | `Paddle.h:15`, `Ball.h:24` |

---

### 2. Знання ООП

| Принцип | Реалізація | Файл |
|---------|-----------|------|
| **Наслідування** | `GameObject` → `Paddle`, `Ball`, `TextObject` | `GameObject.h:6`, `Paddle.h:7` |
| **Поліморфізм** | Віртуальні `update()`, `draw()`... | `GameObject.h` |
| **Інкапсуляція** | `private` поля, `public` методи | `Paddle.h:8-12`... |
| **Композиція** | `Game` містить `Paddle`, `Ball`, UI | `Game.h:20-23` |
| **Абстракція** | `GameObject` як abstract base | `GameObject.h` (pure virtual) |

---

### 3. Використання STL

| Елемент STL | Де використовується | Файл |
|-------------|---------------------|------|
| **std::vector** | Перевірка шляхів завантаження шрифту | `Game.cpp:53-55` |
| **std::string** | Робота з текстом  | `GameOverText.h:12` |
| **std::optional** | Обробка подій SFML 3.x | `Game.cpp:195` |
| **std::clamp** | Обмеження кута відскоку м'яча | `Ball.cpp:89` |

---

### 4. Структурування коду

| Аспект | Реалізація |
|--------|-----------|
| **Розділення `.h/.cpp`** | Всі класи мають окремі `.h` та `.cpp` файли |
| **Іменування** | Класи: `PascalCase`, методи: `camelCase`, поля: `m_` prefix, константи: `UPPER_SNAKE_CASE` |
| **Константи** | `Constants.h` — всі магічні числа винесені |
| **Separation of Concerns** | `handleEvents()`, `update()`, `render()` — окремі методи |
| **DRY Principle** | `TextObject` — базовий клас для всіх текстів (замість дублювання) |

---

### 5. Підключення зовнішніх бібліотек

| Аспект | Реалізація |
|--------|-----------|
| **SFML 3.0.2** | Через Git Submodule (`git clone --recursive`) |
| **CMake** | `add_subdirectory(external/SFML)` + `target_link_libraries` |
| **Автокопіювання ресурсів** | CMake post-build command копіює `Fonts/` |
| **Переносимість** | Перевірка 3-х шляхів завантаження шрифту |

---

### 6. Знання архітектури ігрових рушіїв

| Елемент | Реалізація | Файл |
|---------|-----------|------|
| **Game Loop** | `handleEvents → update → render` | `Game.cpp:111-113` |
| **Delta Time** | `float deltaTime = m_clock.restart().asSeconds()` | `Game.cpp:104` |
| **Delta Time Clamping** | Обмеження максимального `deltaTime` | `Game.cpp:106-109` |
| **Game States** | `m_ballWaiting`, `m_gameOver` | `Game.h:37-40` |
| **Collision Detection** | `handleFieldCollision()`, `handlePaddleCollision()` | `Ball.cpp:33, 74` |
| **AI Logic** | `updateAI()` з dead-zone | `Game.cpp:174-192` |

---

## 🔥 Правки після рев'ю

### Правки (1-ша частина)

| # | Правка | Статус |
|---|--------|--------|
| 1 | Файли в `src/` | ✅ Виправлено |
| 2 | Всі класи мають `.cpp` | ✅ Виправлено |
| 3 | DRY: базовий клас `GameObject` | ✅ Виправлено |
| 7 | Магічні числа в `Constants.h` | ✅ Виправлено |
| 8 | `m_` префікс для полів | ✅ Виправлено |
| 13 | `update()` для всіх об'єктів | ✅ Виправлено |

### Правки (2-га частина)

| # | Правка | Статус |
|---|--------|--------|
| 1 | `sf::Text m_text;` замість `unique_ptr` | ✅ Виправлено |
| 3-5 | `updatePlayerInput()`, `updateAI()` БЕЗ `deltaTime` | ✅ Виправлено |
| 6 | `ScoreText` тримає рахунок (`addPlayerPoint()`, `addBotPoint`) | ✅ Виправлено |
| 7 | `enum class FieldCollision` замість `-1/+1/0` | ✅ Виправлено |
| 8 | Віртуальні `setPosition/getPosition` в `GameObject` | ✅ Виправлено |
| 9 | `setVisible(bool)` замість `show()/hide()` | ✅ Виправлено |
| 14 | `handleFieldCollision` + `handlePaddleCollision` | ✅ Виправлено |
| 15 | `const` для локальних змінних | ✅ Виправлено |
| 16 | Всі магічні числа в константи (`HALF_DIVISOR`..) | ✅ Виправлено |

---

## 📊 Статистика проєкту

- **Загальна кількість рядків коду:** ~1000 LOC
- **Класів:** 9 (1 abstract, 8 concrete)
- **Файлів:** 18 (`.h` + `.cpp` + `CMakeLists.txt`)
- **Констант:** 37 (в `Constants.h`)
- **Enum classes:** 2 (`LaunchDirection`, `FieldCollision`)

---

## 🎯 Особливості реалізації

### Фізика м'яча

- Відскоки від ракетки змінюють кут залежно від місця удару
- Макс. кут відскоку: ±45°
- Швидкість зростає з кожним ударом (+20 px/s, макс. 800 px/s)

**Файл:** `Ball.cpp:33-112` (`handlePaddleCollision`)

### AI логіка

- "Мертва зона" 40px (бот не реагує на малі відхилення)
- Рух до центру м'яча, але НЕ ідеально

**Файл:** `Game.cpp:174-192` (`updateAI`)

### Система рахунку

- `ScoreText` зберігає рахунок (`m_playerScore`, `m_botScore`)
- Методи `addPlayerPoint()`, `addBotPoint()`, `reset()`
- Single Responsibility: рахунок живе в об'єкті, який його малює

**Файл:** `ScoreText.h`, `ScoreText.cpp`

### Collision Detection

- `handleFieldCollision()` повертає `enum class FieldCollision`
- `handlePaddleCollision()` отримує `sf::FloatRect` (не весь `Paddle`)
- Кут відскоку розраховується через offset від центру ракетки

**Файл:** `Ball.cpp:33-71, 73-112`

---

## 🚀 Як запустити

```
bash
# 1. Клонувати з SFML submodule
git clone --recursive https://github.com/yourusername/PongGame.git
cd PongGame

# 2. Згенерувати VS solution
cmake -S . -B build -A x64

# 3. Відкрити в Visual Studio 2022
start build\PongGame.sln

# 4. Зібрати та запустити (F5)
```

---

## 📧 Контакт

**Автор:** Даніела  

**Email:** daniellatskho@gmail.com

**LinkedIn:** daniellatskhovriebova

**Дата:** 26.01.2026
