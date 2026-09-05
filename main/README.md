# Lors Language Specification

Lors is a scientific, logical programming language. It features a self-hosted compiler that directly outputs LLVM IR (`.ll` files) to generate fast, native machine code.

## Philosophy
- **Logical**: Syntax follows a structured, scientific method approach.
- **Explicit**: No magic; types and scopes are clearly defined.
- **Unique**: Avoids common keywords like `if`, `while`, `int`, `void` in favor of more descriptive, scientific terms.

## Data Types
- `whole`: Represents an integer (maps to `i64` in LLVM).
- `precise`: Represents a floating-point number (maps to `double` in LLVM).
- `series`: Represents a string of text (maps to an opaque `ptr` in LLVM).
- `state`: Represents a boolean value (maps to `i1` in LLVM).

## Keywords

### Variable Declaration
Use `datum` to declare variables.
Syntax: `datum <name> : <type> = <value>;`

```lors
datum count : whole = 10;
datum pi : precise = 3.14159;
datum message : series = "Hello Universe";
datum is_valid : state = true;
```

### Control Flow

#### Conditional (The Hypothesis)
Instead of `if/else`, Lors uses `verify`.

```lors
verify (count > 5) then
    reveal("Count is greater than 5");
otherwise
    reveal("Count is small");
conclude
```

#### Loop (The Cycle)
Instead of `while`, Lors uses `cycle`.

```lors
datum i : whole = 0;
cycle (i < 10) do
    reveal(i);
    i = i + 1;
conclude
```

### Functions (Algorithms)
Functions are defined as `algorithm`.
Return values are sent back using `result`.

```lors
algorithm add_numbers(a : whole, b : whole) -> whole
begin
    datum sum : whole = a + b;
    result sum;
end
```

### Input/Output
- Output: `reveal(<expression>);` (Prints to stdout with newline).

### Comments
- Line comments start with `//`. (Standard, logical).

## Program Structure
A Lors program consists of a series of `datum` (globals) and `algorithm` definitions.
The entry point is an algorithm named `genesis` (instead of main).

```lors
algorithm genesis() -> whole
begin
    reveal("Starting Experiment");
    result 0;
end
```

# Lors Programming Language - Compiler Guide
Bienvenido a la documentación oficial del compilador auto-alojado de Lors (v5). Lors no es solo un lenguaje lógico y científico, es una herramienta de sistema madura capaz de generar código nativo y archivos de objetos listos para producción mediante LLVM.

## Uso Básico
Para compilar un archivo fuente `.lr` y generar un ejecutable binario:

```bash
./self_hosted_v5/lors_compiler mi_programa.lr
```
Esto generará un binario llamado `mi_programa` listo para ser ejecutado (`./mi_programa`).

## Flags del Compilador
El compilador de Lors soporta varias flags para dar a los ingenieros un control granular sobre el proceso de compilación, depuración y generación de artefactos.

### `-o` (Generación de Archivo Objeto)
**¿Qué hace?** Detiene el proceso de compilación antes de la fase de enlazado (linking) y genera un archivo objeto relocatable nativo (`.o` ELF/Mach-O) en lugar de un ejecutable final.

**¿Cuándo usarlo?**
- **Proyectos Grandes (Compilación Incremental):** Cuando tienes muchos archivos `.lr`, compilar a `.o` permite usar Makefile para recompilar solo los archivos que han cambiado, reduciendo drásticamente los tiempos de compilación.
- **Creación de Librerías:** Cuando deseas crear una librería estática (`.a`) de código Lors para distribuirla.
- **Interoperabilidad (C/C++/Rust):** Cuando quieres escribir algoritmos en Lors pero llamarlos desde un programa escrito en otro lenguaje de sistemas, enlazando el archivo `.o` directamente.

**Ejemplo:**
```bash
./self_hosted_v5/lors_compiler matematicas.lr -o
# Resultado: matematicas.o
```

## Interoperabilidad con Librerías Nativas (C)
Lors V5 puede comunicarse **directamente** con librerías del sistema escritas en C (como GTK, OpenGL, SQL, etc.) sin necesidad de pasar por C/C++ como intermediario.

Simplemente declara los algoritmos externos en tu código Lors (`algorithm external_function(...) -> tipo;`), compila tu programa usando la flag `-o`, y luego enlaza el archivo objeto resultante usando `clang` con las librerías necesarias.

**Ejemplo (OpenGL):**
```bash
./self_hosted_v5/lors_compiler mi_programa_gl.lr -o
clang mi_programa_gl.o -lGL -lglut -o mi_programa_gl
./mi_programa_gl
```

### `-s` (Save LLVM IR)
**¿Qué hace?** Por defecto, Lors genera código LLVM intermedio (`.ll`) y lo elimina una vez que la compilación (vía `clang`) tiene éxito. La flag `-s` (Save) fuerza al compilador a conservar el archivo `.ll` generado en el disco.

**¿Cuándo usarlo?**
- **Auditoría de Código:** Cuando quieres inspeccionar exactamente cómo Lors está traduciendo tus algoritmos a LLVM IR.
- **Optimización Manual:** Si necesitas tomar el código LLVM generado por Lors para ajustarlo manualmente o compilarlo con herramientas como `opt` o `llc`.

**Ejemplo:**
```bash
./self_hosted_v5/lors_compiler genesis.lr -s
# Resultado: genesis (ejecutable) y genesis.ll (código LLVM conservado)
```

### `-d` (Delete on Error)
**¿Qué hace?** Si la compilación falla (por ejemplo, `clang` devuelve error al procesar el archivo `.ll`), por defecto Lors conserva el archivo `.ll` para que puedas depurarlo. La flag `-d` invierte este comportamiento, forzando la eliminación estricta del archivo `.ll` incluso si hay un error.

**¿Cuándo usarlo?**
- **Entornos CI/CD:** En servidores de integración continua donde no quieres que los archivos intermedios residuales contaminen el espacio de trabajo o artefactos tras un fallo de pipeline.
- **Limpieza Estricta:** Si prefieres confiar puramente en los errores del compilador y no quieres lidiar con archivos `.ll` rotos en tu directorio de trabajo.

**Ejemplo:**
```bash
./self_hosted_v5/lors_compiler script.lr -d
```

### `-debug` (Show Internal Errors)
**¿Qué hace?** Lors captura los errores del compilador backend (`clang`/LLVM) y, por defecto, muestra un mensaje amigable. La flag `-debug` desactiva esta protección y escupe el output de error crudo (`stderr`) del compilador subyacente.

**¿Cuándo usarlo?**
- **Desarrollo del propio compilador:** Si estás trabajando en el generador de código de Lors (`llvm_codegen.inc`) y el LLVM IR generado es inválido.
- **Depuración Avanzada:** Si tu código Lors pasa las fases de Lexer, Parser y Type Checking, pero falla en la etapa nativa, `-debug` te mostrará la traza exacta de `clang`.

**Ejemplo:**
```bash
./self_hosted_v5/lors_compiler bug.lr -debug
```

lors self-hosted version 6 is comming soon guys!
