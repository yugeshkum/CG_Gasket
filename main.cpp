//
//  main.cpp
//  gasket
//
//  Created by Yugesh Kumar on 02/02/19.
//  Copyright © 2019 Yugesh Kumar. All rights reserved.
//

#include <stdio.h>
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGl/glu.h>

#include <GLUT/glut.h>

typedef float point[3];
point v[]={{0.0,0.0,1.0},{0.0,0.9,-0.3},{-0.8,-0.4,-0.3},{0.8,-0.4,-0.3}};
int n;
void triangle(point a,point b,point c)
{
    glBegin(GL_POLYGON);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}
void divide_triangle(point a,point b,point c,int m)
{
    point v1,v2,v3;
    int j;
    if(m>0)
    {
        for(j=0;j<=2;j++)
            v1[j]=(a[j]+b[j])/2;
        for(j=0;j<=2;j++)
            v1[j]=(a[j]+c[j])/2;
        for(j=0;j<=2;j++)
            v1[j]=(b[j]+c[j])/2;
        divide_triangle(a,v1,v2,m-1);
        divide_triangle(c,v2,v3,m-1);
        divide_triangle(b,v3,v1,m-1);
    }
    else
        triangle(a,b,c);
}
void tetrahedron(int m)
{
    glColor3f(1.0,0.0,0.0);
    divide_triangle(v[0],v[1],v[2],m);
    glColor3f(0.0,1.0,0.0);
    divide_triangle(v[3],v[2],v[1],m);
    glColor3f(0.0,0.0,1.0);
    divide_triangle(v[0],v[3],v[1],m);
    glColor3f(1.0,1.0,0.0);
    divide_triangle(v[0],v[2],v[3],m);
}
void display(void)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    tetrahedron(n);
    glFlush();
}
void myReshape(int w,int h)
{
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-2.0,2.0,-2.0,2.0,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc,char **argv)
{
    printf("No of divisions? ");
    scanf("%d",&n);
    glutCreateWindow("3d gasket");
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0,1.0,1.0,1.0);
    glutMainLoop();
    
}
