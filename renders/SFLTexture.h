#ifndef SFLTEXTURE_H
#define SFLTEXTURE_H
#include <QOpenGLFunctions>
#include <QImage>

class SFLTexture : public QOpenGLFunctions
{
public:
    SFLTexture(bool isUseMipMap = false):QOpenGLFunctions() {
        _isUseMipMap = isUseMipMap;
    }
    ~SFLTexture() {
        if (!_isInitialized || !_isCreateBySelf || !_texRef) return;

        glDeleteTextures(1, _texRef);
    }
    void initializeOpenGLFunctions(){
        _isInitialized = true;
        QOpenGLFunctions::initializeOpenGLFunctions();
    }

    void creat(){
        _isCreateBySelf = true;

        glGenTextures(1, _texRef);
        _texID = _texIDMap[_texRef];
    }
    void setRef(GLuint id){
        _isCreateBySelf = false;

        _texRef = id;
        _texID = _texIDMap[id];
    }

    void bind(){
        if (_texRef) return;

        glActiveTexture(_texID);
        glBindTexture(GL_TEXTURE_2D, _texRef);
    }
    void unBind(){
        if (_texRef) return;

        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, GL_TEXTURE0);
    }

    void setWrap(GLint s = GL_CLAMP_TO_EDGE, GLint t = GL_CLAMP_TO_EDGE){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
    }

    void setFilter(GLint min = GL_NEAREST, GLint max = GL_LINEAR){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, max);
    }
    void setFilterMipMap(GLint min = GL_LINEAR_MIPMAP_NEAREST, GLint max = GL_LINEAR_MIPMAP_LINEAR){
        // 采用多级渐远纹理，的过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, max);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void loadTexture2DFromPath(const char * path){
        QImage qImage(imgPath);
        int width = qImage.width();
        int height = qImage.height();

        bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, qImage.bits());

        // 设定当前纹理，开始设置纹理属性
        // 纹理环绕方式
        setWrap();
        // 纹理过滤方式
        if (_isUseMipMap){
            setFilterMipMap();
        } else {
            setFilter();
        }
    }

private:
    bool _isUseMipMap;
    bool _isInitialized = false;
    bool _isCreateBySelf = false;
    GLuint _texRef = 0;
    GLuint _texID = 0;
    GLuint _texIDMap[] = {GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5, GL_TEXTURE6, GL_TEXTURE7};
};
#endif // SFLTEXTURE_H