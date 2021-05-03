#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "GUI\UI_Info.h"
#include "GUI\output.h"
class Statement;

class Connector	//a connector that connects two statements (Source & Destination)
{
private:
	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point Start;	//Start point of the connector
	Point corner;
	Point End;		//End point of the connector
	int branch;
	bool Selected;
	bool pfinderhelper(int a,int b,int c,int d,Point x) const;

public:
	Connector(Statement* Src, Statement* Dst);

	void		setSrcStat(Statement *Src);
	Statement*	getSrcStat();	
	void		setDstStat(Statement *Dst);
	Statement*	getDstStat();
	void SetSelected(bool s);
	bool IsSelected() const;
	void setStartPoint(Point P);
	Point getStartPoint();

	void setEndPoint(Point P);
	Point getEndPoint();
	bool is_p_here(Point c) const ;
	void Draw(Output* pOut) const;
	void setbranch(int b);
	void  save(ofstream &OutFile);
	void  load(ifstream &InFile);


};

#endif