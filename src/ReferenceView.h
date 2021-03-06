// Copyright © 2014, Battelle National Biodefense Institute (BNBI);
// all rights reserved. Authored by: Brian Ondov, Todd Treangen, and
// Adam Phillippy
//
// See the LICENSE.txt file included with this software for license information.

#ifndef __gavqt__ReferenceView__
#define __gavqt__ReferenceView__

#include "DrawingArea.h"
#include "SnpBuffer.h"
#include "Alignment.h"

class ReferenceView : public DrawingArea
{
	Q_OBJECT
	
public:
	
	ReferenceView();
	
	void clear();
	void setAlignment(const Alignment * newAlignment);
	void setLightColors(bool light);
	void setSnpBuffer(const SnpBuffer * newSnpBuffer);
	void setWindow(int newPosStart, int newPosEnd);
	
public slots:
	
	void updateSnpsFinished();

signals:
	
	void positionChanged(int ungapped);
	void signalMouseWheel(int delta);
	
protected:
	
	void leaveEvent(QEvent * event);
	void mouseMoveEvent(QMouseEvent * event);
	void updateBuffer();
	void wheelEvent(QWheelEvent * event);
	
private:
	
	void updatePosition();
	
	const Alignment * alignment;
	const SnpBuffer * snpBuffer;
	
	int start;
	int end;
	int cursorX;
	
	bool lightColors;
};

inline void ReferenceView::setLightColors(bool light) {lightColors = light;}

#endif /* defined(__gavqt__ReferenceView__) */
