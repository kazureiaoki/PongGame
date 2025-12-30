# Pong Game — Тестове завдання Junior C++ Developer

Класична гра **Pong** з AI-противником, реалізована на **C++17** з використанням бібліотеки **SFML 2.6.2**.

---

## 📋 Функціонал

- ✅ Гра "Гравець проти AI"
- ✅ Фізика м'яча з відскоками під різними кутами (залежно від місця удару ракеткою)
- ✅ AI-противник (слідкує за м'ячем з dead-zone)
- ✅ Система рахунку (гра до 5 очок)
- ✅ Екран Game Over з визначенням переможця
- ✅ Пауза після голу (1 секунда) + початкова пауза (2 секунди)
- ✅ Рандомний кут м'яча після кожного голу (-45° до +45°)

---

## 🛠 Технології

- **C++17** (ООП, STL, smart pointers)
- **SFML 2.6.2** (графіка, вікна, події) — через Git Submodule
- **CMake 3.16+** (система збірки)
- **Visual Studio 2022** (MSVC компілятор)

---

## 🏗 Архітектура проєкту

### Структура файлів



```
PongGame/
├── Game.h / Game.cpp       # Головний клас гри (game loop, логіка, рендеринг)
├── Paddle.h                 # Клас ракетки (рух, обмеження)
├── Ball.h                   # Клас м'яча (фізика, колізії)
├── PongGame.cpp             # Точка входу (main)
├── Fonts/                   # Ресурси (шрифт)
├── external/
│   └── SFML/                # SFML як Git Submodule
└── CMakeLists.txt           # Конфігурація збірки
```


### Патерни проєктування
- **Encapsulation**: Paddle, Ball, Game — окремі класи з інкапсульованою логікою
- **Single Responsibility**: Кожен клас відповідає за одну функцію
- **Composition**: Game містить об'єкти Paddle і Ball

### Класи

#### `Game` (`Game.h`, `Game.cpp`)
Головний клас гри, що інкапсулює:
- Вікно (`sf::RenderWindow`)
- Ігровий цикл (game loop з delta time)
- Логіку гри (рух, колізії, рахунок, AI)
- Рендеринг всіх об'єктів

#### `Paddle` (`Paddle.h`)
Клас ракетки з методами:
- `move()` — переміщення по вертикалі
- `clampToWindow()` — обмеження руху в межах вікна
- `draw()` — відмалювання

#### `Ball` (`Ball.h`)
Клас м'яча з логікою:
- `update()` — рух м'яча з урахуванням delta time
- `checkCollision()` — виявлення колізії з ракетками + розрахунок кута відскоку
- `checkGoal()` — перевірка виходу за межі вікна (гол)
- `reset()` — скидання позиції з рандомним кутом

---

## ✅ Відповідність вимогам ТЗ

### 1. Показати знання мови C++ (не C)

**Реалізовано:**
- Використовуються класи (`Game`, `Paddle`, `Ball`)
- Конструктори з member initializer list (наприклад, `Game::Game()` в `Game.cpp`)
- Методи класів з модифікаторами доступу (`public`, `private`)
- References і const-correctness (`const sf::Vector2f&`, `const float`)
- `namespace std` (без `using namespace`)

**Файли:** `Game.cpp:3-19`, `Paddle.h:7-40`, `Ball.h:8-140`

---

### 2. Показати знання ООП та вміння його використовувати

**Реалізовано:**
- **Інкапсуляція:** всі дані класів приховані в `private`, доступ через методи
- **Абстракція:** кожен клас відповідає за свою логіку (Paddle — рух ракетки, Ball — фізика м'яча)
- **Композиція:** клас `Game` містить об'єкти `Paddle` і `Ball` як поля

**Файли:** `Game.h:7-35`, `Paddle.h:7-12`, `Ball.h:8-16`

---

### 3. Показати вміння використовувати STL (контейнери, розумні вказівники)

**Реалізовано:**

#### Розумні вказівники (`std::unique_ptr`)
Використовуються для управління життєвим циклом текстових об'єктів SFML:

```
std::unique_ptrsf::Text scoreText;
std::unique_ptrsf::Text gameOverText;
```

**Файл:** `Game.h:29-30`, `Game.cpp:18-26`


#### STL контейнери (`std::optional`)
SFML 2.6+ повертає події через `std::optional<sf::Event>`:

```
while (const std::optional event = window.pollEvent())
{
if (event->issf::Event::Closed())
window.close();
}
```

**Файл:** `Game.cpp:46-52`


#### STL алгоритми (`std::random_device`, `std::mt19937`)
Рандомізація кута м'яча після голу:

```
static std::random_device rd;
static std::mt19937 rng(rd());
std::uniform_real_distribution<float> distAngle(-45.f, 45.f);
float angleDeg = distAngle(rng);
```


**Файл:** `Ball.h:117-120`

---

### 4. Акуратно оформлений структурований код

**Реалізовано:**
- Код відформатований з консистентним відступом (4 пробіли)
- Іменування змінних: camelCase для локальних, PascalCase для класів
- Коментарі до всіх методів
- Логіка розділена на методи (`handleEvents()`, `update()`, `render()`)

**Файли:** всі `.h` і `.cpp`

---

### 5. Показати вміння підключати та використовувати зовнішні бібліотеки

**Реалізовано:**
- SFML 2.6.2 підключена через **Git Submodule** (посилання: [SFML/SFML](https://github.com/SFML/SFML))
- Автоматична компіляція через CMake — не потребує окремої інсталяції
- Використовуються модулі:
  - `SFML/Graphics.hpp` — графіка, вікна, текстури
  - `SFML/System.hpp` — Clock, Vector2
  - `SFML/Window.hpp` — події, клавіатура

**Файли:** `CMakeLists.txt:13-18`, `Game.cpp:1`, `PongGame.cpp:1`


### Перевірка Submodule

`git submodule status`

Має вивести:

`<commit-hash> external/SFML (2.6.2)`

---

### 6. Показати знання архітектури ігрових рушіїв

**Реалізовано:**

#### Ігровий цикл (Game Loop)
Стандартний цикл з delta time:

```
void Game::run() {
    clock.restart(); // скидання перед циклом

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
    
        handleEvents();  // обробка подій
        update(deltaTime); // оновлення логіки
        render();        // відмалювання
    }
}
```

**Файл:** `Game.cpp:28-56`


#### Розділення логіки
- **handleEvents()** — обробка вводу (закриття вікна)
- **update()** — оновлення стану гри (рух, фізика, AI, колізії)
- **render()** — відмалювання всіх об'єктів

**Файли:** `Game.cpp:46-52` (events), `Game.cpp:58-84` (update), `Game.cpp:86-96` (render)

#### Delta Time
Усі рухи залежать від часу, а не від кадрів:

```
player.move(playerDirection, deltaTime); // швидкість * deltaTime
ball.update(deltaTime, windowWidth, windowHeight);
```

**Файл:** `Paddle.h:19-22`, `Ball.h:23-42`

---

### 7. Показати використання патернів проектування

**Реалізовано:**

#### 1. **Game Loop Pattern**
Стандартний патерн ігрових рушіїв: оновлення стану → відмалювання.

**Файл:** `Game.cpp:28-56`

#### 2. **Encapsulation Pattern**
Кожен клас інкапсулює свою логіку:
- `Paddle` не знає про `Ball`
- `Ball` не знає про `Game`
- `Game` координує всі об'єкти

**Файли:** `Game.cpp`, `Paddle.h`, `Ball.h`


#### 3. **RAII (Resource Acquisition Is Initialization)**
Використання `std::unique_ptr` для автоматичного звільнення ресурсів.

**Файл:** `Game.h:29-30`

---

### 8. Компіляція та запуск

**Реалізовано:**

#### Платформа
- Windows 10/11 x64
- Visual Studio 2022 (MSVC 19.4+)
- CMake 3.16+

#### Запуск
1. Клонувати з `--recursive` (автоматично завантажує SFML)
2. Згенерувати проєкт: `cmake -S . -B build -A x64`
3. Відкрити `build/PongGame.sln`
4. Переключити на **Release | x64**
5. Натиснути **F5** або **Ctrl+F5**

#### Портативність
- Шрифт завантажується з відносного шляху `Fonts/CaesarDressing-Regular.ttf`
- SFML компілюється разом з проєктом через CMake
- Проєкт запускається з будь-якої папки (за умови збереження структури `Fonts/`)

**Файл:** `Game.cpp:12-17` (перевірка помилки завантаження шрифту)

---

## 🎮 Керування

| Клавіша | Дія |
|---------|-----|
| **W** | Рух гравця вгору |
| **S** | Рух гравця вниз |
| **X** (на вікні) | Закриття гри |

---

## 🚀 Як запустити

### Системні вимоги
- **Windows 10/11 x64**
- **Visual Studio 2022** з компонентами:
  - Desktop development with C++
  - CMake tools for Windows
- **Git** (з підтримкою submodules)

### Крок 1: Клонувати репозиторій з submodules
```
git clone --recursive https://github.com/kazureiaoki/PongGame.git
cd PongGame
```

> **Важливо:** Прапорець `--recursive` автоматично завантажить SFML як submodule.

### Крок 2: Згенерувати проєкт через CMake
```
cmake -S . -B build -A x64
```

Ця команда створить папку `build/` з готовим Visual Studio solution.

### Крок 3: Відкрити у Visual Studio
```
start build\PongGame.sln
```

Або вручну: відкрити файл `build/PongGame.sln` у Visual Studio 2022.

### Крок 4: Зібрати і запустити
1. Переключити конфігурацію на **Release | x64**
2. Правою кнопкою на проєкт **PongGame** → **Set as Startup Project**
3. Натиснути **F5** (або **Ctrl+F5** для запуску без дебага)

Гра запуститься у вікні 1280x960 пікселів.

---

## 📝 Примітки з реалізації

### Delta Time
Усі рухи використовують delta time для незалежності від FPS:
`velocity * deltaTime`


### Колізії
Відскок м'яча від ракетки залежить від місця удару (чим ближче до краю, тим гостріший кут).

**Файл:** `Ball.h:49-84`

### AI
Бот реагує на вертикальну позицію м'яча з dead-zone (40 пікселів), щоб не бути ідеальним.

**Файл:** `Game.cpp:98-109`

---

## 🎯 Можливі покращення (за межами ТЗ)

- [ ] Меню (Start/Restart/Settings)
- [ ] Локальний мультиплеєр (2 гравці)
- [ ] Звукові ефекти (відскок, гол)
- [ ] Анімації (trail за м'ячем)
- [ ] Налаштування складності AI
- [ ] Паттерни Observer (для подій голу) / Factory (для створення об'єктів)

---

## 📧 Контакт

**Автор:** Даніела  

**Email:** daniellatskho@gmail.com

**LinkedIn:** https://www.linkedin.com/in/daniellatskhovriebova/

**GitHub:** https://github.com/kazureiaoki/PongGame  

**Дата:** 25.12.2025
