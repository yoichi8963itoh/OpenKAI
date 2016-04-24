/*
 * CamStream.cpp
 *
 *  Created on: Aug 23, 2015
 *      Author: yankai
 */

#include "_CamStream.h"

namespace kai
{

_CamStream::_CamStream()
{
	_ThreadBase();

	m_camName = "";
	m_pCamInput = new CamInput();
	m_pCamFrame = new CamFrame();
	m_pGrayFrame = new CamFrame();
	m_pHSVframe = new CamFrame();

	m_bThreadON = false;
	m_threadID = NULL;

	m_bGray = false;
	m_bHSV = false;

}

_CamStream::~_CamStream()
{
	RELEASE(m_pCamInput);
	RELEASE(m_pCamFrame);
	RELEASE(m_pGrayFrame);
	RELEASE(m_pHSVframe);
}

bool _CamStream::init(JSON* pJson, string camName)
{
	if(!pJson)return false;

//	CHECK_INFO(pJson->getVal("CAM_"+camName+"_CUDADEVICE_ID", &m_cudaDeviceID));
	CHECK_FATAL(pJson->getVal("CAM_"+camName+"_NAME", &m_camName));
	CHECK_ERROR(m_pCamInput->setup(pJson, camName));

	m_bThreadON = false;
	m_tSleep = TRD_INTERVAL_CAMSTREAM;

	return true;
}

bool _CamStream::start(void)
{
	//Open camera
	CHECK_ERROR(m_pCamInput->openCamera());

	//Start thread
	m_bThreadON = true;
	int retCode = pthread_create(&m_threadID, 0, getUpdateThread, this);
	if (retCode != 0)
	{
		m_bThreadON = false;
		return false;
	}

	return true;
}

void _CamStream::update(void)
{
	while (m_bThreadON)
	{
		this->updateTime();

		//Update camera frame
		m_pCamFrame->update(m_pCamInput->readFrame());

		//Update Gray frame
		if(m_bGray)
		{
			m_pGrayFrame->getGrayOf(m_pCamFrame);
		}

		//Update HSV frame
		if(m_bHSV)
		{
			m_pHSVframe->getHSVOf(m_pCamFrame);
		}

		if(m_tSleep>0)
		{
			//sleepThread can be woke up by this->wakeupThread()
			this->sleepThread(0,m_tSleep);
		}
	}

}

bool _CamStream::complete(void)
{
	m_pCamInput->m_camera.release();

	return true;
}

CamFrame* _CamStream::getFrame(void)
{
	return m_pCamFrame;
}

CamFrame* _CamStream::getGrayFrame(void)
{
	return m_pGrayFrame;
}

CamFrame* _CamStream::getHSVFrame(void)
{
	return m_pHSVframe;
}

} /* namespace kai */