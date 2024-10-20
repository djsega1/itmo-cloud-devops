## Инструкция по запуску

```
git clone --depth 1 https://github.com/djsega1/itmo-cloud-devops.git && \
git clone --depth 1 https://github.com/userver-framework/userver.git itmo-cloud-devops/lab1/third_party/userver && \
cd itmo-cloud-devops/lab1/

docker compose up
# для отключения - Ctrl-C + docker compose down
```

## Добавление доменов в /etc/hosts

```
nano /etc/hosts
127.0.0.1 domain1.com
127.0.0.1 domain2.com
```
