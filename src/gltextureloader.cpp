#include "gltextureloader.h"

#include <QGLWidget>
#include <QImage>

#include <QOpenGLTexture>

#include <QDebug>

bool GLTextureLoader::loadTexture(GLuint *texture, QString filename)
{
    QImage buf;
    //GLint alignment;
    //GLuint tex_id=0;
    if(!buf.load(filename))
    {
        qWarning("could not read image file");
        return false;
    }
    //tex = QGLWidget::convertToGLFormat(buf);

    QOpenGLTexture *tex=new QOpenGLTexture(buf.mirrored());

    //tex->setFormat(QOpenGLTexture::RGBA8_UNorm);
    tex->setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);
    tex->setWrapMode(QOpenGLTexture::ClampToBorder);

    *texture=tex->textureId();

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    /*

    glGenTextures(1, &tex_id);
    if(tex_id==0)
    {
        qWarning("could not create texture id");
        return false;
    }
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    //glGetIntegerv (GL_UNPACK_ALIGNMENT, &alignment);
    //glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    //glPixelStorei (GL_UNPACK_ALIGNMENT, alignment);
    *texture=tex_id;
    */


    return true;
}
