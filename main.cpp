#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>




#include <GL/glut.h>





/* Constante utilizada para desenhar um círculo */

#define PI 3.1415926


GLfloat win, r, g, b;
struct tm *data_hora_atual;
time_t segundos;

/* GLUT callback Handlers */

GLint x = 0,y = 0 , raio =100;
GLint altura = 256, largura = 256;
GLfloat Time;
//GLint delay,tm_hour=0,tm_min=0,tm_sec=0;
//GLint horas=8, minutos=47, segundos=24;


#define CIRCLE_STEPS 60
// Função callback de redesenho da janela de visualização

void linha_Hora(float angulo)
{
    glColor3f(1.0f,0.0f,0.0f);
    glVertex2f(x + (cos(angulo) * (raio-20)), y + (sin(angulo) * (raio-20)));

    glVertex2f(x + (cos(angulo) * (raio)), y + (sin(angulo) * (raio)));


}
void linha_Minuto(float angulo)
{
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(x + (cos(angulo) * (raio-10)), y + (sin(angulo) * (raio-10)));

    glVertex2f(x + (cos(angulo) * (raio)), y + (sin(angulo) * (raio)));


}
void  circulo_Amarelo(float angulo){
    GLint i;
    glLoadIdentity();
    gluOrtho2D(-10.0,10.0,-10.0,10.0);
    glLineWidth(3.0);
    glColor3f(1.0, 1.0, 0.0f);

    glBegin(GL_POLYGON);

    for (i = 0; i < CIRCLE_STEPS; i++) {

         angulo = i * PI * 2 / CIRCLE_STEPS;
            glVertex2f(x + (cos(angulo) * raio), y + (sin(angulo) * raio));

    }

    glEnd();

}
void line_Horas(int hora){
    glLoadIdentity();
    // altera a espessura da linha
    glLineWidth(4.0);
    glColor3f(1.0,1.0,0.0f);
    // Rotaciona o ponteiro de horas
    glRotatef(-30.0*(hora),0.0,0.0,1.0);
    // horas
    glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 60.0);
    glEnd();

}

void line_Minuto(int minuto)
{
 // Altera a espessura da linha
    glLoadIdentity();
    glColor3f(1.0,1.0,0.0f);
    glLineWidth(4.0);
    // Rotaciona o ponteiro de minutos
    glRotatef(-6*(minuto),0.0,0.0,1.0);
    // desenha o ponteiro de minutos
    glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 80.0);
    glEnd();

}

void line_Segundo(int seg )
{
    glLoadIdentity();
     glColor3f(1.0,1.0,0.0f);

    // Altera a espessura da linha
    glLineWidth(1.0);

    // Rotaciona o ponteiro de segundos
    glRotatef(-6*(seg),0.0,0.0,1.0);
    // desenha o ponteiro de segundos
    glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, (raio-10));
    glEnd();
}

void desenha ()
{
    float angulo;

    time(&segundos);
    data_hora_atual = localtime(&segundos);


    //inicializa a tela

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


   // Define a cor corrente
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    gluOrtho2D(-150.0,150.0,-150.0,150.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLint i;
    // Altera a espessura da linha
    glLoadIdentity();
    glLineWidth(3.0);


    glBegin(GL_LINES);

    for (i = 0; i < CIRCLE_STEPS; i++) {

        angulo = i * PI * 2 / CIRCLE_STEPS;

         if (i%5==0){

            linha_Hora(angulo);


        }
        else{


            linha_Minuto(angulo);

        }

    }

    glEnd();

        /*----------------------------------------------------------------------------------*/
    circulo_Amarelo(angulo);

        /*----------------------------------------------------------------------------------*/
    line_Horas(data_hora_atual->tm_hour);
    /*----------------------------------------------------------------------------------*/
    line_Minuto(data_hora_atual->tm_min);

      /*----------------------------------------------------------------------------------*/
   line_Segundo( data_hora_atual->tm_sec);


glFlush();
glutSwapBuffers();
}
static void idle(void)
{
    glutPostRedisplay();
}







int main(int argc, char *argv[])
{
    // Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    //Define o tamanho da janela
     glutInitWindowSize(350,300);

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(10,10);


	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(500,500);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Relógio");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(desenha);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //Desenhar a função

     glutIdleFunc(idle);





    /* Iniciar Ciclo da GLUT*/
    glutMainLoop();
    return 0;
}
