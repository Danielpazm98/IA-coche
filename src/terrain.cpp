#include "terrain.h"


#include <iostream>
#include <random>
#include <chrono>

#include <fstream>




terrain::terrain()
{
    
    
}




terrain::~terrain()
{
    
}




void terrain::create(int m, int n, int p)
{
    
    m_ = m;
    n_ = n;
    
    M_.resize(m_, std::vector<char>(n_));
    
    std::cout << "Desea que la generación de obstáculos sea aleatoria? (S/N)" << '\n';
    
    char a;
    char b;
    std::cin >> b;
    
    int q;
    
    if(b == 'S'){
        

        for(int i = 0; i < m_; i++){
            for(int j = 0; j < n_; j++){ 


                std::mt19937_64 rng;
                    // initialize the random number generator with time-dependent seed
                uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
                std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
                rng.seed(ss);
                
                q = 10 - p;

                std::default_random_engine generator;
                std::uniform_int_distribution<int> unif(0,q);
                int dice_roll = unif(rng);  // generates number in the range 0..1 
                
                
                
                if(dice_roll == 0){
                    M_[i][j] = 'o';
                }
                else{
                    M_[i][j] = ' ';
                }

                //write_char(std::cout, i, j);
                
            }
        }
        
        write_all(std::cout);
    }
    
    if( b == 'N'){
        
        std::cout << "Se colocarán los obstáculos en función del fichero \"obstacle.txt\" \n";
        

        std::fstream fs("obstacle.txt", std::ios_base::in);
    
        int obst_n;
    
        fs >> obst_n;

        char aux;
        fs >> aux;
        
        
        std::vector<int> obst_i;
        std::vector<int> obst_j;
        
        obst_i.resize(obst_n);
        obst_j.resize(obst_n);
        
        
        int i = 0;   
        
        while((i <= obst_n) && (!fs.eof())){
        
        
            fs >> obst_i[i] >> aux >> obst_j[i];
        
            std::cout << obst_i[i] << ' ' << aux << ' ' << obst_j[i] << '\n';
        
        
            
            set_pos(obst_i[i], obst_j[i], 'o');
            
            i++;
        }
        
        fill();
        
        write_all(std::cout);
    }
            
            

    
        
/*
    std::cout << "Coloca los obstáculos posición por posición. Se mostrará el avance cada vez que termines una fila (a = vacío / b = obstáculo) \n";    
        
       for(int i = 0; i < m_; i++){
            for(int j = 0; j < n_; j++){ 
                
                std::cout << "Posición" << '[' << i << ',' << j << ']' << ':' << ' ';
                std::cin >> a;
                M_[i][j] = a;

            }
            for(int j = 0; j < n_; j++)
                write_char(std::cout, i, j);
        }
        
            
        std::cout << "\n \n Se procederá a escribir la rejilla completa \n";
        
        write_all(std::cout);
    }
*/
}



void terrain::fill()
{
    
    for(int i = 0; i < m_; i++){
        for(int j = 0; j < n_; j++){
            if(M_[i][j] != 'o') 
                M_[i][j] = ' ';
        }
    }
}





int terrain::get_m()
{
    return m_;
}




int terrain::get_n()
{
    return n_;   
}



char terrain::get_pos(int i, int j)
{

    if(i < m_ && j < n_)    
        return M_[i][j];

    else
        return 'o';
}




void terrain::set_pos(int i, int j, char a)
{
    if((i <= m_) && (j <= n_ ))
        M_[i][j] = a;
}




void terrain::w()
{
    write_all(std::cout);
}




std::ostream& terrain::write_char(std::ostream& os, int i, int j)
{

    //assert((i <= m_) && (j <= n_));
    
    
    
    std::cout << M_[i][j] << "  ";
    
    return os;
}




std::ostream& terrain::write_all(std::ostream& os)
{
    

    for(int i = 0; i < ((m_*4) + 2); i++)
        std::cout << '_';
    
    std::cout << '\n';
    
    for(int i = 0; i < m_; i++){
        for(int j = 0; j < n_; j++){
            
            if(j == 0)
                std::cout << '|';
    
            std::cout << M_[i][j] << ' ';
        
            if(j >= (n_ - 1))
                std::cout << '|' << '\n';
        }
    }
    
    for(int i = 0; i < (m_*2); i++)
        std::cout << '_';
    
    std::cout << '\n';

    return os;
    
}









