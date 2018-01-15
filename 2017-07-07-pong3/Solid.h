#pragma once
#include "stdafx.h"

class Solid
{
public:

	int xl;
	int xr;
	int yu;
	int yd;

	Solid(int xl, int xr, int yu, int yd) : xl(xl), xr(xr), yu(yu), yd(yd) {};
	virtual ~Solid() {};

	virtual void draw(CDC *dc) = 0;
};

class Bat : public Solid
{
public:
	Bat(int xl, int xr, int yu, int yd) : Solid(xl, xr, yu, yd) {};
	virtual ~Bat() {};
	void draw(CDC *dc) { dc->Rectangle(xl, yu, xr, yd); }
};

class Ball : public Solid
{
public:
	Ball(int xl, int xr, int yu, int yd) : Solid(xl, xr, yu, yd) { vx = -1;  vy = 0; };
	int vx;
	int vy;
	virtual ~Ball() {};
	void draw(CDC *dc) { dc->Ellipse(xl, yu, xr, yd); }
};

class Boarder : public Solid
{
public:
	Boarder(int xl, int xr, int yu, int yd) : Solid(xl, xr, yu, yd) {};
	virtual ~Boarder() {};
	void draw(CDC *dc)
	{
		dc->Rectangle(xl, yu, xr, yd);
	}
};

class Brick : public Solid
{
public:
	Brick(int xl, int xr, int yu, int yd) : Solid(xl, xr, yu, yd) { ishit = true; };
	int hits;
	int id;
	bool ishit;
	virtual ~Brick() {};
	virtual void draw(CDC *dc) = 0;
	virtual void dance(CDC *dc) = 0;
	void hit()
	{
		hits--;
	}
};

class EasyBrick : public Brick
{
public:
	EasyBrick(int xl, int xr, int yu, int yd) : Brick(xl, xr, yu, yd) { hits = 1; id = 1; };
	virtual ~EasyBrick() {};
	void draw(CDC *dc)
	{
		dc->Rectangle(xl, yu, xr, yd);
	}
	void dance(CDC *dc)
	{
		int i;
		dc->GetPixel(xl, yu);
		dc->Rectangle(xl, yu, xr, yd);
		for (i = 0; i < 4; i++)
		{
			dc->Rectangle(xl, yu, xr, yd);
			dc->Rectangle(xl, yu, xr, yd);
		}
		dc->Rectangle(xl, yu, xr, yd);
	}

};
class MediumBrick : public Brick
{
public:
	MediumBrick(int xl, int xr, int yu, int yd) : Brick(xl, xr, yu, yd) { hits = 2; id = 2; };
	virtual ~MediumBrick() {};
	void draw(CDC *dc)
	{
		dc->Rectangle(xl, yu, xr, yd);
	}
	void dance(CDC *dc)
	{
		int i;
		dc->GetPixel(xl, yu);
		dc->Rectangle(xl, yu, xr, yd);
		for (i = 0; i < 4; i++)
		{
			dc->Rectangle(xl - 5, yu - 5, xr + 5, yd + 5);
			dc->Rectangle(xl - 5, yu - 5, xr + 5, yd + 5);
			dc->Rectangle(xl - 8, yu - 8, xr + 8, yd + 8);
			dc->Rectangle(xl - 8, yu - 8, xr + 8, yd + 8);
			dc->Rectangle(xl - 11, yu - 11, xr + 11, yd + 11);
			dc->Rectangle(xl - 11, yu - 11, xr + 11, yd + 11);
			dc->Rectangle(xl - 15, yu - 15, xr + 15, yd + 15);
			dc->Rectangle(xl - 15, yu - 15, xr + 15, yd + 15);
			dc->Rectangle(xl - 11, yu - 11, xr + 11, yd + 11);
			dc->Rectangle(xl - 11, yu - 11, xr + 11, yd + 11);
			dc->Rectangle(xl - 8, yu - 8, xr + 8, yd + 8);
			dc->Rectangle(xl - 8, yu - 8, xr + 8, yd + 8);
			dc->Rectangle(xl - 5, yu - 5, xr + 5, yd + 5);
			dc->Rectangle(xl - 5, yu - 5, xr + 5, yd + 5);
		}
		dc->Rectangle(xl, yu, xr, yd);
	}
};
class HardBrick : public Brick
{
public:
	HardBrick(int xl, int xr, int yu, int yd) : Brick(xl, xr, yu, yd) { hits = 3; id = 3; };
	virtual ~HardBrick() {};
	void draw(CDC *dc)
	{
		dc->Rectangle(xl, yu, xr, yd);
	}
	void dance(CDC *dc)
	{
		int i;
		dc->GetPixel(xl, yu);
		dc->Rectangle(xl, yu, xr, yd);
		for (i = 0; i < 4; i++)
		{
			dc->Ellipse(xl - 5, yu - 5, xr + 5, yd + 5);
			dc->Ellipse(xl - 5, yu - 5, xr + 5, yd + 5);
			dc->Ellipse(xl - 8, yu - 8, xr + 8, yd + 8);
			dc->Ellipse(xl - 8, yu - 8, xr + 8, yd + 8);
			dc->Ellipse(xl - 11, yu - 11, xr + 11, yd + 11);
			dc->Ellipse(xl - 11, yu - 11, xr + 11, yd + 11);
			dc->Ellipse(xl - 15, yu - 15, xr + 15, yd + 15);
			dc->Ellipse(xl - 15, yu - 15, xr + 15, yd + 15);
			dc->Ellipse(xl - 18, yu - 18, xr + 18, yd + 18);
			dc->Ellipse(xl - 18, yu - 18, xr + 18, yd + 18);
			dc->Ellipse(xl - 15, yu - 15, xr + 15, yd + 15);
			dc->Ellipse(xl - 15, yu - 15, xr + 15, yd + 15);
			dc->Ellipse(xl - 11, yu - 11, xr + 11, yd + 11);
			dc->Ellipse(xl - 11, yu - 11, xr + 11, yd + 11);
			dc->Ellipse(xl - 8, yu - 8, xr + 8, yd + 8);
			dc->Ellipse(xl - 8, yu - 8, xr + 8, yd + 8);
			dc->Ellipse(xl - 5, yu - 5, xr + 5, yd + 5);
			dc->Ellipse(xl - 5, yu - 5, xr + 5, yd + 5);
		}
		dc->Rectangle(xl, yu, xr, yd);
	}
};