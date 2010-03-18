/*****************************
*   entité presente a l'ecran
*****************************/
class Entity : public sf::Sprite
{
    public:
        Entity(double speed);
        void SetPosition(double x, double y);
        double GetX(){return x;}
        double GetY(){return y;}
        double GetSpeed(){return speed;}
        void Refresh(){current -= 1; if(current <= 0) current = speed;}
        bool CanMove(){return current == speed;}
    protected:
        double x;
        double y;
        double speed;
        int current;

};

/*****************************
*   Monstre
*****************************/
class Monster : public Entity
{
    public:
        Monster();
        void SetPath(list<Point>* path);
        bool HasPath();
        Point GetNext();
    private:
        list<Point>* path;

};

/*****************************
*   Hero
*****************************/
class Hero : public Entity
{
    public:
        Hero();

};

/*****************************
*   Treasure
*****************************/
class Treasure : public Entity
{
    public:
        Treasure();

};
