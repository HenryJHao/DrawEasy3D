#ifndef SFLMODELMAPPING_H
#define SFLMODELMAPPING_H

#include "../common/SFLModelAbstract.h"
#include "../views/SFLViewMapping.h"
#include "../renders/SFLShaderProgram.h"
#include "../renders/SFLVertexArray.h"
#include "../renders/SFLTexture.h"

class SFLModelMapping: public SFLModelAbstract
{
public:
    enum MappingType{
        typeTex,
        typeLightDir,
        typeLightPoint,
        typeLightSpot,
        typeLightMulti
    };

    SFLModelMapping():SFLModelAbstract(){
        _btn->setText("贴图");
        _view = new SFLViewMapping(this);

        _vao = new SFLVertexArray();

        _programLight = new SFLShaderProgram();
        _programTex = new SFLShaderProgram();
        _programDir = new SFLShaderProgram();
        _programPoint = new SFLShaderProgram();
        _programSpot = new SFLShaderProgram();
        _programMulti = new SFLShaderProgram();

        _texDiffuse = new SFLTexture(true);
        _texSpecular = new SFLTexture(true);
        _texEmission = new SFLTexture(true);
    }
    ~SFLModelMapping(){
        DELETE_SAFE(_vao)

        DELETE_SAFE(_programLight)
        DELETE_SAFE(_programTex)
        DELETE_SAFE(_programDir)
        DELETE_SAFE(_programPoint)
        DELETE_SAFE(_programSpot)
        DELETE_SAFE(_programMulti)

        DELETE_SAFE(_texDiffuse)
        DELETE_SAFE(_texSpecular)
        DELETE_SAFE(_texEmission)
    }

    void initializeOpenGL() override {
        float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
        };
        _vao->initializeOpenGLFunctions();
        _vao->create();
        _vao->bind();
        _vao->setData(vertices, 8 * 6 * 6, 36, {3,3,2});

        gm::vec3 lightPosition(1.0f, 0.3f, 2.0f);
        gm::mat4 projection = gm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
        const float *projectonMatPtr = gm::valuePtrFrom(projection);

        initTexture();
        initProgramLight(lightPosition, projectonMatPtr);
        initProgramTex(projectonMatPtr);
        initProgramDir(lightPosition, projectonMatPtr);
        initProgramPoint(lightPosition, projectonMatPtr);
        initProgramSpot(lightPosition, projectonMatPtr);
        initProgramMulti(projectonMatPtr);
    }

    void render() override {
        ++_times;
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1, 0.1, 0.1, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _texDiffuse->active();
        _texDiffuse->bind();
        _texSpecular->active();
        _texSpecular->bind();
        _texEmission->active();
        _texEmission->bind();

        switch (type) {
            case typeTex:
                setProgramTexture();
                break;
            case typeLightDir:
                setProgramDir();
                break;
            case typeLightPoint:
                setProgramPoint();
                break;
            case typeLightSpot:
                setProgramSpot();
                break;
            case typeLightMulti:
                setProgramMulti();
                break;
        }

        if (type == typeLightMulti) return;

        _vao->bind();
        _vao->draw();

        _programLight->bind();
        _programLight->setUniform3f("materialColor", lightColor);
        _programLight->setUniformMatrix4fv("view", gm::valuePtrFrom(_delegateCamaera->viewMatrix()));

        _vao->draw();
    }

    MappingType type;

    gm::vec3 lightColor;
    GLfloat spotAngleInner;
    GLfloat spotAngleOuter;
    GLfloat emissionIntensity;

private:
    SFLVertexArray *_vao;
    SFLTexture *_texDiffuse;  //漫反射贴图
    SFLTexture *_texSpecular; //镜面贴图
    SFLTexture *_texEmission; //放射贴图
    SFLShaderProgram *_programTex;
    SFLShaderProgram *_programDir;
    SFLShaderProgram *_programPoint;
    SFLShaderProgram *_programSpot;
    SFLShaderProgram *_programMulti;
    SFLShaderProgram *_programLight;

    void initTexture(){
        _texDiffuse->initializeOpenGLFunctions();
        _texDiffuse->creat(GL_TEXTURE0);
        _texDiffuse->loadTexture2DFromPath(":/container2.png");

        _texSpecular->initializeOpenGLFunctions();
        _texSpecular->creat(GL_TEXTURE1);
        _texSpecular->loadTexture2DFromPath(":/container2_specular.png");

        _texEmission->initializeOpenGLFunctions();
        _texEmission->creat(GL_TEXTURE2);
        _texEmission->loadTexture2DFromPath(":/magic.jpeg");
    }

    void initProgramLight(gm::vec3 &lightPosition, const float *projectonMatPtr){
        gm::mat4 model = gm::translate(gm::mat4(1.0f), lightPosition);
        model = gm::scale(model, gm::vec3(0.2f));

        _programLight->initializeOpenGLFunctions();
        _programLight->loadFromPath(":/color.vsh",":/color.fsh");
        _programLight->bind();
        _programLight->setUniformMatrix4fv("projection", projectonMatPtr);
        _programLight->setUniformMatrix4fv("model", gm::valuePtrFrom(model));
    }

    void initProgramTex(const float *projectonMatPtr){
        _programTex->initializeOpenGLFunctions();
        _programTex->loadFromPath(":/texture.vsh",":/texture.fsh");
        _programTex->bind();
        _programTex->setUniformMatrix4fv("projection", projectonMatPtr);
        _programTex->setUniformMatrix4fv("model", gm::valuePtrFrom(gm::mat4(1.0)));
        _texDiffuse->bind();
        _programTex->setUniform1i("material", 0);
    }

    void initProgramDir(gm::vec3 &lightPosition, const float *projectonMatPtr){
        _programDir->initializeOpenGLFunctions();
        _programDir->loadFromPath(":/lightDir.vsh",":/lightDir.fsh");
        _programDir->bind();
        setBaseParam(_programDir, lightPosition, projectonMatPtr);
        _programDir->setUniform3f("light.direction", -lightPosition);
    }

    void initProgramPoint(gm::vec3 &lightPosition, const float *projectonMatPtr){
        _programPoint->initializeOpenGLFunctions();
        _programPoint->loadFromPath(":/lightPoint.vsh",":/lightPoint.fsh");
        _programPoint->bind();
        setBaseParam(_programPoint, lightPosition, projectonMatPtr);
    }

    void initProgramSpot(gm::vec3 &lightPosition, const float *projectonMatPtr){
        _programSpot->initializeOpenGLFunctions();
        _programSpot->loadFromPath(":/lightSpot.vsh",":/lightSpot.fsh");
        _programSpot->bind();
        setBaseParam(_programSpot, lightPosition, projectonMatPtr);
    }

    void setBaseParam(SFLShaderProgram *program, gm::vec3 &lightPosition, const float *projectonMatPtr){
        _texDiffuse->bind();
        program->setUniform1i("material.diffuse",  0);
        _texSpecular->bind();
        program->setUniform1i("material.specular", 1);
        _texEmission->bind();
        program->setUniform1i("material.emission", 2);
        program->setUniform1f("material.shininess", 32.0);
        program->setUniform3f("light.position", lightPosition);
        program->setUniformMatrix4fv("model", gm::valuePtrFrom(gm::mat4(1.0)));
        program->setUniformMatrix4fv("projection", projectonMatPtr);
    }

    void initProgramMulti(const float *projectonMatPtr){
        _programMulti->initializeOpenGLFunctions();
        _programMulti->loadFromPath(":/lightMulti.vsh",":/lightMulti.fsh");
        _programMulti->bind();
        _texDiffuse->bind();
        _programMulti->setUniform1i("material.diffuse",  0);
        _texSpecular->bind();
        _programMulti->setUniform1i("material.specular", 1);
        _texEmission->bind();
        _programMulti->setUniform1i("material.emission", 2);
        _programMulti->setUniform1f("material.shininess", 32.0);

        _programMulti->setUniformMatrix4fv("projection", projectonMatPtr);

        _programMulti->setUniform3f("lightDirect.direction", -0.2f, -1.0f, -0.3f);

        _programMulti->setUniform1f("spotlight.wConstant", 1.0f);
        _programMulti->setUniform1f("spotlight.wLinear",   0.09f);
        _programMulti->setUniform1f("spotlight.wQuadratic",0.032f);
    }

    void setProgramTexture(){
        _programTex->bind();
        _programTex->setUniformMatrix4fv("view", gm::valuePtrFrom(_delegateCamaera->viewMatrix()));
    }

    void setProgramDir(){
        _programDir->bind();
        _programDir->setUniform3f("light.ambient", lightColor * float(0.2));
        _programDir->setUniform3f("light.diffuse",lightColor * 0.5f);
        _programDir->setUniform3f("light.specular",lightColor);
        _programDir->setUniform1f("material.emitIntensity", emissionIntensity);

        _programDir->setUniform3f("viewPos", _delegateCamaera->position);
        _programDir->setUniformMatrix4fv("view", gm::valuePtrFrom(_delegateCamaera->viewMatrix()));
    }

    void setProgramPoint(){
        _programPoint->bind();
        _programPoint->setUniform3f("light.ambient", lightColor * float(0.2));
        _programPoint->setUniform3f("light.diffuse",lightColor * 0.5f);
        _programPoint->setUniform3f("light.specular",lightColor);
        _programPoint->setUniform1f("material.emitIntensity", emissionIntensity);

        _programPoint->setUniform3f("viewPos", _delegateCamaera->position);
        _programPoint->setUniformMatrix4fv("view", gm::valuePtrFrom(_delegateCamaera->viewMatrix()));
    }

    void setProgramSpot(){
        _programSpot->bind();
        _programSpot->setUniform3f("light.ambient", lightColor * float(0.2));
        _programSpot->setUniform3f("light.diffuse",lightColor * 0.5f);
        _programSpot->setUniform3f("light.specular",lightColor);

        _programSpot->setUniform1f("material.emitIntensity", emissionIntensity);

        _programSpot->setUniform3f("light.position", _delegateCamaera->position);
        _programSpot->setUniform3f("light.direction", _delegateCamaera->axisFront);

        _programSpot->setUniform1f("light.radiusInner", cos(gm::radians(spotAngleInner)));
        _programSpot->setUniform1f("light.radiusOuter", cos(gm::radians(spotAngleOuter)));

        _programSpot->setUniform3f("viewPos", _delegateCamaera->position);
        _programSpot->setUniformMatrix4fv("view", gm::valuePtrFrom(_delegateCamaera->viewMatrix()));
    }

    void setProgramMulti(){
        gm::vec3 pointLightPositions[] = {
            gm::vec3( 0.7f,  0.2f,  2.0f),
            gm::vec3( 2.3f, -3.3f, -4.0f),
            gm::vec3(-4.0f,  2.0f, -12.0f),
            gm::vec3( 0.0f,  0.0f, -3.0f)
        };
        gm::vec3 cubePositions[] = {
            gm::vec3( 0.0f,  0.0f,  0.0f),
            gm::vec3( 2.0f,  5.0f, -15.0f),
            gm::vec3(-1.5f, -2.2f, -2.5f),
            gm::vec3(-3.8f, -2.0f, -12.3f),
            gm::vec3( 2.4f, -0.4f, -3.5f),
            gm::vec3(-1.7f,  3.0f, -7.5f),
            gm::vec3( 1.3f, -2.0f, -2.5f),
            gm::vec3( 1.5f,  2.0f, -2.5f),
            gm::vec3( 1.5f,  0.2f, -1.5f),
            gm::vec3(-1.3f,  1.0f, -1.5f)
        };

        _programMulti->bind();
        _programMulti->setUniform1f("material.emitIntensity", emissionIntensity);

        // 1. 平行光
        _programMulti->setUniform3f("lightDirect.ambient", lightColor * 0.05f);
        _programMulti->setUniform3f("lightDirect.diffuse", lightColor * 0.4f);
        _programMulti->setUniform3f("lightDirect.specular",lightColor * 0.5f);

        // 2. 聚光灯
        _programMulti->setUniform3f("spotlight.ambient", lightColor * 0.05f);
        _programMulti->setUniform3f("spotlight.diffuse", lightColor * 0.8f);
        _programMulti->setUniform3f("spotlight.specular",lightColor * 0.8f);

        _programMulti->setUniform3f("spotlight.direction",_delegateCamaera->axisFront);
        _programMulti->setUniform3f("spotlight.position", _delegateCamaera->position);

        _programMulti->setUniform1f("spotlight.radiusOuter", cos(gm::radians(spotAngleOuter)));
        _programMulti->setUniform1f("spotlight.radiusInner", cos(gm::radians(spotAngleInner)));

        // 3. 点光源
        for(int i = 0; i < 4; ++i) {
            ostringstream fragmentAttrPrefix;
            fragmentAttrPrefix << "pointLights[" << i <<"].";
            string fragmentAttr = fragmentAttrPrefix.str();
            _programMulti->setUniform3f((fragmentAttr + "ambient").c_str(), lightColor * 0.05f);
            _programMulti->setUniform3f((fragmentAttr + "diffuse").c_str(), lightColor * 0.8f);
            _programMulti->setUniform3f((fragmentAttr + "specular").c_str(),lightColor * 0.8f);
            _programMulti->setUniform3f((fragmentAttr + "position").c_str(), pointLightPositions[i]);
            // 点光源衰减
            _programMulti->setUniform1f((fragmentAttr + "wConstant").c_str(), 1.0f);
            _programMulti->setUniform1f((fragmentAttr + "wLinear").c_str(),   0.09f);
            _programMulti->setUniform1f((fragmentAttr + "wQuadratic").c_str(),0.032f);
        }

        _vao->bind();
        _programMulti->setUniformMatrix4fv("view", gm::valuePtrFrom(_delegateCamaera->viewMatrix()));

        // 4. 画箱子
        for(int i = 0; i < 10; ++i) {
            gm::mat4 model = gm::translate(gm::mat4(1.0), cubePositions[i]);
            model = gm::rotate(model, 20.0f * i, gm::vec3(1.0f, 0.3f, 0.5f));
            _programMulti->setUniformMatrix4fv("model", gm::valuePtrFrom(model));
            _vao->draw();
        }

        // 5. 画灯光
        _programLight->bind();
        _programLight->setUniform3f("materialColor", lightColor);
        _programLight->setUniformMatrix4fv("view", gm::valuePtrFrom(_delegateCamaera->viewMatrix()));

        for(int i = 0; i < 4; ++i) {
            gm::mat4 model = gm::translate(gm::mat4(1.0f), pointLightPositions[i]);
            model = gm::scale(model, gm::vec3(0.2f));
            _programLight->setUniformMatrix4fv("model", gm::valuePtrFrom(model));
            _vao->draw();
        }
    }
};

#endif // SFLMODELMAPPING_H
