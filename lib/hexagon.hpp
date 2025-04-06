#include <map>
#include <utility>
#include <array>
#include <memory>

class hexagon
{
public: 
    using coor = std::pair<int,int>;
    using orientation = std::pair<int,int>;
private:
    class utils{
        private:
            static constexpr int matrix[5][2][2] = {{{ 0, 1},{-1,-1}},
                                                    {{ 1, 1},{-1, 0}},
                                                    {{ 1, 0},{ 0, 1}},
                                                    {{ 0,-1},{ 1, 1}},
                                                    {{-1,-1},{ 1, 0}}};

        public:
            static orientation get_dir_vector(orientation from,int pos)
            {
                int first = matrix[pos][0][0] *from.first + matrix[pos][1][0] *from.second;
                int second = matrix[pos][0][1] *from.first + matrix[pos][1][1] *from.second;
                return std::make_pair(first,second);
            }
            static coor sum(coor from,orientation dir)
            {
                return std::make_pair(from.first + dir.first,from.second + dir.second);
            }
    };
    std::shared_ptr<std::map<std::pair<int,int>,hexagon*>> grid;
    static constexpr int max_children = 5;

    /* data */
    hexagon* children[max_children] = {nullptr};
    hexagon* parent = nullptr;
    int my_index = -1;
    coor my_pos;
    orientation my_orientation;

    hexagon():
        grid(std::make_shared<std::map<std::pair<int,int>,hexagon*>>(std::map<std::pair<int,int>,hexagon*>())),
        my_pos(std::make_pair(0,0)),
        my_orientation(std::make_pair(1,0))
    {
        grid->emplace(my_pos,this);
    }

    hexagon(coor _pos, orientation _orientation,std::shared_ptr<std::map<std::pair<int,int>,hexagon*>>grid):
        grid(grid),
        my_pos(std::move(_pos)),
        my_orientation(std::move(_orientation))
    {
        grid->emplace(my_pos,this);
    }
public:
    static hexagon prepare_grid(){
        return std::move(hexagon());
    }

    hexagon* emplace(int pos){
        hexagon* hex = nullptr;
        orientation new_orientation;
        coor new_coor;
        if(pos < 0 || pos >= max_children || (children[pos] != nullptr)){
            return nullptr;
        }
        else{
            new_orientation = utils::get_dir_vector(my_orientation,pos);
            new_coor = utils::sum(my_pos,new_orientation);
            if(grid->contains(new_coor))
            {
                return nullptr;
            }
            hex = new hexagon(new_coor,new_orientation,grid);
            children[pos] = hex;
        }
        return hex;
    }

    coor get_position()
    {
        return my_pos;
    }

    ~hexagon()
    {
        if(parent != nullptr && my_index >= 0 && my_index < 5){
            parent->children[my_index] = nullptr;
        }
        for(int i = 0; i < max_children; i++)
        {
            if(children[i] != nullptr)
            {
                delete(children[i]);
            }
        }
        grid->erase(my_pos);
    }
    
};
