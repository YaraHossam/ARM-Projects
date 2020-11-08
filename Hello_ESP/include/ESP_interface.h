#ifndef ESP_INTERFACE_H
#define ESP_INTERFACE_H

void HESP_voidInit(void);
void HESP_voidConnectWiFi(u8* copy_wifiname , u8* copy_pass);
void HESP_voidConnectServer(u8* copy_IP , u8* copy_Port);
u8 HESP_u8SendReceiveData(void);

#endif
