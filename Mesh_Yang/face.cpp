#include "face.h"

//Initialization
Face::Face()
{
    for (int k = 0; k < 3; k++)
    {
        to_vertices[k] = -1;
        to_faces[k] = -1;
    };
};
Face::Face(int vertices_[3])
{

    for (int k = 0; k < 3; k++)
    {
        to_vertices[k] = vertices_[k];
        to_faces[k] = -1;

    };
};
Face::Face(int vertices_[3], int faces_[3])
{

    for (int k = 0; k < 3; k++)
    {
        to_vertices[k] = vertices_[k];
        to_faces[k] = faces_[k];
    };
};
Face::Face(Face const& other)
{
    for (int k = 0; k < 3; k++)
    {

        to_faces[k] = other.to_faces[k];
        to_vertices[k] = other.to_vertices[k];
    };
};

//Get

void Face::info()const
{
    printf("--------------------\n");
    printf("Vertex Index : %d %d %d\n",to_vertices[0],to_vertices[1],to_vertices[2]);
    printf("Adjacent Face Index : %d %d %d\n",to_faces[0],to_faces[1],to_faces[2]);
    printf("end--------------------\n");
};
