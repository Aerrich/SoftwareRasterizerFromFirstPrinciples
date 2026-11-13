//
// Created by erikz on 18.07.2026.
//

#ifndef SOFTWARERASTERIZERFROMFIRSTPRINCIPLE_OBJECT_HH
#define SOFTWARERASTERIZERFROMFIRSTPRINCIPLE_OBJECT_HH
#include <string>
#include <vector>

#include "Math.hh"

class Mesh
{

public:
    Mesh(std::string path);

    std::string toString();



private:
    std::vector<Vec3<float>> Vertices;
    std::vector<Vec3<int>> Faces;

};


#endif //SOFTWARERASTERIZERFROMFIRSTPRINCIPLE_OBJECT_HH
