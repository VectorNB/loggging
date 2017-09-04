
#include "server.h"
#include "user.h"
extern USERPRV m_userprv;

/***********************************************************************
�ļ����ƣ�TCP_SERVER.C
��    �ܣ����TCP�������շ������յ�������ԭ·
***********************************************************************/

#define TCP_LOCAL_PORT   5050//���ط������˿�

struct tcp_pcb *PCB;


/***********************************************************************
�������ƣ�tcp_server_recv(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err)
��    �ܣ�TCP���ݽ��պͷ���
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺����һ���ص���������һ��TCP�ε����������ʱ�ᱻ����
***********************************************************************/
static err_t tcp_server_recv(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err)
{

	if(p != NULL)
	{
		tcp_recved(pcb, p->tot_len);//TCP ��������
	  m_userprv.m_usETHRXLength = p->tot_len;
		TCP_server_IN(p,m_userprv.m_ucETHRXbuff,(unsigned short *)&m_userprv.m_usETHRXLength);
		//userprv.toFPGALength = userprv.ETHRecLength;
		m_userprv.m_ucETHRXFLAG =1;//����������ɱ�־
		m_userprv.m_ucETHCommuFlag = 0X01; 
		pbuf_free(p); 											/* �ͷŸ�TCP�� */
	}
	else
	{
		tcp_close(pcb); 									    /* ��ΪTCP��������Ӧ�����ر�������ӣ� */
	}
	err = ERR_OK;
	return err;
}


/***********************************************************************
�������ƣ�tcp_server_accept(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err)
��    �ܣ��ص�����
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺����һ���ص���������һ�������Ѿ�����ʱ�ᱻ����
***********************************************************************/
static err_t tcp_server_accept(void *arg,struct tcp_pcb *pcb,err_t err)
{	
	PCB=pcb;
	tcp_setprio(pcb, TCP_PRIO_MIN); 		/* ���ûص��������ȼ��������ڼ�������ʱ�ر���Ҫ,�˺����������*/
	tcp_recv(pcb,tcp_server_recv); 		    /* ����TCP�ε�ʱ�Ļص����� */
	err = ERR_OK;
	return err;
}


/***********************************************************************
�������ƣ�TCP_server_init(void)
��    �ܣ����TCP�������ĳ�ʼ������Ҫ��ʹ��TCPͨѶ��������״̬
���������
���������
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
void TCP_server_init(void)
{
	
	struct tcp_pcb *pcb;
	/*****************************************************/
	pcb = tcp_new(); 								/* ����ͨ�ŵ�TCP���ƿ�(pcb) */
	tcp_bind(pcb,IP_ADDR_ANY,m_userprv.m_tIPinformation.port); 	    /* �󶨱���IP��ַ�Ͷ˿ںţ���Ϊtcp�������� */
	pcb = tcp_listen(pcb); 							/* �������״̬ */
	tcp_accept(pcb,tcp_server_accept); 			    /* ��������������ʱ�Ļص����� */

}

void TCP_server_out(unsigned char DATA_Buff[], unsigned int LEN)
{
		tcp_write(PCB,DATA_Buff,LEN,1);
		tcp_output(PCB);
}

void TCP_server_IN(struct pbuf *p,unsigned char DATA_Buff[], unsigned short *LEN)
{
	unsigned int i=0,j=0;
	char *data_temp;
	*LEN = p->tot_len;
	data_temp = p->payload;
	while(p !=NULL)
	{
		for(i=0;i<p->len;i++)
		{
			*(DATA_Buff+i+j) = *(data_temp+i);
		}
		j = p->len;
		p = p->next;
		data_temp = p->payload;
	}
}

