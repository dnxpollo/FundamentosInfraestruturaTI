#include <WiFi.h>         // Para conectar ao Wi-Fi
#include <WebServer.h>    // Para criar o servidor web
#include <SPIFFS.h>       // Para acessar arquivos na memória flash

// 🔐 Dados da rede Wi-Fi
const char* ssid = "SEU-WIFI";
const char* password = "SENHA-WIFI";

// 🌐 Cria o servidor na porta 80
WebServer server(80);

// 📄 Função que envia a página HTML
void handleRoot() {
String html = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>Jornal da Escola</title>
  <style>
    html { scroll-behavior: smooth; }
    body {
      font-family: Arial, sans-serif;
      background-color: #fff;
      color: #222;
      line-height: 1.6;
      padding: 1rem;
    }
    header {
      background-color: #0367a6;
      color: white;
      padding: 1rem;
      text-align: center;
    }
    #imgHeader {
      height: 200px;
      width: 200px;
    }
    nav ul {
      list-style: none;
      padding: 0;
      display: flex;
      justify-content: center;
      gap: 1rem;
    }
    nav a {
      color: white;
      text-decoration: none;
      font-weight: bold;
    }
    section { margin: 2rem 0; }
    h2 {
      border-bottom: 2px solid #0367a6;
      padding-bottom: 0.3rem;
    }
    #rodape {
      text-align: center;
      background: #0367a6;
      border-radius: 3px;
      font-weight: bold;
      color: white;
      padding: 1rem;
    }
    #entrevista {
      text-align:start;
      font-weight: bold;
      background-color: #0367a6;
      color: black;
      border-radius: 5px;
      padding: 1rem;
    }
    #folder {
      height: 300px;
      display: block;
      margin: auto;
    }
    .carrossel-container {
      position: relative;
      max-width: 600px;
      margin: auto;
      overflow: hidden;
      border-radius: 10px;
    }
    .carrossel-track {
      display: flex;
      transition: transform 0.5s ease-in-out;
    }
    .carrossel-track img {
      width: 100%;
      height: 350px;
      object-fit: cover;
      flex-shrink: 0;
    }
    .carrossel-btn {
      position: absolute;
      top: 50%;
      transform: translateY(-50%);
      background-color: rgba(0,0,0,0.5);
      color: white;
      border: none;
      font-size: 2rem;
      padding: 0.5rem;
      cursor: pointer;
      z-index: 1;
    }
    .prev { left: 10px; }
    .next { right: 10px; }
    .carrossel-indicadores {
      position: absolute;
      bottom: 10px;
      width: 100%;
      text-align: center;
    }
    .dot {
      display: inline-block;
      height: 10px;
      width: 10px;
      margin: 0 5px;
      background-color: #bbb;
      border-radius: 50%;
      cursor: pointer;
    }
    .dot.active {
      background-color: #0367a6;
    }
  </style>
</head>
<body>
  <header>
    <h1>Jornal Inclusão</h1>
    <img id="imgHeader" src="https://via.placeholder.com/200x200?text=Logo+APAE" alt="Logo APAE">
    <nav>
      <ul>
        <li><a href="#vida-escolar">Vida Escolar</a></li>
        <li><a href="#entrevistas">Entrevistas</a></li>
        <li><a href="#acessibilidade">Inclusão</a></li>
      </ul>
    </nav>
  </header>

  <main>
    <section id="vida-escolar">
      <h2>Vida Escolar</h2>
      <article>
        <h3>Projeto de Horta Inclusiva</h3>
        <p>Horta do CEPROLIM organizada pelos alunos da unidade III da APAE de Goiânia, junto ao Professor Erick.</p>
        <div class="carrossel-container">
          <div class="carrossel-track">
            <img src="https://via.placeholder.com/600x350?text=Horta" alt="Horta">
            <img src="https://via.placeholder.com/600x350?text=Jardinagem" alt="Jardinagem">
            <img src="https://via.placeholder.com/600x350?text=Horta+2" alt="Horta 2">
          </div>
          <button class="carrossel-btn prev">&#10094;</button>
          <button class="carrossel-btn next">&#10095;</button>
          <div class="carrossel-indicadores">
            <span class="dot active"></span>
            <span class="dot"></span>
            <span class="dot"></span>
          </div>
        </div>
      </article>
    </section>

    <section id="entrevistas">
      <h2>Entrevistas</h2>
      <article>
        <h3>Conversa com Diego da Silva Santos</h3>
        <p class="entrevista">Meu nome é Diego, tenho 32 anos, sou flamenguista, e sou estudante da APAE de Goiânia. Meu prato predileto é bucho de boi...</p>
        <div id="entrevista">
          <p><strong>Receita:</strong><br>
          - 1 kg de bucho de boi<br>
          - ½ cebola<br>
          - 4 cravinhos da índia<br>
          - Colorau, salsa, pimenta do reino, sal<br>
          <em>Modo de preparo:</em> Ferver o bucho, fritar bacon e linguiça, refogar e cozinhar na pressão até amolecer.</p>
        </div>
      </article>
    </section>

    <section id="acessibilidade">
      <h2>Acessibilidade & Inclusão</h2>
      <p>Semana Nacional da Pessoa com Deficiência Intelectual e/ou Múltipla. "Nada sobre nós, sem nós"</p>
      <img id="folder" src="https://via.placeholder.com/600x300?text=Semana+da+Inclusao" alt="Folder">
    </section>
  </main>

  <footer id="rodape">
    <p>&copy; 2025 Jornal Inclusão. Todos os direitos reservados.</p>
  </footer>

  <script>
    const track = document.querySelector('.carrossel-track');
    const slides = Array.from(track.children);
    const nextBtn = document.querySelector('.next');
    const prevBtn = document.querySelector('.prev');
    const dots = document.querySelectorAll('.dot');
    let currentIndex = 0;

    function updateCarrossel(index) {
      track.style.transform = `translateX(-${index * 100}%)`;
      dots.forEach(dot => dot.classList.remove('active'));
      dots[index].classList.add('active');
    }

    nextBtn.addEventListener('click', () => {
      currentIndex = (currentIndex + 1) % slides.length;
      updateCarrossel(currentIndex);
    });

    prevBtn.addEventListener('click', () => {
      currentIndex = (currentIndex - 1 + slides.length) % slides.length;
      updateCarrossel(currentIndex);
    });

    dots.forEach((dot, i) => {
      dot.addEventListener('click', () => {
        currentIndex = i;
        updateCarrossel(currentIndex);
      });
    });

    setInterval(() => {
      currentIndex = (currentIndex + 1) % slides.length;
      updateCarrossel(currentIndex);
    }, 5000);
  </script>
</body>
</html>
  )rawliteral";

  server.send(200, "text/html", html);
}


// ⚙️ Inicialização
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.println("Conectando ao Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);  // Rota principal
  server.begin();              // Inicia o servidor
  Serial.println("Servidor iniciado.");
}

// 🔁 Loop principal
void loop() {
  server.handleClient();  // Mantém o servidor respondendo
}

void setup() {
  Serial.begin(115200);

  // Inicializa o SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("Erro ao montar SPIFFS");
    return;
  }

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Conectando ao Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Rotas do servidor
  server.on("/", handleRoot);

  server.on("/assets/horta.jpg", HTTP_GET, []() {
    File file = SPIFFS.open("/horta.jpg", "r");
    server.streamFile(file, "image/jpeg");
    file.close();
  });

  server.on("/assets/jardinagem.jpg", HTTP_GET, []() {
    File file = SPIFFS.open("/jardinagem.jpg", "r");
    server.streamFile(file, "image/jpeg");
    file.close();
  });

  server.on("/assets/apae.png", HTTP_GET, []() {
    File file = SPIFFS.open("/apae.png", "r");
    server.streamFile(file, "image/png");
    file.close();
  });

  server.begin();  // Inicia o servidor
  Serial.println("Servidor iniciado.");
}

void loop() {
  server.handleClient();  // Mantém o servidor respondendo
}




