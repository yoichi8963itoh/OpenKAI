/*
 * _ImageNet.h
 *
 *  Created on: Aug 17, 2016
 *      Author: yankai
 */

#ifndef AI__ImageNet_H_
#define AI__ImageNet_H_

#include "../Base/common.h"
#include "_AIbase.h"
#include "../Stream/_StreamBase.h"

namespace kai
{

class _ImageNet: public _AIbase
{
public:
	_ImageNet();
	~_ImageNet();

	bool init(void* pKiss);
	bool link(void);
	bool start(void);

	double detect(Frame* pFrame, int* classID, string* className);

private:
	void update(void);
	static void* getUpdateThread(void* This)
	{
		((_ImageNet*) This)->update();
		return NULL;
	}

public:
#ifdef USE_TENSORRT
	imageNet* m_pIN;
#endif
	Frame* m_pRGBA;

	int m_nBatch;
	string m_blobIn;
	string m_blobOut;

};

}

#endif
