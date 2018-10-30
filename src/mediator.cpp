#include "mediator.h"


#include <iostream>



mediator::mediator()
{
    char opt;
    
    std::cout << "Deseas introducir el tamaño del mapa y la probabilidad de obstáculos? (S/N) (por defecto: 50x50, 25%) \n";
    std::cin >> opt;

    int i;
    int j;
    int p;

    if(opt == 's' | opt == 'S'){
        std::cout << "Introduce tamaño del mapa (mxn) \n";
        std::cin >> i;
        std::cin >> j;
        
        std::cout << "Cuál es la probabilidad de obstáculos que deseas? (sólo \n";
        
        do{
        std::cout << "Introduce un número del 0-9 (siendo 9 la mayor probabilidad permitida): ";
        std::cin >> p;
        }while((p < 1) | (p > 9));
        
        T.create(i,j, p);
    }
    else{
        i = 50;
        j = 50;
        p = 5;
        T.create(i,j, p);
    }
    
    
    
    std::cout << "Se procederá a colocar el coche. \n Prefiere colocarlo de manera aleatoria? (S/N): ";
    std::cin >> opt;
    
    if((opt == 's') | (opt == 'S')){
        
        bool valid = false;
        
        do{
            C.init_a(i, j);
            
            std::pair<int,int> aux = C.get_pos();
            int pos_x = aux.first;
            int pos_y = aux.second;
            
            char cont = T.get_pos(pos_x, pos_y);
            
            if(cont == ' '){
                valid = true;
                std::cout << "Coche colocado en " << pos_x << ' ' << pos_y << '\n';
            }
            

        }while(valid == false);
        
    }
    else{

        std::cout << "Elije la posición de inicio del coche (si hay un obstáculo, tendrás que repetir la operación \n";
        
        bool valid = false;
        
            int pos_x;
            int pos_y;
            
        do{
            
            
            std::cout << "Introduzca posición x: ";
            std::cin >> pos_x;
            std::cout << "Introduzca posición y: ";
            std::cin >> pos_y;
        
        
            
            if((T.get_pos(pos_x,pos_y) != 'o') && (pos_x <= T.get_m()) && (pos_y <= T.get_n())){        
                C.init_m(pos_x, pos_y);
                valid = true;
            }
            
        }while(valid == false);
        
        
    }
        std::cout << "Se pasará a escribir el terreno con el coche posicionado \n";
        write(std::cout, i, j);
    
}




mediator::~mediator()
{
    
}




void mediator::run(int x, int y)
{
    
    std::cout << "Se empezará el recorrido (sólo modo manual) \n";
    

    bool end = false;
    
    int opt = 1;
    
    int i = T.get_m();
    int j = T.get_n();
    

    if(opt == 0){
        do
        {
            
            std::pair<int,int> pos = C.get_pos();
            
            T.set_pos(pos.first, pos.second, '*');
        
            char w = T.get_pos(pos.first -1, pos.second);
            char a = T.get_pos(pos.first, pos.second - 1);
            char s = T.get_pos(pos.first + 1, pos.second);
            char d = T.get_pos(pos.first, pos.second + 1);
        
            C.move(w, a, s, d, i, j);
        
            write(std::cout, T.get_m(), T.get_n());
        
        }while (end == false);
    }
    
    else{


        int i = 0;
        do
        {
            std::pair<int,int> pos = C.get_pos();
            
            T.set_pos(pos.first, pos.second, '*');
            
            char w = T.get_pos(pos.first -1, pos.second);
            char a = T.get_pos(pos.first, pos.second - 1);
            char s = T.get_pos(pos.first + 1, pos.second);
            char d = T.get_pos(pos.first, pos.second + 1);
        
            
            C.autom(w, a, s, d, x, y);
        
            if((pos.first == x) && (pos.second == y))
                end = true;
            //i++;
        
           write(std::cout, T.get_m(), T.get_n());
        
        
        }while (end == false);
    }
    
    
    
    
}




std::ostream& mediator::write(std::ostream& os, int m, int n)
{
        //system("clear");

    
    for(int i = 0; i <= 2*m; i++)
        std::cout << '_';
    
    std::cout << '\n';
    
    
    
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            
            if(j == 0)
                std::cout << '|';
            
            std::pair<int,int> aux = C.get_pos();
            
            if((i == aux.first) && (j == aux.second))
                C.write(std::cout);
            else
                T.write_char(std::cout, i, j);
            
            if(j >= (n - 1))
                std::cout << '|' << '\n';
            
        }
    }
    
    
    for(int i = 0; i <= 2*m; i++)
        std::cout << '_';
    
    std::cout << '\n';

    
    
    return os;
}


