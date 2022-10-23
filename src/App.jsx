import { useState } from 'react'
import reactLogo from './assets/react.svg'
import './App.css'

function App() {
  // Matrix en formato cadena
  const [myValue, setMyValue] = useState('');
  // Matrix formateada y normalizada
  const [matrix, setMatrix] = useState('');
  // Array con la media de usuarios
  const [media, setMedia] = useState('');
  // Matrix con la similitud entre usuarios
  const [matrixSimilitud, setMatrixSimilitud] = useState('');
  // Metrica elegida(3 opciones)
  const [metrica, setMetrica] = useState('Correlación Pearson');
  // Cantidad vecinos a considerar
  const [vecino, setVecinos] = useState(2);
  // Tipo de predicción(2 opciones)
  const [prediccion, setPrediccion] = useState('Predicción simple');
  // Rango minimo de valoración
  const [minimo, setMinimo] = useState(0);
  // Rango máximo de valoración
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

  /* Calculamos la media de cada usuario */
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

  /* Aplicamos algoritmo filtrado */
  const filtradoColaborativo = () => {
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

  /* Despejamos las incognitas de cada usuario
  *  y guardamos los valores de las predicciones
  *  más los vecinos elegido por el usuario
  */
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

  /* Obtenemos los vecinos más cercanos de la matrix de similitud */
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
      // sacamos el mayor valor, para no repetirlo
      arraySimilitud[obj.indice] = -1;
      obj.indice = obj.indice - index;
      // Guardamos una copia para no modificar las referencia
      arrayObject.push(Object.assign({}, obj));
    }
    return arrayObject;
  }

  // Distancia Coseno rango(0 - 1)
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

  // Distancia Euclidea rango(0 - MAX)
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
  }

  // Correlación de Pearson rango(-1 - 1)
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
  // Mostramos la matriz de utilidad con los calculos realizados
  const showFinal = (result, matrixSimilitud) => {
    let resultado = result.resultado;
    let contador = 0;
    let cadenaMatrix = "";
    for (let i = 0; i < matrix.length; i++) {
      for (let j = 0; j < matrix[i].length; j++) {
        if (matrix[i][j] == "-") {
          cadenaMatrix += "|" + (resultado[contador] * (maximo - minimo) + minimo).toFixed(2) + " | ";
          contador++;
        } else {
          cadenaMatrix += "|" + (matrix[i][j] * (maximo - minimo) + minimo).toFixed(2) + " | ";
        }
      }
      cadenaMatrix += "\n";
    }
    let elemento = document.getElementById("MatrixUtilidad");
    elemento.innerHTML = cadenaMatrix;
    // Mostramos la similitud de los usuarios
    let cadena = "";
    let contador1 = 0;
    let contador2 = 0;
    for (let i = 0; i < matrixSimilitud.length; i++) {
      if (contador1 == matrix.length) {
        contador1 = 0;
        contador2++;
      }
      if (contador2 + 1 != i % matrix.length + 1) {
        cadena += "Similitud entre usuario " + (contador2 + 1) + " y " + (i % matrix.length + 1) + " = " + (matrixSimilitud[i] * (maximo - minimo) + minimo).toFixed(2) + "\n";
      }
      contador1++;
    }
    let elemento1 = document.getElementById("SimilitudUsuarios");
    elemento1.innerHTML = cadena;
    // Mostramos los vecinos seleccionados para cada usuario
    let cadenaIncognita = "";
    let indiceVecino = " ";
    for (let i = 0; i < result.vecinosResult.length; i++) {
      for (let j = 0; j < result.vecinosResult[i].length; j++) {
        if (result.vecinosResult[i][j].indice != -1) {
          indiceVecino += "vecino: " + (result.vecinosResult[i][j].indice + 1) + "=> valor: " + (result.vecinosResult[i][j].valor * (maximo - minimo) + minimo).toFixed(2) + " ";
        }
      }
      cadenaIncognita += "Incónita " + (i + 1) + " = " + indiceVecino + "\n";
      indiceVecino = " ";
    }
    let elemento2 = document.getElementById("VecinosUtilizados");
    elemento2.innerHTML = cadenaIncognita;
  }

  return (
    <>
      <h1 className=''>Sistema de Recomendación</h1>
      <h2>Seleccione el archivo que contiene la matriz:</h2>
      <input className='file' type="file" id="file-input" onChange={readFile} />
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
      <pre id='MatrixUtilidad' className=''></pre>
      <pre id='SimilitudUsuarios'></pre>
      <pre id='VecinosUtilizados'></pre>
    </>
  )
}

export default App
