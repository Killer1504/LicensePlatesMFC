#pragma once

#define MAX_CAM_NUMBER 1
class CCamera
{
public:
	//ham khoi tao
	CCamera(int nCameraSelect, int nDeviceSelect = 0);
	~CCamera();

	enum 
	{
		Webcam =0, Basler
	};

public:
	//cac bien
	int m_nCameraSelect; // camera thu may
	int m_nDeviceSelect; // camera loai gi
	BOOL m_bOpen;
	
	//--------------//
	cv::VideoCapture* m_pWebcam;

public:
	//cac ham lien quan den camera
	BOOL Connect();
	void Disconnect();
	BOOL TakeImage(Mat& image);
};

