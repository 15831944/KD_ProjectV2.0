#ifndef _MSDU2017_H
#define _MSDU2017_H
#define MACADDR_LEN 6
#define MSDU2017_MAXSENDBUFLEN 2048
#include "Tools.h"
#include "MainFrm.h"
#include "cSerBuf_LoopRcv.h"
typedef enum 
{
	PLCAPP_ID_POINT_TRANSMIT = 0x0001,                  // ����������

	PLCAPP_ID_ROUND_TRANSMIT = 0x0002,                  // ·������
	PLCAPP_ID_PARALLEL_TRANSMIT = 0x0003,               //�������� 
	PLCAPP_ID_TIMING = 0x0004,                          //�㲥����ת������   Уʱ����????
	PLCAPP_ID_COMM_TEST = 0x0006,                       //ͨ�Ų��Ա���
	PLCAPP_ID_EVENT_REPORT = 0x0008,                    //�¼�����	
	PLCAPP_ID_GET_METERLIST = 0x0011,                   //��ѯ�ӽڵ�ע����
	PLCAPP_ID_SEARCH_START = 0x0012,                    //�����ӽڵ�����ע��: ��ʼ�ѱ�
	PLCAPP_ID_SEARCH_STOP = 0x0013,                     // ֹͣ�ӽڵ�ע��:     ֹͣ�ѱ�

	PLCAPP_ID_OK_CANCEL = 0x0020,                       //swcol
	PLCAPP_ID_COLLECT_TRANSMIT = 0x0021,                //swcol

	PLCAPP_ID_FTP_START = 0x0030,                       // ��ʼ���� 	
	PLCAPP_ID_FTP_STOP = 0x0031,                        // ֹͣ����
	PLCAPP_ID_FTP_TRANSFER = 0x0032,                    // �����ļ�����
	PLCAPP_ID_FTP_LC_TRANSFER = 0x0033,                 // �����ļ�����(����ת���ع㲥)
	PLCAPP_ID_FTP_GET_STATUS = 0x0034,                  // ��ѯվ������״̬
	PLCAPP_ID_FTP_EXEC = 0x0035,                        // ִ������
	PLCAPP_ID_FTP_GET_STAINFO = 0x0036,                 // ��ѯվ����Ϣ

	PLCAPP_ID_AUTH = 0x00a0,                            //��Ȩ��ȫ

	//��չ����
	PLCAPP_ID_EXTEND = 0x00f0                           //��չ����
} ePLCAPP_ID_TYPE;

//MAC��֡ͷ��ʽ
typedef struct
{
	INT16U          s_macver        : 4;                //Э��汾�� 0
	INT16U          s_ckqtei        : 12;               //ԭʼԴTEI  ��������tei�� 80 3F
	INT16U          s_nodetei       : 12;               //ԭʼĿ��TEI sta��tei FF 2F
	INT16U          s_mactype       : 4;                //�������� 0���� 1ȫ���㲥 2���ع㲥 3����㲥 2
	INT8U           s_macnum        : 5;                //���ʹ�����ֵ һ����1  01 
	INT8U           s_macbaoliu      : 3;               //����
} MacHead_first_5;//80 3F FF 2F 01 


typedef struct
{
	INT16U          s_msdulen       : 11;                //MSDU ���� 
	INT16U          s_rebootnum     : 4;                 //��������
	INT16U          s_dailujing      : 1;                //������·����ʶ 0δ���ô�����·��ģʽ
	INT8U           s_macrote_n     : 4;               //·��������
	INT8U           s_macrote_sn       : 4;                //·��ʣ������
	INT16U           s_macgbfx       : 2;               //�㲥���� 0˫�� 1 ���й㲥����CCO����㲥��STA��2��1�෴
	INT16U           s_ljxfbz       : 1;               //·���޸���־ 0 ��ǰ����δ������·���޸� 1�෴
	INT16U           s_macbz      : 1;               //MAC��ַ��־ 0δЯ��MAC��ַ  1�෴
	INT16U           s_macbaoliu      : 12;               //����
} MacHead_secend_5;//04 28 00 08 00

typedef struct
{
	INT8U      s_MacHeadDataBuf[30];//��MAC֡ͷ����
	INT16U     s_MacHeadDataLen;//��MAC֡ͷ���ȡ�
	union
	{
		MacHead_first_5   MacHead_first5;
		INT8U  s_MacHead_first[5];
	} u_MacHead_first_5;
	INT16U  msduNum;  //MSDU ���к� DF 01
	INT8U   msdutype;//MSDU ���� ����30,����Ӧ�ò㱨��48
	union
	{
		MacHead_secend_5   MacHead_secend5;
		INT8U  s_MacHead_secend[5];
	} u_MacHead_secend_5;
	INT8U   netnum;//�������к�
	INT8U   bl1;//����
	INT8U   bl2;//����
	INT8U    s_macadd[6]; //ԭʼԴMAC��ַ
	INT8U    s_mactoadd[6]; //ԭʼĿ��MAC��ַ
} MacHead;



//***************************MSDU�ṹ�壬��ʼ*********************************
//MsduӦ�ò�ͷ��ʽ
typedef struct
{
	INT8U		s_Port;									//���Ķ˿ں�
	INT16U		s_Id;									//����ID
	INT8U		s_Con;									//���Ŀ�����
} MsduHead;


typedef struct 
{
	INT16U          s_pctver        : 6;                //Э��汾��
	INT16U          s_headlen       : 6;                //����ͷ����
	INT16U          s_reserved      : 4;                //����
	INT16U          s_pcttype       : 4;                //ת�����ݵĹ�Լ����
	INT16U          s_datalen       : 12;               //ת�����ݳ���
} sMSDU_TranData_DOWNHEAD4;// ��������Ӧ������֡ͷǰ�ĸ��ֽ�


typedef struct 
{
	INT16U          s_pctver        : 6;                //Э��汾��
	INT16U          s_headlen       : 6;                //����ͷ����
	INT16U          s_ack_flag      : 4;                //Ӧ��״̬
	INT16U          s_pcttype       : 4;                //ת�����ݵĹ�Լ����
	INT16U          s_datalen       : 12;               //ת�����ݳ���
} sMSDU_TranData_UPHEAD4;// ��������Ӧ������֡ͷǰ�ĸ��ֽ�

//Ӧ�ò㡪�����ݴ���֡ͷ��ʽ��Ӧ���ڵ㳭���ֳ�������������
typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//��֡MSDU����
	INT16U     s_SendDataLen;//��֡MSDU���ȡ�
    MsduHead   Msdu2017_head;
	union
	{
		sMSDU_TranData_DOWNHEAD4   s_DownHead4;
		INT8U  s_MSDUDownHead4[4];
	} u_TranDataDownHead4;
	INT16U          s_seq;                              //�������
	INT8U           s_timeout;                          //���ܱ�ʱʱ��
	INT8U           s_select;                           //ѡ����
	INT8U *         s_databuf;                          //���͵�����Դ
} sPLCPacket_App_Down_TranData;


//Ӧ�ò㡪�����ݴ���֡ͷ��ʽ��Ӧ���ڵ㳭���ֳ�������������
typedef struct 
{
    MsduHead   Msdu2017_head;
	union
	{
		sMSDU_TranData_UPHEAD4    s_UpHead4;
		INT8U  s_MSDUUpHead4[4];
	} u_TranDataUpHead4;
	INT16U          s_seq;                              //�������
	INT16U          s_select;                           //ѡ����
	INT8U *         s_databuf;                          //���յ�����Դ
} sPLCPacket_App_Up_TranData;



//////////////////////******************MSDU��376.2����*****************************////////////////////////////
typedef struct 
{
	INT16U          s_pctver        : 6;                //Э��汾��
	INT16U          s_headlen       : 6;                //����ͷ����
	INT16U          s_reserved      : 4;                //����
} union_Down_13762;//


typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//��֡MSDU����
	INT16U     s_SendDataLen;//��֡MSDU���ȡ�
    MsduHead   Msdu2017_head;
	union
	{
		union_Down_13762    s_Down13762_2;
		INT8U  s_Down13762[2];
	} u_DataDown_13762_2;
	//INT16U          s_KID;                              //�ڲ���չID
	INT16U          s_3762datalen;                       //���ĳ���
	INT16U          s_seq;                              //�������
	INT8U *         s_3762databuf;                       //376.2����
} sPLCPacket_App_Down_13762;

/////////////////////***********************************************////////////////////////////


















//�����ӽڵ�ע�ᣬ����
typedef struct 
{
MsduHead   Msdu2017_head;
INT16U          s_pctver        : 6;                //Э��汾��
INT16U          s_headlen       : 6;                //����ͷ����
INT16U          s_forceackfg    : 1;                //ǿ��Ӧ���־
INT16U          s_regpa         : 3;                //�ӽڵ�ע�����
INT16U          s_reserved;                         //����
INT32U          s_seq;                              //�������
} sPLCPacket_App_Down_EnableRegMsg;


//��ѯ�ӽڵ�ע�������ĸ�ʽ˵��������
typedef struct 
{
MsduHead   Msdu2017_head;
INT16U          s_pctver        : 6;                //Э��汾��
INT16U          s_headlen       : 6;                //����ͷ����
INT16U          s_forceackfg    : 1;                //ǿ��Ӧ���־
INT16U          s_regpa         : 3;                //�ӽڵ�ע�����
INT16U          s_reserved;                         //����
INT32U          s_seq;                              //�������
} sPLCPacket_App_Down_GetRegMsg;


//�ýṹ���������ǿ��ת��
typedef struct 
{
INT8U           s_staadd[6];                        //���ܱ��ַ
INT8U           s_pcttype;                          //��Լ����
INT8U           s_devicetype    : 4;                //ģ������
INT8U           s_secreserved   : 4;                // ����
} sRegNodeMsg;


//��ѯ�ӽڵ�ע�������ĸ�ʽ˵��������
typedef struct 
{
MsduHead   Msdu2017_head;
INT16U          s_pctver        : 6;                //Э��汾��
INT16U          s_headlen       : 6;                //����ͷ����
INT16U          s_status        : 1;                //״̬�ֶΣ����STA�����ѱ�ʱ�����յ�CCO�·��Ĳ�ѯ�ӽڵ�ע�������������б����е�ǿ��Ӧ��״̬Ϊǿ��Ӧ��ʱ��

//����״̬λ��Ϊ1����STA���ѱ���ɣ����յ�CCO�·��Ĳ�ѯ�ӽڵ�ע��������ʱ������״̬λ��Ϊ0��
INT16U          s_regpa         : 3;                //�ӽڵ�ע�����
INT8U           s_meter_num;                        //�������
INT8U           s_type;                             //0:��� 1:�ɼ���
INT8U           s_deviceadd[MACADDR_LEN];           //�豸��ַ���ɼ��������ַ
INT8U           s_idBuf[MACADDR_LEN];               //�豸ID
INT32U          s_seq;                              //�������
INT32U          s_reserved;                         //����
INT8U           s_DevMacAddr[MACADDR_LEN];          //Դ(�ڵ�)MAC��ַ
INT8U           s_DestMacAddr[MACADDR_LEN];         //Ŀ��MAC��ַ
INT16U          s_DataLen;                          //���ݳ���
INT8U *         s_DataBuf;                          //������
} sPLCPacket_App_Up_GetRegMsg;


//ֹͣ�ӽڵ�ע�ᣬ����
typedef struct 
{
MsduHead   Msdu2017_head;
INT16U          s_pctver        : 6;                //Э��汾��
INT16U          s_headlen       : 6;                //����ͷ����
INT16U          s_reserved      : 4;                //����
INT16U          s_secreserved;                      //����
INT32U          s_seq;                              //�������
} sPLCPacket_App_Down_StopRegMsg;


////////////////////////////////ȷ��/���ϣ�������//////////////////////////////////////////////////////

typedef struct 
{
	INT8U          s_pctver        : 6;                //Э��汾��
	INT8U          s_headlen       : 6;                //����ͷ����
	INT8U          s_dir           : 1;                //����λ 0=���з���,1=���з���
	INT8U          s_okcancel      : 1;                //ȷ��λ 0=����,1=ȷ��
	INT16U          s_secreserved   : 2;                //����
} union_ok_cancel2;//

typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//��֡MSDU����
	INT16U     s_SendDataLen;//��֡MSDU���ȡ�
	MsduHead   Msdu2017_head;
	union
	{
		union_ok_cancel2    s_union_ok_cancel_2;
		INT8U  s_union_ok_cancel2[2];
	} u_ok_cancel_2;
	INT16U          s_seq;                              //�������
} sPLCPacket_App_OKCancel;

////////////////////////////////////////////END///////////////////////////////////////////////////////////

//Уʱ���ģ�����
typedef struct 
{
MsduHead   Msdu2017_head;
INT16U          s_pctver        : 6;                //Э��汾��
INT16U          s_headlen       : 6;                //����ͷ����
INT16U          s_reserved      : 4;                //����
INT16U          s_secreserved   : 4;                //����
INT16U          s_datalen       : 12;               //���ݳ���
INT8U *         s_databuf;                          //����
} sPLCPacket_App_Down_AdjustTime;


//�¼�������
typedef struct 
{
MsduHead   Msdu2017_head;
INT32U          s_pctver        : 6;                //Э��汾��
INT32U          s_headlen       : 6;                //����ͷ����
INT32U          s_dir           : 1;                //����λ
INT32U          s_start         : 1;                //����λ
INT32U          s_function      : 6;                //������
INT32U          s_datalen       : 12;               //���ݳ���
INT16U          s_seq;                              //�������
INT8U           s_staadd[MACADDR_LEN];              //���ܱ��ַ
INT8U *         s_databuf;                          //����
} sPLCPacket_App_Up_Event;


//�¼�������
typedef struct 
{
MsduHead   Msdu2017_head;
INT32U          s_pctver        : 6;                //Э��汾��
INT32U          s_headlen       : 6;                //����ͷ����
INT32U          s_dir           : 1;                //����λ
INT32U          s_start         : 1;                //����λ
INT32U          s_function      : 6;                //������
INT32U          s_datalen       : 12;               //���ݳ���
INT16U          s_seq;                              //�������
INT8U           s_staadd[MACADDR_LEN];              //���ܱ��ַ����Э��������û��
INT8U *         s_databuf;                          //����
} sPLCPacket_App_Down_Event;


/////////////////////////////////////////ͨ�Ų��ԣ�����//////////////////////////////////////////////////////////////

typedef struct 
{
	INT16U          s_pctver        : 6;                //Э��汾��
	INT16U          s_headlen       : 6;                //����ͷ����
	INT16U          s_ack_flag      : 4;                //����
	INT16U          s_pcttype       : 4;                //ת�����ݵĹ�Լ����//0 ͸������ 1 DL/T645��1997 2 DL/T645��2007 3 DLT698.45
	INT16U          s_datalen       : 12;               //ת�����ݳ���
} sMSDU_ConnectTest4;// ͨ�Ų������õ��ĸ��ֽ�

typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//��֡MSDU����
	INT16U     s_SendDataLen;//��֡MSDU���ȡ�
	MsduHead   Msdu2017_head;
	union
	{
		sMSDU_ConnectTest4   s_ConnectTest4;
		INT8U  s_MSDUConnectTest4[4];
	} u_ConnectTest4;
	INT8U *         s_databuf;                          //����
} sPLCPacket_App_Down_ConnectTest;

///////////////////////////////////////END//////////////////////////////////////////////////////////

//FTP ��ʼ����������

typedef struct 
{
INT32U          s_pctver        : 6;                //Э��汾��
INT32U          s_headlen       : 6;                //����ͷ����
INT32U          s_reserved      : 20;               //����
} union_Down_FTPStart;

typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//��֡MSDU����
	INT16U     s_SendDataLen;//��֡MSDU���ȡ�
    MsduHead   Msdu2017_head;
	union
	{
		union_Down_FTPStart    s_DownFTP4;
		INT8U  s_MSDUFDownFTP4[4];
	} u_DataDownFTP4START;
	INT32U          s_ftpID;                            //����ID
	INT16U          s_window;                           //����ʱ�䴰
	INT16U          s_blksize;                          //�������С
	INT32U          s_filesize;                         //�����ļ���С
	INT32U          s_fileCRC;                          //�ļ�У�� 
} sPLCPacket_App_Down_FTPStart;

//FTP ��ʼ����������Ӧ��

typedef struct 
{
	INT32U          s_pctver        : 6;                //Э��汾��
	INT32U          s_headlen       : 6;                //����ͷ����
	INT32U          s_reserved      : 12;               //����
	INT32U          s_result        : 8;                //���������
} union_Up_FTPStart;

typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//��֡MSDU����
	INT16U     s_SendDataLen;//��֡MSDU���ȡ�
    MsduHead   Msdu2017_head;
	union
	{
		union_Up_FTPStart    s_UpFTP4;
		INT8U  s_MSDUFUpFTP4[4];
	} u_DataUpFTP4START;

	INT32U          s_ftpID;                            //����ID
} sPLCPacket_App_Up_FTPStart;


//FTP ֹͣ����������
typedef struct 
{

	INT32U          s_pctver        : 6;                //Э��汾��
	INT32U          s_headlen       : 6;                //����ͷ����
	INT32U          s_reserved      : 20;               //����

} union_Down_FTPStop;

typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//��֡MSDU����
	INT16U     s_SendDataLen;//��֡MSDU���ȡ�
    MsduHead   Msdu2017_head;
	union
	{
		union_Down_FTPStop    s_DownFTP4;
		INT8U  s_MSDUFDownFTP4[4];
	} u_DataDownFTP4STOP;

	INT32U          s_ftpID;                            //����ID
} sPLCPacket_App_Down_FTPStop;


//FTP �ļ����䣬����
typedef struct 
{
	INT16U          s_pctver        : 6;                //Э��汾��
	INT16U          s_headlen       : 6;                //����ͷ����
	INT16U          s_reserved      : 4;                //����    
} union_Down_FTPTransfile;
typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//��֡MSDU����
	INT16U     s_SendDataLen;//��֡MSDU���ȡ�
    MsduHead   Msdu2017_head;
	union
	{
		union_Down_FTPTransfile    s_DownFTPTransfile2;
		INT8U  s_DownFTPFile[2];
	} u_DataDownFTPTransfile;

	INT16U          s_blksize;                          //���ݿ��С
	INT32U          s_ftpID;                            //����ID
	INT32U          s_blkno;                            //���ݿ���
	INT8U *         s_DataBuf;                          //����       
} sPLCPacket_App_Down_FTPTransfile;


//FTP ��ѯվ������״̬������

typedef struct 
{

	INT16U          s_pctver        : 6;                //Э��汾��
	INT16U          s_headlen       : 6;                //����ͷ����
	INT16U          s_reserved      : 4;                //����
} union_Down_FTPGetStatus;
typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//��֡MSDU����
	INT16U     s_SendDataLen;//��֡MSDU���ȡ�
    MsduHead   Msdu2017_head;
	union
	{
		union_Down_FTPGetStatus    s_DownFTPGetStatus2;
		INT8U  s_DownFTPStatus[2];
	} u_DataDownFTPGetStatus;

	INT16U          s_blknum;                           //���ݿ���
	INT32U          s_startno;                          //��ʼ���ݿ���    
	INT32U          s_ftpID;                            //����ID
} sPLCPacket_App_Down_FTPGetStatus;


//FTP ��ѯվ������״̬������
typedef struct 
{

	INT16U          s_pctver        : 6;                //Э��汾��
	INT16U          s_headlen       : 6;                //����ͷ����
	INT16U          s_status        : 4;                //����

} union_Up_FTPGetStatus;
typedef struct 
{
    MsduHead   Msdu2017_head;
	union
	{
		union_Up_FTPGetStatus    s_UpFTPGetStatus2;
		INT8U  s_UpFTPStatus[2];
	} u_DataUpFTPGetStatus;

	INT16U          s_blknum;                           //���ݿ���
	INT32U          s_startno;                          //��ʼ���ݿ���    
	INT32U          s_ftpID;                            //����ID
	INT8U *         s_DataBuf;                          //λͼ
} sPLCPacket_App_Up_FTPGetStatus;


//FTP ִ������������
typedef struct 
{

	INT16U          s_pctver        : 6;                //Э��汾��
	INT16U          s_headlen       : 6;                //����ͷ����
	INT16U          s_reserved      : 4;                //����

} union_Down_FTPExec;
typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//��֡MSDU����
	INT16U     s_SendDataLen;//��֡MSDU���ȡ�
    MsduHead   Msdu2017_head;
	union
	{
		union_Down_FTPExec    s_DoFTPFTPExec2;
		INT8U  s_DownFTPExec[2];
	} u_DataDownFTPExec;

	INT16U          s_waitsec;                          //�ȴ���λʱ��
	INT32U          s_ftpID;                            //����ID    
	INT32U          s_trysec;                           //������ʱ��
} sPLCPacket_App_Down_FTPExec;


//FTP ��ѯվ����Ϣ������
typedef struct 
{
	INT16U          s_pctver        : 6;                //Э��汾��
	INT16U          s_headlen       : 6;                //����ͷ����
	INT16U          s_reserved      : 12;                //����
   
} union_Down_FTPGetInfo;
typedef struct 
{
	INT8U      s_SendDataBuf[MSDU2017_MAXSENDBUFLEN];//��֡MSDU����
	INT16U     s_SendDataLen;//��֡MSDU���ȡ�
    MsduHead   Msdu2017_head;
	union
	{
		union_Down_FTPGetInfo    s_DoFTPGetInfo3;
		INT8U  s_DownFTPGetInfo[3];
	} u_DataDownFTPGetInfo;

	INT8U           s_infonum;                          //��Ϣ�б�Ԫ�ظ���
	INT8U *         s_infoDataBuf;                          //����    
} sPLCPacket_App_Down_FTPGetInfo;


//FTP ��ѯվ����Ϣ������
typedef struct 
{
	INT32U          s_pctver        : 6;                //Э��汾��
	INT32U          s_headlen       : 6;                //����ͷ����
	INT32U          s_reserved      : 12;               //����
	INT32U          s_infonum       : 8;                //��Ϣ�б�Ԫ�ظ���
} union_Up_FTPGetInfo;
typedef struct 
{
    MsduHead   Msdu2017_head;
	union
	{
		union_Up_FTPGetInfo    s_UpFTPGetInfo4;
		INT8U  s_UpFTPGetInfo[4];
	} u_DataUpFTPGetInfo;
	INT32U          s_ftpID;                            //����ID        
	INT8U *         s_DataBuf;                          //����    
} sPLCPacket_App_Up_FTPGetInfo;


//��չ
typedef struct 
{
INT8U           s_Port;                             //���Ķ˿ں�
INT16U          s_Id;                               //����ID
INT8U           s_Con;                              //���Ŀ�����
INT16U          s_pctver        : 6;                //Э��汾��
INT16U          s_headlen       : 6;                //����ͷ����
INT16U          s_reserved      : 4;                //����
INT16U          s_ExtendId;                         //��չID
INT16U          s_DataLen;                          //�������ݵĸ���
INT16U          s_seq;                              //�������
INT8U *         s_DataBuf;                          //����������ָ�룬��Σָ�룬��ǰҪ����Ƿ���ֵ��Ҫָ��Ϸ��ռ�
} sPLCPacket_App_Down_Extend;

class MSDU2017
{
public:
	MSDU2017(void);
	~MSDU2017(void);

	//**** ��MSDU��MAC֡ͷ******//
	INT8U Fill_MacHeadStuct(TH_INOUT MacHead &Down_MacHeadForMsdu,INT16U msdulen,INT8U msdutype,INT16U msduseq,INT8U *y_mac,INT8U *to_mac,INT16U y_tei,INT16U to_tei,INT8U sendtype,INT8U macbz);//����MSDU֡����MAC֡ͷ�ṹ
	INT8U Code_MacHeadForMsdu(TH_INOUT MacHead &Down_MacHeadForMsdu);//��MAC֡ͷ����


	//****����MSDU******//
	INT8U Fill_Down_TranDataFrame(TH_INOUT sPLCPacket_App_Down_TranData &Down_TranDataCreatFrame,INT8U *OtherDataBuf,INT16U OtherDataBufLen,INT8U TYPE);//MSDU����ṹ�����
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_TranData &Down_TranDataCreatFrame);//MSDU������֡
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_TranData &Down_TranDataCreatFrame);//�����ֽ�������У��

	//**********//
	//****ת��376.2MSDU******//
	INT8U Fill_DownMSDU_13762Frame(TH_INOUT sPLCPacket_App_Down_13762 &Down_13762CreatFrame,INT8U *s_13762DataBuf,INT16U s_13762DataBufLen);//MSDU��13762�ṹ�����
	INT8U Code_DownMSDU_13762Frame(TH_INOUT sPLCPacket_App_Down_13762 &Down_13762CreatFrame);//MSDU��13762��֡
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_13762 &Down_13762CreatFrame);//�����ֽ�������У��
	//**********//
	//**********//

/****************��������MSDU*********************/
	//*****��ʼ����*****//
	INT8U Fill_sPLCPacket_App_Down_FTPStart(TH_INOUT sPLCPacket_App_Down_FTPStart &Down_FTPStartCreatFrame,INT16U windowTime,INT16U blksize,INT32U filesize,INT32U fileCRC);
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPStart &Down_FTPStartCreatFrame);
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPStart &Down_FTPStartCreatFrame);//�����ֽ�������У��

	//****ֹͣ����MSDU******//
	INT8U Fill_sPLCPacket_App_Down_FTPStop(TH_INOUT sPLCPacket_App_Down_FTPStop &Down_FTPStopCreatFrame,INT32U UPID);
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPStop &Down_FTPStopCreatFrame);
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPStop &Down_FTPStopCreatFrame);//�����ֽ�������У��

	//*****�ļ�����MSDU*****//
	INT8U Fill_sPLCPacket_App_Down_FTPTransfile(TH_INOUT sPLCPacket_App_Down_FTPTransfile &Down_FTPTransfileCreatFrame,INT16U blksize,INT32U UPID,INT32U blkno,INT8U *s_FileDataBuf);
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPTransfile &Down_FTPTransfileCreatFrame);
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPTransfile &Down_FTPTransfileCreatFrame);//�����ֽ�������У��

	//*****��ѯվ������״̬MSDU*****//

	INT8U Fill_sPLCPacket_App_Down_FTPGetStatus(TH_INOUT sPLCPacket_App_Down_FTPGetStatus &Down_FTPGetStatusCreatFrame,INT16U s_blknum,INT32U s_startno,INT32U s_ftpID);
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPGetStatus &Down_FTPGetStatusCreatFrame);
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPGetStatus &Down_FTPGetStatusCreatFrame);//�����ֽ�������У��

	//*****ִ������MSDU*****//

	INT8U Fill_sPLCPacket_App_Down_FTPExec(TH_INOUT sPLCPacket_App_Down_FTPExec &Down_FTPExecCreatFrame,INT8U *OtherDataBuf,INT16U OtherDataBufLen,INT8U TYPE);
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPExec &Down_FTPExecCreatFrame);
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPExec &Down_FTPExecCreatFrame);//�����ֽ�������У��

	//*****��ѯվ����ϢMSDU*****//
	//INT8U infonum;                          //��Ϣ�б�Ԫ�ظ���
	//INT8U *infoDataBuf;                          //����  
	INT8U Fill_sPLCPacket_App_Down_FTPGetInfo(TH_INOUT sPLCPacket_App_Down_FTPGetInfo &Down_FTPGetInfoCreatFrame,INT8U infonum,INT8U *infoDataBuf);
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_FTPGetInfo &Down_FTPGetInfoCreatFrame);
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_FTPGetInfo &Down_FTPGetInfoCreatFrame);//�����ֽ�������У��

/*******************************************/	
		//****ȷ�Ϸ���MSDU******//
	INT8U Fill_App_OKCancel(TH_INOUT sPLCPacket_App_OKCancel &App_OKCancel,INT8U dir,INT8U okcancel,INT16U seq);//MSDU����ṹ�����
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_OKCancel &App_OKCancel);//MSDU������֡
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_OKCancel &App_OKCancel);//�����ֽ�������У��
/*********************************************/

/*******************************************/	
		//****ͨ�Ų���MSDU******//
	INT8U Fill_App_Down_ConnectTest(TH_INOUT sPLCPacket_App_Down_ConnectTest &App_Down_ConnectTest,INT8U *OtherDataBuf,INT16U OtherDataBufLen,INT8U TYPE);//MSDU����ṹ�����
	INT8U Code_DownMsduFrame(TH_INOUT sPLCPacket_App_Down_ConnectTest &App_Down_ConnectTest);//MSDU������֡
	INT8U Add4BataIntegrityCheck(TH_INOUT sPLCPacket_App_Down_ConnectTest &App_Down_ConnectTest);//�����ֽ�������У��
/*********************************************/


	///////////////////MSDU����///////////////////////////
	INT8U Decode_Down_TranDataFrame(INT8U *DataBuf);//MSDU�Ľ�֡



};
#endif

