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

### Діаграма наслідування:

- `GameObject` — базовий клас з `virtual` методами `update()` і `draw()`
- `Paddle` і `Ball` — наслідують фізичну логіку від `GameObject`
- `TextObject` — базовий клас для всіх текстових елементів (рахунок, Game Over, підказки)
- 3 текстові класи — наслідують `TextObject` і додають специфічну логіку

### Використані патерни

1. **Inheritance** — `GameObject` → `Paddle`, `Ball`, `TextObject`
2. **Composition** — `Game` містить об'єкти `Paddle`, `Ball`, текстові елементи
3. **DRY Principle** — `TextObject` для уникнення дублювання коду
4. **Encapsulation** — `getBounds()` замість прямого доступу до `shape`
5. **enum class** — type-safe `LaunchDirection`
6. **Game Loop Pattern** — `handleEvents()` → `update()` → `render()`
7. **RAII** — `std::unique_ptr` для автоматичного управління пам'яттю

---

## ✅ Відповідність вимогам ТЗ

### 1. Показати знання мови C++ (не C)

**Реалізовано:**

#### Класи з конструкторами та деструкторами

```
class Game {
public:
    Game();              // Конструктор
    virtual ~Game() = default;  // Віртуальний деструктор
};
```

**Файл:** `Game.h:25-26`

#### Member Initializer List

```
Game::Game()
    : m_scorePlayer(0)
    , m_scoreBot(0)
    , m_ballWaiting(true)
    , m_ballWaitTimer(0.f)
    , m_gameOver(false)
    , m_lastGoalScorer(LaunchDirection::ToPlayer)
{
    // Тіло конструктора
}
```

**Файл:** `Game.cpp:37-44`

#### References та const-correctness

```
void setPosition(const sf::Vector2f& position);  // const reference
sf::FloatRect getBounds() const;                 // const method
```

**Файли:** `GameObject.h:17`, `Paddle.h:29`

#### namespace (без using namespace std)

```
using namespace PongConstants;
std::unique_ptr<ScoreText> m_scoreText;
```

**Файли:** `Game.cpp:6`, `Game.h:19`

#### enum class

```
enum class LaunchDirection {
    ToPlayer = -1,
    ToBot = 1
};
```

**Файл:** `Game.h:10-13`

#### constexpr (compile-time константи)

```
constexpr float PADDLE_WIDTH = 20.0f;
constexpr float PI = 3.14159265358979323846f;
constexpr float DEG_TO_RAD = PI / 180.0f;  // Обчислюється на етапі компіляції
```

**Файл:** `Constants.h:7,21-22`

#### override keyword (явне перевизначення)

```
void update(float deltaTime) override;  // Явно вказуємо що це override
void draw(sf::RenderWindow& window) override;
```

**Файли:** `Paddle.h:15-16`, `Ball.h:17-18`

---

### 2. Показати знання ООП та вміння його використовувати

**Реалізовано:**

#### Наслідування

Ієрархія класів з базовим абстрактним класом:

```
// Базовий клас
class GameObject {
public:
    virtual void update(float deltaTime) = 0;  // Pure virtual
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~GameObject() = default;
};

// Похідні класи
class Paddle : public GameObject { ... };
class Ball : public GameObject { ... };
class TextObject : public GameObject { ... };
```

**Файли:** `GameObject.h:7-12`, `Paddle.h:7`, `Ball.h:9`, `TextObject.h:10`

#### Поліморфізм

Віртуальні методи перевизначаються в похідних класах:

```
// GameObject.h (базовий)
virtual void update(float deltaTime) = 0;

// Paddle.cpp (реалізація)
void Paddle::update(float deltaTime) {
    m_position += m_velocity * deltaTime;
    m_shape.setPosition(m_position);
}

// Ball.cpp (інша реалізація)
void Ball::update(float deltaTime) {
    m_position += m_velocity * deltaTime;
    m_shape.setPosition(m_position);
}
```

**Файли:** `GameObject.h:9`, `Paddle.cpp:11-14`, `Ball.cpp:20-23`

#### Інкапсуляція

Всі поля private, доступ через методи:

```
class Paddle {
private:
    sf::RectangleShape m_shape;
    float m_speed;
    sf::Vector2f m_size;

public:
    sf::FloatRect getBounds() const;
    float getSpeed() const { return m_speed; }
};
```

**Файл:** `Paddle.h:8-10,26-27`

Приклад правильної інкапсуляції:

```
// ❌ ПОГАНО (direct access to internal state):
m_ball.getShape().setPosition(...);

// ✅ ДОБРЕ (accessor method):
sf::FloatRect bounds = m_ball.getBounds();
```

**Файли:** `Game.cpp:159`, `Ball.cpp:129-131`

#### Композиція

Клас `Game` містить інші об'єкти (has-a relationship):

```
class Game {
private:
    Paddle m_player;
    Paddle m_bot;
    Ball m_ball;
    std::unique_ptr<ScoreText> m_scoreText;
};
```

**Файл:** `Game.h:16-23`

#### Абстракція (Abstraction)

Кожен клас приховує деталі реалізації:

```
// Ball.h — зовнішній інтерфейс
void checkCollision(const sf::FloatRect& bounds);

// Ball.cpp — складна логіка прихована
void Ball::checkCollision(const sf::FloatRect& paddleBounds) {
    // 40 рядків складних обчислень кута відскоку
    // Зовні це виглядає як один простий виклик методу
}
```

**Файли:** `Ball.h:22`, `Ball.cpp:52-89`

---

### 3. Показати вміння використовувати STL (контейнери, розумні вказівники)

**Реалізовано:**

#### Розумні вказівники (std::unique_ptr)

Використовуються для управління пам'яттю текстових об'єктів:

```
// Game.h
std::unique_ptr<ScoreText> m_scoreText;
std::unique_ptr<GameOverText> m_gameOverText;
std::unique_ptr<RestartHintText> m_restartHintText;

// Game.cpp — створення
m_scoreText = std::make_unique<ScoreText>(m_font);
m_gameOverText = std::make_unique<GameOverText>(m_font);
m_restartHintText = std::make_unique<RestartHintText>(m_font);

// Автоматичне звільнення при знищенні Game — не треба delete!
```

**Файли:** `Game.h:19-21`, `Game.cpp:61-63`

Чому `unique_ptr`?

- RAII (Resource Acquisition Is Initialization) — автоматичне звільнення
- Немає ризику memory leak
- Явне ownership (Game володіє текстовими об'єктами)

`std::optional` (C++17)

SFML 2.6+ повертає події через `std::optional`:

```
void Game::handleEvents() {
    while (const std::optional<sf::Event> event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }
    }
}
```

**Файл:** `Game.cpp:109-120`

`std::vector` (STL контейнер)

Використовується для перевірки кількох шляхів завантаження шрифту:

```
const std::vector<std::string> fontPaths = {
    "./Fonts/CaesarDressing-Regular.ttf",
    "../Fonts/CaesarDressing-Regular.ttf",
    "Fonts/CaesarDressing-Regular.ttf"
};

for (const auto& path : fontPaths) {
    if (m_font.openFromFile(path)) {
        fontLoaded = true;
        break;
    }
}
```

**Файл:** `Game.cpp:47-57`

`std::string` (STL контейнер)

Використовується замість C-style `char*`:

```
void GameOverText::setMessage(const std::string& message) {
    if (m_text) {
        m_text->setString(message);
    }
}
```

**Файли:** `GameOverText.h:12`, `GameOverText.cpp:12-16`

STL алгоритми (`std::clamp`)

```
#include <algorithm>

float normalized = std::clamp(offset / maxOffset, -1.f, 1.f);
```

**Файл:** `Ball.cpp:1,70`

---

### 4. Акуратно оформлений структурований код

**Реалізовано:**

Форматування

- Відступ: 4 пробіли
- Фігурні дужки: на новому рядку для функцій, на тому ж для control flow
- Консистентне розташування const, &, *

Іменування

- Класи: `PascalCase` (`GameObject`, `ScoreText`)
- Методи: `camelCase` (`updateScore`, `centerHorizontally`)
- Поля класу: `m_` prefix (`m_player`, `m_scoreBot`)
- Константи: `UPPER_SNAKE_CASE` (`PADDLE_WIDTH`, `AI_DEAD_ZONE`)

#### Розділення логіки на методи:

```
void Game::run() {
    while (m_window.isOpen()) {
        float deltaTime = m_clock.restart().asSeconds();
        
        handleEvents();   // Обробка подій
        update(deltaTime); // Оновлення логіки
        render();         // Відмалювання
    }
}
```

**Файл:** `Game.cpp:76-89`

#### Separation of Concerns

```
// Окремий метод для ініціалізації
void Game::initializeGameObjects();

// Окремий метод для AI
void Game::updateAI(float deltaTime);

// Окремий метод для input
void Game::updatePlayerInput(float deltaTime);

// Окремий метод для запуску м'яча
void Game::launchBall(LaunchDirection direction);
```

**Файли:** `Game.h:37-42`, `Game.cpp:16-35,122-134,170-183,245-269`

Відсутність магічних чисел

```
// ❌ БУЛО:
m_player.setSize(20.f, 100.f);

// ✅ СТАЛО:
m_player.setSize(PADDLE_WIDTH, PADDLE_HEIGHT);
```

**Файли:** `Game.cpp:19`, `Constants.h:7-8`

---

### 5. Показати вміння підключати та використовувати зовнішні бібліотеки

**Реалізовано:**

#### **SFML** через **Git Submodule**

```
# Автоматичне завантаження SFML разом з проєктом:
git clone --recursive https://github.com/kazureiaoki/PongGame.git
```
#### **CMakeLists.txt**:

```
# Підключення SFML як submodule
add_subdirectory(external/SFML)

# Лінкування до проєкту
target_link_libraries(PongGame PRIVATE 
    sfml-graphics 
    sfml-window 
    sfml-system
)
```

**Файл:** `CMakeLists.txt:5,24-28`

Перевірка наявності **submodule**

```
# Перевірка чи завантажився SFML:
git submodule status

# Має вивести:
# <commit-hash> external/SFML (3.0.2)
```

Використання модулів **SFML**

```
#include <SFML/Graphics.hpp>  // Графіка, вікна, текстури
#include <SFML/System.hpp>     // Clock, Vector2
#include <SFML/Window.hpp>     // Події, клавіатура
```

**Файли:** `Game.cpp:1`, `Paddle.cpp:1`, `Ball.cpp:1`

Автоматичне копіювання ресурсів

CMake автоматично копіює шрифти після збірки:

```
add_custom_command(TARGET PongGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Fonts
    $<TARGET_FILE_DIR:PongGame>/Fonts
)
```

**Файл:** `CMakeLists.txt:30-34`

Переносимість

Шрифт завантажується з кількох можливих шляхів:

```
const std::vector<std::string> fontPaths = {
    "./Fonts/CaesarDressing-Regular.ttf",   // Поточна папка
    "../Fonts/CaesarDressing-Regular.ttf",  // Рівень вище
    "Fonts/CaesarDressing-Regular.ttf"      // Subdir
};

bool fontLoaded = false;
for (const auto& path : fontPaths) {
    if (m_font.openFromFile(path)) {
        fontLoaded = true;
        break;
    }
}

if (!fontLoaded) {
    throw std::runtime_error("ERROR: Font not found in any path");
}
```

**Файл:** `Game.cpp:47-59`

---

### 6. Показати знання архітектури ігрових рушіїв

**Реалізовано:**

#### Ігровий цикл (Game Loop)

Стандартний цикл з delta time:

```
void Game::run() {
    if (!m_window.isOpen() || !m_scoreText || !m_gameOverText) {
        return;
    }
    
    m_clock.restart();  // Початкове скидання
    
    while (m_window.isOpen()) {
        float deltaTime = m_clock.restart().asSeconds();
        
        // Обмеження deltaTime при lag spike
        if (deltaTime > 0.1f) {
            deltaTime = 0.016f;  // ~60 FPS
        }
        
        handleEvents();     // 1. Обробка вводу
        update(deltaTime);  // 2. Оновлення логіки
        render();           // 3. Відмалювання
    }
}
```

**Файл:** `Game.cpp:76-89`

#### Delta Time

Всі рухи незалежні від FPS:

```
void Paddle::update(float deltaTime) {
    m_position += m_velocity * deltaTime;  // position += velocity * time
}

```

**Файли:** `Paddle.cpp:11-14`, `Ball.cpp:20-23`

Чому це важливо?

- На слабкому ПК (30 FPS): рух повільніший, але deltaTime більше → результат однаковий
- На потужному ПК (120 FPS): рух швидший, але deltaTime менше → результат однаковий

#### Розділення логіки

```
// 1. ОБРОБКА ПОДІЙ (Input)
void Game::handleEvents() {
    while (const std::optional<sf::Event> event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }
        
        if (event->is<sf::Event::KeyPressed>()) {
            // Обробка клавіш R, ESC
        }
    }
}

// 2. ОНОВЛЕННЯ ЛОГІКИ (Update)
void Game::update(float deltaTime) {
    updatePlayerInput(deltaTime);  // Input handling
    updateAI(deltaTime);            // AI logic
    
    m_player.update(deltaTime);     // Physics
    m_bot.update(deltaTime);
    m_ball.update(deltaTime);
    
    checkGoals();                   // Game logic
    updateScore();                  // UI logic
}

// 3. ВІДМАЛЮВАННЯ (Render)
void Game::render() {
    m_window.clear(sf::Color::Black);
    
    m_player.draw(m_window);
    m_bot.draw(m_window);
    m_ball.draw(m_window);
    m_scoreText->draw(m_window);
    m_gameOverText->draw(m_window);
    m_restartHintText->draw(m_window);
    
    m_window.display();
}
```

**Файли:** `Game.cpp:109-120` (events), `Game.cpp:122-169` (update), `Game.cpp:185-204` (render)

#### State Management

Стани гри керуються через флаги:

```
bool m_gameOver;       // Чи гра завершена?
bool m_ballWaiting;    // Чи м'яч на паузі після голу?
float m_ballWaitTimer; // Таймер паузи
```

**Файл:** `Game.h:20-22`

---

### 7. Показати використання патернів проектування

**Реалізовано:**

#### 1. Game Loop Pattern

Безкінечний цикл оновлення-відмалювання.

**Файл:** `Game.cpp:76-89`

#### 2. Factory Method Pattern

Метод `launchBall()` створює різні конфігурації м'яча:

```
enum class LaunchDirection {
    ToPlayer = -1,
    ToBot = 1
};

void Game::launchBall(LaunchDirection direction) {
    float angleRad = BALL_INITIAL_ANGLE_DEG * DEG_TO_RAD;
    float dir = static_cast<float>(direction);
    
    m_ball.setVelocity(
        std::cos(angleRad) * BALL_INITIAL_SPEED * dir,
        std::sin(angleRad) * BALL_INITIAL_SPEED
    );
}
```

**Файли:** `Game.h:10-13`, `Game.cpp:8-14`

#### 3. Template Method Pattern

Базовий клас визначає skeleton algorithm:

```
// GameObject.h
class GameObject {
public:
    virtual void update(float deltaTime) = 0;  // Template method
    virtual void draw(sf::RenderWindow& window) = 0;
};

// Похідні класи реалізують кроки:
void Paddle::update(float deltaTime) { /* specific logic */ }
void Ball::update(float deltaTime) { /* different logic */ }
```

**Файл:** `GameObject.h:9-10

#### 4. Strategy Pattern

AI логіка винесена в окремий метод, можна легко замінити:

```
void Game::updateAI(float deltaTime) {
    float botDirection = 0.f;
    sf::Vector2f ballPos = m_ball.getPosition();
    sf::FloatRect botBounds = m_bot.getBounds();
    
    float botCenterY = botBounds.position.y + botBounds.size.y / 2.f;
    
    // Стратегія AI: рухатись до м'яча з dead-zone
    if (ballPos.y < botCenterY - AI_DEAD_ZONE) {
        botDirection = -1.f;
    } else if (ballPos.y > botCenterY + AI_DEAD_ZONE) {
        botDirection = 1.f;
    }
    
    sf::Vector2f velocity = { 0.f, botDirection * m_bot.getSpeed() };
    m_bot.setVelocity(velocity);
}
```

**Файл:** `Game.cpp:206-221`

Розширюваність:

```
// Легко додати складніший AI:
void Game::updateHardAI(float deltaTime) {
    // Predict ball position
    // Move to intercept point
}
```

#### 5. Encapsulation Pattern

Приховування внутрішньої реалізації через accessor methods.

```
// ❌ ПОГАНО:
sf::RectangleShape& getShape();  // Прямий доступ

// ✅ ДОБРЕ:
sf::FloatRect getBounds() const;  // Копія bounds
```

**Файли:** `Paddle.h:29`, `Ball.h:27`

#### 6. RAII Pattern

Автоматичне управління ресурсами через `std::unique_ptr`.

**Файл:** `Game.h:19-21`

#### 7. Separation of Concerns Pattern

Різні аспекти гри розділені:

```
void initializeGameObjects();    // Initialization
void handleEvents();             // Input handling
void updatePlayerInput();        // Player logic
void updateAI();                 // AI logic
void update();                   // Game logic
void render();                   // Rendering
void checkGoals();               // Scoring
void updateScore();              // UI update
void launchBall();               // Ball launch logic
void resetGame();                // Game reset
```

**Файл:** `Game.h:37-42`

---

### 8. Компіляція та запуск

**Реалізовано:**

#### Платформа
- Windows 10/11 x64
- Visual Studio 2022 (MSVC 19.4+)
- CMake 3.21+

#### Запуск
1. Клонувати з `--recursive` (автоматично завантажує SFML)

```
git clone --recursive https://github.com/your-username/PongGame.git
cd PongGame
```

> **Важливо:** Прапорець `--recursive` автоматично завантажить SFML як submodule.

2. Згенерувати проєкт: `cmake -S . -B build -A x64`
3. Відкрити у Visual Studio `start build\PongGame.sln`
4. Зібрати і запустити:

    - Переключити на Release | x64
    - Set as Startup Project → PongGame
    - Натиснути F5 або Ctrl+F5

#### Портативність

- ✅ Шрифт завантажується з відносних шляхів (3 варіанти)
- ✅ SFML компілюється разом з проєктом
- ✅ Автоматичне копіювання ресурсів через CMake
- ✅ Проєкт запускається з будь-якої папки (за умови збереження структури Fonts/)

Перевірка портативності:

```
# Скопіюй PongGame.exe + Fonts/ в іншу папку
# Має запуститися без помилок!
```

**Файл:** `Game.cpp:47-59` (перевірка помилки завантаження шрифту)

---

## 🎮 Керування

| Клавіша | Дія |
|---------|-----|
| **W** | Рух гравця вгору |
| **S** | Рух гравця вниз |
| **R** | Рестарт гри (тільки після Game Over) |
| **ESC** | Закриття гри |
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
`position += velocity * deltaTime`

**Файли:** `Paddle.cpp:11-14`, `Ball.cpp:20-23`

### Колізії

Відскок м'яча від ракетки залежить від місця удару:

- Центр ракетки → 0° (горизонтально)
- Край ракетки → ±45° (діагонально)

```
float offset = hitY - paddleCenterY;
float normalized = offset / maxOffset;  // [-1, 1]
float angleDeg = normalized * BALL_MAX_BOUNCE_ANGLE_DEG;
```

**Файл:** `Ball.cpp:64-70`

### AI

Бот реагує на вертикальну позицію м'яча з dead-zone (40 пікселів), щоб не бути ідеальним.

Чому dead-zone?

- Без нього: бот ідеальний, неможливо виграти
- З ним: бот реалістичний, гра цікава

**Файл:** `Game.cpp:206-221`, `Constants.h:15`

### Constants.h

Всі магічні числа винесені в окремий файл:

Переваги:

- Легко змінити параметри (швидкість, розміри)
- Код самодокументований (`PADDLE_WIDTH` > `20.f`)
- `constexpr` — обчислюється на етапі компіляції (швидше!)

**Файл:** `Constants.h`

Чому `getBounds()` а не `getShape()`?

```
// ❌ ПОГАНО (порушення інкапсуляції):
sf::RectangleShape& getShape();
// Проблема: зовнішній код може змінити shape!

// ✅ ДОБРЕ (інкапсуляція):
sf::FloatRect getBounds() const;
// Повертає копію bounds, оригінал захищений
```

**Файли:** `Paddle.h:29`, `Paddle.cpp:44-46`

Чому enum class а не int?

```
// ❌ int (старий стиль):
void launchBall(int direction);  // Що таке 1? Що таке -1?
launchBall(1);  // Незрозуміло!

// ✅ enum class (сучасний C++):
void launchBall(LaunchDirection direction);
launchBall(LaunchDirection::ToBot);  // Зрозуміло!
```

Переваги:

- Type-safe (неможливо передати random int)
- Self-documenting код
- Scoped (не конфліктує з іншими enum)

**Файл:** `Game.h:10-13`

---

## 🎯 Можливі покращення (за межами ТЗ)

- [ ] Меню (Start/Restart/Settings)
- [ ] Локальний мультиплеєр (2 гравці)
- [ ] Звукові ефекти (відскок, гол)
- [ ] Анімації (trail за м'ячем)
- [ ] Налаштування складності AI
- [ ] Паттерни Observer (для подій голу) / Factory (для створення об'єктів)
- [ ] Збереження рекордів (high scores)
- [ ] Кастомізація (кольори, швидкість)

---

## 📧 Контакт

**Автор:** Даніела  

**Email:** daniellatskho@gmail.com

**LinkedIn:** https://www.linkedin.com/in/daniellatskhovriebova/

**GitHub:** https://github.com/kazureiaoki/PongGame  

**Дата:** 18.01.2026
