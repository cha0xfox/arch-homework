# Компонентная архитектура
<!-- Состав и взаимосвязи компонентов системы между собой и внешними системами с указанием протоколов, ключевые технологии, используемые для реализации компонентов.
Диаграмма контейнеров C4 и текстовое описание. 
-->
## Компонентная диаграмма
```plantuml
@startuml
!include https://raw.githubusercontent.com/plantuml-stdlib/C4-PlantUML/master/C4_Container.puml

AddElementTag("microService", $shape=EightSidedShape(), $bgColor="CornflowerBlue", $fontColor="white", $legendText="microservice")
AddElementTag("storage", $shape=RoundedBoxShape(), $bgColor="lightSkyBlue", $fontColor="white")

Person(admin, "Администратор")
Person(techsup, "ТехПоддержка")
Person(user, "Пользователь")

System_Ext(web_site, "Клиентский веб-сайт", "HTML, CSS, JavaScript, React", "Веб-интерфейс")

System_Boundary(order_site, "Сайт услуг") {
   'Container(web_site, "Клиентский веб-сайт", ")
   Container(auth_service, "Сервис авторизации", "C++", "Сервис управления пользователями", $tags = "microService")    
   Container(catalog_service, "Сервис каталога услуг", "C++", "Сервис управления услугами", $tags = "microService") 
   Container(ordering_service, "Сервис заказов", "C++", "Сервис управления заказами", $tags = "microService")   
   ContainerDb(db, "База данных", "MySQL", "Хранение данных о услугах, заказах, пользователях", $tags = "storage")
   
}

Rel(admin, web_site, "Просмотр, добавление и редактирование информации о пользователях, услугах, партнерах","HTTPS")
Rel(techsup, web_site, "Решение инцедентов с пользователями, просмотр заказов, редактирование пользователей","HTTPS")
Rel(user, web_site, "Регистрация, просмотр услуг, заказ услуг, оплата","HTTPS")

Rel(web_site, auth_service, "Работа с пользователями", "HTTPS/REST")
Rel(auth_service, db, "INSERT/SELECT/UPDATE", "JDBC, TCP:3306")

Rel(web_site, catalog_service, "Работа с услугами", "HTTPS/REST")
Rel(catalog_service, db, "INSERT/SELECT/UPDATE", "JDBC, TCP:3306")

Rel(web_site, ordering_service, "Работа с заказами", "HTTPS/REST")
Rel(ordering_service, db, "INSERT/SELECT/UPDATE", "JDBC, TCP:3306")

@enduml
```
## Список компонентов  

### Сервис авторизации
**API**:
- Регистрация пользователя
  - входные параметры: login, password, name, surname, email; (optional): msisdn.
  - выходные параметры: none
- Поиск пользователя по логину
  - входные параметры: login
  - выходные параметры: name, surname, email, msisdn
- Поиск пользователя по имени и фамилии
  - входные параметры: name mask, surname mask
  - выходные параметры: login, name, surname, email, msisdn

### Сервис каталога услуг
**API**:
- Создание услуги
  - Входные параметры: serviceName, serviceId, serviceDescription, paySystem, payAmount
  - Выходные параметры: none
- Получение списка услуг
  - Входные параметры: (optional): serviceName, serviceId
  - Выходные параметры: serviceName, serviceId, serviceDescription, paySystem, payAmount

### Сервис заказов
**API**:
- Добавление услуг в заказ
  - Входные параметры: login, serviceId
  - Выходные параметры: login, orderId, serviceName, serviceId, paySystem, payAmount
- Получение заказа для пользователя
  - Входные параметры: login, (optional): orderId
  - Выходные параметры: serviceName, payAmount

## Возможные будущие сервисы

```plantuml
@startuml
!include https://raw.githubusercontent.com/plantuml-stdlib/C4-PlantUML/master/C4_Container.puml

AddElementTag("microService", $shape=EightSidedShape(), $bgColor="CornflowerBlue", $fontColor="white", $legendText="microservice")
AddElementTag("storage", $shape=RoundedBoxShape(), $bgColor="lightSkyBlue", $fontColor="white")

Person(admin, "Администратор")
Person(techsup, "ТехПоддержка")
Person(user, "Пользователь")

System_Ext(web_site, "Клиентский веб-сайт", "HTML, CSS, JavaScript, React", "Веб-интерфейс")

System_Ext(partner_api, "Партнерский API")

Container(partner_service, "Сервис интеграций", "C++", "Сервис партнерских интеграций", $tags = "microService")   

System_Boundary(order_site, "Сайт услуг") {
   'Container(web_site, "Клиентский веб-сайт", ")
   Container(auth_service, "Сервис авторизации", "C++", "Сервис управления пользователями", $tags = "microService")    
   Container(catalog_service, "Сервис каталога услуг", "C++", "Сервис управления услугами", $tags = "microService") 
   Container(ordering_service, "Сервис заказов", "C++", "Сервис управления заказами", $tags = "microService")
   Container(payment_service, "Сервис оплаты", "C++", "Сервис управления способами оплаты", $tags = "microService")
   ContainerDb(db, "База данных", "MySQL", "Хранение данных о услугах, заказах, пользователях", $tags = "storage")
   
}

Rel(admin, web_site, "Просмотр, добавление и редактирование информации о пользователях, услугах, партнерах")
Rel(techsup, web_site, "Решение инцедентов с пользователями, просмотр заказов, редактирование пользователей")
Rel(user, web_site, "Регистрация, просмотр услуг, заказ услуг, оплата")

Rel(web_site, auth_service, "Работа с пользователями", "HTTPS/REST")
Rel(auth_service, db, "INSERT/SELECT/UPDATE", "JDBC, TCP:3306")

Rel(web_site, catalog_service, "Работа с услугами", "HTTPS/REST")
Rel(catalog_service, db, "INSERT/SELECT/UPDATE", "JDBC, TCP:3306")

Rel(web_site, ordering_service, "Работа с заказами", "HTTPS/REST")
Rel(ordering_service, db, "INSERT/SELECT/UPDATE", "JDBC, TCP:3306")
Rel(ordering_service, partner_service, "/api", "HTTPS/REST")

Rel(web_site, payment_service, "Работа с способами оплаты", "HTTPS/REST")
Rel(payment_service, db, "INSERT/SELECT/UPDATE", "JDBC, TCP:3306")

Rel(partner_api, partner_service, "Работа с услугами", "HTTPS/REST")
Rel(partner_service, partner_api, "Работа с заказами", "HTTPS/REST")
Rel(partner_service, catalog_service, "/api", "HTTPS/REST")

@enduml
```

### Сервис оплаты
**API**:
(future)
Сервис оплаты для работы с оплатами с лицевого счета, банковских карт, кэшбек.

### Сервис партнерской интеграции
**API**:
(future)
Сервис для интеграции с партнерами, которые хотят предоставлять свои услуги через наш LP.
