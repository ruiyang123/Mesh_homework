#ifndef VERTEX_H
#define VERTEX_H
#include<iostream>
#include <string>
#include<stdio.h>
#include<stdlib.h>
#include<map>
#include <math.h>

using namespace std;
class Vertex
{

protected:
    double _cord[3];
    int to_face = -1;

public:
    //Initialization
    Vertex();
    Vertex(float k_);
    Vertex(float x_, float y_, float z_);

    // laplacien
    double lap[3] = {0.,0.,0.};

    // Map to mark the non-delaunay edge
    map<int,int> edge_map;


    //Get
    double x()const { return _cord[0]; };
    double y()const { return _cord[1]; };
    double z()const { return _cord[2]; };
    int toFace()const{return to_face;};
    void info(void)const;
    int test_edge_link(int vp){
        if(edge_map.count(vp)>0){return 1;}
        else{return 0;}
    };

    //Set
    void set_x(const float x_){_cord[0] = x_;};
    void set_y(const float y_){_cord[1] = y_;};
    void set_z(const float z_){_cord[2] = z_;};
    void set_toFace(const int to_face_){to_face = to_face_;};
    void add_edge_link(int vp){
        edge_map[vp] = 1;
    }
    void delete_edge_link(int vp){
        edge_map.erase(vp);
    }



    //overwrite index method
    double operator[](int i) const;
    double& operator[](int i);


    // Calcul
    double comp_norm(void) const;
    double lap_norm(void) ;
    friend double dot(const Vertex&, const Vertex&);
    friend Vertex prod(const Vertex&, const Vertex&);

    // overwrite operator
    Vertex& operator+=(const Vertex&);
    Vertex& operator-=(const Vertex&);
    Vertex& operator/=(const double&);
    Vertex& operator*=(const double&);

    Vertex operator+(const Vertex&);
    Vertex operator-(const Vertex&);
    Vertex operator*(const double&);
    Vertex operator/(const double&);
    Vertex operator=(const Vertex&);
};




#endif // VERTEX_H
