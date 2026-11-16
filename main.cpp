#define UNICODE

#include <format>
#include <iostream>
#include "Mesh.hh"
#include "Window.hh"
#include "Camera.hh"
#include <vector>
#include "Object.hh"

int main() {
    SR::Window window{1080, 720};

    for (int x = 0; x < window.getWidth(); x++)
    {
        for (int y = 0; y < window.getHeight(); y++)
        {
            window.putPixel(x,y,0,0,255);
        }
    }

    std::vector<Object> objects;

    Mesh cube("Cube.obj");

    Object cube1(cube);

    objects.push_back(cube1);



    Camera camera{{0,0,-5}, {0,0,1}, {0,1,0}};

    Mat4<float> viewMatrix = camera.getViewMatrix();
    Mat4<float> projectionMatrix = camera.getProjectionMatrix();

    for (Object& obj : objects) {
        std::vector<Vec4<float>> transformedVertices;
        std::vector<Vec3<int>> faces;
        transformedVertices.reserve(obj.getMesh().getVertices().size());

        Mat4<float> mvp = projectionMatrix * viewMatrix * obj.getTransform();

        for (const Vec3<float>& vertex : obj.getMesh().getVertices()) {
            Vec4<float> tVertex = mvp * Vec4<float>(vertex, 1.0f);
            transformedVertices.push_back(tVertex);
            std::cout << tVertex.x << " " << tVertex.y << " " << tVertex.z << " " << tVertex.w << std::endl;
        }

        // Clip triangles using transformedVertices
        for (const Vec3<int>& face: obj.getMesh().getFaces()) {
            if (!(transformedVertices.at(face.x).z > camera.getFarPlane()
                || transformedVertices.at(face.y).z > camera.getFarPlane()
                || transformedVertices.at(face.z).z > camera.getFarPlane()
                || transformedVertices.at(face.x).z < 0
                || transformedVertices.at(face.y).z < 0
                || transformedVertices.at(face.z).z < 0))
            {

                faces.push_back(face);

            }
        }

        std::cout << faces.size() << std::endl;

        // Perspective division
        for (Vec4<float>& vertex : transformedVertices) {
            vertex = vertex / vertex.w;
            std::cout << vertex.x << " " << vertex.y << " " << vertex.z << " " << vertex.w << std::endl;
        }


        // Viewport transformation
        // Rasterization
        for (Vec3<int>& face : faces) {
            //get Bounding box
            //for every pixel in BB check if it is inside face
            //if it is inside face check depth and update buffer if necessary
            
        }


    }

    window.putPixel(20,20,0,255,0);

    char r = 0;
    char g = 0;
    char b = 0;

    while (window.processEvents())
    {

        window.redraw();

    }

    window.close();

    return 0;

}
