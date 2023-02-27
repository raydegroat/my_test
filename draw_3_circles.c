// Raymond de Groat - (c) 1995
// University of Washngton - C Programming, Graphics

#include<project.h>

static void PlotPointsCircle(CGR_circle_p_t circle, long int x, long int y);
static void PlotPointsEllipse(CGR_ellipse_p_t ellipse, long int x, long int y);
static long int Round(float num);

/* CGR_draw_circle **************************************/

void CGR_draw_circle(CGR_circle_p_t circle)
{
	int x = 0;
	int y = circle->radius;
	int p = 1 - circle->radius;
	PlotPointsCircle(circle, x, y);
	
	while( x < y )
	{
		if( p < 0 )
			x++;
		else
		{
			x++;
			y--;
		}
		if( p < 0 )
			p = p + 2 * x + 1;
		else
			p = p + 2 * (x-y) +1;
		PlotPointsCircle(circle, x, y);
	}
}


/* CGR_draw_circles **************************************/

void CGR_draw_circles(CGR_circle_p_t circles, int num_circles)
{
	while(num_circles--)
		CGR_draw_circle(&circles[num_circles]);
}


/* PlotPointsCircle **************************************/

static void PlotPointsCircle(CGR_circle_p_t circle, long int x, long int y)
{
	const int num_points = 8;
	CGR_point_t points[8];
	
	points[0].xco = circle->center.xco + x; points[0].yco = circle->center.yco + y;
	points[1].xco = circle->center.xco - x; points[1].yco = circle->center.yco + y;
	points[2].xco = circle->center.xco + x; points[2].yco = circle->center.yco - y;
	points[3].xco = circle->center.xco - x; points[3].yco = circle->center.yco - y;
	points[4].xco = circle->center.xco + y; points[4].yco = circle->center.yco + x;
	points[5].xco = circle->center.xco - y; points[5].yco = circle->center.yco + x;
	points[6].xco = circle->center.xco + y; points[6].yco = circle->center.yco - x;
	points[7].xco = circle->center.xco - y; points[7].yco = circle->center.yco - x;
	
	CGR_draw_points(points, num_points);
}


/* CGR_draw_ellipse **************************************/

void CGR_draw_ellipse( CGR_ellipse_p_t ellipse)
{
	long int p, px, py, x, y, Ry2, Rx2, twoRx2, twoRy2;
	
	Ry2 = ellipse->yRadius * ellipse->yRadius;
	Rx2 = ellipse->xRadius * ellipse->xRadius;
	twoRy2 = 2 * Ry2;
	twoRx2 = 2 * Rx2;
	
	/* region 1 */
	
	x = 0;
	y = ellipse->yRadius;
	PlotPointsEllipse(ellipse, x, y);
	p = Round((Ry2 - Rx2 * ellipse->yRadius) + (0.25 * Rx2));
	px = 0;
	py = twoRx2 * y;
	while(px<py)
	{
		x++;
		px += twoRy2;
		if(p>=0)
		{
			y--;
			py -= twoRx2;
		}
		if(p<0)
			p = p + Ry2 + px;
		else
			p = p + Ry2 + px - py;
		PlotPointsEllipse(ellipse, x, y);
	}
	
	/* region 2 */
	
	p = Round(Ry2 * (x +0.5) * (x + 0.5) + Rx2 * (y - 1) * (y - 1) - Rx2 * Ry2);
	while(y>0)
	{
		y--;
		py -= twoRx2;
	
	if(p<=0)
	{
		x++;
		px += twoRy2;
	}
	if(p>0)
		p = p + Rx2 - py;
	else
		p = p + Rx2 - py + px;
	PlotPointsEllipse(ellipse, x, y);
	}
	
}


/* CGR_draw_ellipses **************************************/

void CGR_draw_ellipses( CGR_ellipse_p_t ellipses, int num_ellipses)
{
	while(num_ellipses--)
		CGR_draw_ellipse(&ellipses[num_ellipses]);
}


/* PlotPointsEllipse **************************************/

static void PlotPointsEllipse(CGR_ellipse_p_t ellipse, long int x, long int y)
{
	const int num_points = 4;
	CGR_point_t points[4];
	
	points[0].xco = ellipse->center.xco + x; points[0].yco = ellipse->center.yco + y;
	points[1].xco = ellipse->center.xco - x; points[1].yco = ellipse->center.yco + y;
	points[2].xco = ellipse->center.xco + x; points[2].yco = ellipse->center.yco - y;
	points[3].xco = ellipse->center.xco - x; points[3].yco = ellipse->center.yco - y;
	
	CGR_draw_points(points, num_points);
	
	
}


/* CGR_draw_lines **************************************/

void CGR_draw_line( CGR_line_p_t line)
{
	
	long int dx, dy, xEnd, yEnd, p, xa, xb, ya, yb;
	CGR_point_t point;
	
	xa = line->end1.xco; ya = line->end1.yco;
	xb = line->end2.xco; yb = line->end2.yco;
	
	dx = abs(line->end1.xco - line->end2.xco);
	dy = abs(line->end1.yco - line->end2.yco);
	
	if((line->end1.xco - line->end2.xco) * (line->end1.yco - line->end2.xco) >0
		) /*  Slope is positive. */
	{
	 	if(dx >= dy) 	/* Slope is less than one */
		{
			p = 2 * (dy - dx);
			if(xa >= xb)
			{
				point.xco = xb;
				point.yco = yb;
				xEnd = xa;
			}
			else
			{
				point.xco = xa;
				point.yco = ya;
				xEnd = xb;
			}
			CGR_draw_point(&point);
			while(point.xco < xEnd)
			{
				point.xco++;
				if(p < 0)
					p += 2 * dy;
				else
				{
					point.yco++;
					p += 2 * (dy - dx);
				}
				CGR_draw_point(&point);
			}
		}

		if(dx <= dy)		/* Slope is greater than one */
		{
			p = 2 * (dx - dy);
			if(xa > xb )
		{
			point.xco = xb;
			point.yco = yb;
			yEnd = ya;
		}
		else
		{
			point.xco = xa;
			point.yco = ya;
			yEnd = yb;
		}
		CGR_draw_point(&point);
		while(point.yco < yEnd)
		{
			point.yco++;
			if(p < 0)
				p += 2 * dx;
			else
			{
				point.xco++;
				p += 2 * (dx - dy);
			}
			CGR_draw_point(&point);
			}
		}
	}
		
	else								/* Slope is negetive */
	{	
		if(dx >= dy)					/* Slope less than one */
		{
			p = 2 * (dy - dx);
			if(xb>= xa)
			{
				point.xco = xb;
				point.yco = yb;
				xEnd = xa;
			}
			else
			{
				point.xco = xa;
				point.yco = ya;
				xEnd = xb;
			}
			CGR_draw_point(&point);
			while(point.xco > xEnd)
			{
				point.xco--;
				if(p < 0)
					p += 2 * dy;
				else
				{
					point.yco++;
					p += 2 * (dy - dx);
				}
				CGR_draw_point(&point);
			}
		}
	
 	if(dx < dy)					/* Slope greater than one */
		{
			p = 2 * (dx - dy);
			if(xb>= xa)
			{
				point.xco = xb;
				point.yco = yb;
				yEnd = ya;
			}
			else
			{
				point.xco = xa;
				point.yco = ya;
				xEnd = xb;
				yEnd = yb;
			}
			CGR_draw_point(&point);
			while(point.yco < yEnd)
			{
				point.yco++;
				if(p < 0)
					p += 2 * dx;
				else
				{
					point.xco--;
					p += 2 * (dx - dy);
				}
				CGR_draw_point(&point);
			}
		}
	}
}


	
	
void CGR_draw_lines(CGR_line_p_t lines, int num_lines)
{
	while(num_lines--)
		CGR_draw_line(&lines[num_lines]);
}


/* CGR_draw_point ***************************************/

void CGR_draw_point( CGR_point_p_t point)
{
				MoveTo(point->xco, point->yco);
				LineTo(point->xco, point->yco);
}


/* CGR_draw_points **************************************/

void CGR_draw_points( CGR_point_p_t points, int num_points)
{
	while(num_points--) /* Thats better! */
		CGR_draw_point(&points[num_points]);
}

static long int Round(float num)
{
	return((long int) num +.5);
}

