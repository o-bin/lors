# Lors Graphics Sandbox

Bienvenido al laboratorio de experimentación gráfica de `Lors V5`. 

Aquí puedes construir la librería `graphic.inc` sin afectar el núcleo del compilador.

## Instrucciones de Compilación

Para compilar un programa que use librerías externas (como OpenGL o GTK), sigue estos pasos:

1. **Generar el objeto (.o):**
   ```bash
   ../../lors_compiler tu_programa.lr -o
   ```

2. **Enlazar con librerías del sistema:**
   ```bash
   clang tu_programa.o -lGL -lglut -o tu_programa
   ```
   *(Cambia `-lGL` por las librerías que necesites, como `-lgtk-3`)*

3. **Ejecutar:**
   ```bash
   ./tu_programa
   ```

## Estructura Sugerida para `graphic.inc`

- **Declaraciones Externas:** Usa `algorithm nombre(...) -> tipo;` para declarar funciones de C.
- **Constantes:** Usa `datum NOMBRE : whole = valor;` para los enums de OpenGL/GTK.
- **Abstracciones:** Crea algoritmos en `Lors` que simplifiquen las llamadas complejas.

¡Buena suerte en estos 5-7 días de desarrollo! El compilador ya demostró que puede manejarlo.
