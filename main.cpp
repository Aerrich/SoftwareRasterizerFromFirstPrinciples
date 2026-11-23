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



    Mesh cube("Cube.obj");

    Object cube1(cube);



    while (window.processEvents())
    {


        for (int i = 0; i < window.getWidth(); i++) {
            for (int j = 0; j < window.getHeight(); j++) {
                window.putPixel(i,j,0,0,0);
            }
        }

        for (int i = 0; i < window.getWidth(); i++) {
            for (int j = 0; j < window.getHeight(); j++) {
                window.setDepth(i, j, std::numeric_limits<float>::max());
            }
        }

        float angle = 0.1f * 360.0f / 2.0f * 3.14f;

        cube1.transform(
            {
                {
                    {std::cos(angle), 0, std::sin(angle), 0},
                    {0, 1, 0, 0},
                    {-std::sin(angle), 0, std::cos(angle), 0},
                    {0, 0, 0, 1}
                }
            }
        );

        std::vector<Object> objects;
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
                //std::cout << tVertex.x << " " << tVertex.y << " " << tVertex.z << " " << tVertex.w << std::endl;
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

            // Perspective division
            for (Vec4<float>& vertex : transformedVertices) {
                vertex = vertex / vertex.w;

            }

            //transform into screen coords
            for (Vec4<float>& vertex : transformedVertices) {
                vertex.x = (vertex.x + 1.0f) / 2.0f * static_cast<float>(window.getWidth()) - 1.0f;
                vertex.y = (vertex.y + 1.0f) / 2.0f * static_cast<float>(window.getHeight()) - 1.0f;
                //std::cout << vertex.x << " " << vertex.y << " " << vertex.z << " " << vertex.w << std::endl;
            }

            // Viewport transformation
            // Rasterization

            unsigned char g = 0;

            for (Vec3<int>& face : faces) {

                g = (g + 32) % 256;

                //get Bounding box
                Vec4<float>& v1 = transformedVertices.at(face.x);
                Vec4<float>& v2 = transformedVertices.at(face.y);
                Vec4<float>& v3 = transformedVertices.at(face.z);
                float minX = std::min({v1.x, v2.x, v3.x});
                float maxX = std::max({v1.x, v2.x, v3.x});
                float minY = std::min({v1.y, v2.y, v3.y});
                float maxY = std::max({v1.y, v2.y, v3.y});
                //for every pixel in BB check if it is inside face
                //if it is inside face check depth and update buffer if necessary
                for (int x = std::max(static_cast<int>(minX),0); x < std::min(static_cast<int>(maxX), window.getWidth()); x++) {
                    for (int y = std::max(static_cast<int>(minY),0); y < std::min(static_cast<int>(maxY), window.getWidth()); y++) {
                        //if inside triangle put pixel
                        Vec2<float> ab = {v2.x - v1.x, v2.y - v1.y};
                        Vec2<float> ac = {v3.x - v1.x, v3.y - v1.y};
                        Vec2<float> a = {v1.x, v1.y};

                        Mat2<float> A = {
                            {
                                {ab.x, ac.x},
                                {ab.y, ac.y}
                            }
                        };
                        float detA = A[0][0] * A[1][1] - A[0][1] * A[1][0];

                        Mat2<float> A1 = {
                            {
                                {x - a.x, ac.x},
                                {y - a.y, ac.y}
                            }
                        };
                        float detA1 = A1[0][0] * A1[1][1] - A1[0][1] * A1[1][0];

                        Mat2<float> A2 = {
                            {
                                {ab.x, x - a.x},
                                {ab.y, y - a.y}
                            }
                        };
                        float detA2 = A2[0][0] * A2[1][1] - A2[0][1] * A2[1][0];


                        float beta = detA1 / detA;
                        float gamma = detA2 / detA;
                        float alpha = 1 - beta - gamma;

                        float depth = alpha * v1.z + beta * v2.z + gamma * v3.z;

                        if (alpha >= 0 && beta >= 0 && gamma >= 0 && depth < window.getDepth(x,y)) {
                            window.putPixel(x,y,0,g,0);
                            window.setDepth(x,y,depth);
                        }

                    }
                }

            }


        }



        window.redraw();

    }

    window.close();

    return 0;

}
