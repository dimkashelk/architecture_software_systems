# Маппинг #

## Описание ##
Система обработки заявок в автоматизированной системе хранения и выдачи товаров на складе с роботизированными устройствами для перемещения грузов
1. Источник — (заказчик) заказчик, создающий запрос на перемещение товара на складе.
2. Заявка — запрос на перемещение товара из одной зоны склада в другую.
3. Диспетчер постановки — (диспетчер заказов) система управления очередью, которая заполняет очередь. В случае переполнения очереди удаляет самую старую заявку, выдавая ей статус «Отменено».
4. Буфер — (стек заказов) виртуальная очередь заявок на перемещение товаров (LIFO — последняя заявка обрабатывается первой).
5. Диспетчер выборки — (диспетчер склада) система, выбирающая заявки для роботов (по кольцу), чтобы распределять нагрузку равномерно между ними.
6. Прибор — (робот) роботизированный манипулятор, перемещающий товар (время обработки заявки распределено по экспоненциальному закону).

## Особенности реализации ## 
1.	Распределение заявок: распределяет заявки по роботам по кольцевому принципу, отслеживает их состояние.
2.	Буфер: хранит заявки, использует LIFO. При переполнении удаляет старые заявки.
3.	Планирование роботов: распределяет заявки между освобождающимися роботами, следит за балансом нагрузки.
4.	Управление роботами: заказы на исполнение назначаются роботам из диспетчера, роботы немедленно приступают к выполнению.
5.	Реализация в рамках курсовой работы будет монолитной

## Вариант 16 ## 
ИБ ИЗ2 ПЗ1 Д10З1 Д10О3 Д2П2 Д2Б2 ОР1 ОД1
1.	ИБ — бесконечный источник заявок.
2.	ИЗ2 — равномерный закон генерации заявок.
3.	ПЗ1 — экспоненциальный закон обслуживания заявок.
4.	Д10З1 — заполнение буфера по кольцу.
5.	Д10О3 — самая старая заявка в буфере получает отказ в случае переполнения.
6.	Д2П2 — выбор прибора для обслуживания по кольцу.
7.	Д2Б2 — выбор заявки на обслуживание по принципу LIFO (последний пришел — первый обслужен).
8.	ОР1 — сводная таблица результатов работы программы.
9.	ОД1 — отображение работы модели в виде календаря событий, буфера и текущего состояния.

## Диаграмма классов ## 
1. Класс **Order** <br>
   **Описание:** Класс, описывающий заказ на перемещение. <br>
   **Приватные поля класса**: <br>
    * **_id: uint** — идентификатор заказа
    * **_from: uint** — идентификатор места, откуда требуется взять груз
    * **_to: uint** — идентификатор места, куда требуется положить груз
    * **_status: ExecutionStatus** — статус доставки, определяемый перечислением ExecutionStatus <br>

   **Публичные методы:** <br>
    * **Order(from: uint, to: uint)** — конструктор заказа, принимающий направление перемещения груза
    * **set_status(new_status: ExecutionStatus): void** — устанавливает новый статус **new_status** для заказа
    * **get_status(): ExecutionStatus** — возвращает текущий статус для заказа
    * **get_id(): uint** — возвращает идентификатор заказа
2. Класс **Client** <br>
   **Описание:** Класс, описывающий клиента, создающего заказы <br>
   **Приватные поля класса**: <br>
    * **_orders: [Order]** — массив текущих заказов клиента

   **Публичные методы:** <br>
    * **Client()** — конструктор класс, создающий клиента с пустым списком заказов
    * **generate_order(): void*** — создает новый заказ, добавляет его в массив заказов
3. Класс

## BPMN ##
![bpmn](mapping/bpmn.png)

## Блок схема ##
![block_diagram](mapping/block_diagram.png)

## Сиквенсы ##
![sequence](mapping/sequence.png)
