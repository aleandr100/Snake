#include <GL/glu.h>
#include <GL/glut.h>

#include "scene.h"

Scene::Scene(QWidget *parent) : QGLWidget(parent) {

    Scale = 20;
    this->count = 0;
    this->direction = 103;

    nWidth = Scale*WIDTH;
    nHeight = Scale*HEIGHT;

    this->_state = false;

    setFocusPolicy(Qt::StrongFocus);

    colors.append(new Color(1.0, 0.0, 1.0));
    colors.append(new Color(0.5, 0.3, 0.9));
    colors.append(new Color(1.0, 1.0, 0.0));

    this->setGeometry(nWidth, nHeight, nWidth, nHeight);
}

void Scene::initializeGL(void) {
    glClearColor(0.75, 0.75, 0.75, 1.0);
}

void Scene::resizeGL(int _nWidth, int _nHeight) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)_nWidth, (GLint)_nHeight);
}

void Scene::paintGL(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);              /* чистим буфер изображения и буфер глубины */
    glMatrixMode(GL_PROJECTION);                                     /* устанавливаем матрицу */
    glLoadIdentity();                                                /* загружаем матрицу */
    gluOrtho2D(0, nWidth, 0, nHeight);                               /* подготавливаем плоскости для матрицы */

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    drowField();

    drawScene();
}

void Scene::drowField(void) {

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
         for (int i = 0; i < nWidth; i += this->Scale) {
             glVertex2f(i, 0);
             glVertex2f(i, nHeight);
         }

         for (int j = 0; j < nHeight; j += this->Scale) {
             glVertex2f(0, j);
             glVertex2f(nWidth, j);
         }
    glEnd();
}

void Scene::drawScene(void) {
    int in = 0;

    colors[in++]->operator()();

    if (listPoint.empty()) return;

    QList<Point*>::iterator it = listPoint.begin();
    while (it != listPoint.end()) {
        if ((*it) == NULL){
            if (this->count < 3) ++in;
             colors[in++]->operator()();
            ++it;
            continue;
        }

        glBegin(GL_QUADS);
             glVertex2f(((*it)->xPos+0.1) * this->Scale, ((*it)->yPos+0.1) * this->Scale);
             glVertex2f(((*it)->xPos-0.1) * this->Scale + this->Scale, ((*it)->yPos+0.1) * this->Scale);
             glVertex2f(((*it)->xPos-0.1) * this->Scale + this->Scale, ((*it)->yPos-0.1) * this->Scale + this->Scale);
             glVertex2f(((*it)->xPos+0.1) * this->Scale, ((*it)->yPos-0.1) * this->Scale + this->Scale);
        glEnd();
        ++it;
    }
}

void Scene::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {
        case Qt::Key_Up:
            if (this->get_Dir() == GLUT_KEY_DOWN) {
                break;
            } else this->set_Dir(GLUT_KEY_UP);
                break;
        case Qt::Key_Left:
            if (this->get_Dir() == GLUT_KEY_RIGHT) {
                break;
            } else {
                this->set_Dir(GLUT_KEY_LEFT);
            }
            break;
        case Qt::Key_Right:
            if (this->get_Dir() == GLUT_KEY_LEFT) {
                break;
            } else this->set_Dir(GLUT_KEY_RIGHT);
            break;
        case Qt::Key_Down:
            if (this->get_Dir() == GLUT_KEY_UP) {
                break;
            } else this->set_Dir(GLUT_KEY_DOWN);
                break;
        default: break;
    }
    emit setValue(this->get_Dir());
}

void Scene::clearList(void) {
    if (!listPoint.empty()) {
        QList<Point*>::iterator it = listPoint.begin();
        while (it != listPoint.end()) {
            if ((*it) == NULL){
                ++it;
                continue;
            }
            ++it;
            delete (*it);
        }
        listPoint.clear();
    }
    return;
}

void Scene::set_Dir(int _direction) {
    this->direction = _direction;
}

int Scene::get_Dir(void) {
    return this->direction;
}

QList<Point*> &Scene::getList(void) {
    return this->listPoint;
}

void Scene::setState(int _state) {
    this->_state = _state;
}

int Scene::getState(void) {
    return this->_state;
}

void Scene::setCount(int _count) {
    this->count += _count;
}

void Scene::resetCount(int _count) {
    this->count = _count;
}

