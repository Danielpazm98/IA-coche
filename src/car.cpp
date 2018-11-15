#include "car.h"


#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <set>


#define MAX_INT 999999.0

car::car()
{
    
}




car::~car()
{
    
    
}




void car::init_m(int x, int y)
{
    car_.x_ = x;
    car_.x_ = y;
    car_.direc_ = 'w';
}




void car::init_a(int max_i, int max_j)
{
    std::mt19937_64 rng;
        // initialize the random number generator with time-dependent seed
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);
    
    
    std::default_random_engine generator;
    int dice_roll;
    

    std::uniform_int_distribution<int> unif_i(0,max_i);
    dice_roll = unif_i(rng);  // generates number in the range 0..1 
    
    car_.x_ = dice_roll;

    std::uniform_int_distribution<int> unif_j(0,max_j);
    dice_roll = unif_j(rng);  // generates number in the range 0..1 

    car_.y_ = dice_roll;

}




std::pair<int,int> car::get_pos()
{
    std::pair<int,int> aux;
    aux.first = car_.x_;
    aux.second = car_.y_;
    
    return aux;
}




void car::move(char w, char a, char s, char d, int max_i, int max_j)
{
    
    std::cout << "Muévete. (w,a,s,d) \n";
    char dir;
    
    bool valid = false;
    
    do{
    
        std::cin >> dir;
        
        if((dir == 'w') && (car_.x_ > 0)){
            if(w != 'o'){
                valid = true;
                car_.x_--;
            }
        }
        
        
        if((dir == 'a') && (car_.y_ > 0)){
            if(a != 'o'){
                valid = true;
                car_.y_--;
            }
        }
        
        
        if((dir == 's') && (car_.x_ < max_i)){
            if(s != 'o'){
                valid = true;
                car_.x_++;
            }
        }
        
        if((dir == 'd') && (car_.y_ < max_j)){
            if(d != 'o'){
                valid = true;
                car_.y_++;
            }
        }
        
    }while(valid == false);
    
    
}



/*

void car::autom(char w, char a, char s, char d, int fin_x, int fin_y)
{
    float min;
    float dist_w = MAX_INT;
    float dist_a =  MAX_INT;
    float dist_s = MAX_INT;
    float dist_d = MAX_INT;
    
    
    std::set<float> dist;
    
    
    
    
    
    if(w != 'o'){
        dist_w = heuristic(fin_x, fin_y, 'w');
        dist.insert(dist_w);
    }
        
        
    if(a != 'o'){
        dist_a = heuristic(fin_x, fin_y, 'a');
        dist.insert(dist_a);
    }
        
        
    if(s != 'o'){
        dist_s = heuristic(fin_x, fin_y, 's');
        dist.insert(dist_s);
    }

    if(d != 'o'){
        dist_d = heuristic(fin_x, fin_y, 'd');
        dist.insert(dist_d);
    }
  

    std::cout << dist_a << ' ' << dist_s << ' ' << dist_d << ' ' << dist_w << '\n';


    if(dist_w == *dist.begin()){
        car_.x_--;
        
    }
    
    else if(dist_a == *dist.begin()){
        car_.y_--;
        

    }
    
    else if(dist_s == *dist.begin()){
        car_.x_++;

    }
    
    else if(dist_d == *dist.begin()){
        car_.y_++;

    }
    
    
}



float car::heuristic(int fin_x, int fin_y, char dir)
{


    float r;


    if(dir == 'w'){
        r = sqrt(pow((fin_x - (car_.x_ - 1)), 2.0) + pow((fin_y - car_.y_), 2.0)); 
    }
    
    
    else if (dir == 'a'){
        r = sqrt(pow((fin_x - car_.x_), 2.0) + pow((fin_y - (car_.y_ - 1)), 2.0)); 
    }

    
    else if(dir == 's'){
        r = sqrt(pow((fin_x - (car_.x_ + 1)), 2.0) + pow((fin_y - car_.y_), 2.0)); 
    }

    else if(dir == 'd'){
        r = sqrt(pow((fin_x - car_.x_), 2.0) + pow((fin_y - (car_.y_ + 1)), 2.0)); 
    }

    
    //std::cout << "La distancia al punto es: " << r << '\n';
    
    
    return r;

}



float car::heuristic(std::pair<int,int> pos, int end_x, int end_y)
{
    float r;
    
    r = sqrt(pow((end_x - (pos.first - 1)), 2.0) + pow((end_y - pos.second), 2.0)); 
    
    return r;
    
}

*/



std::ostream& car::write(std::ostream& os)
{
    


    char a = 'Y';
    
    std::cout << a << "  ";
    
    return os;   
}