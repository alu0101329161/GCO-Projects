# Sistema de Recomendación

## Autores:
- Joseph Gabino Rodríguez
- Jonay Méndez Márquez
- Jairo Alonso Abreu
- José Javier Díaz González

## Descripción:
Este proyecto consiste en un sistema de recomendación de empleo, el cual se basa en el algoritmo de filtrado colaborativo, el cual consiste en recomendar productos a un usuario en base a los gustos de otros usuarios similares a él.

### **[Link para probar la web online](hhttps://alu0101329161.github.io/React-Filter-System/)**

## Uso local:
Para poder desplejar el sistema de recomendación en __local__ primero clone el repositorio.
```bash
git clone git@github.com:alu0101329161/React-Filter-System.git
```
Luego, debe instalar las dependencias del proyecto, instalando la última versión del node.
```bash
npm install -g n
sudo n latest
```
Finalmente, puede ejecutar el proyecto con el siguiente comando
```bash
npm run dev
```
## Licencia:
[MIT](https://choosealicense.com/licenses/mit/)

## Explicación

![Foto Ejemplo Matriz](images/01_ejemplomatriz.png)

Tenemos varios apartados, para pedir un archivo, para mostrar la matriz, el tipo de métrica, el número de vecinos a elegir, un rango máximo y mínimo y el tipo de predicción.

Tenemos un botón llamado "Ejecutar" que nos muestra toda la salida esperada tanto de la matriz como las similitudes. Además también tenemos otro botón de "Guardar" para guardar el resultado generado con .txt

Siguiendo con el proyecto, tenemos 1 directorio, en la que encontramos un /src/ en la que dentro se almacena otro directorio  /assets/ que almacena todos las matrices, un /components/ que almacena todo el código js con la hoja de estilos para el HTML y fuera de ello tenemos el readme.md y los paquetes necesarios para este proyecto.

Para explicar un poco las funciones y lógica implementada, tenemos la siguiente imagen donde podemos ver los diferentes métodos que se han ido implementando.

![Foto Ejemplo Funcion 1](images/02_funcion1.png)

Para empezar tenemos varios constantes en la funcion App, en la que se encargará de todas las salidas durante el proceso de cálculo de cada apartado para ser mostradas al final en la página. Tanto como para leer, como calcular la media, o como si sus parámetros son correctos.

Dentro del Algoritmo filtrado:

![Foto Funcion 2](images/03_funcion2.png)

Tenemos funciones para comprobar los errores, y un switch con el tipo de métrica tanto como pearson, euclídea o coseno y se van almacenando en "showFinal" mostrando la matriz de utilidad con sus calculos realizados.


![Foto return](images/04_return.png)

Cabe destacar, que tenemos un "return" que nos devuelve el menú que tenemos en la página web, así como sus botones, o a la hora de seleccionar los archivos, y sus calculos realizados, así como la predicción.
