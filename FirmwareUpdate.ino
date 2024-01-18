void handleFirmwareUpdate() {
  server.sendHeader("Connection", "close");
  server.send(200, "text/html", "<h1>OTA Firmware Update</h1>"
              "<form method='POST' action='/update' enctype='multipart/form-data'>"
              "  <input type='file' name='update'>"
              "  <input type='submit' value='Upload'>"
              "</form>");
}
