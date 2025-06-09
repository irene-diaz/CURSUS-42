INSTALAR EXAMSHELL

✅ Solución Paso a Paso
Aquí tienes los pasos completos para instalar y ejecutar correctamente examshell, especialmente para los exámenes del cursus.

1. 📦 Instalar dependencias necesarias
Primero necesitas tener instalado:

Node.js y npm:
sudo apt update
sudo apt install nodejs npm

Verifica que están bien instalados:
node -v
npm -v

2. 🔽 Clona la rama correcta del repositorio
Esta rama contiene los exámenes del cursus:

git clone -b cursusExam https://github.com/c-bertran/42-exam-shell.git
cd 42-exam-shell

3. 🔧 Instala las dependencias del proyecto
Dentro del proyecto:

npm install
Esto descargará todo lo que necesitas para compilar examshell.

4. 🏗️ Compila el proyecto
Ahora construye el ejecutable:

npm run build
Esto generará los archivos necesarios en dist/.

5. ▶️ Ejecuta examshell
Una vez compilado, ejecuta:

npm start
Este comando lanza el examshell y te permite elegir entre los exámenes disponibles (incluidos los del cursus).

🛠️ (Opcional) Crear alias examshell
Si quieres usar examshell como un comando global en tu sistema, puedes hacer esto:

sudo ln -s $(pwd)/bin/examshell.sh /usr/local/bin/examshell

Y luego solo ejecutas:
examshell

✅ Resultado esperado
Al final deberías ver una interfaz como esta en la terminal:

Welcome to Examshell 👨‍💻
1. Start Exam
2. Settings
3. Exit
