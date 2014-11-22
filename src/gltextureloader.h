#ifndef GLTEXTURELOADER_H
#define GLTEXTURELOADER_H

#include <QOpenGLFunctions>

class GLTextureLoader : protected QOpenGLFunctions
{
public:
    static bool loadTexture(GLuint *texture, QString filename);
};

#endif // GLTEXTURELOADER_H
