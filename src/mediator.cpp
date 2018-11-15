#include "mediator.h"



        // Inicializa el terreno y el coche.
mediator::mediator()
{
    
    counter = 0;
    counter_p = 0;
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
            std::cin.clear();
            std::cin >> pos_x;
            std::cout << "Introduzca posición y: ";
            std::cin.clear();
            std::cin >> pos_y;
            std::cin.clear();
            
            
            if((T.get_pos(pos_x,pos_y) != 'o') && (pos_x <= T.get_m()) && (pos_y <= T.get_n())){        
                C.init_m(pos_x, pos_y);
                valid = true;
            }
            
        }while(valid == false);
        
        
    }
    
    std::pair<int,int> car_start = C.get_pos();
    

    node start(car_start.first, car_start.second);
    node end(40,40);
        std::cout << "Se pasará a escribir el terreno con el coche posicionado \n";
        write(std::cout, i, j);


    std::cout << "Punto inicial es: " << car_start.first <<  ' ' << car_start.second << '\n';
    std::cout << "Punto inicial es: " << start.get_x() << ' ' << start.get_y() << '\n';
    
    astar(start, end);
}




mediator::~mediator()
{
    
}

/*


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

*/


        // Calcula el la distancia más corta, de 3 maneras diferentes
float mediator::heuristic(int start_x, int start_y, int end_x, int end_y, int opt)
{
    if(opt == 1){
        float r = sqrt(pow((end_x - (start_x - 1)), 2.0) + pow((end_y - start_y), 2.0)); 
        return r;
    }
    
    else if(opt == 2){
        float dif_x = abs(start_x - end_x);
        float dif_y = abs(start_y - end_y);
    
        float r = dif_x + dif_y;
        return r;
    }
    
    else
    {
    float r1 = heuristic_1(start_x, start_y, end_x, end_y);
    float r2 = heuristic_2(start_x, start_y, end_x, end_y);
    
    if(r1 < r2)
        return r1;
    else
        return r2;
    }
}



float mediator::heuristic_1(int start_x, int start_y, int end_x, int end_y)
{
        float r = sqrt(pow((end_x - (start_x - 1)), 2.0) + pow((end_y - start_y), 2.0)); 
        return r;
}



float mediator::heuristic_2(int start_x, int start_y, int end_x, int end_y)
{
    float dif_x = abs(start_x - end_x);
    float dif_y = abs(start_y - end_y);
    
    float r = dif_x + dif_y;
    return r;

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



        //Encuentra nuevos caminos, y los añade a la lista
std::list<path> mediator::find_new_paths(std::list<path>& new_path_list,  path& actual_path, int opt)
{
    
    int end_x = 40;
    int end_y = 40;
    

    path aux = actual_path;
    
    int start_x = actual_path.get_last_x();
    int start_y = actual_path.get_last_y();
    
    int before_x = actual_path.get_before_last_x();
    int before_y = actual_path.get_before_last_y();
    
    node nw(start_x -1, start_y);
    node na(start_x, start_y - 1);
    node ns(start_x + 1, start_y);
    node nd(start_x, start_y + 1);
    
    float cost;
    
    char w = T.get_pos(start_x -1, start_y);
    char a = T.get_pos(start_x, start_y - 1);
    char s = T.get_pos(start_x + 1, start_y);
    char d = T.get_pos(start_x, start_y + 1);
        
        
    if((w != 'o') && (start_x > 0)){

        aux.add(nw.get_x(), nw.get_y());
        
        cost = heuristic(start_x - 1, start_y, end_x, end_y, opt);
        aux.update_cost(cost);
        
        new_path_list.push_front(aux);
        
        counter++;
    }

    if((a != 'o') | (a > 0)){
        
        aux = actual_path;
        

        aux.add(na.get_x(), na.get_y());
        
        cost = heuristic(start_x, start_y - 1, end_x, end_y, opt);
        aux.update_cost(cost);
        
        new_path_list.push_front(aux);
        
        counter++;

    }

    if((s != 'o') | (s < T.get_m())){

        aux = actual_path;

        aux.add(ns.get_x(), ns.get_y());
        
        cost = heuristic(start_x + 1, start_y, end_x, end_y, opt);
        aux.update_cost(cost);
        
        new_path_list.push_front(aux);

        counter++;
    }

    if((d != 'o') | (d < T.get_n())){

        aux = actual_path;

    
        aux.add(nd.get_x(), nd.get_y());
        
        cost = heuristic(start_x, start_y + 1, end_x, end_y, opt);
        aux.update_cost(cost);
        
        new_path_list.push_front(aux);
        
        counter++;
    }

    
    return new_path_list;
    
}



        //Algoritmo A*
bool mediator::astar(node start, node goal)
{
    std::list<path> open_list;
    std::list<path> close_list;
    bool solution = false;
    
    std::cout << "Punto inicial es: " << start.get_x() << ' ' << start.get_y() << '\n';
    
    
    int opt;
    std::cout << "Qué función heurística quieres usar? (1: pitágoras; 2: la otra; 3: mínimo) \n";
    std::cin >> opt;
    
    
    path initial_path;
    initial_path.add(start.get_x(), start.get_y());
    
    float cost = heuristic(start.get_x(), start.get_y(), goal.get_x(), goal.get_y(), opt);
    
    initial_path.update_cost(cost);
    
    open_list.push_front(initial_path);
    
    
    int cont = 0;
    
    
    while((!open_list.empty()) && (!solution)){
    
        if((open_list.front().get_last_x() == goal.get_x()) && open_list.front().get_last_y() == goal.get_y())
            solution = true;
        else{
            path aux = (*open_list.begin()).get_path();
            
            open_list.pop_front();
            
            bool explore = false;
            
            explore = insert_path_close_list(close_list, aux);
            
            std::list<path> new_path_list;
            if(explore){
                find_new_paths(new_path_list, aux, opt);
            }
            for(std::list<path>::iterator list_iter = new_path_list.begin(); list_iter != new_path_list.end(); ++list_iter)
                insert_path_open_list(open_list, close_list, (*list_iter).get_path());
            
            sort_list(open_list);

          
        }
        
    
    }
    
    if(open_list.size() != 0){
        path solution_path = (*open_list.begin()).get_path();
        
        for(int i = 0; i < solution_path.get_size(); i++) {
            T.set_pos(solution_path[i].get_x(), solution_path[i].get_y(), 'x');
            
            counter_p++;
            
            T.write_all(std::cout);
        }
        
        std::cout << "\n\n";
        T.write_all(std::cout);
    }
    
    else
    {
        std::cout << "No hay solución  \n";
    }
    
    std::cout << counter << '\n';
    std::cout << counter_p << '\n';
    
}


        //Inserta caminos en una lista secundaria
bool mediator::insert_path_close_list(std::list<path>& close_list,path& path2) {

    bool exist = false;
    bool explore = false;

    int x_path = path2.get_last_x();
    int y_path = path2.get_last_y();
    int path_total_cost = path2.get_cost();

    int iter_total_cost = 0;

    for(std::list<path>::iterator list_iter = close_list.begin(); !exist && (list_iter != close_list.end()); list_iter++) {//Insertando la trayectoria en la lista cerrada
        if (((*list_iter).get_last_x() == x_path) && ((*list_iter).get_last_y() == y_path)) { //Detectando si es un camino similar
            exist = true;


            iter_total_cost = (*list_iter).get_cost();

            if (iter_total_cost > path_total_cost) {
                close_list.erase(list_iter);
                close_list.push_front(path2);
                explore = true;
            }

        }
    }
    if (!exist) {
        close_list.push_front(path2);
        explore = true;
    }

    return explore;
}


    //Lista principal, con el camino más rápido
bool mediator::insert_path_open_list(std::list<path>& open_list,std::list<path>& close_list,path path2)
{

    bool exist = false;

    int x_path = path2.get_last_x();
    int y_path = path2.get_last_y();
    int path_total_cost = path2.get_cost();

    int iter_total_cost = 0;

    for(std::list<path>::iterator list_iter = open_list.begin(); !exist && (list_iter != open_list.end()); list_iter++) {//Insertando la trayectoria en la lista cerrada
        if (((*list_iter).get_last_x() == x_path) && ((*list_iter).get_last_y() == y_path)) { //Detectando si es un camino similar
            exist = true;

            iter_total_cost = (*list_iter).get_cost();

            if (iter_total_cost > path_total_cost) {
                path aux;

                aux = (*list_iter).get_path();
                insert_path_close_list(close_list,aux);

                open_list.erase(list_iter);
                open_list.push_front(path2);
            }
        }
    }
    if (!exist) {
        open_list.push_front(path2);
    }
    


}





//Ordenar para que el primero sea el min
void mediator::sort_list(std::list<path>& source_list) {

    if (source_list.size() != 0) {
        path min_path;

        min_path = (*source_list.begin()).get_path();
        int min_cost = min_path.get_cost();
        std::list<path>::iterator min_iter = source_list.begin();
        int iter_total_cost = 0;

        for(std::list<path>::iterator list_iter = source_list.begin(); list_iter != source_list.end(); list_iter++) {
            iter_total_cost = (*list_iter).get_cost();

                if (iter_total_cost < min_cost) {
                    min_path = (*list_iter).get_path();
                    min_cost = iter_total_cost;
                    min_iter = list_iter;
                }
        }

        source_list.erase(min_iter);

        source_list.push_front(min_path);
    }
}

