//
//  PhylogenyTreeView.h
//  gavqt
//
//  Created by Brian Ondov on 8/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gavqt_PhylogenyTreeView_h
#define gavqt_PhylogenyTreeView_h

#include "TrackListView.h"
#include "PhylogenyTree.h"
#include "Track.h"
#include <QPainter>
#include <QVector>

class PhylogenyTreeView : public TrackListView
{
	Q_OBJECT
	
public:
	
	PhylogenyTreeView();
	~PhylogenyTreeView();
	
	void handleTrackHeightChange(const TrackListView * focus);
	void setNames(QVector<QString> * newNames);
	void setPhylogenyTree(const PhylogenyTree * newTree);
	void setTrackFocus(int track);
	void setTrackHover(int track, int trackEnd);
	
protected:
	
	struct PhylogenyNodeView
	{
		int x;
		int y;
		bool search;
	};
	
	virtual float getHighlight(const PhylogenyNode *, float highlight, bool) const;
	virtual QColor highlightColor(float highlight) const = 0;
	void leaveEvent(QEvent * event);
	virtual bool nodeIsVisible(const PhylogenyNode * node, float leafSize) const = 0;
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent * event);
	void setWindow(const PhylogenyNode * node);
	void updateBuffer();
	
	QVector<QString> * names;
	const PhylogenyTree * phylogenyTree;
	const PhylogenyNode * highlightNode;
	const PhylogenyNode * focusNode;
	PhylogenyNodeView * nodeViews;
	bool zoomIn;
	
signals:
	
	void signalNodeHover(const PhylogenyNode * node);
	void signalTrackZoom(int start, int end);
	
private:
	
	void drawLine(QPainter * painter, float x1, float y1, float x2, float y2, float weight, QColor color) const;
	void drawNode(QPainter * painter, const PhylogenyNode * node, bool drawHighlight, float highlight = 0, float weightTop = 1, float weightBottom = 1) const;
	void drawNodeLeaf(QPainter * painter, const PhylogenyNode * node, float highlight, float weightTop, float weightBottom) const;
	float maxVisibleDepth(const PhylogenyNode * node, float leafSize) const;
	float nameScale(int leaf) const;
	void updateNodeViews(const PhylogenyNode * node);
	float zoomLerp(float start, float end);
	
	int radius;
	
	QPen penDark;
	QPen penLight;
//	QImage * buffer;
	QImage ** nameBuffers;
	int nameBufferCount;
	float xFactor;
	float xFactorStart;
	float xFactorEnd;
	float xOffset;
	float xOffsetStart;
	float xOffsetEnd;
	bool redrawNeeded;
	bool bufferHighlight;
	int fontHeight;
};

inline float maxf(float a, float b) {return a > b ? a : b;}

#endif
