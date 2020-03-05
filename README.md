# Mesh Generation homework
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
and the resultat(original plot) obtained:
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




