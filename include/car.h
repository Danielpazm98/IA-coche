

#include <iostream>
#include <vector>


    //Estructura. tiene Posición y dirección.
struct C
{
    int x_;
    int y_;
    char direc_;
    
};

class car
{
private:
    C car_;
public:

    car();
    ~car();

    void init_m(int x, int y);              //Coloca el coche en una posición que tú le indicas 
    void init_a(int max_i, int max_j);      //Coloca el coche en una posición aleatoria (De las libres)
    
    std::pair<int,int> get_pos();
    
    void move(char w, char a, char s, char d, int i, int j);      //Mueves el coche de manera manual  (Sin implementar)

    void autom(char w, char a, char s, char d, int fin_x, int fin_y);     //El coche se mueve de manera automática (sin implementar)
    
    float heuristic(int x, int y, char d);

    std::ostream& write(std::ostream& os);
};