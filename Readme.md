# Paint Vectorial em OpenGL

## 1. Tecnologias que Vamos Usar

* **Linguagem C++11 (ou superior):** Escolha arquitetural para o aproveitamento de recursos modernos e da *Standard Template Library* (STL), como o uso de vetores dinâmicos (`std::vector`).
* **OpenGL Clássico:** Utilizado para a emissão de primitivas gráficas diretamente para o hardware de vídeo através dos blocos de comandos `glBegin()` e `glEnd()`.
* **OpenGL Utility Library (GLU):** Biblioteca auxiliar encarregada de abstrair projeções e gerenciar o mapeamento transparente entre o Sistema de Coordenadas do Mundo (ponto flutuante) e as Coordenadas da Tela/Dispositivo.
* **FreeGLUT (Free OpenGL Utility Toolkit):** Evolução estável e de código aberto da GLUT original. Fornece o ecossistema multiplataforma para a criação de janelas gráficas, contexto de renderização e tratamento robusto de eventos de entrada guiados por funções *callback* (mouse e teclado).
* **CMake (v3.10+):** Gerador de sistemas de construção (*build system template*) que atua de forma transparente na resolução de dependências multiplataforma, aplicando as diretivas e *flags* corretas de linkagem de acordo com o sistema operacional do desenvolvedor.

---

## 2. Preparação do Ambiente

### Configuração para Linux (Ubuntu / Debian e derivados)

1.  **Instale os Compiladores, CMake e Bibliotecas Gráficas:**
    Abra o terminal e execute o comando abaixo para garantir a presença do GCC, Make, CMake e todas as dependências de desenvolvimento do OpenGL/FreeGLUT:
    ```bash
    sudo apt update
    sudo apt install build-essential cmake freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev
    ```

2.  **Configuração do Editor:**
    * Abra o **VS Code**.
    * Acesse o painel de Extensões e instale o pacote **C/C++** (da Microsoft) e a extensão **CMake Tools** (da Microsoft).

---

### Configuração para Windows (MinGW)

1.  **Instalação do Compilador GCC (MinGW):**
    * Instale o ambiente de desenvolvimento **MinGW** no diretório padrão `C:\MinGW`.
    * Pelo gerenciador do MinGW, marque e instale obrigatoriamente os pacotes básicos `mingw32-base`, `mingw32-gcc-g++` e `msys-base`.
    * Adicione o caminho dos binários (`C:\MinGW\bin` e `C:\MinGW\msys\1.0\bin`) na variável de ambiente **`Path`** do seu sistema Windows.

2.  **Instalação Manual do FreeGLUT:**
    * Baixe os arquivos binários de desenvolvimento do **FreeGLUT** recomendados no material de apoio.
    * Descompacte o arquivo e realize a cópia manual das seguintes pastas/arquivos para dentro da estrutura do MinGW:
        * Conteúdo da pasta `include\GL\` Copiar para `C:\MinGW\include\GL\`
        * Conteúdo da pasta `lib\` Copiar para `C:\MinGW\lib\`
        * Conteúdo da pasta `bin\` (como a `freeglut.dll`) Copiar para `C:\MinGW\bin\`

3.  **Instalação do CMake e do Editor:**
    * Baixe e instale o **CMake** para Windows (marcando a opção para adicionar o CMake ao `Path` do sistema durante o instalador).
    * No **VS Code**, instale as extensões **C/C++** e **CMake Tools** (ambas desenvolvidas pela Microsoft).

---

## Como Compilar e Executar no VS Code (Linux/Winsdows)

1.  No VS Code, vá em **File > Open Folder** e selecione a pasta raiz do projeto.
2.  A extensão **CMake Tools** identificará o arquivo de configuração automaticamente. Uma barra pop-up ou menu será exibido solicitando que você escolha um **Kit** (Compilador).
    * *No Windows:* Escolha o compilador associado ao MinGW (ex: `GCC x.x.x x86_64-w64-mingw32`).
    * *No Linux:* Escolha o compilador nativo do sistema (ex: `GCC x.x.x x86_64-linux-gnu`).
3.  Observe a **Barra de Status** localizada na borda inferior do VS Code. Ela agora conterá botões automatizados do CMake:
    * Clique no botão **Build** (ou pressione `F7`) para compilar todo o projeto. O CMake se encarregará de criar uma pasta isolada chamada `build`, ler as regras corretas do sistema operacional e linkar as bibliotecas gráficas apropriadas de forma invisível.
    * Clique no botão **Launch** (ou no ícone de "Play") na barra inferior para inicializar a aplicação. 
