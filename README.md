# Rescate-de-mu-eca
para ROS fuerte

se necesita el Metric-FF que es el planificador para darle el plan a seguir al robot, y en ese Metric-FF meter el output.c 

cam.cpp es el codigo final.

rec.cpp ademas de detectar color detecta si tiene 4 lados que seria un cuadrado o dependiendo de la definicion de su camara.

rojo.cpp rosa.cpp Color.cpp detecta colores
rojo.cpp lo encontre en internet con otro nombre y rosa.cpp fue brindado por mi profesor.

El orden de ejecucion  para que el p3dx siga los waypoints cuadrados de colores segun el plan (en teoria en un waypoint hay una muñeca):
primero ante todo se debe tener el Metric-FF cuando se tiene en la terminal entran en la carpeta del Metric-FF y le dan un make, eso compila el planificador y hay que meter el output.c hay adentro.

1. ejecutar rosrun andreita cam
2. ejecutar rosrun andreita escucha
3. ejecutar luego dentro del Metric-FF ./f -p "direccion del Metric-FF" -o operadorA.pddl -f andreita.pddl 
que conste que ya deben tener el plan listo que seria andreita.pddl
 
4. ejecutar rosrun andreita andreita_test

el cam.cpp debe estar levantado para comenzar recibir los colores que debe seguir y los guardara en un vector.

el escucha.cpp recibira el plan del Metric-FF y extraera solo los colores que debe seguir y debe estar ya ejecutandose para recibir del Metri-FF

cuando ya termino de recibir los colores cam.cpp, comienza a funcionar la camara.

enviara las ordenes que debe ejecutar a andreita.cpp (andreita_test) para que se mueva el robot, seguira el color que debe seguir en ese momento del plan y evitara los demás.

cuando se encuentre en cierta posicion el color en la camara se tomara como que ya llego al objetivo y cambiara al siguiente color.


