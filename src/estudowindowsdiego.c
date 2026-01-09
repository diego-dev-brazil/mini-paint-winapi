#include <windows.h>

HBITMAP hBitmap = NULL;
HDC hdcMem = NULL;
int largura, altura;
int desenho = 0;
POINT pontoant;
#define TELAMENU 0
#define TELAPINTA 1
int estado = TELAMENU;
RECT botaotitulo;
RECT botaocores;
int Menucores = 0;
RECT botaovermelho;
RECT botaoverde;
RECT botaoazul;
RECT botaoroxo;
RECT botaopreto;
RECT botaoamarelo;
RECT botaobranco;

COLORREF cor = RGB(0,0,0);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    	
    	case WM_CREATE: {
		    HDC hdc = GetDC(hwnd);
		
		    largura = 900;
		    altura  = 600;
		
		    hdcMem = CreateCompatibleDC(hdc);
		    hBitmap = CreateCompatibleBitmap(hdc, largura, altura);
		    SelectObject(hdcMem, hBitmap);
		
		    RECT r = {0, 0, largura, altura};
		    FillRect(hdcMem, &r, (HBRUSH)(COLOR_WINDOW + 1));
		
		    ReleaseDC(hwnd, hdc);
		    return 0;
		}
		
		case WM_KEYDOWN:
    		switch (wParam){
    			case 'R': cor = RGB (255,0,0); break;
    			case 'G': cor = RGB (0,255,0); break;
    			case 'B': cor = RGB (0,0,255); break;
    			case 'O': cor = RGB (255,165,0); break;
    			case 'P': cor = RGB (157,0,255); break;
    			case 'K': cor = RGB (0,0,0); break;
    			case 'E': cor = RGB (255,255,255); break;
    			case 'J':
    				MessageBox (hwnd,"R - RED\nG - GREEN\nB - BLUE\nO - ORANGE\nP - PURPLE\nK - BLACK","HELP",MB_OK); break;
    			case VK_ESCAPE: estado = TELAMENU;
								InvalidateRect(hwnd, NULL, TRUE); 
							break;
			}
			return 0;

    	case WM_SIZE: {
			if (wParam == SIZE_MINIMIZED)
		    return 0;

		    int novaLargura = LOWORD(lParam);
		    int novaAltura  = HIWORD(lParam);
			
			HDC hdc = GetDC(hwnd);
			
			HDC hdcNovo = CreateCompatibleDC (hdc);
		    HBITMAP bmpNovo = CreateCompatibleBitmap(hdc, novaLargura, novaAltura);
		    SelectObject(hdcNovo, bmpNovo);
			
		    
	     	HBRUSH fundo = (HBRUSH)(COLOR_WINDOW + 1);
		    RECT r = {0, 0, novaLargura, novaAltura};
			FillRect(hdcNovo, &r, fundo);
			
			
			if (hdcMem) {
				BitBlt(
					hdcNovo,0,0,
					largura, altura, hdcMem, 0, 0,
					SRCCOPY
				);
			}
			DeleteDC(hdcMem);
        	DeleteObject(hBitmap);
        	
        	hdcMem = hdcNovo;
		    hBitmap = bmpNovo;
		    largura = novaLargura;
		    altura  = novaAltura;
		    
		    ReleaseDC(hwnd, hdc);
    		InvalidateRect(hwnd, NULL, FALSE);

			return 0;
			}

    	case WM_PAINT:{
    		PAINTSTRUCT ps;
    		HDC hdc = BeginPaint (hwnd, &ps);
    		
    			RECT cliente;
    			GetClientRect (hwnd, &cliente);
    			int largurajanela = cliente.right - cliente.left;
    			int alturajanela = cliente.bottom - cliente.top;
    			
    		if (estado == TELAMENU){
    			
    			FillRect(hdc, &cliente, (HBRUSH)(COLOR_WINDOW + 1));
    		
    			HFONT hFont = CreateFont (48,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS,"Arial");
    			HFONT oldFont = SelectObject(hdc, hFont);
    			
				RECT titulo = {0,0,0,0};

    			DrawText (hdc,"Mini Paint",-1,&titulo,DT_CALCRECT);
    			
    			int larguraTexto = titulo.right - titulo.left;
				int alturaTexto  = titulo.bottom - titulo.top;

				titulo.left   = (largurajanela - larguraTexto) / 2;
				titulo.top    = (alturajanela  - alturaTexto)  / 2;
				titulo.right  = titulo.left + larguraTexto;
				titulo.bottom = titulo.top  + alturaTexto;
				
				int margemx = 10;
				int margemy = 12;
				
				botaotitulo.left = titulo.left - margemx;
				botaotitulo.top = titulo.top - margemy;
				botaotitulo.right = titulo.right + margemx;
				botaotitulo.bottom = titulo.bottom + margemy;
				

    			Rectangle (hdc,  botaotitulo.left, botaotitulo.top, botaotitulo.right, botaotitulo.bottom);
    			DrawText (hdc,"Mini Paint",-1,&titulo,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    			
    			SelectObject(hdc, oldFont);
				DeleteObject(hFont);
			}
    		
    		if (estado == TELAPINTA){
    			
	    		BitBlt(
			        hdc,
			        0, 0, largura, altura,
			        hdcMem,
			        0, 0,
			        SRCCOPY
			    );
			    if (Menucores == 1){
			    	RECT vermelho = {160, 30, 180, 60};
			    	HBRUSH hBrush = CreateSolidBrush(RGB(255,0,0));
					HBRUSH old = SelectObject(hdc, hBrush);	
					
					botaovermelho.left = vermelho.left;
					botaovermelho.top = vermelho.top;
					botaovermelho.right = vermelho.right;
					botaovermelho.bottom = vermelho.bottom;
			    	Rectangle (hdc, vermelho.left,vermelho.top,vermelho.right,vermelho.bottom);
			    	
			    	SelectObject(hdc, old);
					DeleteObject(hBrush);
			    	//============================//
			    	RECT verde = {200, 30, 220, 60};
			    	hBrush = CreateSolidBrush(RGB(0,255,0));
					old = SelectObject(hdc, hBrush);	
					
					botaoverde.left = verde.left;
					botaoverde.top = verde.top;
					botaoverde.right = verde.right;
					botaoverde.bottom = verde.bottom;
			    	Rectangle (hdc, verde.left,verde.top,verde.right,verde.bottom);
			    	
			    	SelectObject(hdc, old);
					DeleteObject(hBrush);
					//=====================//
					RECT azul = {240, 30, 260, 60};
			    	hBrush = CreateSolidBrush(RGB(0,0,255));
					old = SelectObject(hdc, hBrush);	
					
					botaoazul.left = azul.left;
					botaoazul.top = azul.top;
					botaoazul.right = azul.right;
					botaoazul.bottom = azul.bottom;
			    	Rectangle (hdc, azul.left,azul.top,azul.right,azul.bottom);
			    	
			    	SelectObject(hdc, old);
					DeleteObject(hBrush);
					//===================//
					RECT roxo = {280, 30, 300, 60};
			    	hBrush = CreateSolidBrush(RGB(157,0,255));
					old = SelectObject(hdc, hBrush);	
					
					botaoroxo.left = roxo.left;
					botaoroxo.top = roxo.top;
					botaoroxo.right = roxo.right;
					botaoroxo.bottom = roxo.bottom;
			    	Rectangle (hdc, roxo.left,roxo.top,roxo.right,roxo.bottom);
			    	
			    	SelectObject(hdc, old);
					DeleteObject(hBrush);
					//===================//
					RECT preto = {320, 30, 340, 60};
			    	hBrush = CreateSolidBrush(RGB(0,0,0));
					old = SelectObject(hdc, hBrush);	
					
					botaopreto.left = preto.left;
					botaopreto.top = preto.top;
					botaopreto.right = preto.right;
					botaopreto.bottom = preto.bottom;
			    	Rectangle (hdc, preto.left,preto.top,preto.right,preto.bottom);
			    	
			    	SelectObject(hdc, old);
					DeleteObject(hBrush);
					//===================//
					RECT amarelo = {360, 30, 380, 60};
			    	hBrush = CreateSolidBrush(RGB(255,255,0));
					old = SelectObject(hdc, hBrush);	
					
					botaoamarelo.left = amarelo.left;
					botaoamarelo.top = amarelo.top;
					botaoamarelo.right = amarelo.right;
					botaoamarelo.bottom = amarelo.bottom;
			    	Rectangle (hdc, amarelo.left,amarelo.top,amarelo.right,amarelo.bottom);
			    	
			    	SelectObject(hdc, old);
					DeleteObject(hBrush);
					//===================//
					RECT branco = {400, 30, 420, 60};
			    	hBrush = CreateSolidBrush(RGB(255,255,255));
					old = SelectObject(hdc, hBrush);	
					
					botaobranco.left = branco.left;
					botaobranco.top = branco.top;
					botaobranco.right = branco.right;
					botaobranco.bottom = branco.bottom;
			    	Rectangle (hdc, branco.left,branco.top,branco.right,branco.bottom);
			    	
			    	SelectObject(hdc, old);
					DeleteObject(hBrush);
					//===================//
				}
			    RECT cores = {0, 0, 100, 100};
	    		botaocores.left = cores.left - 3;
	    		botaocores.top = cores.top - 3;
	    		botaocores.right = cores.right + 3;
	    		botaocores.bottom = cores.bottom + 3;
	    		
	    		Rectangle (hdc, botaocores.left,botaocores.top,botaocores.right,botaocores.bottom);
	    		DrawText (hdc,"Cores",-1,&cores,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	    		
	    		}
	    		EndPaint (hwnd, &ps);
	    		return 0;
    	}
    	
    	case WM_LBUTTONDOWN:{
    		int x = LOWORD (lParam);
    		int y = HIWORD (lParam);
    		if (estado == TELAMENU){
    			if (x >= botaotitulo.left && x<= botaotitulo.right && y >= botaotitulo.top && y <= botaotitulo.bottom){
    				estado = TELAPINTA;	
    				InvalidateRect (hwnd, NULL, TRUE);
    				return 0;
				}
			}
    		if (estado == TELAPINTA){
    			
    		if (x >= botaocores.left && x<= botaocores.right && y >= botaocores.top && y <= botaocores.bottom){
    				Menucores = !Menucores;
    				InvalidateRect (hwnd, NULL, TRUE);
    	            return 0;
				}
			if (Menucores == 1){
				if (x >= botaovermelho.left && x<=botaovermelho.right && y >= botaovermelho.top && y <= botaovermelho.bottom){
					cor = RGB (255,0,0); 
					Menucores = 0; 
					InvalidateRect(hwnd, NULL, TRUE);
					return 0;
				}
				if (x >= botaoverde.left && x<=botaoverde.right && y >= botaoverde.top && y <= botaoverde.bottom){
					cor = RGB (0,255,0); 
					Menucores = 0; 
					InvalidateRect(hwnd, NULL, TRUE);
					return 0;
				}
				if (x >= botaoazul.left && x<=botaoazul.right && y >= botaoazul.top && y <= botaoazul.bottom){
					cor = RGB (0,0,255); 
					Menucores = 0; 
					InvalidateRect(hwnd, NULL, TRUE);
					return 0;
				}
				if (x >= botaoroxo.left && x<=botaoroxo.right && y >= botaoroxo.top && y <= botaoroxo.bottom){
					cor = RGB (157,0,255); 
					Menucores = 0; 
					InvalidateRect(hwnd, NULL, TRUE);
					return 0;
				}
				if (x >= botaopreto.left && x<=botaopreto.right && y >= botaopreto.top && y <= botaopreto.bottom){
					cor = RGB (0,0,0); 
					Menucores = 0; 
					InvalidateRect(hwnd, NULL, TRUE);
					return 0;
				}
				if (x >= botaoamarelo.left && x<=botaoamarelo.right && y >= botaoamarelo.top && y <= botaoamarelo.bottom){
					cor = RGB (255,255,0); 
					Menucores = 0; 
					InvalidateRect(hwnd, NULL, TRUE);
					return 0;
				}
				if (x >= botaobranco.left && x<=botaobranco.right && y >= botaobranco.top && y <= botaobranco.bottom){
					cor = RGB (255,255,255); 
					Menucores = 0; 
					InvalidateRect(hwnd, NULL, TRUE);
					return 0;
				}
			}
    		desenho = 1;
    		pontoant.x = x;
    		pontoant.y = y;
    		}
    		return 0;
    	}
    		
    	case WM_LBUTTONUP:
    		desenho = 0;
    		return 0;
    		
    	case WM_MOUSEMOVE:
    		if (desenho && estado == TELAPINTA){
    			
    			HPEN hPen = CreatePen (PS_SOLID, 2, cor);
    			if (cor == RGB (255,255,255)){
    				hPen = CreatePen (PS_SOLID, 25, cor);
				}
    			HPEN oldpen = SelectObject (hdcMem, hPen);
    			
    			MoveToEx(hdcMem, pontoant.x, pontoant.y, NULL);
    			LineTo (hdcMem, LOWORD (lParam), HIWORD (lParam));
    			
    			pontoant.x = LOWORD (lParam);
    			pontoant.y = HIWORD (lParam);
    			
    			InvalidateRect(hwnd, NULL, FALSE);
    			SelectObject(hdcMem, oldpen);
				DeleteObject(hPen);
				}
    		return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(
    HINSTANCE hInst,
    HINSTANCE hPrev,
    LPSTR lpCmdLine,
    int nCmdShow
) {
    WNDCLASS wc = {0};

    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInst;
    wc.lpszClassName = "mini paint do diego";
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        "mini paint do diego",
        "mini paint do diego",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        900, 600,
        NULL, NULL, hInst, NULL
    );

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
