#include <cstdlib>
#include <iostream>

#include <cruthu/cruthu.hpp>

int main(int argc, char * argv[]) {
    cruthu::Version();

    size_t world_size(40075000);
    
    // cruthu::Cruthu dev = cruthu::Cruthu(world_size);
    // dev.GenerateWorld();

    // cruthu::voxel::Block *** temp = dev.GetWorld();

    // int flat_map[world_size][world_size];

    // for(auto x = 0; x < world_size; ++x) {
    // 	for(auto y = 0; y < world_size; ++y) {
    // 		int sum = 0;
    // 		for(auto z = 0; z < world_size; ++z) {
    // 			sum += (temp[x][y][z].IsActive()) ? 0 : 1;
    // 		}
    // 		int color = 255 - sum;
    // 		std::cout << "\033[38;5;" << color <<"m\u25A0\033[39m ";
    // 	}
    // 	std::cout << std::endl;

    // }

    return EXIT_SUCCESS;
}
