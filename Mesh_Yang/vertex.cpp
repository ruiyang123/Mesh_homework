#include "vertex.h"

// Initialization
Vertex::Vertex()
{
    for (int k = 0; k < 3; k++)
    {
        _cord[k] = 0;
    };
};
Vertex::Vertex(float k_)
{
    for (int k=0;k<3;k++)
    {
        _cord[k] = k_;
    };
};
Vertex::Vertex(float x_, float y_, float z_)
{
    _cord[0] = x_;
    _cord[1] = y_;
    _cord[2] = z_;
};

// Get
void Vertex::info() const
{
    cout << "-----------------------------" << "\n";
    cout << "Information about the Point" << "\n";
    cout << "x,y,z : " << _cord[0]<<", "<<_cord[1]<<", "<<_cord[2]<<"" << "\n";
    cout << "Index to Face: " << to_face << "\n";
    cout << "norm:  " << comp_norm() << "\n";
    cout << "end------------------------" << "\n";
};

//Cal
double Vertex::comp_norm() const
{
    double val_norm = 0;
    for (int k = 0; k < 3; k++)
    {
        val_norm += _cord[k] * _cord[k];
    }
    return sqrt(val_norm);
};
double dot(const Vertex& V1, const Vertex& V2)

{
    double val_dot = 0;
    for (int k = 0; k < 3; k++)
    {
        val_dot += V1[k] * V2[k];
    };
    return val_dot;
};
Vertex prod(const Vertex& V1, const Vertex& V2)

{
    Vertex v_prod;

    v_prod[0] = V1[1] * V2[2] - V1[2] * V2[1];
    v_prod[1] = -V1[0] * V2[2] + V1[2] * V2[0];
    v_prod[2] = V1[0] * V2[1] + V1[1] * V2[0];

    return v_prod;
};


//Overwrite index method
double Vertex::operator[](int k) const
{
    return _cord[k];
};

double& Vertex::operator[](int k)
{
    return _cord[k];
};


// overwrite operator
Vertex& Vertex:: operator+=(const Vertex& other)
{
    for (int k = 0; k < 3; k++)
    {
        _cord[k] += other[k];

    };
    return *this;
};
Vertex& Vertex:: operator*=(const double& _k)
{
    for (int k = 0; k < 3; k++)
    {
        _cord[k] *= _k;
    };
    return *this;
};
Vertex& Vertex:: operator-=(const Vertex& other)
{
    for (int k = 0; k < 3; k++)
    {
        _cord[k] -= other[k];
    };
    return *this;
};
Vertex& Vertex:: operator/=(const double& _k)
{
    for (int k = 0; k < 3; k++)
    {
        _cord[k] /= _k;

    };
    return *this;
};
Vertex Vertex:: operator+(const Vertex& other)
{
    Vertex sv; // sum vertex
    for (int k = 0; k < 3; k++)
    {
        sv[k] = this->_cord[k] + other[k];

    };
    return sv;

};
Vertex Vertex:: operator-(const Vertex& other)
{
    Vertex mv;//minus vertex
    for (int k = 0; k < 3; k++)
    {
        mv[k] = this->_cord[k] - other[k];

    };
    return mv;

};
Vertex Vertex::operator*(const double &_k)
{
    Vertex fv;
    for (int k =0;k<3;k++)
    {
        fv[k] = this->_cord[k]*_k;
    };
    return fv;
};
Vertex Vertex::operator/(const double &_k)
{
    Vertex sv;
    for(int k=0;k<3;k++)
    {
        sv[k] = this->_cord[k]/_k;
    };
    return sv;
};
Vertex  Vertex::operator=(const Vertex &other)
{
    for(int k=0;k<3;k++)
    {
      _cord[k] = other[k];
      lap[k] = other.lap[k];
    };
    to_face = other.toFace();
    return *this;

};
double Vertex::lap_norm(){
    double val_norm = 0;
    for (int k = 0; k < 3; k++)
    {
        val_norm += lap[k] * lap[k];
    }
    return sqrt(val_norm);

}
