#!/usr/bin/env python3

def factores_primos(n: int) -> list[int]:
    if n < 2:
        return []
    factores = []
    divisor = 2
    valor = n
    while divisor * divisor <= valor:
        while valor % divisor == 0:
            factores.append(divisor)
            valor //= divisor
        divisor += 1
    if valor > 1:
        factores.append(valor)
    return factores

def dificultad(n: int) -> int:
    return len(factores_primos(n))

def main() -> None:
    datos = []
    for numero in range(1, 101):
        factores = factores_primos(numero)
        datos.append((numero, factores, len(factores)))
    # Prioridad: primero los más fáciles, luego los más difíciles y desempate por valor numérico.
    datos.sort(key=lambda x: (x[2], x[0]))
    for numero, factores, diff in datos:
        if numero == 1:
            print(f"{numero}: sin factores primos (dificultad={diff})")
        else:
            print(f"{numero}: {' * '.join(map(str, factores))} (dificultad={diff})")


if __name__ == "__main__":
    main()
