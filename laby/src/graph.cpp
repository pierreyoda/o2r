#include "core.hpp"
/*****************************
*   macro utilisé pour faciliter le codage
*****************************/
#define tab (*this)
#define able(x, y) (x > 0) && (y > 0) && (x < Size - 1) && (y < Size - 1)
#define able2(x, y) (x >= 0) && (y >= 0) && (x < Size) && (y < Size)
#define check(monster)\
if(hero.GetX() == monster.GetX() && hero.GetY() == monster.GetY())\
{\
    lose = true;\
    return;\
}

/*****************************
*   meilleur node dans une map
*****************************/
inline pair<int,int> BestNode(map< pair<int,int>, Node>& l)
{
    unsigned int m_poundf = l.begin()->second.pound_f;
    pair<int,int> m_node = l.begin()->first;
    //Parcour la map
    for (map< pair<int,int>, Node>::iterator it = l.begin(); it!=l.end(); ++it)
    {
        //si meilleur poids
        if (it->second.pound_f < m_poundf)
        {
            m_poundf = it->second.pound_f;
            m_node = it->first;
        }
    }
    //On retourne le noeud
    return m_node;
}


/********************************
*   carre de la norme euclidiene
********************************/
inline unsigned int Pound(int x1, int y1, int x2, int y2)
{
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

/************************************************
*   ajoute le noeud suivant et calcule ses cout
*************************************************/
inline void AddNext(pair<int,int> next, pair <int,int>& n, map< pair<int,int>, Node>& open, map< pair<int,int>, Node>& close, Point& end)
{
    Node tmp;
    //Si le noeud n'est pas présent
    if(close.find(next) == close.end())
    {
        //1 = Pound(next.first,next.second,n.first,n.second) car deplacement en diagonales interdit
        tmp.pound_g = close[n].pound_g + 1;
        tmp.pound_h = Pound(next.first,next.second,end.x, end.y);
        tmp.pound_f = tmp.pound_g + tmp.pound_h;
        tmp.first = n.first;
        tmp.second = n.second;
        if (open.find(next) != open.end())
        {
            // noeud est déjà présent dans la liste ouverte, on compare les poids
            if (tmp.pound_f < open[next].pound_f)
            {
                //On a trouvé un meileur chemin
                open[next] = tmp;
            }

        }
        else
        {
            //on ajoute dans la liste ouverte si il n'est pas dedans
            open[pair<int,int>(next.first, next.second)] = tmp;
        }
    }
}



sf::Image Graph::clear;
sf::Image Graph::wall;

/******************************
*   constructeur de l'equichier
*******************************/
Graph::Graph(unsigned int size)
{
    if(!clear.LoadFromFile("node.png"))
    {
        cout << "le chargement de l'image node.png a echoué" << endl;
        exit(EXIT_FAILURE);
    }
    if(!wall.LoadFromFile("Wall.png"))
    {
        cout << "le chargement de l'image wall.png a echoué" << endl;
        exit(EXIT_FAILURE);
    }
    sf::Image* loseImg = new sf::Image();
    if(!loseImg->LoadFromFile("lose.png"))
    {
        cout << "le chargement de l'image lose.png a echoué" << endl;
        exit(EXIT_FAILURE);
    }
    losed.SetImage(*loseImg);
    losed.SetPosition((Width - losed.GetSize().x)/2, Height/2);
    Resize(size);
}


/*****************************
*   redimenssione l'equichier
*****************************/
void Graph::Resize(unsigned int size)
{
    lose = false;
    resize(0);
    resize(size);
    double x = (Height - clear.GetHeight()*size) / 2;
    for(Graph::iterator it = begin(); it != end(); ++it)
    {
        double y = (Width - clear.GetWidth()*size) / 2;
        (*it).resize(size, Case(sf::Vector2f(x,y)));
        for(vector<Case>::iterator node = (*it).begin(); node != (*it).end(); ++node)
        {
            (*node).SetY(y);
            y += clear.GetWidth();
        }
        x += clear.GetHeight();
    }

    //liberation des points d'emplacement
    //enemies
    tab[1][1].Clear();
    tab[1][Size - 2].Clear();
    tab[Size - 2][Size - 2].Clear();
    tab[Size - 2][1].Clear();
    //joueur
    tab[Size/2][Size/2].Clear();
    //On relie les points
    for(int n=1; n < (Size - 2); ++n)
    {
        tab[n][1].Clear();
        tab[1][n].Clear();
        tab[n][Size - 2].Clear();
        tab[Size - 2][n].Clear();
    }
    //creation de 10 galleries
    srand ( time(NULL) );
    for(int n=0; n < 9; ++n)
    {
        int x = rand()%Size;
        int y = rand()%Size;
        int size = rand()%(Size/2) + Size/2 - 2;
        for(int i = 0; i < size; ++i)
        {
            if(able(x, y+i))
                tab[x][y+i].Clear();
            if(able(x+i, y+size))
                tab[x+i][y+size].Clear();
            if(able(x+i, y))
                tab[x+i][y].Clear();
            if(able(x+size, y+i))
                tab[x+size][y+i].Clear();
        }

    }

    //ajout du hero
    hero.SetPosition(Size/2,Size/2);
    //Ajout des monstres
    monsters.resize(4);
    monsters[0].SetPosition(1, 1);
    monsters[1].SetPosition(1, Size - 2);
    monsters[2].SetPosition(Size - 2, 1);
    monsters[3].SetPosition(Size - 2, Size - 2);
    monsters[0].SetPath(PathFinding(Point(1, 1), Point(Size/2,Size/2)));
    monsters[1].SetPath(PathFinding(Point(1, Size - 2), Point(Size/2,Size/2)));
    monsters[2].SetPath(PathFinding(Point(Size - 2, 1), Point(Size/2,Size/2)));
    monsters[3].SetPath(PathFinding(Point(Size - 2, Size - 2), Point(Size/2,Size/2)));
    heroLastPosition.x = Size/2;
    heroLastPosition.y = Size/2;

    //Ajoute de coffre
    treasures.resize(10);
    for(list<Treasure>::iterator it = treasures.begin(); it != treasures.end(); ++it)
    {
        unsigned int x = 0;
        unsigned int y = 0;
        while(!tab[x][y].IsClear() && ((x = Size/2) &&  (y = Size/2)))
        {
            x = 1 + rand()%(Size-1);
            y = 1 + rand()%(Size-1);
            (*it).SetPosition(x, y);
        }
    }
}

/*****************************
*   verifie recursivement pour chaque node si connexe
*****************************/
void Graph::Check(vector<bool>& connexe, int x, int y)
{
    if(!tab[x][y].IsClear())
        return;
    if(connexe[x + y * Size])
        return;
    connexe[x + y * Size] = true;
    if(able2(x - 1,y))
        Check(connexe, x - 1, y);
    if(able2(x + 1,y))
        Check(connexe, x + 1, y);
    if(able2(x,y - 1))
        Check(connexe, x, y - 1);
    if(able2(x,y + 1))
        Check(connexe, x, y + 1);
}
/*****************************
*   verifie recursivement si le graph est connexe
*****************************/
bool Graph::Connexe()
{
    vector<bool> connexe;
    connexe.resize(Size*Size, false);
    int n, i;
    for(int x=0; x < Size; ++x)
    {
        for(int y=0; y < Size; ++y)
        {
            connexe[x + y*Size] = !tab[x][y].IsClear();
            if(!connexe[x + y*Size])
            {
                n = x;
                i = y;
            }
        }
    }
    Check(connexe, n, i);
    for(int x=0; x < Size; ++x)
    {
        for(int y=0; y < Size; ++y)
        {
            if(!connexe[x + y*Size])
                return false;
        }
    }
    return true;
}

/*****************************
*   recherche un chemin
*****************************/
list<Point>* Graph::PathFinding(Point start, Point end)
{

    //Init
    map< pair<int,int>, Node> open;
    map< pair<int,int>, Node> close;
    list<Point>* path = new list<Point>();
    pair <int,int> current;

    current.first  = start.x;
    current.second = start.y;

    // ajout du départ dans la liste fermé
    close[current] = Node(start);

    //ajoute des nodes voisin
    if(tab[current.first - 1][current.second].IsClear())
        AddNext(pair<int,int>(current.first - 1, current.second), current, open, close ,end);
    if(tab[current.first][current.second - 1].IsClear())
        AddNext(pair<int,int>(current.first, current.second - 1), current, open, close ,end);
    if(tab[current.first + 1][current.second].IsClear())
        AddNext(pair<int,int>(current.first + 1, current.second), current, open, close ,end);
    if(tab[current.first][current.second + 1].IsClear())
        AddNext(pair<int,int>(current.first , current.second + 1), current, open, close ,end);

;
    while(!(current.first == end.x && current.second == end.y) && !open.empty())
    {
        // on cherche le meilleur noeud de la liste ouverte
        current = BestNode(open);

        // on le passe dans la liste fermee et on le suprime de la liste ouverte
        close[current] = open[current];
        open.erase(current);

        //ajoute des nodes voisin
        if(tab[current.first - 1][current.second].IsClear())
            AddNext(pair<int,int>(current.first - 1, current.second), current, open, close ,end);
        if(tab[current.first][current.second - 1].IsClear())
            AddNext(pair<int,int>(current.first, current.second - 1), current, open, close ,end);
        if(tab[current.first + 1][current.second].IsClear())
            AddNext(pair<int,int>(current.first + 1, current.second), current, open, close ,end);
        if(tab[current.first][current.second + 1].IsClear())
            AddNext(pair<int,int>(current.first , current.second + 1), current, open, close ,end);
    }

    //aucune solution
    if ((current.first != end.x) || (current.second != end.y))
        return path;


    //On part de la fin
    Node& tmp = close[std::pair<int, int>(end.x,end.y)];

    Point n;
    n.x = end.x;
    n.y = end.y;
    path->push_front(n);

    //tant nous ne sommes pas arrivé au début
    while (tmp != pair<int,int>(start.x,start.y))
    {
        n.x = tmp.first;
        n.y = tmp.second;
        path->push_front(n);
        //on récupere le noeud précédent
        tmp = close[tmp];
    }
    return path;
}

/*****************************
*   Déplacement du joeur et des monstres
*****************************/
void Graph::Move(sf::RenderWindow& App)
{
    if(lose)
        return;
    if(hero.CanMove())
    {
        if(App.GetInput().IsKeyDown (sf::Key::Down))
            if(tab[hero.GetX()][hero.GetY() + 1].IsClear())
                hero.SetPosition(hero.GetX(), hero.GetY() + 1);
        if(App.GetInput().IsKeyDown (sf::Key::Up))
            if(tab[hero.GetX()][hero.GetY() - 1].IsClear())
                hero.SetPosition(hero.GetX(), hero.GetY() - 1);

        if(App.GetInput().IsKeyDown (sf::Key::Left))
            if(tab[hero.GetX() - 1][hero.GetY()].IsClear())
                hero.SetPosition(hero.GetX() - 1, hero.GetY());
        if(App.GetInput().IsKeyDown (sf::Key::Right))
            if(tab[hero.GetX() + 1][hero.GetY()].IsClear())
                hero.SetPosition(hero.GetX() + 1, hero.GetY());
    }

    for(list<Treasure>::iterator it = treasures.begin(); it != treasures.end(); ++it)
    {
        if((*it).GetX() == hero.GetX() && (*it).GetY() == hero.GetY())
        {
            treasures.erase(it);
            it = treasures.begin();
        }
    }
    check(monsters[0]);
    check(monsters[1]);
    check(monsters[2]);
    check(monsters[3]);


    if(monsters[0].CanMove() )
    {
        Point next;
        if((hero.GetX() != heroLastPosition.x || hero.GetY() != heroLastPosition.y))
        {
            monsters[0].SetPath(PathFinding(Point(monsters[0].GetX(), monsters[0].GetY()), Point(hero.GetX(),hero.GetY())));
            monsters[1].SetPath(PathFinding(Point(monsters[1].GetX(), monsters[1].GetY()), Point(hero.GetX(),hero.GetY())));
            monsters[2].SetPath(PathFinding(Point(monsters[2].GetX(), monsters[2].GetY()), Point(hero.GetX(),hero.GetY())));
            monsters[3].SetPath(PathFinding(Point(monsters[3].GetX(), monsters[3].GetY()), Point(hero.GetX(),hero.GetY())));
            heroLastPosition.x = hero.GetX();
            heroLastPosition.y = hero.GetY();
        }

        if(monsters[0].HasPath())
        {
            next = monsters[0].GetNext();
            monsters[0].SetPosition(next.x, next.y);
            check(monsters[0]);
        }


        if(monsters[1].HasPath())
        {
            next = monsters[1].GetNext();
            monsters[1].SetPosition(next.x, next.y);
            check(monsters[1]);
        }


        if(monsters[2].HasPath())
        {
            next = monsters[2].GetNext();
            monsters[2].SetPosition(next.x, next.y);
            check(monsters[2]);
        }


        if(monsters[3].HasPath())
        {
            next = monsters[3].GetNext();
            monsters[3].SetPosition(next.x, next.y);
            check(monsters[3]);
        }
    }

    hero.Refresh();
    monsters[0].Refresh();
}

/*****************************
*   on dessine le jeu
*****************************/
void Graph::Draw(sf::RenderWindow& App)
{


    for(Graph::iterator it = begin(); it != end(); ++it)
        for(vector<Case>::iterator node = (*it).begin(); node != (*it).end(); ++node)
            App.Draw(*node);
    App.Draw(hero);
    for(vector<Monster>::iterator it = monsters.begin(); it != monsters.end(); ++it)
        App.Draw(*it);
    for(list<Treasure>::iterator it = treasures.begin(); it != treasures.end(); ++it)
        App.Draw(*it);
    if(lose)
        App.Draw(losed);

}

/*****************************
*   verifie si il reste des trésors
*****************************/
bool Graph::Win()
{
    return treasures.empty();
}
