
/*****************************
*   représente l'echiquier
*****************************/
class Graph : public vector< vector<Case> >
{
    public:
        Graph(unsigned int size);
        bool Connexe();
        void Resize(unsigned int size);
        void Move(sf::RenderWindow& App);
        void Draw(sf::RenderWindow& App);
        void Check(vector<bool>& connexe, int x, int y);
        static sf::Image clear;
        static sf::Image wall;
        bool Collide(double x, double y);
        list<Point>* PathFinding(Point start, Point end);
        bool Win();
    private:
        Hero hero;
        vector<Monster> monsters;
        list<Treasure> treasures;
        Point heroLastPosition;
        bool lose;
        sf::Sprite losed;

};
