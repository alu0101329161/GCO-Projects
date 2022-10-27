# Sistema de Recomendación

## Autores:
- Joseph Gabino Rodríguez
- Jonay Méndez Márquez
- Jairo Alonso Abreu
- José Javier Díaz González

## Descripción:
Este proyecto consiste en un sistema de recomendación de empleo. Se basa en el algoritmo de filtrado colaborativo, que consiste en recomendar productos a un usuario en base a los gustos de otros usuarios similares.

### **[Link para probar la web online](hhttps://alu0101329161.github.io/React-Filter-System/)**

<br>

---

<br>

## Uso local
Para poder desplegar el sistema de recomendación en __local__ primero clone el repositorio.
```bash
git clone git@github.com:alu0101329161/React-Filter-System.git
```
Luego, debe instalar las dependencias del proyecto, instalando la última versión de *node*.
```bash
npm install -g n
sudo n latest
```
Finalmente, puede ejecutar el proyecto con el siguiente comando.
```bash
npm run dev
```
## Licencia 
[MIT](https://choosealicense.com/licenses/mit/)

<br>

---

<br>

## Uso de la aplicación
> Explicación paso a paso de cómo utilizar nuestra app

La interfaz consta de varios elementos, todos ellos parte de un único proceso secuencial:
  - 1) Solicitud de un fichero de texto (matriz)
  - 2) Botón para mostrar la matriz
  - 3) Selector del tipo de métrica
      - &emsp;Correlación de Pearson
      - &emsp;Distancia Coseno
      - &emsp;Distancia Euclídea
  - 4) Selector del número de vecinos a elegir
  - 5) Selector del rango.
  - 6) Selector del tipo de predicción.
      - &emsp;Predicción simple
      - &emsp;Diferencia con la media

**Ejecución**

Una vez cargada la matriz y todos los parámetros, solo quedaría presionar el botón **[Ejecutar]**, que mostrará por pantalla tanto la matriz resultado como las similitudes calculadas en el proceso. Además

**Guardar**

Para guardar la matriz resultado, está disponible el botón **[Guardar]**, que se encargará de servirnos un fichero de texto con la solución.

<br>

---

<br>

## Estructura del proyecto
> Descripción de las carpetas y ficheros que componen el proyecto

**Esquema de directorios**
  - **/src/**&ensp;➔&ensp;Baúl de recursos
    - **assets/**&ensp;➔&ensp;Donde se encuentran las matrices de ejemplo
    - **components/**&ensp;➔&ensp;Ficheros con código JS que enlaza la hoja de estilos para el HTML.
    - **App.css**&ensp;➔&ensp;Hoja de estilos de la App
    - **App.jsx**&ensp;➔&ensp;Funciones de la App
    - **index.css**&ensp;➔&ensp;Estilos para la interfaz
    - **main.jsx**&ensp;➔&ensp;Convergencia de componentes
  - **/public/**&ensp;➔&ensp;Recursos generales
  - **/img/**&ensp;➔&ensp;Imágenes explicativas (No relevante para la aplicación)

<br>

---

<br>

## Backstage
> ¿Cómo funciona la aplicación?

Como en cualquier programa, el desarrollo empieza resolviendo una serie de problemas planteados de inicio. En este caso, sabiendo que la app recibirá un fichero de texto, surge un objetivo bastante obvio: Convertir esa gran cadena de texto en un array de arrays numéricos (una matriz). Solo así podremos operar con sus elementos, y por tanto solo así podremos conseguir los resultados esperados por el usuario.

Para eso, separar la cadena de texto en números independientes y reordenarlos en una matriz, se construyó la función **separateElements()**:

<br>

## separateElements()

    function separateElements() {
      var elemento = document.getElementById('contenido-archivo');
      var matriz = elemento.innerHTML;
      var arrays = matriz.split('\n');
      /* Eliminamos el ultimo elemento del array(empty string) */
      arrays.pop();
      arrays.forEach(function (array, i) {
        arrays[i] = array.split(' ');
      }
      )
      var int_arrays = [];
      for (var i = 0; i < arrays.length; i++) {
        var iteration_array = [];
        for (var j = 0; j < arrays[i].length - 1; j++) {
          if (arrays[i][j] != "-") {
            // Normalizamos los valores
            iteration_array.push((parseInt(arrays[i][j]) - minimo) / (maximo - minimo));
          } else {
            iteration_array.push(arrays[i][j]);
          }
        }
        int_arrays.push(iteration_array);
      }
      setMatrix(int_arrays);
    }

Recogemos el contenido mostrado por pantalla, que para este entonces será el fichero que el usuario haya escogido al principio. Luego, convertimos esa única *string* en un array de *strings*, donde cada elemento es una fila completa de la matriz (hemos usado como separador el caracter especial '\n'). Luego, haciendo algo parecido, separamos de nuevo cada string en su correspondiente array de *strings*, siendo esta vez cada elemento un caracter de la fila. Así conseguimos un array de arrays de *strings*.

Acto seguido generamos una nueva array, la que contendrá los números, y con bucles for anidados vamos inyecántodle a dicho array una serie de arrays cargados con números. Esto es, inyectarle fila por fila a la matriz.

<br>

## calculateAverage()
> Cálculo de las medias

Con la matriz separada por números, podemos realizar el que seguramente sea uno de los cálculos más importantes de todo el proceso: Las medias de cada fila.

    const calculateAverage = () => {
      let mediaUser = [];
      for (let i = 0; i < matrix.length; i++) {
        let suma = 0;
        let contador = 0;
        for (let j = 0; j < matrix[i].length; j++) {
          if (matrix[i][j] != "-") {
            suma += matrix[i][j];
            contador++;
          }
        }
        mediaUser.push(suma / contador);
      }
      setMedia(mediaUser);
      return mediaUser;
    }

No requiere demasiada explicación, pues a simple vista se ve que se trata del algoritmo clásico. Generamos un array para contener a todas las medias (su posición equivaldrá al índice de la fila, para mantenerla vinculada al usuario al que corresponde). Luego, para conseguir cada una, acumulamos en un numerador el sumatorio de todos los números de la fila, que dividiremos por el total de números tenidos en cuenta (Habremos omitido aquellos elementos que aún sean una incógnita).

<br>

## filtradoColaborativo()
> Hora de escoger el tipo de métrica

    const filtradoColaborativo = () => {
      comprobarError();
      var mediaUser = calculateAverage();
      let matrizSimilitud = [];
      switch (metrica) {
        case "Correlación Pearson":
          matrizSimilitud = pearson(mediaUser);
          break;
        case "Distancia Euclídea":
          matrizSimilitud = euclidea();
          break;
        case "Distancia Coseno":
          matrizSimilitud = coseno();
          break;
        default:
          break;
      }
      let resultado = despejarIncognita(matrizSimilitud, mediaUser);
      showFinal(resultado, matrizSimilitud);
    }

Se trata de una función sencilla en la que el programa se dirige a una función u otra dependiendo del método que haya escogido el usuario. Es en este método donde se realiza el cálculo de las medias (llamando a la función previamente explicada) y también donde se muestra el resultado final.

<br> 

## Métricas
> Tres formas distintas de calcular similitudes

<br>

### Pearson
 
    const pearson = (mediaUser) => {
      let matrixPearson = [];
      let result = 0;
      let numerador = 0, denominador1 = 0, denominador2 = 0;
      for (let i = 0; i < matrix.length; i++) {
        for (let j = 0; j < matrix.length; j++) {
          if (i != j) {
            for (let k = 0; k < matrix[i].length; k++) {
              if (matrix[i][k] != "-" && matrix[j][k] != "-") {
                numerador += (matrix[i][k] - mediaUser[i]) * (matrix[j][k] - mediaUser[j]);
                denominador1 += Math.pow((matrix[i][k] - mediaUser[i]), 2);
                denominador2 += Math.pow((matrix[j][k] - mediaUser[j]), 2);
              }
            }
            result = numerador / (Math.sqrt(denominador1) * Math.sqrt(denominador2));
            numerador = 0, denominador1 = 0, denominador2 = 0;
            // Normalizamos rango entre -1 y 1
            matrixPearson.push((result + 1) / (2));
          } else {
            matrixPearson.push(2);
          }
        }
      }
      setMatrixSimilitud(matrixPearson);
      return matrixPearson;
    }

Si bien puede parecer un método complejo, lo cierto es que es una traducción prácticamente literal de la fórmula matemática propuesta por definición. Un acumulador para el numerador, y otros dos para las dos raíces (una para el usuario principal, otra para el que se compare en la iteración). 

Cabe destacar que siempre se ha tenido la cautela de omitir aquellas iteraciones donde se tropiece con una incógnita (símbolo '-')

<br>

### Coseno
    const coseno = () => {
        let matrixCoseno = [];
        let numerador = 0, denominador1 = 0, denominador2 = 0;
        for (let i = 0; i < matrix.length; i++) {
          for (let j = 0; j < matrix.length; j++) {
            if (i != j) {
              for (let k = 0; k < matrix[i].length; k++) {
                if (matrix[i][k] != "-" && matrix[j][k] != "-") {
                  numerador += matrix[i][k] * matrix[j][k];
                  denominador1 += Math.pow((matrix[i][k]), 2);
                  denominador2 += Math.pow((matrix[j][k]), 2);
                }
              }
              matrixCoseno.push(numerador / (Math.sqrt(denominador1) * Math.sqrt(denominador2)));
              numerador = 0, denominador1 = 0, denominador2 = 0;
            } else {
              // No se puede calcular la distancia consigo mismo
              matrixCoseno.push(2);
            }
          }
        }
        setMatrixSimilitud(matrixCoseno);
        return matrixCoseno;
      }

De igual manera que para calcular mediante correlación de Pearson, para la Distancia Coseno podemos hacer una traducción a código de la fórmula matemática mediante bucles for y acumuladores.


<br>

### Euclídea

    const euclidea = () => {
        let matrixEuclidea = [];
        let resultado = 0, contador = 0;
        for (let i = 0; i < matrix.length; i++) {
          for (let j = 0; j < matrix.length; j++) {
            if (i != j) {
              for (let k = 0; k < matrix[i].length; k++) {
                if (matrix[i][k] != "-" && matrix[j][k] != "-") {
                  resultado += Math.pow((matrix[i][k] - matrix[j][k]), 2);
                  contador++;
                }
              }
              // Normalizamos resultado entre 0 y sqrt(N)
              matrixEuclidea.push(Math.sqrt(resultado) / Math.sqrt(contador));
              resultado = 0, contador = 0;
            } else {
              // No se puede calcular la distancia consigo mismo
              matrixEuclidea.push(2);
            }
          }
        }
        setMatrixSimilitud(matrixEuclidea);
        return matrixEuclidea;

Finalmente, aprovechando por última vez la librería 'Math' para el cálculo de las potencias y de las raíces, recorremos la matriz con tres bucles anidados. El índice 'i' fijará la fila comparada con el resto, mientras que el 'j' servirá para ir pasando de fila en fila calculando la similitud con la fija. Para esto es el tercer bucle, índice 'k', para recorrer elemento a elemento ambas filas comparadas.


<br>

## despejarIncognita
> Sacando las conclusiones

Una vez se haya pasado por el cálculo de similitudes, mediante cualquiera de los métodos escogidos, la aplicación puede finalmente deducir los valores restantes de la matriz.

    const despejarIncognita = (arraySimilitud, mediaUser) => {
      let vecinos = [];
      let vecinosResult = [];
      let resultado = [];
      let numerador = 0, denominador = 0;
      for (let i = 0; i < matrix.length; i++) {
        for (let j = 0; j < matrix[i].length; j++) {
          if (matrix[i][j] == "-") {
            // X vecinos cercanos y sus indices
            vecinos = maxVecinos(arraySimilitud, matrix.length * i, matrix.length * (i + 1))
            for (let k = 0; k < vecinos.length; k++) {
              if (prediccion == "Predicción simple") {
                if (matrix[vecinos[k].indice][j] != "-") {
                  numerador += vecinos[k].valor * matrix[vecinos[k].indice][j];
                  denominador += Math.abs(vecinos[k].valor);
                } else {
                  // el vecino no tenia valoracion para ese item
                  vecinos[k].indice = -1;
                }
              }
              if (prediccion == "Diferencia con la Media") {
                if (matrix[vecinos[k].indice][j] != "-") {
                  numerador += vecinos[k].valor * (matrix[vecinos[k].indice][j] - mediaUser[vecinos[k].indice]);
                  denominador += Math.abs(vecinos[k].valor);
                } else {
                  // el vecino no tenia valoracion para ese item
                  vecinos[k].indice = -1;
                }
              }
            }
            prediccion == "Predicción simple" ? resultado.push(numerador / denominador) : resultado.push(mediaUser[i] + (numerador / denominador));
            denominador = 0, numerador = 0;
            vecinosResult.push(vecinos); // tantas veces como incognitas
          }
        }
      }
      return { vecinosResult, resultado };
    }

Recorremos la matriz, deteniéndonos solo en aquellas posiciones que contengan una incógnita "-". Para hacer el cálculo final, el programa decidirá entre "Predicción Simple" o "Diferencia con la Media" según lo que haya escogido el usuario en la interfaz. Ambas opciones, aun así, son también una traducción literal de la fórmula matemática. Empleamos acumuladores (sumatorios) y valores absolutos (Math.abs).

Esto se repetirá, claro está, tantas veces como incógnitas encuentre el bucle inicial. Es decir, se recorrerá completamente la matriz hasta haber finiquitado el trabajo.

<br>

## Resto del código

Se han explicado las partes que se consideran de fundamental explicación. Aun así, cabe una mención especial al resto de funciones que hacen posible la aplicación. Por ejemplo, la función *showFinal* se encarga de mostrar finalmente todos los resultados por pantalla. Esto ya no es mera operatoria, sino que empiezan a mezclarse los recorridos de la matriz con el código HTML.

<br>

# Conclusiones

Al final, las dificultades que pueden surgir del desarrollo de una aplicación como esta son causadas por la naturaleza del propio lenguaje de programación. En lo que respecta a los algoritmos, teóricamente hablando, es de gran ayuda tener las definiciones matemáticas y entender los conceptos empleados, pues al final realmente solo se trata de saber cómo plasmarlos. 

**Esperamos que, del mismo modo, hayamos sabido plasmar aquí las secciones, funciones y virtudes de nuestro propio Sistema de Recomendación.**

_**Ahora es su turno, instale y juegue con la aplicación.**_
