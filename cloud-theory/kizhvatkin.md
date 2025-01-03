## Рубежная работа №1 (Вариант 7)

> Опишите бессерверные вычисления. Как это так, вычисления без сервера?

Бессерверные вычисления (они же FaaS - Function as a Service) - стратегия предоставления облачных услуг,
при которой разработчики могут запускать код без необходимости управлять серверами. На самом деле вся работа, конечно, выполняется на сервере, но
разработчику не нужно думать о сервере, его настройке, масштабировании и поддержке. Все это автоматически управляется облачным провайдером.
Разработчику нужно лишь написать функции (или небольшие блоки кода), которые выполняются по требованию, в ответ на события или запросы.
При этом бессерверный код может быть частью приложений, построенных на традиционной архитектуре.
Например, при обращении к API, изменения в базе данных или поступление данных через очередь сообщений.

**Особенности бессерверных вычислений:**
+ Отсутствие необходимости в управлении серверами
+ Модульность (исполняются небольшие блоки кода)
+ Автоматическое выделение вычислительных ресурсов
+ Оплата по фактическому использованию вычислительных ресурсов
+ Простота разработки и быстрая доставка

**Примеры бессерверных платформ:**
+ [AWS Lambda](https://aws.amazon.com/lambda)
+ [Azure Functions](https://azure.microsoft.com/en-us/products/functions)
+ [Google Cloud Functions](https://cloud.google.com/functions)

**Когда использовать бессерверные вычисления?**
+ Для приложений с непредсказуемыми или переменными нагрузками.
+ Когда важна высокая скорость разработки.
+ Для задач, которые выполняются редко или для микросервисной архитектуры.

**Заключение**  
Бессерверная модель отлично подходит для таких сценариев, как обработка событий, REST API, автоматизация задач, обработка данных и многого другого, где не требуется постоянное поддержание серверных мощностей.

## Рубежная работа №2 (Вариант 7)

> Поговорим про безопасность. Какие существуют направления повышения безопасности в облаке?

В облачной безопасности существует несколько ключевых направлений для повышения уровня защиты данных и систем.

**Основные направления повышения безопасности в облаке:**
1. Шифрование данных
2. Управление доступом и аутентификация:
   + [Multi-factor authentication](https://habr.com/ru/companies/epam_systems/articles/178507/)
   + [Identity and Access Management](https://habr.com/ru/companies/otus/articles/775994/)
   + [Zero Trust Policy](https://habr.com/ru/companies/varonis/articles/472934/)
   + [Role-based Access Control](https://ru.wikipedia.org/wiki/Управление_доступом_на_основе_ролей)
3. Защита от DDoS-атак (вроде [Cloudflare](https://www.cloudflare.com/ddos/))
4. Мониторинг и логирование
5. Защита контейнеров и виртуализации
6. Резервное копирование данных
7. Сегментация сети (разделение сети на логические зоны с разными уровнями доступа, настройка и управление firewall-ами).

> Какие компоненты безопасности настраивать **обязательно**?

Кажется, никакой из компонентов нельзя выделить как обязательный, ведь каждый из них дает ощутимую прибавку к безопасности.
Однако, по моему мнению, начать стоит с пунктов 2, 6 и 7. Грамотное распредение доступов к инфраструктуре снизит угрозу компрометации,
а резервное копирование даст шанс на исправление нештатной ситуации. Да и большая часть остальной безопасности ложится на плечи провайдера.

**Заключение**  
Облачная безопасность, определенно, должна всегда быть в голове и под присмотром. Основная задача состоит в защите данных и инфраструктуры.
Это требует как знаний технологий, так и хороших навыков ориентирования в облачных сервисах и принципах информационной безопасности.
