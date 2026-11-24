#include <iostream>
#include <string>

using namespace std;

class Animal
{
private:
    string name;
    int age;

public:
    void setName(string animalName)
    {
        name = animalName;
    }

    string getName()
    {
        return name;
    }

    void setAge(int animalAge)
    {
        age = animalAge;
    }

    int getAge()
    {
        return age;
    }

    void displayInfo()
    {
        cout << "Name: " << getName() << '\n';
        cout << "Age: " << getAge() << '\n';
    }
};

class Mammal : public Animal
{
public:
    void feedBaby()
    {
        cout << "Feeding baby mammal.\n";
    }
};

class Bird : public Animal
{
public:
    void layEgg()
    {
        cout << "Laying an egg.\n";
    }
};

class Reptile : public Animal
{
public:
    void shedSkin()
    {
        cout << "Shedding skin.\n";
    }
};

int main()
{
    Mammal mammal;
    mammal.setName("Elephant");
    mammal.setAge(12);
    mammal.displayInfo();
    mammal.feedBaby();

    cout << '\n';

    Bird bird;
    bird.setName("Parrot");
    bird.setAge(4);
    bird.displayInfo();
    bird.layEgg();

    cout << '\n';

    Reptile reptile;
    reptile.setName("Turtle");
    reptile.setAge(8);
    reptile.displayInfo();
    reptile.shedSkin();

    return 0;
}
