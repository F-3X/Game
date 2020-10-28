#include<Windows.h>   //���������ڳ���
#include<time.h>

//��ͼ
int g_arrBackground[20][10] = { 0 };

//����˹����
int g_arrElsfk[2][4] = { 0 };

//���ڴ���������
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//���ڻ�ͼ��������
void OnPaint(HDC hDC);
//���Ʒ�������
void DrawBlock(HDC hDC);
//������ɶ���˹��������
void CreateTrtrisBlock();

//main:�ڴ�����ڳ��� 
//WinMain:���ڳ������ں��� 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//��һ������

	//1����ƴ����ࣨ���һ�����ڵ����ͣ� 
	TCHAR szAppClassName[] = TEXT("DunkaiEDU");

	WNDCLASS wc = { 0 };
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255)); //����ı�����ɫ����
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);		   //���ع��
	wc.lpfnWndProc   = WindowProc;					       //���ڴ�����
	wc.hInstance     = hInstance;						   //��ǰӦ�ó���ʵ�����
	wc.style         = CS_HREDRAW | CS_VREDRAW;            //������ķ��
	wc.lpszClassName = szAppClassName;					   //���ڵ�������

	//2��ע�ᴰ���ࣨ������׼��ͬ�⣩
	RegisterClass(&wc);

	//3���������ڣ�ʲô���ͣ�
	HWND hWnd = CreateWindow(
		szAppClassName,										//����������
		L"F-3X����˹����",									//���ڵı���
		WS_BORDER | WS_CAPTION | WS_SYSMENU |WS_MINIMIZEBOX, //���ڵķ��
		200, 100,											//�������Ͻ�����
		500, 630,											//���ڵĿ�͸�
		NULL,												//�����ھ��
		NULL,												//�˵����
		hInstance,											//Ӧ�ó���ʵ�����
		NULL												//������Ϣ
	);

	//4����ʾ����
	ShowWindow(hWnd, SW_SHOW);

	//5�����´���
	UpdateWindow(hWnd);

	//6����Ϣѭ�� 
	MSG msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		//���������Ϣת��Ϊ�ַ���Ϣ
		TranslateMessage(&msg);
		//����Ϣ�ַ������ڴ�����
		DispatchMessage(&msg);
	}
	return 0;
}

//���ڴ�����
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;

	switch (uMsg)
	{
	case WM_CREATE:
		CreateTrtrisBlock();break;
	case WM_PAINT://���ڻ�ͼ��Ϣ
		//��ʼ��ͼ
		hDC=BeginPaint(hWnd,&ps);

		OnPaint(hDC);

		//������ͼ
		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE://���ڹر���Ϣ
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY://����������Ϣ
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//���ڻ�ͼ����
void OnPaint(HDC hDC) 
{
	//����Ϸ�߿�
	Rectangle(hDC, 0, 0, 300, 600);

	//������
	DrawBlock(hDC);
}

//���Ʒ���
void DrawBlock(HDC hDC)
{
	for (int i = 0;i < 20;i++) //��
	{
		for (int j = 0;j < 10;j++) //��
		{
			if (g_arrBackground[i][j] == 1|| g_arrBackground[i][j]==2)
			{
				//��������
				HPEN hPen = CreatePen(PS_SOLID, 1, RGB(50, 78, 188));
				HPEN oldPen = (HPEN)SelectObject(hDC, hPen);
				//������ˢ
				HBRUSH hBrush=CreateSolidBrush(RGB(51,201,255));
				HBRUSH oldBrush =(HBRUSH) SelectObject(hDC, hBrush);
				Rectangle(hDC, j * 30+1, i * 30+1, j * 30 + 30-1, i * 30 + 30-1);
				SelectObject(hDC, oldBrush);
			}
		}
	}
}

//������ɶ���˹����
void CreateTrtrisBlock() 
{
	srand((UINT)time(NULL));
	int nIndex = rand() % 7;//0->6

	switch (nIndex) 
	{
	case 0:
		g_arrElsfk[0][0] = 1, g_arrElsfk[0][1] = 0, g_arrElsfk[0][2] = 0, g_arrElsfk[0][3] = 0;
		g_arrElsfk[1][0] = 1, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 1, g_arrElsfk[1][3] = 0;
		break;
	case 1:
		g_arrElsfk[0][0] =01, g_arrElsfk[0][1] = 0, g_arrElsfk[0][2] = 1, g_arrElsfk[0][3] = 0;
		g_arrElsfk[1][0] = 1, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 1, g_arrElsfk[1][3] = 0;
		break;
	case 2:
		g_arrElsfk[0][0] = 1, g_arrElsfk[0][1] = 1, g_arrElsfk[0][2] = 0, g_arrElsfk[0][3] = 0;
		g_arrElsfk[1][0] = 0, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 1, g_arrElsfk[1][3] = 0;
		break;
	case 3:
		g_arrElsfk[0][0] = 0, g_arrElsfk[0][1] = 1, g_arrElsfk[0][2] = 1, g_arrElsfk[0][3] = 0;
		g_arrElsfk[1][0] = 1, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 0, g_arrElsfk[1][3] = 0;
		break;
	case 4:
		g_arrElsfk[0][0] = 1, g_arrElsfk[0][1] = 1, g_arrElsfk[0][2] = 0, g_arrElsfk[0][3] = 0;
		g_arrElsfk[1][0] = 1, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 0, g_arrElsfk[1][3] = 0;
		break;
	case 5:
		g_arrElsfk[0][0] = 0, g_arrElsfk[0][1] = 1, g_arrElsfk[0][2] = 0, g_arrElsfk[0][3] = 0;
		g_arrElsfk[1][0] = 1, g_arrElsfk[1][1] = 1, g_arrElsfk[1][2] = 1, g_arrElsfk[1][3] = 0;
		break;
	case 6:
		g_arrElsfk[0][0] = 1, g_arrElsfk[0][1] = 1, g_arrElsfk[0][2] = 1, g_arrElsfk[0][3] = 1;
		g_arrElsfk[1][0] = 0, g_arrElsfk[1][1] = 0, g_arrElsfk[1][2] = 0, g_arrElsfk[1][3] = 0;
		break;
	}

	//���Ƶ�������
	for (int i = 0;i < 2;i++) 
	{
		for (int j = 0;j < 4;j++) 
		{
			g_arrBackground[i][j+4] = g_arrElsfk[i][j];
		}
	}
}