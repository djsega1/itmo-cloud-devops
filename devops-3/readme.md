## "Плохой" CI/CD файл

```
name: Flask App Test (Bad Practices)

on:
  push:
    branches:
      - main

jobs:

  test:
    runs-on: ubuntu-latest
    defaults:
      run:
        working-directory: ./devops-3/app

    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Install dependencies
        run: |
          pip install flask
          pip install pytest
          pip install requests

      - name: Run app
        env:
          FLASK_ENV: production
          SECRET_KEY: "42"
        run: python app.py &

      - name: Run tests
        env:
          FLASK_ENV: production
          SECRET_KEY: "42"
        run: pytest test_app.py

  deploy:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Push to server
        run: echo "PUSHING TO SERVER"

      - name: Run app
        run: echo "RUNNING ON PROD"
```

**Успешное выполнение:**

![image](https://github.com/user-attachments/assets/aa6a72ad-5047-4f86-bd05-7763bb695518)

## "Хороший" CI/CD файл

```
name: Flask App Test Workflow (Good Practices)

on:
  push:
    branches:
      - main
  pull_request:
    branches:
      - main

jobs:
  test:
    runs-on: ubuntu-22.04
    defaults:
      run:
        working-directory: ./devops-3/app

    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Set up Python
        uses: actions/setup-python@v4
        with:
          python-version: '3.12'

      - name: Install dependencies
        run: |
          python3.12 -m venv venv
          source venv/bin/activate
          pip install -r requirements.txt

      - name: Run app
        env:
          FLASK_ENV: production
          SECRET_KEY: ${{ secrets.SECRET_KEY }}
        run: |
          source venv/bin/activate
          python app.py &

      - name: Run tests
        env:
          FLASK_ENV: production
          SECRET_KEY: ${{ secrets.SECRET_KEY }}
        run: |
          source venv/bin/activate
          pytest test_app.py

  deploy:
    runs-on: ubuntu-22.04
    needs: test
    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Push to server
        run: echo "PUSHING TO SERVER"

      - name: Run app
        run: echo "RUNNING ON PROD"
```

**Успешное выполнение:**

![image](https://github.com/user-attachments/assets/1ad8d014-ea09-42ef-898f-386ba4de58c3)

## Описание плохих практик

### 1. Указание `:latest` версии

Сегодня на `latest` версии все прогонится хорошо. Что будет завтра на следующей `latest`- загадка.

### 2. Установка зависимостей напрямую

Каждая зависимость устанавливается вручную.

### 3. Использование секретов

Переменные окружения пробрасываются в контейнер явно, их можно подглядеть из пайплайна.

### 4. Параллельный запуск джоб

`deploy` джоба может по приколу исполниться раньше `test`, который может и не пройти, а потом свалится прод.

### 5. Пайплайн выполняется только на пуше в `main` ветку.

Параллельная разработка в разных ветках - частая задача разработчиков. Как гонять тесты при попытке слияния?

## Исправление плохих практик

- Вместо версий `latest` указываем точные версии `python-3.12` и `ubuntu-22.04`
- Зависимости фиксируются пакетным менеджером и устанавливаются одной командой
- Секреты зашиты в **GitHub Secrets** внутри репозитория
- С помощью тега `needs` определен параметр выполнения джоб
- Добавлен триггер на срабатывание пайплайн при пулл-реквестах 

## Результаты

На выходе имеем базовый безопасный и стабильный CI/CD файл для простенького проекта без заморочек.
