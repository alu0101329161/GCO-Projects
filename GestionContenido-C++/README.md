# Sistema de Recomendación. Modelos basados en el contenido

## Autores:
- Joseph Gabino Rodríguez
- Jonay Méndez Márquez
- Jairo Alonso Abreu
- José Javier Díaz González

## Descripción:

Este proyecto consiste en un sistema de recomendación basado en el contenido. Este sistema de recomendación utiliza algoritmos para identificar patrones en el contenido y así generar recomendaciones de forma automática. Este sistema de recomendación utiliza una variedad de técnicas para identificar patrones, como el **TF, el IDF o el TF-IDF**. Este sistema es útil ya que permite recomendaciones de manera automática y precisa.

## Ejecución
Para poder ejecutar el programa se ha de usar el comando **make**.
```bash
make
```
Luego, se ejecuta el comando **./main** y automáticamente se podrá ver todas las opciones seleccionadas
```bash
./main
```

## Licencia 
#### **[MIT](https://choosealicense.com/licenses/mit/)**

---

## Descripción de uso

La interfaz consta de varios elementos:
  - 1) `Corpus files`: Idioma del fichero en cuestión.
  - 2) `Stop words files`: Idioma del fichero stop word.
  - 3) `Docs files`: Fichero .txt en cuestión.
  - 4) `Nombre`: Nombre del documento.
  - 5) `Ruta`: Ruta del directorio donde se encuentra el .txt.
  - 6) `Palabra`: Palabras que contienen dentro del fichero .txt.
  - 7) `TF`: (Term Frequency). Cantidad de veces que aparece una palabra.
  - 8) `IDF`: (Inverse Document Frequency). Reduce el peso de los términos que aparecen en los documentos.
  - 9) `TF-IDF`: (Term Frequency – Inverse Document Frequency). Codifica documentos en un espacio Euclídeo multi-dimensional.
  - 10) `Longitud`: Longitud del fichero .txt
  - 11) `Tabla de similitud`: Similaridad coseno entre cada par de documentos.

---

## Estructura del proyecto
> Descripción de las carpetas y ficheros que componen el proyecto

**Esquema de directorios**
  - **/corpus/**&ensp;➔&ensp;Baúl de corpus
    - **corpus-en.txt/**&ensp;➔&ensp;Donde se encuentra el idioma es de corpus.
  - **/docs/**&ensp;➔&ensp;Baúl de docs
      - **documents-01.txt/**&ensp;➔&ensp;Donde se encuentra el idioma del fichero.txt
  - **/stop-words/**&ensp;➔&ensp;Baúl de stop words
      - **stop-words-en.txt/**&ensp;➔&ensp;Donde se encuentra elstop word
  - **file_control.cc**&ensp;➔&ensp;Fichero de control en .cc
  - **file_control.h**&ensp;➔&ensp;Fichero de control en .h
  - **file.cc**&ensp;➔&ensp; Fichero .cc
  - **file.h**&ensp;➔&ensp; Fichero .h
  - **main.cc**&ensp;➔&ensp;Archivo main del programa
  - **sistema.cc**&ensp;➔&ensp;Programa funcional con todas las características .cc
  - **sistema.h**&ensp;➔&ensp;Programa funcional con todas las características .h
  - **Makefile**&ensp;➔&ensp;Archivo Makefile
  - **README.md**&ensp;➔&ensp;Documentación del programa

---

## Backstage
> ¿Cómo funciona el programa?

- Como en cualquier programa, el desarrollo empieza resolviendo una serie de problemas planteados de inicio. En este caso, sabemos que el programa sabiendo que la app recibirá un fichero de texto, surge un objetivo bastante obvio: Convertir esa gran cadena de texto en un array de arrays numéricos (una matriz). Solo así podremos operar con sus elementos, y por tanto solo así podremos conseguir los resultados esperados por el usuario.

- Para eso, separar la cadena de texto en números independientes y reordenarlos en una matriz, se construyó la función `separateElements()`:

<br>

## Función `separateElements()`
```c++
vector<string> File_Control::obtener_archivos(const char *dir) {
  vector<string> archivos;

  if (DIR *pDIR = opendir(dir)) {
    while (dirent *entry = readdir(pDIR)) {
      std::string fileName = entry->d_name;

      if (fileName != "." && fileName != "..") {
        archivos.push_back(fileName);
      }
    }
    closedir(pDIR);
  }

  return archivos;
}
```
- 

<br>


## Resto del código

- Se han explicado las partes que se consideran de fundamental explicación. Aun así, cabe una mención especial al resto de funciones que hacen posible el programa. 

<br>

# Conclusiones Finales

Al final, las dificultades que pueden surgir del desarrollo de´l programa como esta son causadas por la naturaleza del propio lenguaje de programación. En lo que respecta a los algoritmos, teóricamente hablando, es de gran ayuda tener las definiciones matemáticas y entender los conceptos empleados, pues al final realmente solo se trata de saber cómo plasmarlos. 

**Esperamos que, del mismo modo, hayamos sabido plasmar aquí las secciones, funciones y virtudes de nuestro propio Sistema de Recomendación basado en el contenido.**