#include <windows.h>
#include <math.h>
#include <iostream>
#include <map>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>

#include "vectors.h"

//TODO make shape namespace
#include "MatteSphere.h"
#include "FlatSphere.h"
#include "Ray.h"
#include "World.h"
#include "ReflectSphere.h"
#include "FlatTriangle.h"
#include "ReflectTriangle.h"
#include "ReflectColorSphere.h"

const double HW_RATIO = 3.0/4;

int RAYTRACE_WIDTH = 256;
int RAYTRACE_HEIGHT = HW_RATIO*RAYTRACE_WIDTH;

const int SCREENWIDTH = 512+256;
const int SCREENHEIGHT = HW_RATIO*SCREENWIDTH;
const WORD BITCOUNT = 24;

const double VIEWDISTANCE = 1;
const double CAMERA_SPEED = 0.5;
const double ROTATE_SPEED = 3.141592/64;

const int THREAD_COUNT = 16;

//resize stuff
HDC hDC;
BITMAPINFO bmi;
PBYTE pRgb;
HBITMAP hBitmap, midBitmap;
int bytesPerLine;

Ray eye;
Ray look;
vectors::mat3 eyeXZ, eyeYZ;
World w;

std::map<int, bool> keys;
bool isHacking = false;
std::string hackText = ">";//32 characters
bool redrawText = false;

void log(std::string a){
	isHacking = true;
	TextOut(hDC,5,5,a.c_str(),a.length());
}

void resize(int width){
	RAYTRACE_WIDTH = width;
	RAYTRACE_HEIGHT = width*HW_RATIO;
	
	bmi = BITMAPINFO{ BITMAPINFOHEADER{sizeof(BITMAPINFOHEADER), RAYTRACE_WIDTH, RAYTRACE_HEIGHT, 1, BITCOUNT, BI_RGB}};
	pRgb = NULL;
	hBitmap = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, (void**)&pRgb, NULL, NULL);
	
	bytesPerLine = RAYTRACE_WIDTH*3;
	if(bytesPerLine % 4 != 0){//pad to byte size
	    bytesPerLine += 4 - bytesPerLine % 4;
	}
}

void processHack(){
	std::vector<std::string> ss = std::vector<std::string>();
	std::string cur = "";
	ss.push_back("");
	for(int i=1; i<hackText.length(); i++){
		if(hackText.at(i) == ' '){
			ss.push_back("");
		}else{
			ss[ss.size()-1].push_back(hackText[i]);
		}
	}
	
	log(std::to_string(ss.size()));
	
	if(ss[0] == "RES" && ss.size() == 2){
		resize(stoi(ss[1]));
	}else if(ss[0] == "TP" && ss.size() == 3){
		eye.pos.x = stod(ss[1]);
		eye.pos.z = stod(ss[2]);
	}
}

void draw(int multiple, int offset){
	PBYTE pixel = NULL;
	Ray clook = look;
	for (int y = offset; y < RAYTRACE_HEIGHT; y+=multiple){
	    for (int x = 0; x < RAYTRACE_WIDTH; x++){
	    	pixel = pRgb+bytesPerLine*y+x*3;

			clook.direction.x = ((double)(RAYTRACE_WIDTH/2-x))/RAYTRACE_HEIGHT;
			clook.direction.y = ((double)(RAYTRACE_HEIGHT/2-y))/RAYTRACE_HEIGHT;
			clook.direction.z = VIEWDISTANCE;
			clook.direction = clook.direction.normalize()*eyeYZ*eyeXZ;

			Color current = w.processRay(clook, 0);
			pixel[0] = current.b;
        	pixel[1] = current.g;
        	pixel[2] = current.r;
	    }
	}
}

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_KEYDOWN:
			if(!isHacking){
				if(wParam == 0x45){
					isHacking = true;
					redrawText = true;
					hackText = ">";
				}
				
				if(keys.find(wParam) != keys.end()){
					keys[wParam] = true;
				}
			}else{
				switch(wParam){
					case VK_ESCAPE:
						isHacking = false;						
						break;
					case VK_RETURN:
						processHack();
						hackText = ">";
						redrawText = true;
						break;
					case 0x08://backspace
						if(hackText.length()>1){
							hackText.pop_back();
						}
						redrawText = true;
						break;
					case VK_OEM_MINUS:
						hackText.append("-"); 
						redrawText = true;
						break;
					default:
						hackText.append(std::string(1,(TCHAR) wParam)); 
						redrawText = true;
						break;
				}
			}
			break;
		case WM_KEYUP:
			if(keys.find(wParam) != keys.end()){
				keys[wParam] = false;
			}
			break;
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		SCREENWIDTH, /* width */
		SCREENHEIGHT, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
	//Setup keystore
	keys[VK_UP] = false;
	keys[VK_DOWN] = false;
	keys[VK_LEFT] = false;
	keys[VK_RIGHT] = false;
	keys[0x57] = false;//W
	keys[0x41] = false;//A
	keys[0x53] = false;//S
	keys[0x44] = false;//D
	
	//My code to setup screen
	hDC = GetDC(hwnd);
	
	resize(256);
	
	//setup view
	
	w.addObject(new ReflectTriangle(vectors::vec3(15,1,15), vectors::vec3(15,-15,-15), vectors::vec3(15,-15,15)));
	w.addObject(new ReflectTriangle(vectors::vec3(15,1,15), vectors::vec3(15,1,-15), vectors::vec3(15,-15,-15)));
	w.addObject(new ReflectTriangle(vectors::vec3(-15,1,15), vectors::vec3(-15,-15,-15),  vectors::vec3(-15,1,-15)));
	w.addObject(new ReflectTriangle(vectors::vec3(-15,1,15), vectors::vec3(-15,-15,15), vectors::vec3(-15,-15,-15)));

	w.addObject(new ReflectTriangle(vectors::vec3(15,1,15), vectors::vec3(-15,-15,15), vectors::vec3(-15,1,15)));
	w.addObject(new ReflectTriangle(vectors::vec3(15,-15,15), vectors::vec3(-15,-15,15), vectors::vec3(15,1,15)));
	w.addObject(new ReflectTriangle(vectors::vec3(15,1,-15), vectors::vec3(-15,1,-15), vectors::vec3(-15,-15,-15)));
	w.addObject(new ReflectTriangle(vectors::vec3(15,-15,-15), vectors::vec3(15,1,-15), vectors::vec3(-15,-15,-15)));

	
	w.addLightSource(Light(vectors::vec3(0,-2,4),Color{255,255,255},1));
	w.addObject(new FlatSphere(vectors::vec3(0,-2,4), 0.2, Color{255,255,255}));
	
	w.addObject(new ReflectSphere(vectors::vec3(0,0,8), 1));
	w.addObject(new ReflectSphere(vectors::vec3(0,-2,8), 1));
	w.addObject(new ReflectSphere(vectors::vec3(-8,-2,8), 1));
	w.addObject(new MatteSphere(vectors::vec3(-2,0,8), 1, Color{255,10,127}));
	w.addObject(new MatteSphere(vectors::vec3(2,0,5), 1, Color{127,255,10}));
	
	/*
	w.addObject(new ReflectColorSphere(vectors::vec3(1,0,3),1,Color{63,63,255}));
	w.addObject(new ReflectColorSphere(vectors::vec3(-1,0,3),1,Color{255,63,63}));
	w.addObject(new ReflectColorSphere(vectors::vec3(0,-1.713,3),1,Color{63,255,63}));
	*/
	w.addObject(new FlatTriangle(vectors::vec3(1000,1,1000),vectors::vec3(1000,1,-1000),vectors::vec3(-1000,1,-1000),Color{70,70,70}));
	w.addObject(new FlatTriangle(vectors::vec3(1000,1,1000),vectors::vec3(-1000,1,1000),vectors::vec3(-1000,1,-1000),Color{70,70,70}));
	
	eye = Ray(vectors::vec3(0,0,0), vectors::vec3(0,0,1));
	double eyeXZtheta = 0;
	double eyeYZtheta = 0;
	double sXZ, cXZ, sYZ, cYZ;
	eyeXZ = vectors::mat3(
			vectors::vec3(0,0,0),
			vectors::vec3(0,1,0),
			vectors::vec3(0,0,0)
		);
	eyeYZ = vectors::mat3(
			vectors::vec3(1,0,0),
			vectors::vec3(0,0,0),
			vectors::vec3(0,0,0)

		);

	look = Ray(vectors::vec3(0,0,0), vectors::vec3(0,0,1));
	
	//threading
	std::vector<std::thread> threads(THREAD_COUNT);
	//framerate
	auto time = std::chrono::steady_clock::now();
	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(msg.message != WM_QUIT) { /* If no error is received... */
		if(!isHacking){
			if(std::chrono::steady_clock::now() >= time) {
				time = std::chrono::steady_clock::now() + std::chrono::milliseconds(1000/30);
				for(const auto& pair:keys){
					if(pair.second){
						switch(pair.first){
							case 0x57://W
								eye.pos = eye.pos+vectors::vec3(0,0,CAMERA_SPEED)*eyeXZ;
								break;
							case 0x53://S
								eye.pos = eye.pos-vectors::vec3(0,0,CAMERA_SPEED)*eyeXZ;
								break;
							case 0x41://A
								eye.pos = eye.pos+vectors::vec3(CAMERA_SPEED,0,0)*eyeXZ;
								break;
							case 0x44://D
								eye.pos = eye.pos-vectors::vec3(CAMERA_SPEED,0,0)*eyeXZ;
								break;
		
							case VK_UP:
								eyeYZtheta+=ROTATE_SPEED;
								break;
							case VK_DOWN:
								eyeYZtheta-=ROTATE_SPEED;;					
								break;
							case VK_LEFT:
								eyeXZtheta+=ROTATE_SPEED;
								break;
							case VK_RIGHT:
								eyeXZtheta-=ROTATE_SPEED;
								break;
							}
					}
				}		
				//rotation			
				sXZ = sin(eyeXZtheta);
				cXZ = cos(eyeXZtheta);
				sYZ = sin(eyeYZtheta);
				cYZ = cos(eyeYZtheta);
				
				eyeXZ.row1.x = cXZ;
				eyeXZ.row1.z = sXZ;
				eyeXZ.row3.x = -sXZ;
				eyeXZ.row3.z = cXZ;
				
				eyeYZ.row2.y = cYZ; 
				eyeYZ.row2.z = -sYZ; 
				eyeYZ.row3.y = sYZ; 
				eyeYZ.row3.z = cYZ; 
		
				look = eye;
				
				for(int i=0; i<THREAD_COUNT;i++){
					threads[i] = std::thread(draw, THREAD_COUNT, i);
				}
				for(int i=0; i<THREAD_COUNT;i++){
					threads[i].join();
				}
		
				StretchDIBits(hDC, 0, 0, SCREENWIDTH, SCREENHEIGHT, 0, 0, RAYTRACE_WIDTH, RAYTRACE_HEIGHT, pRgb, &bmi, DIB_RGB_COLORS, SRCCOPY);
			}
		}else{
			if(redrawText){
				Rectangle(hDC, 4, SCREENHEIGHT-66,SCREENWIDTH-25, SCREENHEIGHT-48);
				TextOut(hDC, 5, SCREENHEIGHT-65,hackText.c_str(), hackText.length());
				redrawText = false;
			}
		}

		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0){
			TranslateMessage(&msg); /* Translate key codes to chars if present */
			DispatchMessage(&msg); /* Send it to WndProc */
		}
	}
//	std::cout << "The value of variable num is " << msg.wParam << std::endl;
//	char*a;
//	std::cin>>a;
	return msg.wParam;
}
