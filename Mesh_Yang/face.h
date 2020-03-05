#ifndef FACE_H
#define FACE_H
#include <string>
#include<stdio.h>
#include <math.h>
#include<vertex.h>
#include<iostream>
using namespace std;
class Face
{
public:
    int to_vertices[3]; //index to a vertex
    int to_faces[3];// index to a face
    double _courbure = 0;
    //Initialization
    Face(); // initial all index equal -1 that represent not konwn
    Face(int vertices_[3]);
    Face(int vertices_[3], int faces_[3]);
    Face(Face const&);

    Vertex circle_center;

    //Get
    void info(void) const;
    void cal_circle_center();

};


#endif // FACE_H
