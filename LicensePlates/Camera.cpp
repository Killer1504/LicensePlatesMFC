#include "pch.h"
#include "Camera.h"

CCamera::CCamera()
{
	m_nCameraSelect = 0;
	m_nDeviceSelect = CCamera::Webcam;
	m_bOpen = FALSE;
	m_bOpen = Connect();
}

CCamera::CCamera(int nCameraSelect, int nDeviceSelect)
{
	m_nCameraSelect = nCameraSelect;
	m_nDeviceSelect = nDeviceSelect;
	m_bOpen = FALSE;
	m_bOpen = Connect();
}

CCamera::~CCamera()
{
	if (m_pWebcam != NULL)
		delete m_pWebcam;
}

BOOL CCamera::Connect()
{
	if (m_bOpen) return TRUE;
	switch (m_nDeviceSelect)
	{
	case CCamera::Webcam:
	{
		if (!m_bOpen)
		{
			m_pWebcam = new VideoCapture(0);
			if (m_pWebcam->isOpened())
			{
				m_bOpen = TRUE;
			}
		}

	}
	break;
	default:
		break;
	}
	return m_bOpen;
}

void CCamera::Disconnect()
{
	m_bOpen = FALSE;
}

BOOL CCamera::TakeImage(Mat& image)
{
	if (!m_bOpen) return FALSE;

	BOOL bRet = TRUE; //Ket qua tra ve
	switch (m_nDeviceSelect)
	{
	case CCamera::Webcam:
	{
		if (m_bOpen)
		{
			m_pWebcam->read(image);
			if (image.empty())
			{
				m_bOpen = FALSE;
				CString msg = _T("Khong the lay anh tu Camera");
				AfxMessageBox(msg, MB_ICONERROR);
				delete m_pWebcam;
				return FALSE;
			}
			bRet = TRUE;
		}

	}
	break;
	default:
		break;
	}
	return bRet;
}
