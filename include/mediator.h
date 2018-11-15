#include "car.h"
#include "terrain.h"
#include "path.h"
#include "node.h"

#include <iostream>
#include <list>


    // Coordina todo, e indica que tienen que hacer terrain y car
class mediator
{
private:
    car C;
    terrain T;
    std::vector<path> P;

public:
    mediator();
    
    ~mediator();
    
    void run(int x, int y);         // Itera hasta que acabe.
    
    
    float heuristic(int start_x, int start_y, int end_x, int end_y, int opt);
    float heuristic_2(int start_x, int start_y, int end_x, int end_y);
    float heuristic_min(int start_x, int start_y, int end_x, int end_y);
    
    
    std::list<path> find_new_paths(std::list<path>& new_path_list, path& actual_path, int opt);
    bool astar(node start, node end);
    bool insert_path_close_list(std::list<path>& closed_list, path& path);
    bool insert_path_open_list(std::list<path>& open_list, std::list<path>& close_list, path path);
    void sort_list(std::list<path>& source_list);
    
    std::ostream& write(std::ostream& os, int i, int j);
    
    
    
    
};

