# Sistemas de recomendación - Laura Cañizares Herrera 

## Introducción. 
  A modo de introducción, se detalla un informe de la práctica de Sistemas de recomendación de la asignatura Gestión del conocimiento en las Organizaciones del grado de Ingeniería Informática.

  Esta práctica se ha realizado con el lenguaje de programación C++ y el editor de código Visual Studio Code.

## Descripción del código desarrollado.
  En primer lugar, se ha decidido modular el código en tres clases diferenciables: Recomendation, Matrix y User. La clase encargada de poner en marcha el sistema recomendador en la denominada "Recomendation". Esta tiene un atributo de tipo Matrix, un vector de usuarios y un número natural que será el tipo de filtrado elegido durante la ejecución del programa. Cuando se ejecuta el mismo, se pasa como parámetro al constructor de esta clase el argumento número 1 que corresponda al nombre del fichero donde se leerán los datos de la matriz de utilidad. 

  Este fichero contiene una matriz compuesta por números naturales y "-". Estos números naturales representan valoraciones. Cada fila de la matriz corresponde a un determinado usuario y las columnas se relacionan a los items que estos usuarios valoraron. El símbolo "-" significa que ese usuario no ha valorado ese items y por tanto, mediante el sistema recomendador se le debe establecer una puntuación coherente. 

  Siguiendo el algoritmo, se procede a explicar la clase Matrix, desde la cual se leerá el fichero de entrada y se creará un objeto Matrix. Este contiene filas y columnas como bien se detalló anteriormente, el nombre del fichero que se le pasa al constructor por parámetro y la propia matriz creada con un vector de vectores de enteros. 

  Cuando se abre y se lee el fichero, se generan las filas con sus respectivas valoraciones (vectores de enteros). Esto se produce cuando el tamaño de la línea que lee del fichero es mayor que 1 y mientras que el fichero no haya llegado a su fin. Para realizar esto, se ha creado una función que genera las filas, la cual va leyendo la línea que se le pasa del fichero por parámetro hasta que encuentra un espacio en blanco y guarda los valores de enteros en una variable temporal de tipo string que va acumulando en un vector de enteros (se convierten de string a enteros). Además, cambia el valor del fichero de entrada "-" por un -1 para trabajar con valores numéricos.

  Como todos estos valores se han acumulado en el objeto matriz de la clase Matrix, podemos detallar su número de filas (número de filas anteriormente almacenadas) y de columnas, para la cual se ha cogido la fila 0 pero podría haber sido una cualquiera, y se le ha indicado el tamaño de esa fila para poder saber la cantidad de columnas (almacenadas mediante set_Columns).

  Una vez se tenga el objeto matriz, se comienza a operar con ella. Para ello, se llama a la función runProgram(), establecida en la clase Recomendation. Esta se encarga de elaborar el algoritmo de recomendación. En primer lugar, imprime la matriz que se ha creado por pantalla para observar las futuras predicciones que el programa debe calcular. 

  Posteriormente, genera los usuarios. Estos usuarios están formados por su id, el cual corresponde al número de la fila en la que se encuentra la valoración del mismo en la matriz, el vector de valoraciones, el vector que contiene a sus vecinos, el vector de float que contiene la similitud con cada uno de los usuarios (depende de qué filtrado se seleccione), el simType que corresponde al tipo de filtrado que se seleccione, y la media de las valoraciones del usuario. 

  Cuando se generan los usuarios, se guarda el tipo de filtrado seleccionado por quien esté ejecutando el programa. Así, recorre la matriz y almacena en el usuario que se cree en ese momento el id correspondiente (fila que se esté recorriendo con la variable i en el bucle), sus valoraciones correspondientes, la media, el tipo de filtrado y por último, almacena el usuario creado en el vector de usuarios de la clase Recomendation. 

  Acto seguido, se almacena en el vector de similitud del usuario indicado en el bucle, los valores de similitud con el resto de usuarios dependiendo del tipo de filtrado seleccionado. Para ello, se llama a la función similitud que tiene bien diferenciados los tres casos. El primero, la correlación de pearson, siguiendo la fórmula de las transparencia de la asignatura simplemente halla el sumatorio de las valoraciones del usuario menos su media, multiplicado por las valoraciones del usuario que está comparando menos su media. Esto se divide entre la raíz cuadrada del mismo cálculo pero con la media al cuadrado. Destacar que se debe asegurar que el cálculo no se realiza con el valor -1, puesto que esto significa que el usuario no tiene valoración en ese item. 

  En el caso dos, la distancia coseno es muy similar al anterior. Multiplica las valoraciones de los dos usuarios que se están comparando, partido entre la multiplicación de la raíz cuadrada de dichas valoraciones al cuadrado. El último caso, la distancia euclídea es la más sencilla. Simplemente realiza la raíz cuadrada de la resta al cuadrado de las clasificaciones de ambos usuarios. 

  Una vez se tengan las similitudes, se generan los vecinos de cada uno de los usuarios. Se ha establecido que cada uno tenga un mínimo de tres vecinos. Siguiendo además las transparencias de clase, la función resetNeigbors simplemente divide el caso de la correlación de pearson y la distancia coseno por un lado y la distancia euclídea por otro ya que siguen los mismos valores para el cálculo. 

  En el primer caso, es decir, el de la correlación de pearson y la distancia coseno, simplemente inicializa una variable temporal de similitud al peor valor posible, en este caso, -1, y posteriormente, busca el valor de similitud más grande. Luego lo único que hace es asegurarse de que el identificador pasado por parámetro no coincida con la variable j del bucle que está recorriendo el vector de similitud del usuario, ya que no debería de seleccionar la similitud de sí mismo. También, se asegura de que el usuario que vaya a meter en el vector de vecinos, no se encuentre ya en el mismo. Para esto último, se utiliza una nueva función que devuelve un booleano indicando si el usuario se encuentra o no en el vector de vecinos del usuario que se esté estudiando en el bucle en ese momento. 

  Por tanto, el objetivo de la función resetNeigbors es quedarse con los tres mejores vecinos del usuario que esté recorriendo. De esta manera, en la correlación de pearson y distancia coseno cogerá aquellos usuarios cuya similitud esté más cercana a 1 para que se produzca una correlación perfecta. Y en el caso de la distancia euclídea, el valor más bajo posible en la similitud ya que es directamente proporcional la distancia con la valoración que establezcan los usuarios, es decir, a menor diferencia entre las valoraciones de los usuarios, menor distancia euclídea entre los mismos. Por esta razón, la variable que se inicializa para poder realizar la comparación, se inicializa a un valor muy grande, para que al compararlo con la similitud se quede con valores más pequeños. 

  Por último, se realiza el cálculo de predicciones. Según la opción que se seleccione en la ejecución se realizará una predicción u otra siguiendo las fórmulas de las transparencias. Como tanto en la predicción simple como en la de diferencia con la media, el denominador es el módulo, se asegura en el código que sea positivo multiplicando el valor de la similitud por -1. Luego dependiendo del tipo elegido calcula el numerador por separado según la fórmula y su respectivo resultado. 

  Finalmente, mediante el método changeValue() cambia el -1 de la matriz por el valor calculado en la predicción de ese elemento y se muestra la matriz resultante por pantalla. 


## Ejemplo de uso.

