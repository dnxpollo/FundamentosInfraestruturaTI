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

  Seu código deve estar escrito aqui para subir para o servidor.
  No meu caso, usei essa atividade para subir um pequeno jornal que faço com os alunos 
  (esse jornal pode ser visto em: https://github.com/dnxpollo/Jornal-APAE)

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




