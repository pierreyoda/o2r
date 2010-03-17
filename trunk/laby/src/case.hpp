

class Case : public sf::Sprite
{
    public:
        Case(sf::Vector2f vector);
        void Clear();
        bool IsClear();
    private:
        bool clear;

};
