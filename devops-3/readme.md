CI заключается в тесте, что сервер отдает переменную окружения `SECRET_KEY=42`.

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

## Звездочка

### Установка HashiCorp Vault

Его забанили в России, так что пришлось делать так:

```
sudo snap install vault
```

```
vault server -dev -dev-root-token-id root
```

![image](https://github.com/user-attachments/assets/37c18835-db70-4a06-a0a1-f39303432829)

Добавляем переменные окружения для обращения к Vault и сам секрет

```
export VAULT_ADDR=http://127.0.0.1:8200
export VAULT_TOKEN=root
vault kv put secret/ci app_secret=SecretProvidedByVault
```

![image](https://github.com/user-attachments/assets/30447f50-0ecb-4a13-84e8-91e2b3dd7f23)

Выдаем право на получение секрета
```
vault policy write ci-secret-reader - <<EOF
path "secret/data/ci" {
    capabilities = ["read"]
}
EOF
```

![image](https://github.com/user-attachments/assets/f0156b71-0b89-466b-9425-fc211b613a8b)

Создаем токен для репозитория и пробуем получить с его помощью секрет

```
GITHUB_REPO_TOKEN=$(vault token create -policy=ci-secret-reader -format json | jq -r ".auth.client_token")
VAULT_TOKEN=$GITHUB_REPO_TOKEN vault kv get secret/ci
```
![image](https://github.com/user-attachments/assets/d66200bb-982c-4423-92a5-825ba989173e)

Добавляем токен в репозиторий
![image](https://github.com/user-attachments/assets/047a16c8-f19f-46dd-a0dc-3fbd36f99de6)

Поднимаем ngrok на порт 8200 с адресом https://close-peacock-monthly.ngrok-free.app
```
ngrok http --url=close-peacock-monthly.ngrok-free.app 8200
```
![image](https://github.com/user-attachments/assets/9c34275d-68ae-4a88-a81a-35daf40a2225)

Теперь по этому адресу доступен наш Vault
![image](https://github.com/user-attachments/assets/34d872e3-0df5-4356-b8b7-8a4730c52447)

В "хороший" пайплайн добавляем коннект к Vault
```
  - name: Import secrets
    uses: hashicorp/vault-action@v2
    with:
      url: http://close-peacock-monthly.ngrok-free.app:80
      token: ${{ secrets.VAULT_TOKEN }}
      tlsSkipVerify: true
      secrets: |
        secret/data/ci SECRET_KEY
```

Запускаем:

![image](https://github.com/user-attachments/assets/58f85460-c80d-4503-95c2-50f201b34bc3)

Вспоминаем тест и понимаем, что секреты подтягиваются и не светятся в логах.
