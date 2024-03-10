#include <iostream>
#include <memory>

class Toy
{
private:
    std::string name;
public:
    Toy(std::string inName)
    {
        name = inName;
    }

    std::string getName()
    {
        return name;
    }

    ~Toy()
    {
        std::cout << "Toy " << name << " was dropped" << std::endl;
    }
};

class Dog
{
private:
    std::string nameDog;
    std::shared_ptr<Toy> lovelyToy;

public:
    Dog(std::string inName, std::shared_ptr<Toy> toy) : nameDog(inName), lovelyToy(toy) {};
    Dog() : Dog("Snow", std::make_shared<Toy>("SomeToy")) {};
    Dog(std::string inName) : Dog(inName, std::make_shared<Toy>("SomeToy")) {};

    void getToy(std::shared_ptr<Toy>& toy)
    {
        if (lovelyToy == toy) std::cout << "I already have this toy." << std::endl;
        else if (toy.use_count() > 1) std::cout << "Another dog is playing with this toy." << std::endl;
        else lovelyToy = toy;
    }

    void dropToy()
    {
        std::cout << lovelyToy.use_count() << std::endl;
        if (lovelyToy.use_count() == 1) std::cout << "Nothing to drop." << std::endl;
        else lovelyToy = nullptr;
    }
};

int main() {
    std::shared_ptr<Toy> ball = std::make_shared<Toy>("Ball");

    Dog a("Druzok");
    Dog b("Tor");
    Dog c("Nelsi");

    a.getToy(ball);
    b.dropToy();
    c.getToy(ball);
    a.dropToy();
    b.getToy(ball);
    b.getToy(ball);
}
