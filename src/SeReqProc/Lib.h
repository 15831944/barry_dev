# ifndef LIB_H
# define LIB_H
/*
��������:	��ָ��������Դ�ļ����н�������Ը������ݽ������洢����Ӧ�ļ�
			�˺������ⲿ���ýӿ�
����:	SorPath:	Դ�����ļ��ľ���·��		��:char sor[] = "D:\\HM\\DLL\\data\\data.ecg";
		DesPath:	Ŀ�������ļ���ŵľ���·��	��:char des[] = "D:\\HM\\DLL\\data";
���:	6500.ecg:	�洢�ĵ�����ֵ
		6500.pres:	�洢Ѫѹ����
		6500.resp:	�洢����������
		6500.tmp:	�洢���µ�ֵ
		6500.rr:	�洢Ѫ�����Ͷ�����
����ֵ: -1:�ļ������ڻ�·������
		 1:����ת���ɹ�
*/

#ifdef __cplusplus
extern "C"
{
#endif

extern int UnPackFile(char* SorPath, char* DesPath);

#ifdef __cplusplus
}
#endif

# endif
