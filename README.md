# Compilar asciiInvaders
```bash
$ make
$ make clean
```

# Ejecutar asciiInvaders
```bash
$ ./asciiInvaders.exe "objeto[posX=6,posY=9,sprite=A,tipo=personaje,vida=5,puntuacion=0]" "objeto[posX=6,posY=3,sprite=.,tipo=misil,direccion=ascendente,danio=10]" "objeto[posX=5,posY=3,sprite=.,tipo=misil,direccion=descendente,danio=10]" "objeto[posX=5,posY=7,sprite=V,tipo=enemigo,vida=100,puntuacion=10,movimientos=x=0,y=1,x=1,y=0,x=-1,y=0,x=0,y=-1]" "objeto[posX=1,posY=3,sprite=V,tipo=enemigo,vida=100,puntuacion=10,x=0,y=1,x=1,y=0,x=-1,y=0,x=0,y=-1]"
```
> ***NOTAS:***
> - El movimiento del enemigo puede ser definido sin 'movimientos='
> - Los parametros tienen que ir entre comillas como en bash
