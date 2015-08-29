#ifndef SCENE_H
#define SCENE_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QMap>
#include <QDebug>

#define WIDTH  35
#define HEIGHT 20

struct Point {
    int xPos, yPos;

    Point(int _xPos, int _yPos) : xPos(_xPos), yPos(_yPos) {
        /**/
    }

    Point(void) {
        this->xPos = -1;
        this->yPos = -1;
    }
};

struct Color {
    GLfloat red, green, blue;

    Color(GLfloat _red, GLfloat _green, GLfloat _blue) {
        this->red = _red;
        this->green = _green;
        this->blue = _blue;
    }

    void operator()(void) {
        glColor3f(this->red, this->green, this->blue);
    }
};

class Scene : public QGLWidget
{
    Q_OBJECT
public:
    explicit Scene(QWidget *parent = 0);

    void drowField(void);
    void drawScene(void);

    QList<Point*> &getList(void);

    int getState(void);
    void setState(int _state);

    void set_Dir(int _direction);
    int get_Dir(void);

    void clearList(void);

    void setCount(int _count);
    void resetCount(int _count);

signals:
    void setValue(int);

protected:
    void initializeGL(void);
    void resizeGL(int _nWidth, int _nHeight);
    void paintGL(void);
    void keyPressEvent(QKeyEvent *event);

private:
    int count;
    int direction;
    float Scale;

    int nWidth;
    int nHeight;

    bool _state;

    QString color;

    QList<Color*> colors;
    QList<Point*> listPoint;
};

#endif // SCENE_H
