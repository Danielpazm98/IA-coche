

#include <iostream>
#include <vector>


    //Terreno. tiene dimensiones, y es un vector<vector<char>>. Los obstáculos se identifican según el char.
class terrain
{
private:
    int m_;
    int n_;

    std::vector<std::vector<char> > M_;     //Terreno sobre el que se ponen los obstáculos.

public:

    terrain();
    ~terrain();

    void create(int m, int n, int p);              //Crea el terreno y lo imprimes
    void w();                               //Manda a imprimir el terreno
    
    
    int get_m();
    int get_n();
    char get_pos(int i, int j);
    void set_pos(int i, int j, char a);

    void fill();


    std::ostream& write_char(std::ostream& os, int i, int j);       //Escribe una posición del terreno
        
    std::ostream& write_all(std::ostream& os);                              //Escribe el terreno entero

};
