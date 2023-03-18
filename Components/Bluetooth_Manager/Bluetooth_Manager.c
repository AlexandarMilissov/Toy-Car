#include "Bluetooth_Manager.h"
#include "Common.h"
#include "esp_bt_device.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"
#include "esp32-hal-bt.h"
#include "esp_spp_api.h"
//char bl_controller_mac[] = "7c:66:ef:45:7e:e1";
//char bl_controller_mac[] = "d0:bc:c1:75:7e:e3";
esp_bd_addr_t bt_4 = {0xd0,0xbc,0xc1,0x75,0x7e,0xe3};
esp_bd_addr_t bt_5 = {0x7c,0x66,0xef,0x45,0x7e,0xe1};
esp_bd_addr_t moto = {0xc8,0x58,0x95,0xff,0x14,0x77};
#define bt bt_4

void bt_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param);
void BluetoothControllerInit();
void BluedroidInit();
void BluetoothGapInit();
void SppInit();

esp_bt_controller_config_t bt_config = BT_CONTROLLER_INIT_CONFIG_DEFAULT();

void Bluetooth_Manager_Init(btInitMode btInitState)
{    
    esp_bt_dev_set_device_name("ESP32");
    
    BluetoothControllerInit();
    BluedroidInit();
    switch (btInitState)
    {
        case btInitStateInitiator:
        {
            
            break;
        }
        case btInitStateAcceptorController:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}

void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param)
{
    switch(event)
    {
        case ESP_SPP_DISCOVERY_COMP_EVT:
        {
            if (param->disc_comp.status == ESP_SPP_SUCCESS) 
            {
                printf("ESP_SPP_DISCOVERY_COMP_EVT scn_num: %d\n", param->disc_comp.scn_num);
                for (uint8 i = 0; i < param->disc_comp.scn_num; i++) 
                {
                    printf("-- [%d] scn:%d service_name:%s\n", i, param->disc_comp.scn[i], param->disc_comp.service_name[i]);
                }
                /* We only connect to the first found server on the remote SPP acceptor here */
                esp_spp_connect(ESP_SPP_SEC_NONE, ESP_SPP_ROLE_MASTER, param->disc_comp.scn[0], bt);
            } 
            else 
            {
                printf("ESP_SPP_DISCOVERY_COMP_EVT status = %d\n", param->disc_comp.status);
            }

            //esp_spp_connect(ESP_SPP_SEC_NONE,ESP_SPP_ROLE_MASTER,param->disc_comp.scn[0],bt);
            break;
        }
        case ESP_SPP_CL_INIT_EVT:
        {
            printf("ESP_SPP_CL_INIT_EVT\n");
            break;
        }
        case ESP_SPP_OPEN_EVT:
        {
            printf("ESP_SPP_OPEN_EVT\n");
            break;
        }
        default:
        {
            printf("%d\n",event);
            break;
        }
    }
}
void bt_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param)
{
    static bool discoverd = false;
    if(ESP_BT_GAP_DISC_RES_EVT == event && false == discoverd)
    {
        struct disc_res_param* res = (struct disc_res_param*)param;
        for (uint8 i = 0; i < 6; i++)
        {
            if(bt[i] != res->bda[i])
            {
                return;
            }
            
        }
        printf("Eurika!  \n");
        for (uint8 i = 0; i < res->num_prop; i++)
        {
            switch(res->prop[i].type)
            {
                case ESP_BT_GAP_DEV_PROP_BDNAME:
                {
                    printf("Name: \n");
                    for(uint8 j = 0; j < res->prop[i].len; j++)
                    {
                        printf("%c",(char)((char*)res->prop[i].val + j));
                    }
                    printf("\n");
                    break;
                }
                case ESP_BT_GAP_DEV_PROP_COD:
                {
                    printf("Class: %u\n", (uint32)res->prop[i].val);
                    break;
                }
                case ESP_BT_GAP_DEV_PROP_RSSI:
                {
                    printf("RSSI: %d\n", (sint8)res->prop[i].val);
                    break;
                }
                case ESP_BT_GAP_DEV_PROP_EIR:
                {
                    printf("EIR %d:\n",res->prop[i].len);
                    uint8* items = res->prop[i].val;
                    for(uint8 j = 0; j < res->prop[i].len; j++)
                    {
                        printf("\t%u\n",items[j]);
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }     
        }
        
        printf("%02X-%02X-%02X-%02X-%02X-%02X\n",
                       res->bda[0], res->bda[1], res->bda[2], res->bda[3],
                       res->bda[4], res->bda[5]);
        discoverd = true;
        esp_bt_gap_cancel_discovery();

        
        esp_spp_start_discovery(res->bda);
    }
}

void BluetoothControllerInit()
{
}

void BluedroidInit()
{
    btStart();
    
    return;
}

void BluetoothGapInit()
{
    
    esp_bt_cod_t siscod;

    siscod.major   = esp_bt_gap_get_cod_major_dev(0x040680);
    siscod.minor   = esp_bt_gap_get_cod_minor_dev(0x040680);
    siscod.service = esp_bt_gap_get_cod_srvc(0x040680);

    esp_bt_gap_register_callback(bt_gap_cb);


    esp_bt_io_cap_t iocap = ESP_BT_IO_CAP_IN;
    esp_bt_gap_set_security_param(ESP_BT_SP_IOCAP_MODE,&iocap,sizeof(uint8_t));

    esp_bt_pin_code_t pin_code;
    esp_bt_gap_set_pin(ESP_BT_PIN_TYPE_VARIABLE, 0, pin_code);

    esp_bt_gap_set_cod(siscod, ESP_BT_INIT_COD);
    esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
    esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 30, 0);
}

void SppInit()
{   
    esp_spp_register_callback(esp_spp_cb);
    esp_spp_init(ESP_SPP_MODE_CB);
    esp_spp_start_srv(ESP_SPP_SEC_NONE,ESP_SPP_ROLE_SLAVE,0,"spp server");
}
