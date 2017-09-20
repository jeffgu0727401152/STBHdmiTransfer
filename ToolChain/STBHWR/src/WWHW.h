#ifndef __WWHW_H__
#define __WWHW_H__


typedef                int              HW_INT32;
typedef unsigned       int              HW_UINT32;

typedef                short            HW_INT16;
typedef unsigned       short            HW_UINT16;


#define WWHW_RANGE_NUMBER				0x1         /* ʶ��Χ������     */
#define WWHW_RANGE_LOWER_CHAR			0x2         /* ʶ��Χ��Сд��ĸ */
#define WWHW_RANGE_UPPER_CHAR			0x4         /* ʶ��Χ����д��ĸ */
#define WWHW_RANGE_ASC_PUNCTUATION		0x8         /* ʶ��Χ����Ǳ���� */

/* ʶ��Χ��ASCII�룬�����֡�Сд��ĸ����д��ĸ�Ͱ�Ǳ���� */
#define WWHW_RANGE_ASCII				(WWHW_RANGE_NUMBER | WWHW_RANGE_LOWER_CHAR | WWHW_RANGE_UPPER_CHAR | WWHW_RANGE_ASC_PUNCTUATION)

#define WWHW_RANGE_GB2312				0x8000      /* ʶ��Χ��GB2312���� */
#define WWHW_RANGE_BIG5					0x200       /* ʶ��Χ��BIG5����   */
#define WWHW_RANGE_GBK					0x400       /* ʶ��Χ��GBK����    */
#define WWHW_RANGE_GB18030				0x1000      /* ʶ��Χ��GB18030-2003��涨�ĺ��� */

#define WWHW_RANGE_CHN_PUNCTUATION		0x800       /* ʶ��Χ�����ı���� */
#define WWHW_RANGE_PUNCTUATION	        (WWHW_RANGE_ASC_PUNCTUATION | WWHW_RANGE_CHN_PUNCTUATION)
#define WWHW_RANGE_CONTROL_CHAR			0x2000      /* ʶ��Χ���ո񡢻س��Լ�ɾ�����������ַ� */


/* ʶ��Χ��Ĭ��ʶ��Χ��ΪGB2312���֡����֡���ĸ�ͱ���š����������Ʒ�� */
#define WWHW_RANGE_DEFAULT				(WWHW_RANGE_GB2312 | WWHW_RANGE_ASCII | WWHW_RANGE_PUNCTUATION)

#ifndef WWAPI
#ifdef WWIMPORT
#define WWAPI  __declspec(dllimport)
#else
#define WWAPI	extern
#endif
#endif

#ifdef __cplusplus
extern "C"{
#endif

enum WWHW_ERROR
{
	WWHW_OK             = 0x0,
	WWHW_ERR_NOT_INIT   = 0x100,
	WWHW_ERR_NULL_DATA,       /* ����� */
	WWHW_ERR_INVALID_DATA,    /* ��ݸ�ʽ���� */
	WWHW_ERR_INVALID_PARAM,   /* �������  */
    WWHW_ERR_COUNT
};

/***********************************************************************************************************
// 
//  ��ʼ������
//
//  data - ��ݿ⿪ʼ��ַ�� �������������ݿ⣬����ת�� null ����
//  param - ����
//
//  ���أ�0 �ɹ�����0ʧ��
//
 ***********************************************************************************************************/
WWAPI int WWInitRecognition(const void * data,void* param);


/***********************************************************************************************************
// 
// �ر�����
//
// ���أ�0�ɹ�����0ʧ��
//
 ***********************************************************************************************************/
WWAPI int WWExitRecognition(void);


/***********************************************************************************************************
//
// ʶ����
//
// pStrokeAry       (in)  �ֹ켣��ָ����ڴ�����д����Ϊ�����п��ܻ��޸����������
// pResultStr       (out) ����Ľ�� (Unicode )
// iCount           (in)  Ҫ�󷵻غ�ѡ����
// uMatchRange      (in)  ʶ��Χ
//
// return ���ؽ��ĸ���
//
 ***********************************************************************************************************/
WWAPI int WWRecognizeChar(const short* pStrokeAry, unsigned short * pResultStr, int iCount, HW_UINT32 uMatchRange);
WWAPI int WWRecognize(const short* pStrokeAry, unsigned short * pResultStr, int iCount, HW_UINT32 uMatchRange);

#ifdef __cplusplus
}
#endif

#endif
