#include <bits/stdc++.h>
using namespace std;

enum Food { peanuts, carrots, bananas };

class Money {
  public:
    Money(int, int);
    int get_in_cents() const;
    Money operator+(const Money& tmp) const;
    Money operator-(const Money& tmp) const;
    friend ostream& operator<<(ostream& cout, const Money& money);

  private:
    int dollars, cents;
};

class AnimalFood {
  public:
    AnimalFood(Food, int = 0);
    Food get_type() const;
    int get_num() const;
    void add(int);
    void sub(int);

  private:
    Food food_type;
    int num;
};

class AnimalEnclosure {
  public:
    bool is_open() const;
    int get_dirty() const;
    int get_close_day() const;
    void add_dirty(int);
    void open();
    void clean();

  private:
    bool close;
    int dirty;
    int close_day;
};

class Animal {
  public:
    void feed(int);
    int get_ate() const;
    void set_ate(int);
    // about enclosure
    bool is_open() const;
    bool dirty_enough() const;
    int get_close_day() const;
    void add_dirty(int);
    void open_enclosure();
    void clean_enclosure();

    virtual bool can_eat(Food) = 0;
    virtual void check_ate() = 0;

  private:
    int weight;
    int ate;
    AnimalEnclosure enclosure;
};

class Elephant: public Animal {
  public:
    bool can_eat(Food) override;
    void check_ate() override;

  private:
    int trunk_length;
};

class Giraffe: public Animal {
  public:
    bool can_eat(Food) override;
    void check_ate() override;

  private:
    int neck_length;
};

class Monkey: public Animal {
  public:
    bool can_eat(Food) override;
    void check_ate() override;

  private:
    int arm_length;
};

class Person {
  private:
    string name;
    int age;
};

class ZooKeeper: public Person {
  public:
    void clean(Animal*);
    int get_clean_days() const;
    bool clean_enough() const;
    string close_reason() const;

  private:
    int clean_days;
};

class FoodSeller: public Person {
  public:
    FoodSeller();
    Money get_income() const;
    bool check_empty() const;
    string close_reason() const;
    AnimalFood buy_elephant_food(Money&, Money);
    AnimalFood buy_giraffe_food(Money&, Money);
    AnimalFood buy_monkey_food(Money&, Money);

  private:
    Money income;
    const int price[3] = {20, 30, 50};
    AnimalFood elephant_food;
    AnimalFood giraffe_food;
    AnimalFood monkey_food;
};

class Visitor: public Person {
  private:
    int id;
};

class Child: public Visitor {
  public:
    void recieve_food(AnimalFood);
    void feed_animal(Animal*);

  private:
    vector<AnimalFood> animal_foods;
};

class Adult: public Visitor {
  public:
    Adult();
    int number_of_children() const;
    void spend_money(Money);
    void buy_food(FoodSeller*);
    void give_food(AnimalFood);
    void lead_to_feed(Animal*);

  private:
    Money money;
    vector<Child> children;
};

class Zoo {
  public:
    Zoo();
    bool is_close();
    void run_one_day();
    void run_whole_loop();
    void print_close_info() const;

  private:
    int days;
    string close_reason;
    int visit_adult, visit_child;
    bool close;
    // animal
    vector<Animal*> list_animal;
    Elephant elephant;
    Giraffe giraffe;
    Monkey monkey;
    // person
    ZooKeeper zookeeper;
    FoodSeller foodseller;
};
