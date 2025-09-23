🌐 Projeto - ESP32 Microserver

📘 Descrição
Este projeto demonstra como transformar um ESP32 em um servidor web local, capaz de hospedar uma página HTML acessível via Wi-Fi.
A atividade foi desenvolvida como parte da disciplina de Fundamentos de Infraestrutura, utilizando a IDE Arduino na versão 2.3.6.

🎯 Objetivos
Configurar o ESP32 como servidor HTTP.

Servir conteúdo HTML diretamente do microcontrolador.

Utilizar SPIFFS para armazenar e servir arquivos estáticos.

Compreender a arquitetura cliente-servidor em sistemas embarcados.

🧰 Requisitos
ESP32 DevKit
![Foto ESP32](esp32.jpg)

Cabo USB Micro (use de preferência um original)
![Cabo USB](cabo.jpg)
![Porta USB](usb.jpg)

Arduino IDE 2.3.6

Linguagem: C++ (Arduino Framework)

Bibliotecas:

WiFi.h — conexão com rede Wi-Fi

WebServer.h — servidor HTTP

SPIFFS.h — sistema de arquivos interno

🗂️ Organização de Arquivos
index.html — página principal (embutida no código)

/assets/horta.jpg — imagem servida via SPIFFS

/assets/jardinagem.jpg — imagem servida via SPIFFS

/assets/apae.png — imagem servida via SPIFFS

Para carregar os arquivos no SPIFFS, utilize o plugin "ESP32 Sketch Data Upload" ou o gerenciador de arquivos do PlatformIO.

📡 Acesso ao Servidor
Após o upload do código e conexão do ESP32 à rede, o IP local será exibido no monitor serial. Basta digitar esse IP no navegador para acessar a página hospedada.

🧠 Aprendizados
Como configurar um servidor HTTP embarcado.

Como servir arquivos estáticos com SPIFFS.

Como estruturar rotas e responder requisições HTTP.

Como integrar HTML, CSS e JavaScript em sistemas embarcados.



-----------------------------------------------------------------------------------------

💻Simulação local: Alternativa sem o hardware ESP32

Permite explorar conceitos de servidor embarcado, arquitetura cliente x servidor, e integração web simulando diretamente no computador.

🎯 Objetivos
- Reproduzir a lógica de um servidor HTTP local.
- Simular o comportamento de SPIFFS servindo arquivos estáticos localmente.
- Compreender o fluxo de requisições e respostas HTTP.


🛠️Ferramentas 
- Visual Studio Code com a extensão Live Server.
- Python 3 com módulo http.server.
- Node.js com http-server ou Express.js.


🚀Execução
  - Live Server
      ¹ Instale a extensão Live Server.
      ² Abra a pasta do projeto.
      ³ Clique com botão direito no arquivo `index.html` e selecione "Open with Live Server".

  -Python
      ¹ No PROMPT/TERMINAL --> cd simulador
                               python -m http.server 8080
      ² Acesse http://localhost:8080 no navegador.

  -Node.js
      ¹ npm install -g http-server
      ² http-server ./simulador -p 8080

🧠 Aprendizados
  -Como preparar arquivos para serem servidos por sistemas embarcados.
  -Como o navegador interage com servidores HTTP.

🧾Conclusão
  Este projeto tem por finalidade oferecer uma introdução prática á arquitetura cliente-servidor em sistemas embarcados, com possibilidade de simulação local para ampliar o acesso e a compreensão dos conceitos fundamentais de infraestrutura de rede.
  
