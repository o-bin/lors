Te voy a contar la historia completa de lors. 

1. Inicialmente fue escrito en Python, localizado como x@zx:~/projects/6ls$ python3 main/compiler.py
Usage: python3 compiler <script>.lr
zx@zx:~/projects/6ls$ y su codigo fuente alojado en /home/zx/projects/6ls/main/lors/src/ Fue definitivamente donde Lors se escribio por primera vez (Stage 0)

2. Despues en la ruta /home/zx/projects/6ls/main/self_compiler/ (Stage 0) lo compilo, especificamente el archivo home/zx/projects/6ls/lors_bootstrap.lr
aqui naciendo la (Stage 1)

3. Para experimentar que la (Stage 1) se autocompilara su propio codigo, se renombro el archivo lors_bootstrap.lr a twin.lr localizado en /home/zx/projects/6ls/main/twin.lr logro comerce su propio codigo naciendo la (Stage 2)

4. Luego decidi que ya era el momento de integrarle mejoras y en ese entonces decidi icorporarle flags y un recolector de basura /home/zx/projects/6ls/main/self_compiler_s/ aqui la (Stage 2) compilo el archivo /home/zx/projects/6ls/main/self_compiler_s/lors_bootstrap.lr surgiendo la (Stage 3) y para validar su logica, se repitio el la clausula '3' renombrando el archivo lors_bootstrap.lr dentro del directorio self_compiler.s y una vez mas funciono (Actualmente ese binario no esta disponible ni puedo recordar su nombre pero podremos llamarlo Stage4.lr

5. Luego la (Stage 4) comenzo a compilar /home/zx/projects/6ls/main/self_hosted_v5/ especificamente el archivo /home/zx/projects/6ls/main/self_hosted_v5/lors_compiler.lr naciendo la (Stage 5) donde por primera vez, Lors dejo de ser un transpilador para siempre, sabemos que la Stage 5 a diferencia de su generacion anterior no podia comerce su propio codigo.

6. Entonces nacio la (Stage 6) compilada por (Stage 5) proyecto /home/zx/projects/6ls/main/v6-dv/ donde no solo se alejaba de C++ sino que se se podia autoreproducirse y consumirse asi mismo de forma infinita. Aqui (Stage 5) compilo el archivo /home/zx/projects/6ls/main/v6-dv/compiler.lr naciendo la (Stage 6)


7. sabiamos que el binario /home/zx/projects/6ls/main/v6-dv/compiler (Stage 6) podia comerce su propio codigo, solo que habia una limitacion que tu y yo descubrimos y lo solucionamos utilizando dos scripts 2 scripts requeridos, el /home/zx/projects/6ls/main/v6-dv/build_all_modules.sh y /home/zx/projects/6ls/main/v6-dv/link_all_modules.sh aqui ha nacido oficialmente la (Stage 7) donde la generacion de Lors en LLVM puro se compila infinitamente 
