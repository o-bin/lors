Steps to install Lors

First install essential dependences

```
sudo apt-get update
sudo apt-get install -y build-essential cmake clang python3 git
```

Now compile & install

```
mkdir -p build && cd build
cmake ..
cmake --build .
```

Run 'lr' to verify that Lors is installed

If you want to read the full doc, go to [Wiki](https://github.com/o-bin/xls/wiki)

...

Pasos para instalar Lors guia en Español

Lo primero que debes hacer es instalar las dependencias esenciales

```
sudo apt-get update
sudo apt-get install -y build-essential cmake clang python3 git
```

Ahora configura, compila y instala Lors

```
mkdir -p build && cd build
cmake ..
cmake --build .
```

Usa el comando 'lr' para verificar que Lors se haya instalado. 

Si quieres leer la documentacion oficial y completa de Lors, se encuentra en [Wiki](https://github.com/o-bin/xls/wiki)
