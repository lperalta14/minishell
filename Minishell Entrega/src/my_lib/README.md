# 🧠 Mi librería personal 🚀

> Mi librería personal en C, evolucionando con cada proyecto.  
> Una colección de funciones útiles que han sido mi compañera fiel durante todo el cursus de 42.

---

## 📘 Descripción general

**My_library** (también conocida como **libft mejorada**) es mi librería personal de C que nació con el proyecto **Libft** en el **MILESTONE_0** de 42 Málaga, pero que ha crecido y evolucionado con cada nuevo proyecto del cursus.

Esta librería es mi **caja de herramientas** personal:
- Recodificaciones de funciones estándar de C (libc)
- Funciones adicionales que he necesitado en proyectos posteriores
- Utilidades para strings, memoria, listas enlazadas, y más
- Funciones personalizadas creadas por necesidad real

**Filosofía:** En 42 no podemos usar funciones de las librerías estándar de C en nuestros proyectos. Cada función que necesitas, debes crearla tú mismo. Esta librería es el resultado de ese aprendizaje progresivo.

**Estado actual:** 🔄 En constante evolución. Cada nuevo proyecto del cursus puede traer nuevas funciones.

---

## ⚙️ Tecnologías y herramientas

| Categoría | Herramienta / Tecnología |
|------------|--------------------------|
| Lenguaje | C (C99) |
| Compilador | GCC / CC / Clang |
| Estilo | Norminette (estándar de 42) |
| Depuración | Valgrind / GDB |
| Build System | Makefile |
| Control de versiones | Git + GitHub |
| Normas | `-Wall -Wextra -Werror` |

---

## 🧩 Estructura del proyecto

```bash
📦 My_library
├── GNL/                    # Get Next Line
│   └── get_next_line.c    # Función para leer línea por línea
├── ft_lib/                 # Funciones básicas de libft
│   ├── ft_is*.c           # Verificación (isalpha, isdigit...)
│   ├── ft_str*.c          # Manipulación de strings
│   ├── ft_mem*.c          # Manipulación de memoria
│   ├── ft_put*.c          # Funciones de salida
│   └── ft_*.c             # Conversiones y utilidades
├── ft_list/                # Listas enlazadas
│   └── ft_lst*.c          # Funciones de listas (lstnew, lstadd...)
├── ft_printf/              # Printf personalizado
│   ├── ft_printf.c        # Implementación principal
│   └── ft_printf_*.c      # Funciones auxiliares de printf
├── ft_utils/               # Utilidades extra
│   ├── ft_replacechar.c   # Reemplazar caracteres
│   └── *.c                # Otras funciones útiles
├── includes/
│   └── libft.h            # Cabeceras y prototipos de todas las funciones
├── obj/                   # Archivos objeto (generados por make)
├── .gitignore             # Archivos ignorados por git
├── Makefile               # Compilación automatizada
├── libft.a                # Librería compilada (generada)
└── README.md              # Esta documentación
```

**Organización modular:** La librería está dividida por funcionalidad en carpetas separadas, facilitando el mantenimiento y la expansión de funciones según las necesidades de cada proyecto del cursus.

---

## 🚀 Compilación y uso

### 📥 Clonar la librería

```bash
git clone https://github.com/lperalta14/My_library.git
cd My_library
```

### 🛠️ Compilar

```bash
# Compilar la librería
make

# Esto genera libft.a
```

### 📚 Usar en tu proyecto

**1. Incluir el header en tu código:**
```c
#include "libft.h"

int main(void)
{
    char *str;
    
    str = ft_strdup("Hello 42!");
    ft_putendl_fd(str, 1);
    free(str);
    return (0);
}
```

**2. Compilar tu proyecto con la librería:**
```bash
# Forma manual
cc -Wall -Wextra -Werror main.c -L. -lft -I./includes -o mi_programa

# O mejor, crea un Makefile que enlace libft.a
```

**3. Ejemplo de Makefile para tu proyecto:**
```makefile
NAME = mi_programa
LIBFT = libft.a
LIBFT_DIR = my_library

SRCS = main.c utils.c
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)/includes

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

---

## 📚 Funciones incluidas

La librería está organizada en **módulos** según funcionalidad:

### 📁 ft_lib/ - Funciones básicas de libc

#### 🔤 Verificación de caracteres (ctype)
| Función | Descripción |
|---------|-------------|
| `ft_isalpha` | Verifica si es letra (a-z, A-Z) |
| `ft_isdigit` | Verifica si es dígito (0-9) |
| `ft_isalnum` | Verifica si es alfanumérico |
| `ft_isascii` | Verifica si es carácter ASCII (0-127) |
| `ft_isprint` | Verifica si es carácter imprimible |
| `ft_toupper` | Convierte a mayúscula |
| `ft_tolower` | Convierte a minúscula |

#### 📝 Manipulación de strings
| Función | Descripción |
|---------|-------------|
| `ft_strlen` | Calcula longitud de string |
| `ft_strlcpy` | Copia string (segura) |
| `ft_strlcat` | Concatena strings (segura) |
| `ft_strchr` | Busca carácter en string |
| `ft_strrchr` | Busca carácter desde el final |
| `ft_strncmp` | Compara n caracteres de strings |
| `ft_strnstr` | Busca substring en n caracteres |
| `ft_strdup` | Duplica string (malloc) |
| `ft_substr` | Extrae substring |
| `ft_strjoin` | Une dos strings |
| `ft_strtrim` | Elimina caracteres del inicio y final |
| `ft_split` | Divide string por delimitador |
| `ft_strmapi` | Aplica función a cada char (con índice) |
| `ft_striteri` | Itera sobre string aplicando función |

#### 🧠 Manipulación de memoria
| Función | Descripción |
|---------|-------------|
| `ft_memset` | Rellena memoria con byte específico |
| `ft_bzero` | Rellena memoria con ceros |
| `ft_memcpy` | Copia memoria |
| `ft_memmove` | Copia memoria (segura con overlap) |
| `ft_memchr` | Busca byte en memoria |
| `ft_memcmp` | Compara bloques de memoria |
| `ft_calloc` | Reserva e inicializa memoria a cero |

#### 🔢 Conversión
| Función | Descripción |
|---------|-------------|
| `ft_atoi` | Convierte string a entero |
| `ft_itoa` | Convierte entero a string |

#### 📤 Funciones de salida
| Función | Descripción |
|---------|-------------|
| `ft_putchar_fd` | Escribe carácter en fd |
| `ft_putstr_fd` | Escribe string en fd |
| `ft_putendl_fd` | Escribe string + newline en fd |
| `ft_putnbr_fd` | Escribe número en fd |

---

### 📁 ft_list/ - Listas enlazadas

#### 🔗 Estructura de lista
```c
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;
```

#### Funciones de lista
| Función | Descripción |
|---------|-------------|
| `ft_lstnew` | Crea nuevo nodo |
| `ft_lstadd_front` | Añade nodo al inicio |
| `ft_lstadd_back` | Añade nodo al final |
| `ft_lstsize` | Cuenta nodos de la lista |
| `ft_lstlast` | Retorna último nodo |
| `ft_lstdelone` | Elimina un nodo |
| `ft_lstclear` | Elimina toda la lista |
| `ft_lstiter` | Itera aplicando función |
| `ft_lstmap` | Crea nueva lista aplicando función |

---

### 📁 GNL/ - Get Next Line

| Función | Descripción |
|---------|-------------|
| `get_next_line` | Lee una línea de un file descriptor |

**Uso:**
```c
int fd = open("archivo.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

**Características:**
- ✅ Lee de múltiples file descriptors simultáneamente
- ✅ Configurable con BUFFER_SIZE
- ✅ Gestión eficiente de memoria
- ✅ Funciona con stdin, archivos y pipes

---

### 📁 ft_printf/ - Printf personalizado

| Función | Descripción |
|---------|-------------|
| `ft_printf` | Implementación de printf con conversiones básicas |

**Conversiones soportadas:**
- `%c` - Carácter
- `%s` - String
- `%p` - Puntero (hexadecimal)
- `%d` / `%i` - Entero decimal
- `%u` - Unsigned decimal
- `%x` - Hexadecimal minúsculas
- `%X` - Hexadecimal mayúsculas
- `%%` - Símbolo de porcentaje

**Uso:**
```c
ft_printf("Hola %s, tienes %d años\n", "Luis", 25);
ft_printf("Puntero: %p\n", ptr);
ft_printf("Hexadecimal: %x\n", 255);
```

---

### 📁 ft_utils/ - Utilidades adicionales

Funciones personalizadas creadas para proyectos específicos:

| Función | Descripción | Usado en |
|---------|-------------|----------|
| `ft_replacechar` | Reemplaza caracteres en un string | so_long |
| *(Otras funciones según necesidad)* | ... | ... |

**ft_replacechar:**
```c
char *ft_replacechar(char *str, char find, char replace);
```
Reemplaza todas las ocurrencias de `find` por `replace` en `str`.

---

## 🔍 Testing

### Compilar y probar

```bash
# Compilar
make

# Probar con tu propio main
gcc -Wall -Wextra -Werror test.c libft.a -I./includes -o test
./test
```

### Tests automáticos (Testers de terceros)

Puedes usar testers de la comunidad de 42:

```bash
# Libft Unit Test
git clone https://github.com/alelievr/libft-unit-test.git
cd libft-unit-test
make f

# Libft Tester
git clone https://github.com/Tripouille/libftTester.git
cd libftTester
make
```

### Valgrind (verificar memory leaks)

```bash
valgrind --leak-check=full --show-leak-kinds=all ./tu_programa
```

### Norminette

```bash
norminette src/ includes/
```

---

## 🧠 Conceptos clave aprendidos

- [x] Punteros y gestión de memoria dinámica
- [x] Manipulación de strings y arrays
- [x] Estructuras de datos (listas enlazadas)
- [x] Gestión de file descriptors
- [x] Makefiles y compilación modular
- [x] Prevención de memory leaks
- [x] Normas de código estrictas (Norminette)
- [x] Recodificación de funciones estándar de C

---

## 📈 Evolución de la librería

### MILESTONE_0: Libft (Origen) - Carpeta `ft_lib/`
✅ Funciones básicas de libc (string, memory, ctype)  
✅ Funciones adicionales de strings  
✅ Conversiones (atoi, itoa)

### MILESTONE_0: Bonus - Carpeta `ft_list/`
✅ Estructura de listas enlazadas  
✅ Funciones completas de manipulación de listas

### MILESTONE_1: Get_next_line - Carpeta `GNL/`
✅ Función `get_next_line` con lectura eficiente  
✅ Soporte para múltiples file descriptors  
✅ Gestión de buffer configurable

### MILESTONE_1: Ft_printf - Carpeta `ft_printf/`
✅ Implementación completa de `ft_printf`  
✅ Conversiones: c, s, p, d, i, u, x, X, %  
✅ Funciones auxiliares de conversión

### MILESTONE_2: Proyectos varios - Carpeta `ft_utils/`
✅ `ft_replacechar` (para so_long)  
✅ Otras funciones auxiliares según necesidad  

### 🔄 Presente y Futuro
La librería continúa creciendo con cada nuevo proyecto del cursus. Cada vez que necesito una función nueva, la añado aquí para reutilizarla en proyectos futuros.

**Próximas adiciones posibles:**
- Funciones matemáticas avanzadas
- Sistema de logging
- Utilidades de archivos
- ¿Tu sugerencia?

---

## 💡 ¿Por qué hacer tu propia librería?

En 42, no puedes usar las funciones estándar de C (como `strlen`, `strcpy`, etc.) en tus proyectos. Debes recodificarlas tú mismo. Esto tiene varios beneficios:

1. **Entiendes cómo funcionan** las funciones por dentro
2. **Aprendes a gestionar memoria** correctamente
3. **Desarrollas debugging skills** al encontrar bugs en tu propio código
4. **Creas código reutilizable** para futuros proyectos
5. **Mejoras tu comprensión** de C a nivel bajo

**Cada función en esta librería tiene una historia:** un bug que costó horas arreglar, una optimización que mejoró el rendimiento, un caso edge que no había considerado.

---

## 🔧 Comandos del Makefile

```bash
make          # Compila la librería (genera libft.a)
make clean    # Elimina archivos objeto (.o)
make fclean   # Elimina archivos objeto y libft.a
make re       # Recompila desde cero (fclean + all)
make bonus    # Compila incluyendo funciones bonus
```

---

## 🤝 Uso en otros proyectos del cursus

Esta librería se descarga y compila automáticamente en mis otros proyectos mediante Makefiles:

```makefile
LIBFT_DIR = mylib
LIBFT_REPO = https://github.com/lperalta14/My_library.git
LIBFT_LIB = $(LIBFT_DIR)/libft.a

$(LIBFT_LIB):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		git clone $(LIBFT_REPO) $(LIBFT_DIR); \
	fi
	@make -C $(LIBFT_DIR)
```

---

## ⚠️ Normas y restricciones

Esta librería respeta todas las normas de 42:

✅ **Norminette** aprobada  
✅ Compilación con `-Wall -Wextra -Werror`  
✅ Sin variables globales  
✅ Sin memory leaks  
✅ Solo funciones permitidas: `write`, `malloc`, `free`  
✅ Nombres de función con prefijo `ft_`  
✅ Makefile debe recompilar solo archivos modificados  

---

## 📖 Cómo contribuir (para mí mismo)

Checklist para añadir una nueva función:

- [ ] Crear archivo `ft_nueva_funcion.c` en `src/`
- [ ] Añadir prototipo a `includes/libft.h`
- [ ] Añadir el `.c` al `SRCS` del Makefile
- [ ] Verificar con Norminette
- [ ] Testear exhaustivamente
- [ ] Verificar memory leaks con Valgrind
- [ ] Documentar en este README
- [ ] Commit con mensaje descriptivo

---

## 🎓 Recursos útiles

- [Manual de C (man pages)](https://man7.org/linux/man-pages/)
- [C Reference](https://en.cppreference.com/w/c)
- [Beej's Guide to C](https://beej.us/guide/bgc/)
- [42 Docs](https://harm-smits.github.io/42docs/)

---

## 👤 Autor

**Luis Peralta (lperalta14)**  
📍 42 Málaga  
💼 [LinkedIn](https://www.linkedin.com/in/lperaltamuñoz/)  
💻 [GitHub](https://github.com/lperalta14)  
📧 luisperaltamunoz@gmail.com

---

## 📜 Licencia

Este proyecto es parte del cursus de 42 School y está sujeto a las normas de la escuela.  
El código es de uso libre para estudiantes de 42.

---

⭐ **Si usas esta librería en tus proyectos, considera darle una estrella al repo!**

💡 *"Una librería no es solo código, es la historia de tu aprendizaje."*  
🔧 *Cada función aquí ha sido debuggeada con sudor, lágrimas y café.*
