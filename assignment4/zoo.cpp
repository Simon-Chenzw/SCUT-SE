/**
 *  @brief:code of assignment4
 *  @file:zoo.cpp
 *  @author:Simon_Chen
 */

#include "zoo.h"

Zoo::Zoo():
      days(0),
      close_reason(""),
      visit_adult(0),
      visit_child(0),
      close(false),
      list_animal(vector<Animal*> {&elephant, &giraffe, &monkey}),
      elephant(Elephant()),
      giraffe(Giraffe()),
      monkey(Monkey()),
      zookeeper(ZooKeeper()),
      foodseller(FoodSeller()) {}

bool Zoo::is_close() {
    return close;
}

void Zoo::run_one_day() {
    // start check
    days++;
    // visitor
    int number_adult = rand() % (40 - 20 + 1) + 20;
    for (int i = 0; i < number_adult; i++) {
        Adult adult;
        visit_adult++;
        visit_child += adult.number_of_children();
        adult.spend_money(Money(0, 100 + 40 * adult.number_of_children()));
        adult.buy_food(&foodseller);
        for (auto& animal : list_animal)
            if (animal->is_open()) adult.lead_to_feed(animal);
    }
    for (auto& animal : list_animal) animal->check_ate();
    // end check
    for (auto& animal : list_animal) animal->open_enclosure();
    if (foodseller.check_empty()) close_reason = foodseller.close_reason();
    if (zookeeper.clean_enough())
        close_reason = zookeeper.close_reason();
    else {
        for (auto& animal : list_animal) {
            if (animal->dirty_enough()) {
                zookeeper.clean(animal);
                break;
            }
        }
    }
    if (close_reason != "") close = true;
}

void Zoo::run_whole_loop() {
    while (!close) {
        run_one_day();
    }
}

void Zoo::print_close_info() const {
    cout << "The number of days the zoo was opened for: " << days << endl;
    cout << "The reason why the zoo closed: " << close_reason << endl;
    cout << "The total number of adult visitors: " << visit_adult << endl;
    cout << "The total number of children: " << visit_child << endl;
    cout << "The total amount of money made by the seller: " << foodseller.get_income() << endl;
    cout << "The number of days the zoo keeper spent cleaning: " << zookeeper.get_clean_days() << endl;
    cout << "The number of days elephant enclosure was closed for: " << elephant.get_close_day() << endl;
    cout << "The number of days giraffe enclosure was closed for: " << giraffe.get_close_day() << endl;
    cout << "The number of days monkey enclosure was closed for: " << monkey.get_close_day() << endl;
}

Money::Money(int _dollars, int _cents) {
    cents = _dollars * 100 + _cents;
    if (cents < 0) throw invalid_argument("Money is negative\n");
    dollars = cents / 100;
    cents %= 100;
}

int Money::get_in_cents() const {
    return dollars * 100 + cents;
}

Money Money::operator+(const Money& tmp) const {
    return Money(0, dollars * 100 + cents + tmp.dollars * 100 + tmp.cents);
}

Money Money::operator-(const Money& tmp) const {
    return Money(0, dollars * 100 + cents - tmp.dollars * 100 - tmp.cents);
}

ostream& operator<<(ostream& cout, const Money& money) {
    if (money.dollars > 0) cout << money.dollars << " dollar";
    if (money.dollars > 1) cout << 's';
    cout << ' ';
    if (money.cents > 0) cout << money.cents << " cent";
    if (money.cents > 1) cout << 's';
    if (money.dollars == 0 && money.cents == 0) cout << "0 cent";
    return cout;
}

AnimalFood::AnimalFood(Food _food_type, int _num) {
    food_type = _food_type;
    num = _num;
}

Food AnimalFood::get_type() const {
    return food_type;
}

int AnimalFood::get_num() const {
    return num;
}

void AnimalFood::add(int val) {
    num += val;
}

void AnimalFood::sub(int val) {
    num -= val;
    if (num < 0) throw invalid_argument("the number of AnimalFood cant be negative");
}

bool AnimalEnclosure::is_open() const {
    return !close;
}

int AnimalEnclosure::get_dirty() const {
    return dirty;
}

int AnimalEnclosure::get_close_day() const {
    return close_day;
}

void AnimalEnclosure::add_dirty(int val) {
    dirty += val;
}

void AnimalEnclosure::open() {
    close = false;
}

void AnimalEnclosure::clean() {
    dirty = 0;
    close = true;
    close_day++;
}

void Animal::feed(int val) {
    ate += val;
}

int Animal::get_ate() const {
    return ate;
}

void Animal::set_ate(int val) {
    ate = val;
}

bool Animal::is_open() const {
    return enclosure.is_open();
}

bool Animal::dirty_enough() const {
    return enclosure.get_dirty() >= 2000;
}

int Animal::get_close_day() const {
    return enclosure.get_close_day();
}

void Animal::add_dirty(int val) {
    enclosure.add_dirty(val);
}

void Animal::open_enclosure() {
    enclosure.open();
}

void Animal::clean_enclosure() {
    enclosure.clean();
}

bool Elephant::can_eat(Food food) {
    return food == peanuts;
}

void Elephant::check_ate() {
    add_dirty(get_ate() - 750);
    set_ate(0);
}

bool Giraffe::can_eat(Food food) {
    return food == carrots;
}

void Giraffe::check_ate() {
    add_dirty(get_ate() - 500);
    set_ate(0);
}

bool Monkey::can_eat(Food food) {
    return food == bananas;
}

void Monkey::check_ate() {
    add_dirty(get_ate() - 300);
    set_ate(0);
}

void ZooKeeper::clean(Animal* animal) {
    clean_days++;
    animal->clean_enclosure();
}

int ZooKeeper::get_clean_days() const {
    return clean_days;
}

bool ZooKeeper::clean_enough() const {
    return clean_days == 10;
}

string ZooKeeper::close_reason() const {
    return "The zoo closed because the zoo keeper had enough of cleaning and quit!";
}

FoodSeller::FoodSeller():
      income(Money(0, 0)),
      elephant_food(AnimalFood(peanuts, 10000)),
      giraffe_food(AnimalFood(carrots, 7000)),
      monkey_food(AnimalFood(bananas, 4000)) {}

Money FoodSeller::get_income() const {
    return income;
}

bool FoodSeller::check_empty() const {
    return elephant_food.get_num() == 0 || giraffe_food.get_num() == 0 || monkey_food.get_num() == 0;
}

string FoodSeller::close_reason() const {
    if (elephant_food.get_num() == 0) return "The zoo closed because the seller ran out of peanuts.";
    if (giraffe_food.get_num() == 0) return "The zoo closed because the seller ran out of carrots.";
    if (monkey_food.get_num() == 0) return "The zoo closed because the seller ran out of bananas.";
    throw logic_error("none is empty while get reason");
}

AnimalFood FoodSeller::buy_elephant_food(Money& money, Money max_spend) {
    int cnt = min(elephant_food.get_num(), max_spend.get_in_cents() / price[0]);
    money = money - Money(0, price[0] * cnt);
    income = income + Money(0, price[0] * cnt);
    elephant_food.sub(cnt);
    return AnimalFood(peanuts, cnt);
}

AnimalFood FoodSeller::buy_giraffe_food(Money& money, Money max_spend) {
    int cnt = min(giraffe_food.get_num(), max_spend.get_in_cents() / price[1]);
    money = money - Money(0, price[1] * cnt);
    income = income + Money(0, price[1] * cnt);
    giraffe_food.sub(cnt);
    return AnimalFood(carrots, cnt);
}

AnimalFood FoodSeller::buy_monkey_food(Money& money, Money max_spend) {
    int cnt = min(monkey_food.get_num(), max_spend.get_in_cents() / price[2]);
    money = money - Money(0, price[2] * cnt);
    income = income + Money(0, price[2] * cnt);
    monkey_food.sub(cnt);
    return AnimalFood(bananas, cnt);
}

void Child::recieve_food(AnimalFood animalfood) {
    animal_foods.push_back(animalfood);
}

void Child::feed_animal(Animal* animal) {
    for (auto& animalfood : animal_foods) {
        if (animal->can_eat(animalfood.get_type())) {
            animal->feed(animalfood.get_num());
            animalfood.sub(animalfood.get_num());
        }
    }
}

Adult::Adult(): money(Money(0, 0)) {
    money = Money(rand() % (20 - 10 + 1) + 10, 0);
    int child_num = rand() % (3 - 1 + 1) + 1;
    for (int i = 0; i < child_num; i++) children.push_back(Child());
}

int Adult::number_of_children() const {
    return children.size();
}

void Adult::spend_money(Money spend) {
    money = money - spend;
}

void Adult::buy_food(FoodSeller* foodseller) {
    int tmp = money.get_in_cents();
    give_food(foodseller->buy_elephant_food(money, Money(0, tmp / 3)));
    give_food(foodseller->buy_giraffe_food(money, Money(0, (tmp + 1) / 3)));
    give_food(foodseller->buy_monkey_food(money, Money(0, (tmp + 2) / 3)));
}

void Adult::give_food(AnimalFood animalfood) {
    for (int i = children.size() - 1; i >= 0; i--)
        children[i].recieve_food(AnimalFood(animalfood.get_type(), animalfood.get_num() / (i + 1)));
}

void Adult::lead_to_feed(Animal* animal) {
    for (auto& child : children) child.feed_animal(animal);
}