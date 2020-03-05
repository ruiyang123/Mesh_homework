#include "mesh.h"


Mesh::Mesh(){
    char const file_name[]("..//off_files//teapot.off");
    test_for_loc.set_x(4.537200e-01);
    test_for_loc.set_y(2.716548e-01 );
    test_for_loc.set_z(-1.775901e-01);
    load_Mesh(file_name);

    //create_mesh(file_name);
    //info();

    //_test_iterators();
    //cal_lap();
    //info_lap();
    //cal_courbure();
};

void Mesh::load_Mesh(const char *file_name)
{
    vertexTab.clear();
    faceTab.clear();

    FILE *fp;
    fp = fopen(file_name,"r");
    if (fp==NULL)
    {
        cout<<"fail opening file\n";
    };
    rewind(fp);
    fscanf(fp, "%d %d %d\n", &_n_vertex, &_n_face,&_n_edge);
    printf("the Number of vertex |%d|\n",_n_vertex);
    printf("the Number of face |%d|\n", _n_face);
    printf("the Number of edge |%d|\n", _n_edge);

    double _x,_y,_z;

    for (int k=0;k<_n_vertex;k++)
    {
        fscanf(fp,"%lf %lf %lf\n", &_x,&_y,&_z);
        vertexTab.push_back(Vertex(_x,_y,_z));
    };

    int n_face =0 ,v0 = 0,v1 = 0,v2 = 0;
    int to_vertex[3];
    for (int k=0;k<_n_face;k++)
    {
        fscanf(fp,"%d %d %d %d\n", &n_face, &v0 ,&v1, &v2);
        to_vertex[0] = v0;
        to_vertex[1] = v1;
        to_vertex[2] = v2;
        faceTab.push_back(Face(to_vertex));
    };
    fclose(fp);

    // link a vertex to a face
    int _to_vertex[3];
    for(int k=0;k<_n_face;k++)
    {
        for(int i=0;i<3;i++)
        {
            _to_vertex[i] = faceTab[k].to_vertices[i];
        };
        for(int i=0;i<3;i++)
        {
            if(vertexTab[_to_vertex[i]].toFace()==-1)
            {
                vertexTab[_to_vertex[i]].set_toFace(k);
            };
        };

    };

    // link a face to 3 adjacent faces

    map<pair<int,int>,pair<int,int>> M;
    int va,vb;
    for (int k=0;k<_n_face;k++)
    {
        for(int i=0;i<3;i++)
        {   // ordre (0,1);(1,2);(2,0)
            va = faceTab[k].to_vertices[i];
            vb = faceTab[k].to_vertices[(i+1)%3];
            if (M.count({vb,va})>0)
            {
                faceTab[k].to_faces[(i+2)%3] = M[{vb,va}].first;
                faceTab[ M[{vb,va}].first].to_faces[M[{vb,va}].second] = k;
            }
            else
            {
                pair<int,int> key = {va,vb};
                M[key] = pair<int,int> {k,(i+2)%3};
            };

        };
    };


};




void Mesh::info()const
{
   printf("----information of Mesh-------\n");
   printf("the Number of vertex |%d|\t",_n_vertex);
   printf("the Number of face |%d|\t", _n_face);
   printf("the Number of edge |%d|\n", _n_edge);

   printf("-----info about vertices----\n");
   for(int i=0;i<_n_vertex;i++)
   {
       printf("cord of x |%lf|\t",vertexTab[i][0]);
       printf("cord of y |%lf|\t", vertexTab[i][1]);
       printf("cord of z |%lf|\t", vertexTab[i][2]);
       printf("index to face |%d|\n",vertexTab[i].toFace());
   };

   printf("-------info about Faces--------\n");
   for (int i=0;i<_n_face;i++)
   {   printf("face : |%d|\n",i);
       printf("index to v0 |%d|\t",faceTab[i].to_vertices[0]);
       printf("index to v1 |%d|\t",faceTab[i].to_vertices[1]);
       printf("index to v2 |%d|\t",faceTab[i].to_vertices[2]);
       printf("index to f0 |%d|\t",faceTab[i].to_faces[0]);
       printf("index to f1 |%d|\t",faceTab[i].to_faces[1]);
       printf("index to f2 |%d|\n",faceTab[i].to_faces[2]);
   };


};

void Mesh::info_lap(void) const
{
    printf("-----info about vertices----\n");
    for(int i=0;i<_n_vertex;i++)
    {
        printf("Vertex |%d|\t",i);
        printf("lap of x |%lf|\t", vertexTab[i].lap[0]);
        printf("lap of y |%lf|\t", vertexTab[i].lap[1]);
        printf("lap of z |%lf|\n", vertexTab[i].lap[2]);

    };


};



// Draw method
void glVertexDraw(const Vertex & v) {
    glVertex3f(v.x(), v.y(), v.z());
}
void glVertex2D(const Vertex & v) {
    glVertex3f(v.x(), v.y(), 0);
}
void glVertex_parabolic(const Vertex & v) {
    float z = v.x()*v.x()+ v.y()+v.y();
    glVertex3f(v.x(), v.y(), z);
}

void draw_circle(const Vertex & v){
    glColor4f(0,0,1,1);
     float radius = 0.005;
     double twicePi = 2.0 * 3.142;
     float x = v.x(), y = v.y();
     glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
     glVertex2f(x, y); // center of circle
     for (int i = 0; i <= 20; i++)   {
         glVertex2f (
             (x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20)))
             );
     }
     glEnd();
}

// Normal 3D mesh
void Mesh::drawMesh() const
{
    int i_color, iR, iG, iB;
    for(int i_triangle = 0; i_triangle <  _n_face; i_triangle++) {
        i_color = i_triangle % 6 +1;
        iR = i_color%2;
        iG = (i_color/2)%2;
        iB = (i_color/4)%2;
        glColor3d(iR, iG, iB);

        glBegin(GL_TRIANGLES);
       for (int k = 0; k < 3; k++)
        {
            glVertexDraw(vertexTab[faceTab[i_triangle].to_vertices[k]]);
       };
        glEnd();



    };
};


// Mesh 2D
void Mesh::drawMesh2D() const
{
    int i_color, iR, iG, iB;
    for(int i_triangle = 0; i_triangle <  _n_face; i_triangle++) {
        i_color = i_triangle % 6 +1;
        iR = i_color%2;
        iG = (i_color/2)%2;
        iB = (i_color/4)%2;
        glColor3d(iR, iG, iB);

        glBegin(GL_TRIANGLES);
        for (int k = 0; k < 3; k++)
        {
            glVertex2D(vertexTab[faceTab[i_triangle].to_vertices[k]]);
        };
        glEnd();
    };
};

// WireFrame 3D
void Mesh::drawMeshWireFrame() const
{

    glColor3d(0,1,0);
    for(int i_triangle = 0; i_triangle < _n_face; i_triangle++) {
        for (int k_line = 0; k_line < 3; k_line++)
        {
            glBegin(GL_LINE_STRIP);
            glVertexDraw(vertexTab[faceTab[i_triangle].to_vertices[k_line]]);
            glVertexDraw(vertexTab[faceTab[i_triangle].to_vertices[(k_line+1)%3]]);
            glEnd();
        }
    }
}

//Wire Frame 2D
void Mesh::drawMeshWireFrame2D()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3d(0,1,0);
    for(int i_triangle = 0; i_triangle < _n_face; i_triangle++) {
        for (int k_line = 0; k_line < 3; k_line++)
        {
            glBegin(GL_LINE_STRIP);
            glVertex2D(vertexTab[faceTab[i_triangle].to_vertices[k_line]]);
            glVertex2D(vertexTab[faceTab[i_triangle].to_vertices[(k_line+1)%3]]);
            glEnd();
        }
    }
    draw_circle(test_for_loc);
   // draw_circle(vertexTab[faceTab[0].to_vertices[0]]);
//draw_circle(vertexTab[faceTab[0].to_vertices[1]]);
//draw_circle(vertexTab[faceTab[0].to_vertices[2]]);


    //path for location point
if(!loc_queue2.empty())
{
    glColor4f(0.5,0.5,0,1);
    glBegin(GL_TRIANGLES);
    for (int j = 0; j < 3; j++)
    {
        glVertex2D(vertexTab[faceTab[loc_queue2[0]].to_vertices[j]]);
    };
    glEnd();

    glColor4f(1,0,0,0.5);

    for(int k=1;k<loc_queue2.size();k++) {
        glBegin(GL_TRIANGLES);
        for (int j = 0; j < 3; j++)
        {
            glVertex2D(vertexTab[faceTab[loc_queue2[k]].to_vertices[j]]);
        };
        glEnd();
    }}



}

// Test for the connexion triangle
void Mesh::draw_atta() const

{
   // printf("test\n");

   int index_to_face = 0;
   if(index_to_face>=_n_face)
   {
       index_to_face = rand()%_n_face;
   }

glColor3d(0,1,0);
glBegin(GL_TRIANGLES);
for(int i =0;i<3;i++){
    glVertexDraw(vertexTab[faceTab[index_to_face].to_vertices[i]]);
}


   for (int i_triangle = 0; i_triangle<3;i_triangle++){
       glColor3d(1,0,0);
       glBegin(GL_TRIANGLES);
       for(int k =0;k<3;k++)
       {
           glVertexDraw(vertexTab[faceTab[faceTab[index_to_face].to_faces[i_triangle]].to_vertices[k]]);
       };
       glEnd();

   };
};


// draw a circle
void Mesh::draw_cir()

{
    int index_to_vertex = 0;
    if(index_to_vertex>=_n_face)
    {
        index_to_vertex = rand()%_n_face;
    }

    It_on_vertices it = It_on_vertices(*this,index_to_vertex);
    //printf("%lf",(*it).x());
    int i_color,iR,iG,iB;
    int c =0;

    for(cir_on_faces cf=faces_begin_circle(*it);cf!=faces_end_circle(*it);++cf)
    {
        printf("Face : %d %d %d\n",(*cf).to_vertices[0],(*cf).to_vertices[1],(*cf).to_vertices[2]);
        i_color = c % 6 +1;
        iR = i_color%2;
        iG = (i_color/2)%2;
        iB = (i_color/4)%2;
        glColor3d(iR,iG,iB);
        glBegin(GL_TRIANGLES);
        for(int k=0;k<3;k++)
        {
            glVertexDraw(vertexTab[(*cf).to_vertices[k]]);
        };
        glEnd();
        c++;

    };


};



void Mesh::drawMeshCurvature()
{
    _n_vertex = vertexTab.size();
    _n_face = faceTab.size();
    printf("draw_curvature");
    cal_lap();
    double seuil = 0;
    for(int i_vertex = 0; i_vertex < _n_vertex; i_vertex++) {
        double value = abs(1./vertexTab[i_vertex].lap_norm());
        if (value > seuil) {seuil = value;}
    };
    seuil = 0.1;
    double iR, iG, iB;


     for (int k =0;k<_n_face;k++) {
        double courbure_ = 0;
        Vertex norm_vect;
        Vertex va = (vertexTab[faceTab[k].to_vertices[1]]-vertexTab[faceTab[k].to_vertices[0]]);
        Vertex vb = (vertexTab[faceTab[k].to_vertices[2]]-vertexTab[faceTab[k].to_vertices[0]]);
        Vertex v;
        norm_vect = prod(va,vb);
        norm_vect = (norm_vect/norm_vect.comp_norm());




        double value;
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < 3; i++)
        {
            v.set_x(vertexTab[faceTab[k].to_vertices[i]].lap[0]);
            v.set_y(vertexTab[faceTab[k].to_vertices[i]].lap[1]);
            v.set_z(vertexTab[faceTab[k].to_vertices[i]].lap[2]);


            if (dot(norm_vect, v) > 0)
            {
                value = 1/v.comp_norm()/seuil;
            }
            else
            {
                value = - 1/v.comp_norm()/seuil;
            }
            value = max(min(1.,value),-1.);
            value = value/2+0.5;


            cout<<courbure_/3<<"\n";
            iR = GradientRayon::red(value);
            iG = GradientRayon::green(value);
            iB = GradientRayon::blue(value);
            glColor3d(iR, iG, iB);
            glVertexDraw(vertexTab[faceTab[k].to_vertices[i]]);

        }
        glEnd();
    }
}
//Iterator Method
It_on_faces Mesh::faces_begin(){return It_on_faces(*this);};
It_on_faces Mesh::faces_end(){return It_on_faces(*this,_n_face);};
cir_on_faces Mesh::faces_begin_circle(Vertex &v)
{
  return cir_on_faces(*this,v);
};
cir_on_faces Mesh::faces_end_circle(Vertex &v)
{
  return cir_on_faces(*this,v,1);
};

It_on_vertices Mesh::vertex_begin(){return It_on_vertices(*this);};
It_on_vertices Mesh::vertex_end(){return It_on_vertices(*this,_n_vertex);};

cir_on_vertices Mesh::vertex_begin_circle(Vertex &v)
{return cir_on_vertices(*this,v);};
cir_on_vertices Mesh::vertex_end_circle(Vertex &v)
{return cir_on_vertices(*this,v,1);};

//it on face
It_on_faces::It_on_faces(Mesh& mesh,int pos):_mesh(mesh),_current_pos(pos){};
It_on_faces& It_on_faces::operator++(void)
{
  ++_current_pos;
    return(*this);
};
Face& It_on_faces::operator*(void)
{
  return _mesh.faceTab[_current_pos];
};
Face* It_on_faces::operator->(void)
{
    return &_mesh.faceTab[_current_pos];
};
bool It_on_faces::operator==(It_on_faces other)
{
    return (&_mesh == &other._mesh) && (_current_pos == other._current_pos);
};

bool It_on_faces::operator!=(It_on_faces other)
{
    return !(*this == other);
};

// cir on face
cir_on_faces::cir_on_faces(Mesh& mesh, Vertex& vertex,int nb_lab):
    _mesh(mesh),_vertex(vertex),_current_face(vertex.toFace()),_nb_lap(nb_lab){};
cir_on_faces& cir_on_faces::operator++(void)
{
    //anti-clockwise
    for (int k =0; k<3;k++)
    {
        if(&_mesh.vertexTab[_mesh.faceTab[_current_face].to_vertices[k]]==&_vertex)
        {
            _current_face = _mesh.faceTab[_current_face].to_faces[(k+1)%3];
            break;
        }
    }
    if(_current_face == _vertex.toFace()){++_nb_lap;}
    if(_current_face == -1){++_nb_lap;}
};

Face& cir_on_faces::operator*(void)
{
    return _mesh.faceTab[_current_face];
};
Face* cir_on_faces::operator->(void)
{
  return &_mesh.faceTab[_current_face];
};

bool cir_on_faces::operator==(cir_on_faces other)
{
    return (&_mesh == &other._mesh)
            &&(&_vertex == &other._vertex)
            &&(_current_face == other._current_face)
            && (_nb_lap == other._nb_lap);
};

bool cir_on_faces::operator!=(cir_on_faces other)
{
    return !(*this==other);
};

// It on vertices

It_on_vertices::It_on_vertices(Mesh& mesh,int current_pos):_mesh(mesh),_current_pos(current_pos){};
It_on_vertices& It_on_vertices::operator++(void)
{
    ++_current_pos;
    return(*this);
};

It_on_vertices It_on_vertices::operator++(int)
{
    It_on_vertices clone(*this);
    ++_current_pos;
    return clone;
};

bool It_on_vertices::operator==(It_on_vertices other)
{
    return (&_mesh == &other._mesh)&&(_current_pos == other._current_pos);
};
bool It_on_vertices::operator!=(It_on_vertices other)
{
    return !(*this == other);
};

Vertex& It_on_vertices::operator*(void)
{
    return _mesh.vertexTab[_current_pos];
};

Vertex* It_on_vertices::operator->(void)
{
    return &_mesh.vertexTab[_current_pos];
};


// cir on vertices

cir_on_vertices::cir_on_vertices(Mesh& mesh, Vertex& v,int n):cir_on_faces(mesh,v,n){};
Vertex& cir_on_vertices::operator*(void)
{
    for(int k=0;k<3;k++)
    {
        if(&_mesh.vertexTab[_mesh.faceTab[_current_face].to_vertices[k]]== &_vertex)
          {
            return _mesh.vertexTab[_mesh.faceTab[_current_face].to_vertices[(k+1)%3]];
        };
    }
};
Vertex* cir_on_vertices::operator->(void)
{
    for (int k =0; k<3;k++)
    {
        if(&_mesh.vertexTab[_mesh.faceTab[_current_face].to_vertices[k]]== &_vertex)
          {
            return &_mesh.vertexTab[_mesh.faceTab[_current_face].to_vertices[(k+1)%3]];
        };
    };
};

void Mesh::_test_iterators(void)
{
    int c = 0;
    for(It_on_vertices it = vertex_begin();it!=vertex_end();++it)
    {
        printf("Vertex  : %d\n",c);
        for(cir_on_faces cf=faces_begin_circle(*it);cf!=faces_end_circle(*it);++cf)
        {
            printf("Face : %d %d %d\n",(*cf).to_vertices[0],(*cf).to_vertices[1],(*cf).to_vertices[2]);
        }
        c++;
    }
    c = 0;
    for (It_on_vertices it = vertex_begin();it!=vertex_end();++it)
    {
        printf("vertex : %d\n",c);
        for(cir_on_vertices cv = vertex_begin_circle(*it);cv!=vertex_end_circle(*it);++cv)
        {
            printf("Adjacent : %lf %lf %lf\n",(*cv)[0],(*cv)[1],(*cv)[2]);
        };

    };
};



//Cal
double Mesh::cal_aera(Face &f)
{
    Vertex va = vertexTab[f.to_vertices[1]] - vertexTab[f.to_vertices[0]];
    Vertex vb = vertexTab[f.to_vertices[2]] - vertexTab[f.to_vertices[0]];

    double aera = prod(va,vb).comp_norm()/2;
    return aera;
};

double Mesh::cal_cot(Face &f, int k)
{
    Vertex va = vertexTab[f.to_vertices[(k+1)%3]] - vertexTab[f.to_vertices[k]];
    Vertex vb = vertexTab[f.to_vertices[(k+2)%3]] - vertexTab[f.to_vertices[k]];
    //cot = cos/sin
    double cos = dot(va,vb)/va.comp_norm()/vb.comp_norm();
    double sin = 2*cal_aera(f)/va.comp_norm()/vb.comp_norm();
    double cot = cos/sin;
    return cot;
};
void Mesh::cal_lap(void)
{

    if(_lap_computed == 0)

    {int n = 0; // index of the center point in this triangle
    Vertex va;
    Vertex vb;
    double cot_a;
    double cot_b;
    Vertex vt;

    for (It_on_vertices it = vertex_begin();it!=vertex_end();++it)
    {
        double aera = 0;
        vt.set_x(0);
        vt.set_y(0);
        vt.set_z(0);
        for (cir_on_faces cf = faces_begin_circle(*it);cf!=faces_end_circle(*it);++cf)
        {
            for(int k =0;k<3;k++)
            {
                if(&vertexTab[cf->to_vertices[k]] == &(*it))
                {
                    n = k;
                };
            };
            va.set_x(vertexTab[cf->to_vertices[(n+1)%3]][0]);
            va.set_y(vertexTab[cf->to_vertices[(n+1)%3]][1]);
            va.set_z(vertexTab[cf->to_vertices[(n+1)%3]][2]);

            vb.set_x(vertexTab[cf->to_vertices[(n+2)%3]][0]);
            vb.set_y(vertexTab[cf->to_vertices[(n+2)%3]][1]);
            vb.set_z(vertexTab[cf->to_vertices[(n+2)%3]][2]);

            cot_a = cal_cot(*cf,(n+1)%3);
            cot_b = cal_cot(*cf,(n+2)%3);
            vt += ((vb-(*it))*cot_a + (va-(*it))*cot_b);
            aera += (cal_aera(*cf)/3.);
            cout<<vt.x()<<"\n";



        };
        vt /= (2*aera);

        it->lap[0] = vt.x();
        it->lap[1] = vt.y();
        it->lap[2] = vt.z();


    };
    _lap_computed = 1;
    }

};

void Mesh::cal_courbure(void)
{
    for (int k =0;k<_n_face;k++)
    {   double courbure_ = 0;
        Vertex norm_vect;
        Vertex va = (vertexTab[faceTab[k].to_vertices[1]]-vertexTab[faceTab[k].to_vertices[0]]);
        Vertex vb = (vertexTab[faceTab[k].to_vertices[2]]-vertexTab[faceTab[k].to_vertices[0]]);
        Vertex v;
        norm_vect = prod(va,vb);
        norm_vect = (norm_vect/norm_vect.comp_norm());
        for(int i=0;i<3;i++)
        {
            v.set_x(vertexTab[faceTab[k].to_vertices[i]].lap[0]);
            v.set_y(vertexTab[faceTab[k].to_vertices[i]].lap[1]);
            v.set_z(vertexTab[faceTab[k].to_vertices[i]].lap[2]);

            courbure_ += 1/dot(v,norm_vect);
        };
        faceTab[k]._courbure =courbure_/3;
        cout<<courbure_/3<<"\n";
    };

};

//TD4
int Mesh::triangle_test(Vertex &va, Vertex &vb, Vertex &vc, Vertex &vp)
{
    float v0x = vc.x()-va.x();
    float v1x = vb.x()-va.x();
    float v2x = vp.x() - va.x();

    float v0y = vc.y()-va.y();
    float v1y = vb.y()-va.y();
    float v2y = vp.y() - va.y();

    float u = (v2x*v1y - v2y*v1x)/(v0x*v1y - v1x*v0y);
    float v = (v2x*v0y - v2y*v0x)/(v1x*v0y - v1y*v0x);

    if((u>0) and(v>0) and(u+v<1))
    {   cout<<"inside\n";
        return 1;} // inside
    else if(u==0)
    {   cout<<"boundary 0-1\n";
        return 2;} // boundary va->vb
    else if(v==0)
    {   cout<<"boundary 0-2\n";
        return 3;} // boundary va->vc
    else if(u+v==1)
    {   cout<<"boundary 1-2\n";
        return 4;}// boundary vb->vc
    else
    {   cout<<"ouside\n";
        return -1;} // outside
}
int Mesh::orientation_test(Vertex &va, Vertex &vb, Vertex &vc)
{
    float v0x = vc.x()-va.x();
    float v1x = vb.x()-va.x();

    float v0y = vc.y()-va.y();
    float v1y = vb.y()-va.y();

    float indice = v1x*v0y - v1y*v0x;
    cout<<"indice"<<indice<<"\n";
    if(indice > 0){return 1;}
    else if(indice ==0){return 0;}
    else{return -1;}
}


float Mesh::cal_angle(Vertex &va, Vertex &vp, Vertex &vb){
    float v0x = va.x()-vp.x();
    float v0y = va.y()-vp.y();
    float norm_1 = sqrt(v0x*v0x+v0y*v0y);

    float v1x = vb.x()-vp.x();
    float v1y = vb.y()-vp.y();
    float norm_2 = sqrt(v1x*v1x+v1y*v1y);

    float dot_ = v0x*v1x + v0y*v1y;
    float angle = acos(dot_/(norm_1*norm_2));
    return angle;

}
map<pair<int,int>,pair<int,int>> Mesh::boundary_map(void){
    cout<<"use boundary_map\n";
    //map<index_to_face,<edge>>
    map<pair<int,int>,pair<int,int>> M;
    int c = 0;
    int j =0;
    for(QVector<Face>::iterator iter = faceTab.begin();iter!=faceTab.end();iter++){
        for (int k=0;k<3;k++){
            if(iter->to_faces[k]==-1)
            {M[pair<int,int> {j,c}] = pair<int,int> {(k+1)%3,(k+2)%3};};
            j++;
        }
        c++;
    }

    map<pair<int,int>,pair<int,int>>:: iterator iter;
    for(iter = M.begin();iter!=M.end();iter++)
    {
        cout<<iter->first.second<<"\t"<<iter->second.first<<"\t"<<iter->second.second<<"\n";
    }


    return M;
};


void Mesh::split_triangle(int index_point,int index_to_face,int mode){
    int point_start,point_end,face_i,face_s;

    cout<<"use split triangle\n";
    cout<<"mode :"<<mode<<"\n";
    faceTab[index_to_face].info();
    int v0 = faceTab[index_to_face].to_vertices[0];
    int v1 = faceTab[index_to_face].to_vertices[1];
    int v2 = faceTab[index_to_face].to_vertices[2];

    int f0 = faceTab[index_to_face].to_faces[0];
    int f1 = faceTab[index_to_face].to_faces[1];
    int f2 = faceTab[index_to_face].to_faces[2];

    int length = faceTab.size();
   // cout<<length<<"\n";
    int index0 = index_to_face;
    int index1 = length;
    int index2 = length+1;

    int _to_vs[3],_to_fs[3];

// for the triangle v0->v1->vp

    faceTab[index_to_face].to_vertices[0] = v0;
    faceTab[index_to_face].to_vertices[1] = v1;
    faceTab[index_to_face].to_vertices[2] = index_point;

    faceTab[index_to_face].to_faces[0] = index1;
    faceTab[index_to_face].to_faces[1] = index2;
    faceTab[index_to_face].to_faces[2] = f2;
    if(f2!=-1){
        for(int k=0;k<3;k++){
            if(faceTab[f2].to_faces[k] == index_to_face){
                faceTab[f2].to_faces[k] = index0;
            }
        }
    }
    faceTab[index_to_face].info();

    // mis-a-jour index to face
    vertexTab[index_point].set_toFace(index_to_face);
    if(mode == 1 and f2!=-1 and in_circle_test(index_to_face,2)!=-1){
        point_start = v0;
        point_end = v1;
        face_i = index_to_face;
        face_s = f2;

        if(vertexTab[point_start].test_edge_link(point_start)!=1){

        edge_queue.push(tuple<int,int,int,int> (point_start,point_end,face_i,face_s));
        vertexTab[point_start].add_edge_link(point_start);
        vertexTab[point_end].add_edge_link(point_start);
    }
    }


    // for the triangle v1->v2->vp

        _to_vs[0] = v1;
        _to_vs[1] = v2;
        _to_vs[2] = index_point;

        _to_fs[0] = index2;
        _to_fs[1] = index0;
        _to_fs[2] = f0;

        faceTab.push_back(Face(_to_vs,_to_fs));

    if(f0!=-1){
            for(int k=0;k<3;k++){
                if(faceTab[f0].to_faces[k] == index_to_face){
                    faceTab[f0].to_faces[k] = index1;
                }
            }
        }
    faceTab[length].info();
    vertexTab[v2].set_toFace(length);

    if(mode == 1 and f0!=-1 and in_circle_test(length,2)!=-1){
        point_start = v1;
        point_end = v2;
        face_i = length;
        face_s = f0;

        if(vertexTab[point_start].test_edge_link(point_start)!=1){

        edge_queue.push(tuple<int,int,int,int> (point_start,point_end,face_i,face_s));
        vertexTab[point_start].add_edge_link(point_start);
        vertexTab[point_end].add_edge_link(point_start);
    }
    }



       // for the triangle v2->v0->vp

           _to_vs[0] = v2;
           _to_vs[1] = v0;
           _to_vs[2] = index_point;

           _to_fs[0] = index0;
           _to_fs[1] = index1;
           _to_fs[2] = f1;

           faceTab.push_back(Face(_to_vs,_to_fs));

           if(f1!=-1){
               for(int k=0;k<3;k++){
                   if(faceTab[f1].to_faces[k] == index_to_face){
                       faceTab[f1].to_faces[k] = index2;
                   }
               }
           }
           faceTab[length+1].info();

           if(mode == 1 and f1!=-1 and in_circle_test(length+1,2)!=-1){
               point_start = v2;
               point_end = v0;
               face_i = length+1;
               face_s = f1;

               if(vertexTab[point_start].test_edge_link(point_start)!=1){

               edge_queue.push(tuple<int,int,int,int> (point_start,point_end,face_i,face_s));
               vertexTab[point_start].add_edge_link(point_start);
               vertexTab[point_end].add_edge_link(point_start);
           }
           }


}

void Mesh::outside_point(int index_point, map<pair<int,int>, pair<int, int> > M){
    cout<<"use outside_point\n";

    map<pair<int,int>,pair<int,int>>:: iterator iter;
    //map<pair<_,index_to_face>,pair<v0,v1>(edge)>
    int _face_begin = faceTab.size();
    int c = 0;
    // triangle v1->v0->vp
    for(iter = M.begin();iter!=M.end();iter++)
    {
        int _to_vs[3],_to_fs[3];
        int v0 = iter->second.first;
        int v1 = iter->second.second;
        int i2f = iter->first.second;
        int indice = orientation_test(vertexTab[faceTab[i2f].to_vertices[v0]],vertexTab[faceTab[i2f].to_vertices[v1]],vertexTab[index_point]);
        if (indice==-1){
            c++;
            _to_vs[0] = faceTab[i2f].to_vertices[v1];
            _to_vs[1] = faceTab[i2f].to_vertices[v0];
            _to_vs[2] = index_point;
            _to_fs[0] = -1;
            _to_fs[1] = -1;
            _to_fs[2] = iter->first.second;
            faceTab.push_back(Face(_to_vs,_to_fs));

        }
    }
    vertexTab[index_point].set_toFace(_face_begin);
    // Link faces
    int _face_end = faceTab.size();
    map<pair<int,int>,pair<int,int>> M2;
    int va,vb;
    for (int k=0;k<_face_end;k++)
    {
        for(int i=0;i<3;i++)
        {   // ordre (0,1);(1,2);(2,0)
            va = faceTab[k].to_vertices[i];
            vb = faceTab[k].to_vertices[(i+1)%3];
            if (M2.count({vb,va})>0)
            {
                faceTab[k].to_faces[(i+2)%3] = M2[{vb,va}].first;
                faceTab[ M2[{vb,va}].first].to_faces[M2[{vb,va}].second] = k;
            }
            else
            {
                pair<int,int> key = {va,vb};
                M2[key] = pair<int,int> {k,(i+2)%3};
            };

        };
    };

}

// test if a edge is the edge of the given face
int Mesh::test_edge_in_face(int v0, int v1, int index_to_face){


    int va = faceTab[index_to_face].to_vertices[0];
    int vb = faceTab[index_to_face].to_vertices[1];
    int vc = faceTab[index_to_face].to_vertices[2];

    int s = 0;

    if(va==v0 or vb==v0 or vc==v0){s = s+1;};
    if(va==v1 or vb==v1 or vc==v1){s = s+1;};

    if(s==2){return 1;}
    else{return 0;}


}


void Mesh::boundary_point(int index_point, int index_to_face, int index_edge){
    cout<<"use boundary point\n";
    int length = faceTab.size();
    int _to_v[3];
    int _to_face[3];

    int v0 = faceTab[index_to_face].to_vertices[0];
    int v1 = faceTab[index_to_face].to_vertices[1];
    int v2 = faceTab[index_to_face].to_vertices[2];

    int f0 = faceTab[index_to_face].to_faces[0];
    int f1 = faceTab[index_to_face].to_faces[1];
    int f2 = faceTab[index_to_face].to_faces[2];
    vertexTab[index_point].set_toFace(index_to_face);

    if(index_edge == 2) // v0-v1
    {
        if(faceTab[index_to_face].to_faces[2]==-1)
        {
            faceTab[index_to_face].to_vertices[1] = index_point;
            faceTab[index_to_face].to_vertices[2] = v2;
            faceTab[index_to_face].to_faces[0] = length;

            _to_v[0] = v1;
            _to_v[1] = v2;
            _to_v[2] = index_point;

            _to_face[0] = index_to_face;
            _to_face[1] = f2;
            _to_face[2] = f0;
            faceTab.push_back(Face(_to_v,_to_face));

        }
        else{
            faceTab[index_to_face].to_vertices[1] = index_point;
            faceTab[index_to_face].to_vertices[2] = v2;
            faceTab[index_to_face].to_faces[0] = length;

            _to_v[0] = v1;
            _to_v[1] = v2;
            _to_v[2] = index_point;

            _to_face[0] = index_to_face;
            _to_face[1] = length+1;
            _to_face[2] = f0;
            faceTab.push_back(Face(_to_v,_to_face));



            for(int k=0;k<3;k++){
                if(faceTab[f2].to_vertices[k] == v1)
                {
                    int v0_f2 = v1;
                    int v1_f2 = faceTab[f2].to_vertices[(k+1)%3];
                    int v2_f2 = faceTab[f2].to_vertices[(k+2)%3];

                    int f0_f2 = faceTab[f2].to_faces[k];
                    int f1_f2 = faceTab[f2].to_faces[(k+1)%3];
                    int f2_f2 = faceTab[f2].to_faces[(k+2)%3];

                    faceTab[f2].to_vertices[0] = index_point;
                    faceTab[f2].to_vertices[1] = v1_f2;
                    faceTab[f2].to_vertices[2] = v2_f2;

                    faceTab[f2].to_faces[0] = f0_f2;
                    faceTab[f2].to_faces[1] = length+1;
                    faceTab[f2].to_faces[2] = index_to_face;

                    _to_v[0] = v0_f2;
                    _to_v[1] = index_point;
                    _to_v[2] = v2_f2;

                    _to_face[0] = f2;
                    _to_face[1] = f1_f2;
                    _to_face[2] = length;
                    faceTab.push_back(Face(_to_v,_to_face));
                    break;
                }
            }

        }
    }
    else if(index_edge == 3)//v2->v0
    {
        if(faceTab[index_to_face].to_faces[1]==-1)
        {

            faceTab[index_to_face].to_vertices[2] = index_point;
            faceTab[index_to_face].to_faces[0] = length;

            _to_v[0] = v1;
            _to_v[1] = v2;
            _to_v[2] = index_point;

            _to_face[0] = f1;
            _to_face[1] = index_to_face;
            _to_face[2] = f0;
            faceTab.push_back(Face(_to_v,_to_face));
        }
        else{
            faceTab[index_to_face].to_vertices[2] = index_point;
            faceTab[index_to_face].to_faces[0] = length;

            _to_v[0] = v1;
            _to_v[1] = v2;
            _to_v[2] = index_point;

            _to_face[0] = length+1;
            _to_face[1] = index_to_face;
            _to_face[2] = f0;
            faceTab.push_back(Face(_to_v,_to_face));

            for(int k=0;k<3;k++){
                if(faceTab[f1].to_vertices[k] == v0)
                {
                    int v0_f1 = v0;
                    int v1_f1 = faceTab[f1].to_vertices[(k+1)%3];
                    int v2_f1 = faceTab[f1].to_vertices[(k+2)%3];

                    int f0_f1 = faceTab[f1].to_faces[k];
                    int f1_f1 = faceTab[f1].to_faces[(k+1)%3];
                    int f2_f1 = faceTab[f1].to_faces[(k+2)%3];

                    faceTab[f1].to_vertices[0] = v0_f1;
                    faceTab[f1].to_vertices[1] = index_point;
                    faceTab[f1].to_vertices[2] = v2_f1;

                    faceTab[f1].to_faces[0] = length+1;
                    faceTab[f1].to_faces[1] = f1_f1;
                    faceTab[f1].to_faces[2] = index_to_face;

                    _to_v[0] = index_point;
                    _to_v[1] =  v1_f1;
                    _to_v[2] = v2_f1;

                    _to_face[0] = f0_f1;
                    _to_face[1] = f1;
                    _to_face[2] = length;
                    faceTab.push_back(Face(_to_v,_to_face));
                    break;
                }
            }
        }
    }

    else if(index_edge == 4)//v1->v2
    {

        if(faceTab[index_to_face].to_faces[0]==-1)
        {

            faceTab[index_to_face].to_vertices[2] = index_point;
            faceTab[index_to_face].to_faces[1] = length;

            _to_v[0] = v0;
            _to_v[1] = index_point;
            _to_v[2] = v2;

            _to_face[0] = f0;
            _to_face[1] = f1;
            _to_face[2] = index_to_face;
            faceTab.push_back(Face(_to_v,_to_face));
        }
        else{
            faceTab[index_to_face].to_vertices[2] = index_point;
            faceTab[index_to_face].to_faces[1] = length;

            _to_v[0] = v0;
            _to_v[1] = index_point;
            _to_v[2] = v2;

            _to_face[0] = length+1;
            _to_face[1] = f1;
            _to_face[2] = index_to_face;
            faceTab.push_back(Face(_to_v,_to_face));

            for(int k=0;k<3;k++){
                if(faceTab[f0].to_vertices[k] == v1)
                {
                    int v0_f0 = v1;
                    int v1_f0 = faceTab[f0].to_vertices[(k+1)%3];
                    int v2_f0 = faceTab[f0].to_vertices[(k+2)%3];

                    int f0_f0 = faceTab[f0].to_faces[k];
                    int f1_f0 = faceTab[f0].to_faces[(k+1)%3];
                    int f2_f0 = faceTab[f0].to_faces[(k+2)%3];

                    faceTab[f0].to_vertices[0] = v0_f0;
                    faceTab[f0].to_vertices[1] = v1_f0;
                    faceTab[f0].to_vertices[2] = index_point;

                    faceTab[f0].to_faces[0] = length+1;
                    faceTab[f0].to_faces[1] = index_to_face;
                    faceTab[f0].to_faces[2] = f2_f0;

                    _to_v[0] = index_point;
                    _to_v[1] =  v1_f0;
                    _to_v[2] = v2_f0;

                    _to_face[0] = f0_f0;
                    _to_face[1] = length;
                    _to_face[2] = f0;
                    faceTab.push_back(Face(_to_v,_to_face));
                    break;
                }
            }
        }
    }


}

// point v0, point v1 , incident face (orientation anti-clockwise)
void Mesh::flip_edge(int v0, int v1, int index_to_face){
    int fa = index_to_face;
    int index_edge;
    for (int k=0;k<3;k++)
    {
        if(faceTab[fa].to_vertices[k]==v0)
        {index_edge = (k+2)%3;}
    }
    int fb = faceTab[fa].to_faces[index_edge];

    int v2 = faceTab[fa].to_vertices[index_edge];

    int index_edge2;
    for(int k=0;k<3;k++)
    {
        if(faceTab[fb].to_vertices[k]==v1)
        { index_edge2 = (k+2)%3;}
    }

    int v3 = faceTab[fb].to_vertices[index_edge2];

    int f0 = faceTab[fa].to_faces[(index_edge+2)%3];
    int f1 = faceTab[fb].to_faces[(index_edge2+1)%3];
    int f2 = faceTab[fb].to_faces[(index_edge2+2)%3];
    int f3 = faceTab[fa].to_faces[(index_edge+1)%3];

    faceTab[fa].to_vertices[(index_edge+2)%3] = v3 ;
    faceTab[fa].to_vertices[index_edge] = v1;
    faceTab[fa].to_vertices[(index_edge+1)%3] = v2;
    faceTab[fa].to_faces[(index_edge+2)%3] = f3;
    faceTab[fa].to_faces[index_edge] = fb;
    faceTab[fa].to_faces[(index_edge+1)%3] = f2;

    faceTab[fb].to_vertices[index_edge2] = v0 ;
    faceTab[fb].to_vertices[(index_edge2+1)%3] = v3;
    faceTab[fb].to_vertices[(index_edge2+2)%3] = v2;
    faceTab[fb].to_faces[index_edge2] = fa;
    faceTab[fb].to_faces[(index_edge2+1)%3] = f0;
    faceTab[fb].to_faces[(index_edge2+2)%3] = f1;

    vertexTab[v0].set_toFace(fb);
    vertexTab[v1].set_toFace(fa);
    vertexTab[v2].set_toFace(fa);
    vertexTab[v3].set_toFace(fa);

    for(int k=0;k<3;k++){
        if(f2!=-1){
        if(faceTab[f2].to_vertices[k]==v1)
        {
            faceTab[f2].to_faces[(k+2)%3] = fa;
        }}

        if(f3!=-1){
        if(faceTab[f3].to_vertices[k]==v2)
        {
            faceTab[f3].to_faces[(k+2)%3] = fa;
        }}



        if(f0!=-1){
        if(faceTab[f0].to_vertices[k]==v0)
        {
            faceTab[f0].to_faces[(k+2)%3] = fb;
        }}

        if(f1!=-1){
        if(faceTab[f1].to_vertices[k]==v3)
        {
            faceTab[f1].to_faces[(k+2)%3] = fb;
        }}
    }




if(in_circle_test(fa,(index_edge+2)%3)!=-1 and vertexTab[v1].test_edge_link(v2)==0)
{
    edge_queue.push(tuple<int,int,int,int>(v1,v2,fa,f3));
    vertexTab[v1].add_edge_link(v2);
    vertexTab[v2].add_edge_link(v1);}

if(in_circle_test(fa,(index_edge+1)%3)!=-1 and vertexTab[v3].test_edge_link(v1)==0)
{edge_queue.push(tuple<int,int,int,int>(v3,v1,fa,f2));
    vertexTab[v3].add_edge_link(v1);
    vertexTab[v1].add_edge_link(v3);
}

if(in_circle_test(fb,(index_edge2+1)%3)!=-1 and vertexTab[v2].test_edge_link(v0)==0)
{edge_queue.push(tuple<int,int,int,int>(v2,v0,fb,f0));
    vertexTab[v0].add_edge_link(v2);
    vertexTab[v2].add_edge_link(v0);
}

if(in_circle_test(fb,(index_edge+2)%3)!=-1 and vertexTab[v0].test_edge_link(v3)==0)
{edge_queue.push(tuple<int,int,int,int>(v0,v3,fb,f1));

    vertexTab[v0].add_edge_link(v3);
    vertexTab[v3].add_edge_link(v0);}




}

// we don't know the orientation va,vb in the given face, we test if va->vb is anti-clockwise in the face
int Mesh::orientation_test2(int va, int vb, int index_to_face){

    for(int k =0;k<3;k++)
    {
        if(va == faceTab[index_to_face].to_vertices[k])
        {
            if(faceTab[index_to_face].to_vertices[(k+1)%3]==vb)
            {return 1;}
            else{return 0;}
        }
    }
}



void Mesh::initial_edge_queue(){
//tuple<v0,v1,f0,f1> v0,v1 is the edge; f0 the incident face; f1 the adjacent face.

    int v0;
    int v1;
    int f0;
    int f1;
    int indice = -1;
    for(int i=0;i<_n_face;i++)
    {
        f0 = i;
        for(int k=0;k<3;k++)
        {
            indice = in_circle_test(f0,k);
            if(indice!=-1){
                f1 = faceTab[f0].to_faces[k];
                v0 = faceTab[f0].to_vertices[(k+1)%3];
                v1 = faceTab[f0].to_vertices[(k+2)%3];
                if(vertexTab[v0].test_edge_link(v1)!=1){

                edge_queue.push(tuple<int,int,int,int> (v0,v1,f0,f1));
                vertexTab[v0].add_edge_link(v1);
                vertexTab[v1].add_edge_link(v0);}
            }

        }

    }
}


// lawson algo
void Mesh::test_flip(){
//tuple<v0,v1,f0,f1> v0,v1 is the edge; f0 the incident face; f1 the adjacent face.

    //for (int k=0;k<_n_face;k++){
      //  local_del_test(k);
    //}
while(!edge_queue.empty()){
    while(!edge_queue.empty()){


        tuple<int,int,int,int> e = edge_queue.front();
        int index;
        for(int k=0;k<3;k++){
        if(faceTab[get<2>(e)].to_vertices[k]==get<0>(e))
        {index = k;}
        }

        if(test_edge_in_face(get<0>(e),get<1>(e),get<2>(e))==1)
        {



            if(orientation_test2(get<0>(e),get<1>(e),get<2>(e))==1)

            {
                if(in_circle_test(get<2>(e),(index+2)%3)!=-1)
                {flip_edge(get<0>(e),get<1>(e),get<2>(e));}}

            else{

                if(in_circle_test(get<2>(e),(index+1)%3)!=-1)
                {flip_edge(get<1>(e),get<0>(e),get<2>(e));} }

        }
        else{
            if(test_edge_in_face(get<0>(e),get<1>(e),get<3>(e))==1)
            {
                if(orientation_test2(get<0>(e),get<1>(e),get<3>(e))==1)

            {    if(in_circle_test(get<3>(e),(index+2)%3)!=-1)
                    {flip_edge(get<0>(e),get<1>(e),get<3>(e));}
                }




            else{
                    if(in_circle_test(get<3>(e),(index+1)%3)!=-1)
                    {flip_edge(get<1>(e),get<0>(e),get<3>(e));}

                }
            }

        }
        vertexTab[get<0>(e)].delete_edge_link(get<1>(e));
        vertexTab[get<1>(e)].delete_edge_link(get<0>(e));
        edge_queue.pop();
    }
initial_edge_queue();}

}



// create a primary mesh
void Mesh::create_mesh(const char *file_name){
    vertexTab.clear();
    faceTab.clear();

    FILE *fp;
    fp = fopen(file_name,"r");
    if (fp==NULL)
    {
        cout<<"fail opening file\n";
    };
    rewind(fp);
    fscanf(fp, "%d %d %d\n", &_n_vertex, &_n_face,&_n_edge);
    printf("the Number of vertex |%d|\n",_n_vertex);
    printf("the Number of face |%d|\n", _n_face);
    printf("the Number of edge |%d|\n", _n_edge);

    double _x,_y,_z;

    // initialisation les trois premier triangles.
    for (int k=0;k<3;k++)
    {
        fscanf(fp,"%lf %lf %lf\n", &_x,&_y,&_z);
        vertexTab.push_back(Vertex(_x,_y,_z));
    };
    vertexTab[0].set_toFace(0);
    vertexTab[1].set_toFace(0);
    vertexTab[2].set_toFace(0);
    int to_vertex[3];
    int orient_test = orientation_test(vertexTab[0],vertexTab[1],vertexTab[2]);
    if (orient_test==1){
        to_vertex[0] = 0;
        to_vertex[1] = 1;
        to_vertex[2] = 2;
        faceTab.push_back(Face(to_vertex));
    }
    if (orient_test==-1){
        to_vertex[0] = 2;
        to_vertex[1] = 1;
        to_vertex[2] = 0;
        faceTab.push_back(Face(to_vertex));
    }

   // cout<<orient_test<<"\n";
    _n_face = faceTab.size();
    //cout<<_n_face<<"\n";
    int k_point = 3;
    for(int k=3;k<50;k++)
        {
            fscanf(fp,"%lf %lf %lf\n", &_x,&_y,&_z);
            Vertex vp =Vertex(_x,_y,_z);
            int i2f = -1;
            int _c = 0;
            int idex_tri_test=-1;
            for(QVector<Face>::iterator iter = faceTab.begin();iter!=faceTab.end();iter++){
                i2f = _c;
                idex_tri_test = triangle_test(vertexTab[iter->to_vertices[0]],vertexTab[iter->to_vertices[1]],vertexTab[iter->to_vertices[2]],vp);
                if(idex_tri_test!=-1){

                    break;
                }

                _c++;
            }
           // cout<<idex_tri_test<<"\n";
            //cout<<i2f<<"\n";

            if(idex_tri_test ==1)
            {   vertexTab.push_back(Vertex(_x,_y,_z));

                split_triangle(k_point,i2f);
                k_point++;
              //  cout<<k_point<<'\n';
                }
            else if(idex_tri_test == -1)
            {   vertexTab.push_back(vp);
                outside_point(k_point,boundary_map());
                k_point++;
            }
            else{
                vertexTab.push_back(vp);
                boundary_point(k_point,i2f,idex_tri_test);
                k_point++;

            }

         }
    _n_vertex = vertexTab.size();
    _n_face = faceTab.size();
    printf("vertex : |%d| ; face: |%d|\n",_n_vertex,_n_vertex);
    //test_flip(100);
   // flip_edge_tot( flip_edge_map());
    //flip_edge_tot( flip_edge_map());
   // flip_edge_tot( flip_edge_map());
    //flip_edge_tot( flip_edge_map());
    initial_edge_queue();

}
void Mesh::create_mesh_plot(void){
     char const file_name[]("..//off_files//franke4.off");
     create_mesh(file_name);
     drawMesh();
     info();


}



//
int Mesh::in_circle_test(int index_to_face, int index_edge){
    // index_to_face : the index to the incident triangle
    // the edge need test. if -1 : no edge.

    int fp = faceTab[index_to_face].to_faces[index_edge];
    if(fp==-1){return -1;}

    int v0 = faceTab[index_to_face].to_vertices[0];
    int v1 = faceTab[index_to_face].to_vertices[1];
    int v2 = faceTab[index_to_face].to_vertices[2];

    int vp;

    for (int k=0;k<3;k++)
    {
        if(faceTab[fp].to_vertices[k]==faceTab[index_to_face].to_vertices[(index_edge+2)%3])
        {
            vp = faceTab[fp].to_vertices[(k+2)%3];
        }

    }

    float px = vertexTab[v0].x();
    float py = vertexTab[v0].y();
    float qx = vertexTab[v1].x();
    float qy = vertexTab[v1].y();
    float rx = vertexTab[v2].x();
    float ry = vertexTab[v2].y();
    float sx = vertexTab[vp].x();
    float sy = vertexTab[vp].y();

    float a = (qx-px)*((ry-py)*((sx-px)*(sx-px)+(sy-py)*(sy-py)) - (sy-py)*((rx-px)*(rx-px)+(ry-py)*(ry-py))) ;
    float b = -(qy-py)*((rx-px)*((sx-px)*(sx-px)+(sy-py)*(sy-py)) - (sx-px)*((rx-px)*(rx-px)+(ry-py)*(ry-py))) ;
    float c = ((qx-px)*(qx-px)+(qy-py)*(qy-py))*((rx-px)*(sy-py)-(sx-px)*(ry-py));

    if(-(a+b+c)<=0)
    {return -1;}
        else{return 1;}

}

void Mesh::local_del_test(int index_to_face){
    int indice = -1;
    for(int k =0;k<3;k++){
        indice = in_circle_test(index_to_face,k);
        if (indice!=-1){

            flip_edge(faceTab[index_to_face].to_vertices[(k+1)%3],faceTab[index_to_face].to_vertices[(k+2)%3],index_to_face);
        }

    }
}


queue<pair<int,int>> Mesh::location_point(Vertex &vp){
    queue<pair<int,int>> q1;
    queue<pair<int,int>> q2;

    q1.push(pair<int,int>{0,-1});
    pair<int,int> l = q1.back();
    while(l.first!=-1)
    {
        pair<int,int> e = q1.front();
        q2.push(e);
        q1.pop();
        q1.push(location_one_face(e.first,e.second,vp));
        l = q1.back();
    }
    return q2;
}



pair<int,int> Mesh::location_one_face(int index_to_face, int indice, Vertex &vp){


    int v0 = faceTab[index_to_face].to_vertices[0];
    int v1 = faceTab[index_to_face].to_vertices[1];
    int v2 = faceTab[index_to_face].to_vertices[2];
    int f0 = faceTab[index_to_face].to_faces[0];
    int f1 = faceTab[index_to_face].to_faces[1];
    int f2 = faceTab[index_to_face].to_faces[2];


    if(triangle_test(vertexTab[v0],vertexTab[v1],vertexTab[v2],vp)!=-1)
    {
        return pair<int,int> {-1,-1};
    }

    int index_v3 = -1;
    if(f1==-1)
    {index_v3 = -1;}
    else{
        for(int k =0;k<3;k++)
        {if (faceTab[f1].to_vertices[k]==v0)
        {index_v3 = (k+2)%3;}
        }

    }

    int index_v4 = -1;
    if(f2==-1)
    {index_v4 = -1;}
    else{
        for(int k =0;k<3;k++)
        {if (faceTab[f2].to_vertices[k]==v1)
        {index_v4 = (k+2)%3;}
        }

    }

    int index_v5 = -1;
    if(f0==-1)
    {index_v5 = -1;}
    else{
        for(int k =0;k<3;k++)
        {if (faceTab[f0].to_vertices[k]==v2)
        {index_v5 = (k+2)%3;}
        }

    }



    if(indice==-1)
    {
        if(orientation_test(vertexTab[v1],vertexTab[v2],vp)<=0 and f0!=-1)
        {return pair<int,int> {f0,index_v5};}

        if(orientation_test(vertexTab[v2],vertexTab[v0],vp)<=0 and f1!=-1)
        {return pair<int,int> {f1,index_v3};}

        if(orientation_test(vertexTab[v0],vertexTab[v1],vp)<=0 and f2!=-1)
        {return pair<int,int> {f2,index_v4};}

    }

    if (indice==0)
    {

        if(orientation_test(vertexTab[v2],vertexTab[v0],vp)<0 and f1!=-1)
        {return pair<int,int> {f1,index_v3};}

        if(orientation_test(vertexTab[v0],vertexTab[v1],vp)<0 and f2!=-1)
        {return pair<int,int> {f2,index_v4};}

    }

    if (indice==1)
    {

        if(orientation_test(vertexTab[v1],vertexTab[v2],vp)<0 and f0!=-1)
        {return pair<int,int> {f0,index_v5};}


        if(orientation_test(vertexTab[v0],vertexTab[v1],vp)<0 and f2!=-1)
        {return pair<int,int> {f2,index_v4};}
    }

    if (indice==2)
    {
        if(orientation_test(vertexTab[v1],vertexTab[v2],vp)<0 and f0!=-1)
        {return pair<int,int> {f0,index_v5};}

        if(orientation_test(vertexTab[v2],vertexTab[v0],vp)<0 and f1!=-1)
        {return pair<int,int> {f1,index_v3};}

    }

    return pair<int,int> {-1,-1};


}


void Mesh::test_location_point(){

    test_for_loc.set_x(4.537200e-01);
    test_for_loc.set_y(2.716548e-01 );
    test_for_loc.set_z(-1.775901e-01);
    loc_queue = location_point(test_for_loc);
    while(!loc_queue.empty())
    {
        pair<int,int> e = loc_queue.front();
        printf("loc face : |%d|\n",e.first);
        int a = triangle_test(vertexTab[faceTab[e.first].to_vertices[0]],vertexTab[faceTab[e.first].to_vertices[1]],vertexTab[faceTab[e.first].to_vertices[2]],test_for_loc);
        printf("indice : |%d|\n",a);
        loc_queue2.push_back(e.first);
        loc_queue.pop();
    }


}

int Mesh::index_loc_point(Vertex &vp){


    loc_queue = location_point(vp);
    int index;
    while(!loc_queue.empty())
    {
        pair<int,int> e = loc_queue.front();
        printf("loc face : |%d|\n",e.first);
        int a = triangle_test(vertexTab[faceTab[e.first].to_vertices[0]],vertexTab[faceTab[e.first].to_vertices[1]],vertexTab[faceTab[e.first].to_vertices[2]],test_for_loc);
        printf("indice : |%d|\n",a);
        index = e.first;
        loc_queue.pop();
    }

    return index;
}


void Mesh::incremental_delaunay_insertion(Vertex &vp)
{
    int index_to_face = index_loc_point(vp);
    vertexTab.push_back(vp);
    _n_vertex = vertexTab.size();
    split_triangle(_n_vertex-1,index_to_face,1);
    while(!edge_queue.empty())
    {test_flip();}
}

void Mesh::test_incre_delaunay(){

   cout<<"test_incre_delaunay"<<"\n";
    test_for_loc.set_x(4.537200e-01);
    test_for_loc.set_y(2.716548e-01 );
    test_for_loc.set_z(-1.775901e-01);

    incremental_delaunay_insertion(test_for_loc);


}
