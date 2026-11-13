//
// Created by erikz on 18.07.2026.
//

#include "Mesh.hh"

#include <fstream>
#include <iostream>
#include <sstream>


Mesh::Mesh(std::string path)
{

    std::ifstream ifs(path);

    if (!ifs) {
        throw std::runtime_error("Cannot open OBJ file: " + path);
    }

    std::string line;

    while (std::getline(ifs, line))
    {

        std::stringstream stream(line);

        std::string token;

        stream >> token;

        if (token == "v")
        {
            Vec3<float> v{};
            stream >> v.x >> v.y >> v.z;
            Vertices.push_back(v);
        }
        else if (token == "f")
        {
            Vec3<int> f{};
            stream >> f.x >> f.y >> f.z;
            Faces.push_back(f);
        }

    }

}


std::string Mesh::toString()
{

    std::ostringstream stream;
    for (const Vec3<float> &v : Vertices)
    {
        stream << v.x << " " << v.y << " " << v.z << std::endl;
    }

    return stream.str();

}
