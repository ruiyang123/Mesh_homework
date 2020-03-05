# Mesh Generation homework
Author : Rui YANG
---
## 1.GUI
<img src="imgs/gui.PNG" width = "600" height = "400"  align=center />
There are six radio buttons and five push buttons.

### Radio buttons
- original plot : Draw the original Mesh that means 3D mesh and three colors
- connexion triangle : Draw three ajacents triangles and the center triangle
- test circulateur : Draw the center point and all the surrounding triangles
- drawwire2D : Draw 2D wire frame Mesh
- check_loc : Check location point algo
- draw_curv :Calculate Laplacian and curvature, then draw the mesh colored by curvature

### Push buttons
- Check_create_mesh : Create a primary mesh form a set of points
- flip edge : Using lawson algo for optimiser the primary mesh
- test_add_point : add a point in the delaunay mesh
- test_loc_point : Check location point algo
- exit : Exit the app

## 2.TD1

### (1) Load a file and draw the mesh 

you can change the file path here.
![avatar](imgs/change_file_path.PNG)
and the result(original plot) obtained:
<img src="imgs/teapot.PNG" width = "300" height = "200"  align=center />

### (2) Find three adjacent faces 
The aim is to find three adjacent faces for each triangle. 
<div><I>Instructions :</I> <br/>
  <p>After load a file, you can select the button <strong>connexion triangle</strong> to show three adjacent faces of the target face  </p>
  You can change the index of the target face here:<br/> 
  
  <img src="imgs/change_atta.PNG" width="600" height="200"></img>
</div>

Here I plot three faces of the first face(index 0) of teapot: 

<div><p>green : target face; red: adjacent face </p>
  <img src="imgs/adjacents.PNG" width = "300" height = "200" align = center /></div>


## 3.TD2 Circulator

The aim of this part is to crate a vertex circulator and a triangle circulator.
The vertex circulator is to traverse the surrounding faces of the target point.
The triangle circulator is to traverse the surrounding faces of the target face.

<div><I>Instructions :</I> <br/>
  <p>After load a file, you can select the button <strong>test circulateur</strong> to show all the adjacent faces of the target point  </p>
  You can change the index of the target point here:<br/> 
  
  <img src="imgs/change_cir.PNG" width="600" height="200"></img>
</div>

Here I plot all adjacent faces of the first point(index 0) of teapot

<img src="imgs/cir.PNG" width="400" height="250"></img>

## 4.TD3 Laplacien and Curvature

After we create the circulator, then the calculate is very simple. 
The formule we use : 
![avatar](imgs/lap.PNG)

<div><I>Instructions :</I> <br/>
  <p>After load a file, you can select the button <strong>draw_curv</strong> to calculate the laplacien and draw the mesh colored by curvature</p>
</div>

The result we obtain : 
<div><br/>
<img src="imgs/cur.PNG" width="400" align="center"></img><div>

## 5.TD4 

### (1) Create a primary mesh from a set of points
Algo:
- Initialize the first triangle by using  the point with the index 0,1,2
- test for the next point : if inside the triangle then split the triangle;  if outside the point then link with the visible boundary edges;  if in the boundary then link with another vertex.
- we do this iteratively.
 
<div><I>Instructions :</I> <br/>
  <p>You can select the button <strong>Check_create_mesh</strong> to create a primary mesh </p>, I use the file <strong>franke4.off</strong> which has 1000 points.
  You can change the pathe of the data:<br/> 
  
  <img src="imgs/create_mesh_plot.PNG" width="600" height="200"></img>
  
You can change the number of points used in the mesh generation process here:

<table>
<tr>
<td>
<a><img src="imgs/func_create_mesh.PNG" width="50%"></a>
</td>
<td>
<a><img src="imgs/ins_create_mesh" width="50%"></a>
</td>
</tr>
</table>
</div>






