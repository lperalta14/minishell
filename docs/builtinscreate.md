```

---

## 🔧 Implementación paso a paso

### **PASO 1: Dispatcher de builtins**

**Función**: Detectar si un comando es builtin y ejecutarlo.

**Dónde**: `src/builtins/builtins.c`

**Lógica**:
```
1. is_builtin(cmd) → retorna 1 si es builtin, 0 si no
2. execute_builtin(cmd, env) → ejecuta el builtin correspondiente
```

**¿Por qué un dispatcher?**
- Centraliza la detección
- Facilita añadir nuevos builtins
- Separa lógica de ejecución

---

### **PASO 2: Orden de implementación recomendado**

#### **1️⃣ PWD (el más fácil)**
```
Función: builtin_pwd()
Lógica:
  - Llamar a getcwd()
  - Imprimir resultado
  - Retornar 0 si ok, 1 si error
```

#### **2️⃣ ENV (también fácil)**
```
Función: builtin_env(t_env *env)
Lógica:
  - Recorrer lista env
  - Imprimir cada key=value
  - Retornar 0
```

#### **3️⃣ ECHO (con flag -n)**
```
Función: builtin_echo(char **args)
Lógica:
  - Detectar si hay flag -n
  - Imprimir argumentos separados por espacio
  - Si NO hay -n, imprimir \n al final
  - Retornar 0
```

#### **4️⃣ CD (más complejo)**
```
Función: builtin_cd(char **args, t_env **env)
Lógica:
  - Sin args → ir a HOME
  - cd - → ir a OLDPWD
  - cd path → cambiar a path
  - Actualizar PWD y OLDPWD en env
  - Retornar 0 si ok, 1 si error
```

#### **5️⃣ EXPORT (necesita parseo)**
```
Función: builtin_export(char **args, t_env **env)
Lógica:
  - Sin args → imprimir env ordenado con "declare -x"
  - Con args → parsear key=value
  - Añadir o actualizar variable en env
  - Validar nombre de variable (solo alfanum y _)
  - Retornar 0 si ok, 1 si error
```

#### **6️⃣ UNSET (buscar y eliminar)**
```
Función: builtin_unset(char **args, t_env **env)
Lógica:
  - Para cada arg, buscar en env
  - Si existe, eliminar nodo
  - Retornar 0
```

#### **7️⃣ EXIT (manejo de códigos)**
```
Función: builtin_exit(char **args)
Lógica:
  - Sin args → exit(0)
  - Con arg numérico → exit(arg)
  - Con arg no numérico → error + exit(2)
  - Más de 1 arg → error, NO salir, retornar 1
```

---

## 🔍 Decisiones de diseño

### **Pregunta 1: ¿Dónde se ejecutan los builtins?**

**Opción A**: En el executor, detectar si es builtin ANTES de hacer fork
```
Ventajas: No creas proceso hijo innecesario
Desventajas: Complica la lógica del executor
```

**Opción B**: Función separada en executor que llama al dispatcher
```
Ventajas: Código más limpio y modular
Desventajas: Ninguna