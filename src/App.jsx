import { useState, useEffect } from 'react'
import reactLogo from './assets/react.svg'
import './App.css'

function App() {
  const [myValue, setMyValue] = useState('');
  const [matrix, setMatrix] = useState('');
  const [media, setMedia] = useState('');
  const [matrixSimilitud, setMatrixSimilitud] = useState('');
  const [metrica, setMetrica] = useState('Correlación Pearson');
  const [vecino, setVecinos] = useState(2);
  const [prediccion, setPrediccion] = useState('Predicción simple');
  const [minimo, setMinimo] = useState(0);
  const [maximo, setMaximo] = useState(5);

  /* Leemos fichero con la matriz */
  const readFile = (e) => {
    const file = e.target.files[0];
    if (!file) {
      return;
    }
    const reader = new FileReader()
    reader.readAsText(file)
    reader.onload = () => {
      console.log(reader.result)
      setMyValue(reader.result)
    }
    reader.onerror = () => {
      console.log(reader.error)
    }
  }
  /* Imprimimos la matriz leida */
  function showContent() {
    var elemento = document.getElementById('contenido-archivo');
    elemento.innerHTML = myValue;
    separateElements();
  }
  /* Separamos los elementos de la matriz */
  function separateElements() {
    var elemento = document.getElementById('contenido-archivo');
    var matriz = elemento.innerHTML;
    var arrays = matriz.split('\n');
    /* Eliminamos el ultimo elemento del array(empty string) */
    arrays.pop();
    console.table(arrays);
    arrays.forEach(function (array, i) {
      arrays[i] = array.split(' ');
    }
    )
    var int_arrays = [];
    for (var i = 0; i < arrays.length; i++) {
      var iteration_array = [];
      for (var j = 0; j < arrays[i].length - 1; j++) {
        if (arrays[i][j] != "-") {
          iteration_array.push((parseInt(arrays[i][j]) - minimo) / (maximo - minimo));
          // iteration_array.push((parseInt(arrays[i][j])));
        } else {
          iteration_array.push(arrays[i][j]);
        }
      }
      int_arrays.push(iteration_array);
    }
    console.table(int_arrays);
    setMatrix(int_arrays);
  }
  const calculateAverage = () => {
    /* Calculamos la media de cada usuario */
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

  const filtradoColaborativo = () => {
    var mediaUser = calculateAverage();
    let matrizSimilitud = [];
    switch (metrica) {
      case "Correlación Pearson":
        console.log("Correlación de Pearson");
        matrizSimilitud = pearson(mediaUser);
        break;
      case "Distancia Euclídea":
        console.log("Distancia Euclídea");
        matrizSimilitud = euclidea();
        break;
      case "Distancia Coseno":
        console.log("Distancia Coseno");
        matrizSimilitud = coseno();
        break;
      default:
        break;
    }
    despejarIncognita(matrizSimilitud, mediaUser);
  }

  const despejarIncognita = (arraySimilitud, mediaUser) => {
    console.log("Despejando incognita");
    let vecinos = [];
    let vecinosResult = [];
    let resultado = [];
    let numerador = 0, denominador = 0;
    for (let i = 0; i < matrix.length; i++) {
      for (let j = 0; j < matrix[i].length; j++) {
        if (matrix[i][j] == "-") {
          vecinos = maxVecinos(arraySimilitud, matrix.length * i, matrix.length * (i + 1)) // X vecinos cercanos y sus indices
          for (let k = 0; k < vecinos.length; k++) {
            if (prediccion == "Predicción simple") {
              console.log("Predicción simple");
              if (matrix[vecinos[k].indice][j] != "-") {
                numerador += vecinos[k].valor * matrix[vecinos[k].indice][j];
                denominador += Math.abs(vecinos[k].valor);
              } else {
                vecinos[k].indice = -1;
              }
            }
            if (prediccion == "Diferencia con la Media") {
              console.log("Predicción diferencia con la media");
              if (matrix[vecinos[k].indice][j] != "-") {
                numerador += vecinos[k].valor * (matrix[vecinos[k].indice][j] - mediaUser[vecinos[k].indice]);
                denominador += Math.abs(vecinos[k].valor);
              } else {
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
    console.log(vecinosResult);
    console.log(resultado);
    return { vecinosResult, resultado };
  }

  const maxVecinos = (vecinos, index, max) => {
    let arraySimilitud = vecinos.slice(0);
    let obj = {
      indice: 0,
      valor: 0
    };
    let arrayObject = [];
    // Suponemos que el primer valor es el mayor
    obj.indice = index;
    obj.valor = arraySimilitud[index];
    for (let i = 0; i < vecino; i++) {
      obj.indice = 0;
      obj.valor = 0;
      for (let j = index; j < max; j++) {
        if (arraySimilitud[j] > obj.valor && arraySimilitud[j] != 2) {
          obj.indice = j;
          obj.valor = arraySimilitud[j]; 
        }
      }
      arraySimilitud[obj.indice] = -1;
      obj.indice = obj.indice - index;
      arrayObject.push(Object.assign({}, obj));
    }
    return arrayObject;
  }

  // Distancia Coseno (0 - 1)
  const coseno = () => {
    console.log("Coseno");
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
          matrixCoseno.push(2);
        }
      }
    }
    setMatrixSimilitud(matrixCoseno);
    console.table(matrixCoseno);
    return matrixCoseno;
  }

  // Distancia Euclidea (0 - MAX)
  const euclidea = () => {
    console.log("Euclidea");
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
          matrixEuclidea.push(2);
        }
      }
    }
    setMatrixSimilitud(matrixEuclidea);
    console.table(matrixEuclidea);
    return matrixEuclidea;
  }

  // Correlación de Pearson (-1 - 1)
  const pearson = (mediaUser) => {
    console.log("Pearson");
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
    console.table(matrixPearson)
    return matrixPearson;
  }
  return (
    <>
      <h1>Sistema de Recomendación</h1>
      <h2>Seleccione el archivo que contiene la matriz:</h2>
      <a href="https://reactjs.org" target="_blank">
        <img src={reactLogo} className="logo react" alt="React logo" />
      </a>
      <input type="file" id="file-input" onChange={readFile} />
      <h3>Contenido del archivo:</h3>
      <pre id="contenido-archivo"></pre>
      <button onClick={showContent}>Mostrar Matriz</button>
      <h2>Parámetros a intoducir:</h2>
      <p>Métrica elegida: </p>
      <select name='metrica' id='metrica' onChange={e => setMetrica(e.target.value)}>
        <option value="Correlación Pearson">Correlación de Pearson</option>
        <option value="Distancia Coseno">Distancia Coseno</option>
        <option value="Distancia Euclídea">Distancia Euclídea</option>
      </select>
      <p>Numero de vecinos:<br></br> <input type="number" id="n" onChange={e => setVecinos(parseInt(e.target.value))} /></p>
      <p>Rango maximo: <input type="number" id="n" onChange={e => setMaximo(parseInt(e.target.value))} /></p>
      <p>Rango minimo:<input type="number" id="n" onChange={e => setMinimo(parseInt(e.target.value))} /></p>
      <p>Tipo de predicción: </p>
      <select name='prediccion' id='prediccion' onChange={e => setPrediccion(e.target.value)}>
        <option value="Predicción Simple">Predicción Simple</option>
        <option value="Diferencia con la Media">Diferencia con la Media</option>
      </select>
      <br></br>
      <br></br>
      <button onClick={filtradoColaborativo}>Ejecutar</button>
    </>
  )
}

export default App
