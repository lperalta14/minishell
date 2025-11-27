# 🚀 Workflow Git Profesional para Minishell (2 Personas)

Este documento resume **cómo proteger main**, **cómo trabajar con develop**, el **workflow profesional**, y **los comandos exactos** que tú y tu compi usaréis durante el desarrollo del proyecto *minishell*.

---

# 🛡️ 1. Cómo proteger la rama `main`

Proteger `main` evita que alguien haga un push directo y rompa el proyecto.

### 🔧 Pasos en GitHub:

1. Ve al repositorio → **Settings**
2. En el menú lateral: **Branches**
3. En “Branch protection rules” → **Add rule**
4. Selecciona la rama **main**
5. Actcalas siguientes opciones:

- ✔ **Require a pull request before merging**  
- ✔ **Require at least 1 approval**  
- ✔ **Require status checks to pass** (opcional si tenéis tests)  
- ✔ **Don’t allow direct pushes**  

💡 Esto garantiza que `main` siempre sea una versión estable del proyecto.

---

# 🌱 2. Cómo organizar la rama `develop`

La rama `develop` es el lugar donde ambos integráis vuestro trabajo.

### Reglas importantes:

- ❌ Nadie trabaja directamente en `develop`.
- ✔ Solo se fusiona mediante **Pull Requests**.
- ✔ PRs siempre desde vuestra rama personal → develop.
- ✔ Antes de hacer merge:
  - El compañero revisa (compila, norminette, leaks…)
  - El código debe ser estable.

---

# 👥 3. Workflow profesional para minishell

```
main        ← solo lo final y estable
 |
develop     ← integración de vuestro trabajo
 |         |         maricabranch   mariabranch   ← ramas personales
```

### 🔄 Flujo de trabajo

1. Cada uno trabaja en su propia rama:  
   - `maricabranch`
   - `mariabranch`

2. Cuando terminas una parte **estable** → haces **Pull Request a develop**

3. El compañero revisa:

   - Estilo  
   - Leaks  
   - Compilación  
   - Comportamiento básico  

4. Merge a `develop`.

5. Cuando un bloque grande está COMPLETO (ejecución, pipes, señales, builtins, etc.):

   → PR: **develop → main**

📌 Objetivo:  
`main` **SIEMPRE COMPILA**, **SIEMPRE ESTÁ LIMPIA**, y representa la versión actual del proyecto.

---

# 🔧 4. Comandos que usaréis cada día

## 🫵 Para tu rama personal (`maricabranch`)

### 🔄 1. Mantener tu rama actualizada desde develop
*(Hazlo al empezar el día o antes de programar)*

```bash
git checkout maricabranch
git pull --rebase origin develop
```

---

### 💻 2. Trabajar normalmente

```bash
git add .
git commit -m "lo que has hecho"
git push
```

---

### 🔗 3. Enviar trabajo a develop

En GitHub:  
**Pull Request → maricabranch → develop**

---

## 🧑‍🤝‍🧑 Para integrar trabajo en develop

Cuando tú o tu compañera queráis actualizar develop:

1. Merge del Pull Request  
2. Resolver conflictos si los hay  
3. develop queda actualizado  
4. El otro compañero sincroniza su rama:

```bash
git checkout mariabranch
git pull --rebase origin develop
```

---

# 🌟 5. Cuando actualizar `main`

Solo cuando tengáis bloques grandes y terminados.

### Pasos:

1. Crear Pull Request:
   **develop → main**
2. Revisar en pareja  
3. Merge  
4. ¡`main` actualizado con una versión estable del proyecto! 🚀

---

# 📄 Fin del documento  
Puedes guardar este archivo como referencia rápida para tu flujo de trabajo profesional con Git.
