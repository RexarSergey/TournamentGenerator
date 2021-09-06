# TournamentGenerator

Исходники плагина для генерации турниров вида PlayOff и RoundRobin на Unreal Engine 4 (UE4).
Разработан Неугодниковым С.И. и Поповым А.Э.

Проект находится в альфа тестировании. Поэтому если вы найдете какой-либо баг или недочет, то напишите нам (Telegram: @Azzazzin892 - Неугодников С.И.; @Kaino0 - Попов А.Э.).
Мы будем рады вашему сообщению и попытаемся устранить неполадки.

### Установка
(Дорабатывается)
В данном проекте пока что только исходники. Запуск возможен только при ручной сборке плагина.
Билд появится чуть позднее.

### Документация

Плагин доступен для исползования в Blueprints. Доступные виды турнира представлены компонентами:
UPlayOffTournamentComponent и URRTournamentComponent

#### PlayOffTournamentComponent
  GenerateTournament - Генерирует турнир. Необходимо сообщить список id участников турнира и список их рейтингов. А также необходимо выбрать тип генерации турнира.

  Вообще говоря, для турнира на выбывание требуется число игроков, равное степени двойки. Поэтому если число игроков не равно степени двойки - первый этап турнира уменьшит число     игроков до степени двойки.
  О типах генерации:
    Random - случайная генерация турнирной сетки.
    WorstAgainstBest - Слабый игрок будет играть против сильного.Например для игроков с рейтнгами: 1,2,3,4,5,6,7,8 будут составлены следующие матчи: 1 vs 8, 3 vs 6, 4 vs 5, 2 vs 7
    Directly - Посланный список игроков будет использован напрямую без каких-либо изменений. Для игроков с id: 1, 2, 3, 4. Будут составлены следующие матчи: 1 vs 2, 3 vs 4.
    
