#pragma once

#include <iostream>
#include <Windows.h>
#include <algorithm>

class Donut
{

#pragma region Properties

public:

	float A;

	float B;

	float XPos = 0;

	float YPos = 0;

	float ZPos = 0;

	float thetaStep = 0.02f;

	float phiStep = 0.03f;

	float R1 = 1;

	float R2 = 4;

	float K2 = 10;

	float K1;



private:

	char _luminenceVals[12] = { '.', ',', '-', '~', ':',';', '=','!', '*', '#', '$', '@' };

	int _luminenceValuesLength = 12;

	char* _buf;

	int _height;

	int _width;

	int _lastHeight = 0;

	int _lastWidth = 0;

	float pi = 3.141f;

	int lightIntensity = 1;



#pragma endregion


public:

	Donut()
	{
		getConsoleSize(_width, _height);
	
		int size = _width * _height;
		_buf = new char[size];

		K1 = _width * K2 * 3 / (24 * (R1 + R2));

		//std::cout << "Width: " << _width << " Height: " << _height << std::endl;
	}

	void getConsoleSize(int& columns, int& rows) {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	}

    float clamp(float n, float lower, float upper) {
		return max(lower, min(n, upper));
    }


	void drawDonut()
	{
		int sizeOfScreen = _width * _height;

		float* zBuffer = new float[sizeOfScreen];

		std::fill(zBuffer, zBuffer + sizeOfScreen , 0.0f);
		std::fill(_buf, _buf + sizeOfScreen, ' ');


		float cosA = cos(A);
		float sinA = sin(A);
		float cosB = cos(B);
		float sinB = sin(B);

        for (float theta = 0; theta < 2 * pi; theta += thetaStep)
        {
            float cosTheta = cos(theta);
            float sinTheta = sin(theta);

            float circleX = R2 + R1 * cosTheta;
            float circleY = R1 * sinTheta;

            for (float phi = 0; phi < 2 * pi; phi += phiStep)
            {
                float cosPhi = cos(phi);
                float sinPhi = sin(phi);

                float x1 = cosB * cosPhi + sinB * sinA * sinPhi;
                float x2 = cosA * sinB;

                float y1 = sinB * cosPhi - cosB * sinA * sinPhi;
                float y2 = cosA * cosB;

                float z1 = cosA * sinPhi;
                float z2 = sinA;

                float x = XPos + circleX * x1 - circleY * x2;
                float y = YPos + circleX * y1 + circleY * y2;
                float z = K2 + circleX * z1 + circleY * z2;

                float ooz = 1 / z;

                int xp = (int)(_width / 2 + K1 * ooz * x);
                int yp = (int)(_height / 2 - K1 * ooz * y);

                
				xp = clamp(xp, 0, _width - 1);
				yp = clamp(yp, 0, _height - 1);
               

                int idx = xp + yp * _width;

                float nx = cosTheta;
                float ny = sinTheta;

                float Nx = nx * x1 - ny * x2;
                float Ny = nx * y1 + ny * y2;
                float Nz = nx * z1 + ny * z2;

                float mag = sqrtf(Nx * Nx + Ny * Ny + Nz * Nz);

                Nx = Nx / mag;
                Ny = Ny / mag;
                Nz = Nz / mag;


                //float Luminence = Nx * LightSource.NormalizedX + Ny * LightSource.NormalizedY + Nz * LightSource.NormalizedZ;
                float Luminence = Nx * 1 + Ny * 0 + Nz * 1;

                if (idx > sizeOfScreen || idx < 0)
                    continue;

                if (ooz > zBuffer[idx])
                {
                    //int luminance_index = (int)((Luminence + 1) * (_luminenceValuesLength) / (2) * LightSource.GetIntensity(x, y, z));
                    int luminance_index = (int)((Luminence + 1) * (_luminenceValuesLength) / (2) * lightIntensity);
                    luminance_index = clamp(luminance_index, 0, _luminenceValuesLength -1);
                    zBuffer[idx] = ooz;
                    _buf[idx] = _luminenceVals[luminance_index];
                }
            }
        }

		Display();
	}

    void Display()
    {
        // Get the console handle
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Retrieve screen buffer information
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);

        int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

        // Check if the size has changed
        if (height != _lastHeight || width != _lastWidth) {
            system("cls");  // Clear the console
        }

        int startX = (width - _width) / 2;
        int startY = (height - _height) / 2;

        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                int index = y * _width + x;
                // Set cursor position
                COORD pos = { static_cast<SHORT>(startX + x), static_cast<SHORT>(startY + y) };
                SetConsoleCursorPosition(hConsole, pos);
                // Write to console
                std::cout << _buf[index];
            }
        }

        _lastHeight = _height;
        _lastWidth = _width;
    }
        






};

