## Инструкция по запуску
Описание запуска nginx и сервера.

```
git clone --depth 1 https://github.com/djsega1/itmo-cloud-devops.git && \
git clone --depth 1 https://github.com/userver-framework/userver.git itmo-cloud-devops/lab1/third_party/userver && \
cd itmo-cloud-devops/devops-1/

docker compose up -d
# для отключения - Ctrl-C + docker compose down
```

![image](https://github.com/user-attachments/assets/dc904500-38fd-4c3c-ae70-9b220746c63c)

## Добавление доменов в /etc/hosts

Это нужно для резолва доменных имен.

```
nano /etc/hosts
127.0.0.1 domain1.com
127.0.0.1 domain2.com
```

Генерируем самоподписанные серты через `openssl`

```
openssl req -days 365 -new -x509 -key domain1.com.key -out domain1.com.crt
openssl req -days 365 -new -x509 -key domain2.com.key -out domain2.com.crt
```

Пишем суперкрутой `default.conf` для `nginx`:

```
server { 
    listen 443 ssl;
    server_name domain1.com;

    ssl_certificate /etc/nginx/ssl/domain1.com/domain1.com.crt;
    ssl_certificate_key /etc/nginx/ssl/domain1.com/domain1.com.key;

    location / {
        proxy_pass http://backend:8080;
    }
}

server { 
    listen 443 ssl;
    server_name domain2.com;

    ssl_certificate /etc/nginx/ssl/domain2.com/domain2.com.crt;
    ssl_certificate_key /etc/nginx/ssl/domain2.com/domain2.com.key;

    location /cat {
        alias /var/www/static/cat.jpg;
    }
}

server {
    listen 80;
    server_name domain1.com domain2.com;
    return 301 https://$host$request_uri;
}
```

*Все работает с кайфом!*

## Что сделано

- Созданы самоподписанные сертификаты для двух доменов через `openssl`.
- Один ведет к одному из эндпоитнов userver'a (сам он изолирован от внешней сети), другой к статик файлу с котиком через `alias`.
- Принудительный редирект HTTP к HTTPS.
