#ifndef WebSocket_h
#define WebSocket_h

#include "StructPlan.h"
#include "Arduino.h"
#include <WiFi.h>
#include <WebServer.h>
#include "esp_websocket_client.h"
// #include <AsyncTCP.h>
// #include <ESPAsyncWebServer.h>

class WebSocket
{
private:
    esp_websocket_client_handle_t client;
    // this part is for First Requests that indicate the GS try to connect to Rover
    static WebServer *server;
    static String ReceivedURL;
    static void HandleData();
    static bool IsConnected();
    static char *GetSocketsURL();

    static void EventHandler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
    void AcceptText();
    void ExecutionCommand(char *Body, FrameType Type);

public:
    WebSocket(const char *url);
    ~WebSocket();
    void SendText(char *message, size_t len);
    void SendBinary(const char *data, size_t len, size_t chunkSize);
    void DeserializeHeader(char *message, size_t len);
    void AESEncryptCBC(char *message, size_t len, char *IV);
    void AESDecryptCBC(char *message, size_t len, char *IV);

    static WebServer *InitWebSocketConnectListner();
    // they are not implmented yet
    void Connect(const char *url);
    void Disconnect();
    void onMessage(void (*callback)(String message));
    void onOpen(void (*callback)());
    void onClose(void (*callback)());
    void onError(void (*callback)(String message));
};
#endif