#ifndef MESH_H
#define MESH_H

#include <QGLWidget>
#include <string>
#include<stdio.h>
#include<stdlib.h>
#include <map>
#include <math.h>
#include<iostream>
#include<queue>
#include "vertex.h"
#include "face.h"
#include "gradient.h"


using namespace std;

// Advice => You should create a new file for each module but not necessarily for each class

class It_on_faces;
class It_on_vertices;
class cir_on_faces;
class cir_on_vertices;

class Mesh
{
    friend class It_on_faces;
    friend class cir_on_faces;
    friend class It_on_vertices;
    friend class cir_on_vertices;

    protected:
        int _n_vertex; // number of vertex
        int _n_face; // number of face
        int _n_edge = 0;// number of edge
        int _lap_computed = 0; // 0 : doesn't compute laplacien; 1: laplacien computed

        QVector<Vertex> vertexTab; // Vertex table
        QVector<Face> faceTab; // Triangle table
        queue<tuple<int,int,int,int>> edge_queue; // stock edges need to be flipped
        //tuple<v0,v1,f0,f1> v0,v1 is the edge; f0 the incident face; f1 the adjacent face.

        QVector<int> loc_queue2; // queue applied to locate the position of a point in the mesh
        queue<pair<int,int>> loc_queue;
        Vertex test_for_loc; // the point for the location test
    public:
        Mesh();
        void load_Mesh(const char file_name[]);
        void drawMesh() const;
        void drawMeshWireFrame()const;
        void draw_cir(); // test for circulator
        void draw_atta()const; // test the attachement of the mesh
        void drawMesh2D()const;
        void drawMeshWireFrame2D();// draw 2d lines
        void drawMeshCurvature(); // draw the mesh curvature
        void drawVoronoi(); // voronoi plot

        double cal_aera(Face &f); // calculate the area of a triangle

        // given a face object and a int number (0 or 1 or 2)
        // means the cot of vertex v0 or v1 or v2
        double cal_cot(Face &f,int k);// calculate cotangente

        void cal_lap(void); // calculate laplacien
        void cal_courbure(void); // calculate courbure



    //get info
        void info(void) const;
   //information about laplacien
        void info_lap(void) const;

    // Iterator method
        It_on_faces faces_begin();
        It_on_faces faces_end();
        It_on_vertices vertex_begin();
        It_on_vertices vertex_end();

        cir_on_faces faces_begin_circle(Vertex& v);
        cir_on_faces faces_end_circle(Vertex& v);
        cir_on_vertices vertex_begin_circle(Vertex& v);
        cir_on_vertices vertex_end_circle(Vertex& v);

        void _test_iterators(void);

     // TD4
        // test if a point in a triangle
        int triangle_test(Vertex &va,Vertex &vb, Vertex &vc,Vertex &vp);

        // test orientation of three points
        int orientation_test(Vertex &va,Vertex &vb,Vertex &vc);

        // test the order of two points in a triangle
        int orientation_test2(int va,int vb, int index_to_face);

        // test if a point lies on the circumscribed circle of the triangle
        // index_to_face : incident face
        // index_edge the edge we want to test annd we use it to find the fourth point.
        int in_circle_test(int index_to_face,int index_edge);

        // create a map that contains all the boundary edge
        //map<pair<_,index_to_face>,pair<v0,v1>>
        map<pair<int,int>,pair<int,int>> boundary_map(void);

        // split a triangle to three
        // mode = 0 : split a triangle to three
        // mode = 1 : add three edge to the flip_edge_queue
        void split_triangle(int index_point,int index_to_face,int mode=0);

        // if a point is outside the mesh, we use this function to add the point
        void outside_point(int index_point,map<pair<int,int>,pair<int,int>> M);

        // create a primary mesh from a set of points
        void create_mesh(const char file_name[]);

        // if a point is in the edge of a triangle, we use this function to add the point
        void boundary_point(int index_point, int index_to_face,int index_edge);

        // test if a edge is the edge of a given triangle
        int test_edge_in_face(int v0,int v1, int index_to_face);

        // calculate the angle of three points
        float cal_angle(Vertex &va,Vertex &vp,Vertex &vb);

        // flip the edge (we need two points(edge) and the triangle of the edge)
        void flip_edge(int v0,int v1, int index_to_face);



        void initial_edge_queue(); // Initialize edges needed to be flipped ( not pass loc delaunay test)

        void test_flip(); // lawson algo(flip all edges)


        void create_mesh_plot(void);// create new mesh from a set of points


        void local_del_test(int index_to_face);// another version to flip edge


        // incremental Delaunay insertion
        void incremental_delaunay_insertion(Vertex &vp); // vp is the point we want to add
        void test_incre_delaunay(); //



        // for the point location
        queue<pair<int,int>> location_point(Vertex &vp);// create a queue which contain the path to the target point
        //pair<index_to_face, index represent the situation>

        pair<int,int> location_one_face(int index_to_face,int indice,Vertex &vp);
        // indice represent which edge have beed already tested

        void test_location_point();// call the location_point to add the element to the loc_queue2.
        int index_loc_point(Vertex &vp); // return the index of the face which contain the target point
        void draw_location(); // draw location point and the path to the point



};

class It_on_faces
{

protected:
    Mesh& _mesh;
    int _current_pos;

public :
    // Initialization
    It_on_faces(Mesh& mesh,int pos=0);
    // Overwrite operator
    It_on_faces& operator++(void);
    Face& operator*(void);
    Face* operator->(void);
    bool operator==(It_on_faces other);
    bool operator!=(It_on_faces other);

};

class cir_on_faces
{
protected:
    Mesh& _mesh;
    Vertex& _vertex;
    int _current_face;
    int _nb_lap;
public:
   // initialization
    cir_on_faces(Mesh& mesh, Vertex& vertex,int nb_lap = 0);
   // overwrite operators
    cir_on_faces& operator++ (void);
    Face& operator*(void);
    Face* operator->(void);
    bool operator==(cir_on_faces other);
    bool operator!=(cir_on_faces other);
};

class It_on_vertices
{
public:
    It_on_vertices(Mesh& mesh,int pos =0);
    It_on_vertices& operator++(void);
    It_on_vertices operator++(int);
    bool operator==(It_on_vertices other);
    bool operator!=(It_on_vertices other);
    Vertex& operator*(void);
    Vertex* operator->(void);
protected:
    Mesh& _mesh;
    int _current_pos;
};

class cir_on_vertices :public cir_on_faces
{
public:
    cir_on_vertices(Mesh& mesh, Vertex& vertex,int nb_lap=0);
    Vertex& operator*(void);
    Vertex* operator->(void);
};


#endif // MESH_H
