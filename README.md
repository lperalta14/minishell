<div align="center">
  
![Minishell Banner](banners/minishell.gif)

**Una reimplementación moderna de Bash como proyecto de 42**

[![42 School](https://img.shields.io/badge/42-School-000000?style=flat&logo=42&logoColor=white)](https://42.fr)
[![Norminette](https://img.shields.io/badge/Norminette-passing-success)](https://github.com/42School/norminette)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

[Características](#-características) • [Instalación](#-instalación) • [Uso](#-uso) • [Testing](#-testing) • [Arquitectura](#-arquitectura)

</div>

---

## 📋 Tabla de Contenidos

- [Acerca del Proyecto](#-acerca-del-proyecto)
- [Características](#-características)
- [Requisitos](#-requisitos)
- [Instalación](#-instalación)
- [Uso](#-uso)
- [Testing Automatizado](#-testing-automatizado)
- [Arquitectura](#-arquitectura)
- [Pipeline de Ejecución](#-pipeline-de-ejecución)
- [Documentación](#-documentación)
- [Workflow Git](#-workflow-git)
- [Autores](#-autores)

---

## 🎯 Acerca del Proyecto

**Minishell** es una implementación simplificada de un intérprete de comandos estilo Bash, desarrollado como proyecto educativo en 42 School. El proyecto pone énfasis en:

- 🏗️ **Arquitectura modular** con separación de responsabilidades
- 🤖 **Testing automatizado** con suite completa de pruebas
- 🔄 **Flujo de trabajo Git** estandarizado y colaborativo
- 📚 **Documentación técnica** detallada

---

## ✨ Características

### Funcionalidades Implementadas

- ✅ **Prompt interactivo** con historial de comandos (readline)
- ✅ **Búsqueda de comandos** en PATH
- ✅ **Gestión de comillas** con jerarquía y backtracking
  - Comillas dobles (`"..."`) - Expansión parcial
  - Comillas simples (`'...'`) - Sin expansión
  - Sin comillas - Expansión completa
- ✅ **Redirecciones**
  - Input: `<`
  - Output: `>`
  - Append: `>>`
  - Heredoc: `<<`
- ✅ **Pipes** (`|`) - Comunicación entre procesos
- ✅ **Expansión de variables** (`$VAR`, `$?`)
- ✅ **Operadores lógicos** (`&&`, `||`)
- ✅ **Subshells** con paréntesis `(...)`
- ✅ **Señales** (Ctrl+C, Ctrl+D, Ctrl+\\)

### Builtins Implementados

| Comando | Descripción |
|---------|-------------|
| `echo` | Imprime argumentos (con opción `-n`) |
| `cd` | Cambia directorio de trabajo |
| `pwd` | Muestra directorio actual |
| `export` | Define variables de entorno |
| `unset` | Elimina variables de entorno |
| `env` | Muestra variables de entorno |
| `exit` | Cierra el shell |

---

## 📦 Requisitos

### Sistema
- **OS**: Linux / macOS
- **Compilador**: GCC o Clang
- **Make**: GNU Make 3.81+

### Dependencias
```bash
# Ubuntu/Debian
sudo apt-get install libreadline-dev

# macOS (Homebrew)
brew install readline
```

---

## 🚀 Instalación

```bash
# Clonar el repositorio
git clone https://github.com/lperalta14/minishell.git
cd minishell

# Compilar
make

# Ejecutar
./minishell
```

### Comandos Make Disponibles

| Comando | Acción |
|---------|--------|
| `make` | Compila el proyecto |
| `make clean` | Elimina archivos objeto |
| `make fclean` | Limpieza completa |
| `make re` | Recompila desde cero |

---

## 💻 Uso

### Ejemplos Básicos

```bash
# Comandos simples
minishell> ls -la
minishell> echo "Hello World"

# Pipes
minishell> ls | grep .c | wc -l

# Redirecciones
minishell> cat < input.txt > output.txt
minishell> echo "log" >> file.log

# Heredoc
minishell> cat << EOF
> línea 1
> línea 2
> EOF

# Variables
minishell> export VAR="value"
minishell> echo $VAR

# Operadores lógicos
minishell> make && ./minishell
minishell> ls archivo_inexistente || echo "Error"

# Subshells
minishell> (cd /tmp && ls) && pwd
```

---

## 🧪 Testing Automatizado

El proyecto incluye una **suite completa de tests automatizados** para garantizar la calidad y robustez del código.

### Estructura de Testing

```
tests/
├── unit/           # Tests unitarios por módulo
│   ├── lexer/
│   ├── parser/
│   ├── expander/
│   └── executor/
├── integration/    # Tests de integración
├── regression/     # Tests de regresión
└── testers/        # Testers externos
    ├── minishell-tester/
    ├── mpanic/
    └── 42_minishell_tester/
```

### Ejecutar Tests

```bash
# Test suite completo
make test

# Tests por módulo
make test-lexer
make test-parser
make test-executor

# Tests con valgrind (memory leaks)
make test-valgrind

# Testers externos
./tests/run_external_testers.sh
```

### Testers Integrados

| Tester | Descripción | Cobertura |
|--------|-------------|-----------|
| **minishell-tester** | Suite oficial 42 | Funcionalidades básicas |
| **mpanic** | Tests exhaustivos | Edge cases y memoria |
| **42_minishell_tester** | Community tester | Casos complejos |

### Métricas de Testing

- ✅ **Cobertura de código**: >85%
- ✅ **Memory leaks**: 0 (verificado con Valgrind)
- ✅ **Norminette**: 100% compliant
- ✅ **Edge cases**: >200 casos de prueba

---

## 🏗️ Arquitectura

### Estructura del Proyecto

```
minishell/
├── src/
│   ├── main.c              # Punto de entrada
│   ├── lexer/              # Tokenización
│   │   └── token.c
│   ├── parser/             # Análisis sintáctico
│   │   └── parse.c
│   ├── expander/           # Expansión de variables
│   │   └── expand.c
│   ├── executor/           # Ejecución de comandos
│   │   └── pipes.c
│   ├── builtins/           # Comandos internos
│   │   └── cdcommand.c
│   ├── utils/              # Utilidades
│   │   └── prints/
│   │       └── banner.c
│   └── my_lib/             # Librería personalizada
├── include/                # Headers
│   └── minishell.h
├── banners/                # ASCII art
├── docs/                   # Documentación
│   ├── minishell_functions.md
│   └── Workflow_Git_Minishell.md
├── tests/                  # Suite de tests
├── obj/                    # Archivos objeto (generado)
└── Makefile
```

### Diseño Modular

```
┌─────────────────────────────────────────┐
│           MINISHELL CORE                │
└─────────────────────────────────────────┘
                    │
        ┌───────────┴───────────┐
        ▼                       ▼
┌───────────────┐       ┌───────────────┐
│   READLINE    │       │   SIGNALS     │
│   (Input)     │       │   Handler     │
└───────┬───────┘       └───────────────┘
        │
        ▼
┌───────────────┐
│     LEXER     │  ← Tokenización con backtracking
│  (Tokenizer)  │
└───────┬───────┘
        │
        ▼
┌───────────────┐
│    PARSER     │  ← AST (Abstract Syntax Tree)
│               │
└───────┬───────┘
        │
        ▼
┌───────────────┐
│   EXPANDER    │  ← Variables y wildcards
│               │
└───────┬───────┘
        │
        ▼
┌───────────────┐
│   EXECUTOR    │  ← Fork/Exec + Builtins
│               │
└───────────────┘
```

---

## 🔄 Pipeline de Ejecución

```
┌─────────────┐     ┌─────────────┐     ┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│   INPUT     │────▶│    LEXER    │────▶│   PARSER    │────▶│  EXPANDER   │────▶│  EXECUTOR   │
│  (String)   │     │  (Tokens)   │     │    (AST)    │     │ (Variables) │     │  (Process)  │
└─────────────┘     └─────────────┘     └─────────────┘     └─────────────┘     └─────────────┘
```

### 1️⃣ Lexer - Tokenización

**Función**: Convertir string de entrada en tokens

**Jerarquía de comillas** (implementada con backtracking):
1. Comillas dobles `"..."` - Mayor prioridad
2. Comillas simples `'...'`
3. Sin comillas - Expansión normal

**Tipos de tokens**:
```c
TOKEN_WORD           // Palabra/argumento
TOKEN_PIPE           // |
TOKEN_REDIR_IN       // <
TOKEN_REDIR_OUT      // >
TOKEN_REDIR_APPEND   // >>
TOKEN_REDIR_HEREDOC  // <<
TOKEN_AND            // &&
TOKEN_OR             // ||
TOKEN_LPAREN         // (
TOKEN_RPAREN         // )
```

### 2️⃣ Parser - Construcción del AST

**Función**: Construir árbol de sintaxis abstracta

**Ejemplo**:
```bash
echo "hello" | grep world && ls
```

```
        AND
       /   \
     PIPE  CMD(ls)
     /  \
  CMD   CMD
 echo  grep
```

### 3️⃣ Expander - Expansión de Variables

**Función**: Expandir variables según contexto de comillas

**Reglas**:
- Sin comillas → Expandir todo
- `"..."` → Expandir variables, no wildcards
- `'...'` → No expandir nada

### 4️⃣ Executor - Ejecución

**Función**: Ejecutar comandos y gestionar I/O

**Componentes**:
- Fork/exec para comandos externos
- Builtins nativos
- Gestión de pipes y redirecciones
- Manejo de señales

---

## 📚 Documentación

### Documentos Técnicos

| Documento | Descripción |
|-----------|-------------|
| [Funciones Autorizadas](docs/minishell_functions.md) | Especificación de todas las funciones permitidas |
| [Workflow Git](docs/Workflow_Git_Minishell.md) | Guía de uso de Git en el proyecto |
| [API Reference](#) | Documentación de la API interna |

### Recursos Útiles

- 📖 [Bash Reference Manual](https://www.gnu.org/software/bash/manual/)
- 🔧 [Readline Documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)
- 🐛 [Debugging Guide](#) - Próximamente

---

## 🔀 Workflow Git

### Estrategia de Branches

```
main                    ← Branch protegida (stable releases)
  │
  ├── develop          ← Branch de integración
  │     │
  │     ├── feature/lexer-backtracking
  │     ├── feature/heredoc-implementation
  │     ├── fix/memory-leak-parser
  │     └── test/integration-pipes
  │
  └── hotfix/critical-bug
```

### Convención de Commits

Seguimos [Conventional Commits](https://www.conventionalcommits.org/):

```
<type>(<scope>): <description>

[optional body]

[optional footer]
```

**Tipos permitidos**:
- `feat`: Nueva funcionalidad
- `fix`: Corrección de bug
- `docs`: Documentación
- `style`: Formato (no afecta lógica)
- `refactor`: Refactorización
- `test`: Tests
- `chore`: Mantenimiento

**Ejemplos**:
```bash
feat(lexer): implement quote hierarchy with backtracking
fix(parser): resolve segfault on empty pipe
docs(readme): update testing section
test(executor): add pipe integration tests
```

### Flujo de Trabajo

```bash
# 1. Crear feature branch desde develop
git checkout develop
git pull origin develop
git checkout -b feature/my-feature

# 2. Desarrollar y commitear
git add .
git commit -m "feat(module): description"

# 3. Push y crear Pull Request
git push origin feature/my-feature

# 4. Code review + tests automáticos

# 5. Merge a develop tras aprobación
```

### Pre-commit Hooks

El proyecto incluye hooks automatizados:

- ✅ **Norminette** check
- ✅ **Compilación** sin warnings
- ✅ **Tests unitarios** básicos
- ✅ **Format check** de commits

---

## 👥 Autores

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/lperalta14">
        <img src="https://github.com/lperalta14.png" width="100px;" alt="Luis Peralta"/>
        <br />
        <sub><b>Luis Peralta</b></sub>
      </a>
      <br />
      <sub> lperalta@student.42malaga.com</sub>
    </td>
    <td align="center">
      <a href="https://github.com/casimarasn">
        <img src="https://cdn.intra.42.fr/users/1c2b22c55757980443f96ecd768eddf3/msedeno-.jpg" width="100px;" alt="Colaborador"/>
        <br />
        <sub><b>María Sedeno</b></sub>
      </a>
      <br />
      <sub>msedeno-@student.42malaga.com</sub>
    </td>
  </tr>
</table>

---

## 🤝 Contribuciones

Este es un proyecto académico de 42 School. No se aceptan contribuciones externas, pero el código se comparte con fines educativos.

### Para Estudiantes de 42

Si encuentras este proyecto útil:
1. ⭐ Dale una estrella al repo
2. 📚 Úsalo como referencia, no lo copies
3. 💬 Comparte feedback constructivo

---

## 📄 Licencia

Este proyecto es parte del curriculum de 42 School y está disponible únicamente con fines educativos.

---

## 🙏 Agradecimientos

- **42 School** por el proyecto desafiante
- **Comunidad 42** por los testers y recursos compartidos
- **Desarrolladores de Bash** por la inspiración

---

<div align="center">

**[⬆ Volver arriba](#-minishell)**

Hecho con ☕ y 💻 en 42 School

</div>
