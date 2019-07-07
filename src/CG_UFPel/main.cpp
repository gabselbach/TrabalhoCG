#if defined(_MSC_VER) && (_MSC_VER >= 1310)
#   pragma warning(disable: 4996) // Disable the fopen, strcpy, sprintf being unsafe warning
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>
#include <learnopengl/game.h>
#include <irrklang/irrKlang.h>
#include <iostream>
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
#include <math.h>  
#include<string>
using std::string;
#define GLT_IMPLEMENTATION
#include "gltext.h" /* https://github.com/MrVallentin/glText */

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
    
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// camera
Camera camera(glm::vec3(0.0f, 1.5f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float positionx1 = 0.0f, positionx2 = 0.0f,deltaT =0.0f;
int modelCurrent = 5;
bool animacao = false;
bool perdeu = false;
bool ganhou = false;
float anda=0.0f;
float sleep = 10.0f; 
float altura_objetos = 5.8f;
bool play_cai_phone = false;
bool play_cai_book = false;
float duracao_caida = 6.9f;
float first_t_phone=0.0f;
float first_t_book=0.0f;
 float min_x = -4.5f;
  float max_x =  4.3f;
  float yPersonagem =0.8f;
  int qual_model =1;
  //divide um pelo outro
  //pega a parte fracionaria e  multiplica pelo divisior
  Game game(5);
int main()
{
  
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // para o texto
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);

    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    // glfw window creation
    // --------------------
    
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // OPÇÕES ṔARA MEXER A CAMERA PELO SCROLL DO MOUSE
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(1);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
         fprintf(stderr, "Failed to load OpenGL functions and extensions\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

   
    // ATE AQUI

    // build and compile shaders
    // -------------------------
    Shader ourShader(FileSystem::getPath("resources/cg_ufpel.vs").c_str(), FileSystem::getPath("resources/cg_ufpel.fs").c_str());

    // load models
    // -----------
    Model ourModel1(FileSystem::getPath("resources/objects/nanosuit/nanosuit.obj"));
   Model ourModel2(FileSystem::getPath("resources/objects/mo/SS4_Zoom.obj"));
    Model ourModel3(FileSystem::getPath("resources/objects/book2/bookVintage.obj"));
    Model ourModel4(FileSystem::getPath("resources/objects/planet/planet.obj"));
    Model ourModel5(FileSystem::getPath("resources/objects/cyborg/cyborg.obj"));
    vector <glm::mat4> books;
    vector <glm::mat4> phones;
    int pontos=0;
    int vidas = 3;
    int contador_tempo_caidos_books=0;
     int contador_tempo_caidos_phones=0;
    int atual_books=0;
    int atual_phones=0;
    int liberado_books=1;
    int liberado_phones=1;
    int num_books=10;
    int num_phones=15;
    float res_b = 0.5f;
    int res=0;
    float delta_books[num_books];
    float delta_phones[num_phones];
    float first_books[num_books];
    float first_phones[num_phones];
    float resto=3.0f;
    int valido_phones=0,i,j;
     float temp_caindo_phones =0.0f;
     int valido_books=0;
     float temp_caindo_books =0.0f;
     bool colision[num_phones];
     bool colision_b[num_books];
     float positionXModel =0.0f;
     float positionXPhones[num_phones];
  srand(time(NULL)); 
    for (int i = 0; i < num_books; ++i)
    {
         colision_b[i]=false;
        delta_books[i]=0.0f;
        first_books[i] =0.0f;
        glm::mat4 m;
        float pos_x = min_x + rand() * (max_x - min_x) / RAND_MAX;
        m = glm::translate(m, glm::vec3(pos_x, altura_objetos, 0.0f)); 
        m = glm::scale(m, glm::vec3(0.1f, 0.1f, 0.1f));  
      books.push_back(m);
    }
    for (int i = 0; i < num_phones; ++i)
    {
     
        colision[i]=false;
        delta_phones[i]=0.0f;
         first_phones[i] =0.0f;
      glm::mat4 m;
        float pos_x = min_x + rand() * (max_x - min_x) / RAND_MAX;
        m = glm::translate(m, glm::vec3(pos_x, altura_objetos, 0.0f)); 
        positionXPhones[i]=pos_x;
        m = glm::scale(m, glm::vec3(0.1f, 0.1f, 0.1f));  
      phones.push_back(m);
    }
    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    float firstTime =0.0f;

      glm::mat4 model1; 
        model1 = glm::translate(model1, glm::vec3(0.0f, -2.5f, 0.0f)); 
        model1 = glm::scale(model1, glm::vec3(0.2f, 0.2f, 0.2f));
        //model2 = glm::translate(model2, glm::vec3(0.0f, -2.5f, 0.0f)); 
       // model2= glm::scale(model2, glm::vec3(0.2f, 0.2f, 0.2f));
       // modelaux = glm::translate(modelaux, glm::vec3(model1[3][0]+1.0f, -2.0f, 0.0f)); 
        //modelaux = glm::scale(modelaux, glm::vec3(0.2f, 0.2f, 0.2f));  
        // std::cout <<"\n\n";
        // std::cout <<"Bem vindo ao jogo tal\n\n";
         //std::cout <<"Instruções de jogo:\n";
        res=2;
       
    float temp_caindo =0.0f;
    i=valido_phones;
    j=valido_books;
    // texto
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    if (!gltInit())
    {
        fprintf(stderr, "Failed to initialize glText\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }
    GLTtext *text2 = gltCreateText();
     GLTtext *text3 = gltCreateText();
     
     int viewportWidth, viewportHeight;
     bool comeco = false;
     bool play_jogo= false;
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        if(glfwGetKey(window, GLFW_KEY_P) && !play_jogo){
            play_jogo=true;
        }
        if(play_jogo){
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && qual_model==2 && currentFrame >0.5f && !comeco){
            model1[0][0]=0.2f;
             model1[1][1]=0.2f;
             model1[2][2]=0.2f;
            qual_model =1;
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && qual_model==1 && currentFrame >0.5f && !comeco){
             model1[0][0]=0.8f;
             model1[1][1]=0.8f;
             model1[2][2]=0.8f;
             //model1 = glm::scale(model1, glm::vec3(0.8f, 0.8f, 0.8f));
            qual_model =2;
        }
    if(vidas==0)
        perdeu = true;
    if(pontos==10)
        ganhou = true;
    char *pt = game.setaTexto(pontos,"pontos=");
    char *vd = game.setaTexto(vidas,"vidas=");
    gltSetText(text2,pt );
    gltSetText(text3,vd );

        //texto
         glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
         glViewport(0, 0, viewportWidth, viewportHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         gltBeginDraw();
        gltColor(1.0f, 1.0f, 1.0f, 1.0f);
        
         
         if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && play_cai_phone==false && play_cai_book==false){
            comeco = true;
            play_cai_phone= true;
            play_cai_book= true;
            first_phones[0]=currentFrame;
            first_books[0]=currentFrame+0.2f;
         }
         if(comeco && !play_cai_phone && !play_cai_book)
                std::cout <<"Acabou as coisas\n\n";
         if(!perdeu && !ganhou ){
            gltDrawText2D(text2, 10.0f, 0.0f, 1.0f);
            gltDrawText2D(text3, 10.0f, 30.0f, 1.0f);
         if(play_cai_phone){
            temp_caindo_phones+=deltaTime;
            
            if(i <liberado_phones){
                
                delta_phones[i] = currentFrame - first_phones[i];
                if(delta_phones[i] >0.0f){
                     float x_min = model1[3][0]-0.5f;
                                float x_max = model1[3][0]+0.5f;
                    if(delta_phones[i]<duracao_caida){
                            float val_y = (delta_phones[i] * 0.03f);
                            phones[i][3][1] -= val_y;

                            if(phones[i][3][1]<- 0.9f && colision[i]==false && (phones[i][3][0]+2.0f)>x_min && phones[i][3][0]<x_max){
                                ++pontos;
                                colision[i]=true;
                            }
                    }else{
                        ++valido_phones;
                        phones[i][3][1] = -30.0f;
                    }
                    if ((temp_caindo_phones>res) && (liberado_phones!= num_phones))  {
                       
                          res+=2;
                        first_phones[liberado_phones] = currentFrame;
                        delta_phones[liberado_phones] =0.0f;
                        if(liberado_phones!= num_phones){
                            ++liberado_phones;
                           
                        }
                        if(liberado_phones>num_phones)
                             play_cai_phone = false;
                    }
                }
                ++i;
            }else{
                i=valido_phones;
            }
            if(valido_phones==num_phones && !ganhou)
                perdeu=true;
        }
        if(play_cai_book){
             
            temp_caindo_books+=deltaTime;
            if(j <liberado_books)
            {
                delta_books[j] = currentFrame - first_books[j];
                if(delta_books[j] >0.0f){
                    float x_min = model1[3][0]-0.2f;
                    float x_max = model1[3][0]+0.2f;
                    if(delta_books[j]<duracao_caida){  
                        float val_t = (delta_books[j] * 0.03f);
                        books[j][3][1] -= val_t;
                        if(books[j][3][1]< -0.9f && colision_b[j]==false && (books[j][3][0]+1.0f)>x_min && books[j][3][0]<x_max){
                                --vidas;
                                colision_b[j]=true;
                            }
                    }else{
                        ++valido_books;
                        books[j][3][1] = -30.0f;
                    }
                    if ((temp_caindo_books>res_b) && (liberado_books!= num_books))  {
                          res_b+=2.8f;
                        first_books[liberado_books] = currentFrame;
                        delta_books[liberado_books] =0.0f;
                        if(liberado_books!= num_books){
                            ++liberado_books;
                           
                        }else{
                           
                            play_cai_book = false;
                            break;
                        }
                    }
                }
                ++j;
            }else{
                j=valido_books;
            }
        }
    }else{
         GLTtext *tfinal = gltCreateText();
         if(ganhou)
            gltSetText(tfinal,"Parabens voce esta formado" );
        if(perdeu)
            gltSetText(tfinal,"Voce ficara eternamente na faculdade" );
         gltDrawText2DAligned(tfinal,
            (GLfloat)(viewportWidth / 2),
            (GLfloat)(viewportHeight / 2),
            1.5f,
            GLT_CENTER, GLT_CENTER);
    }
    gltEndDraw(); 
        processInput(window);
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        ourShader.use();
       
     glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        if(!perdeu && !ganhou ){
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
            anda = sleep * deltaTime;
            positionXModel -=0.1f;
            model1 = glm::translate(model1,glm::vec3(-0.1f,0.0f,0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
            anda = sleep * deltaTime;
            positionXModel +=0.1f;
            if((model1[3][0]+0.1)> min_x && (model1[3][0]+0.1)< max_x)
                model1 = glm::translate(model1,glm::vec3(0.1f,0.0f,0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
            float we=0;
            //restart jogo
        }
        
            ourShader.setMat4("model", model1);
            if(qual_model==1)
                ourModel1.Draw(ourShader);
            if(qual_model==2)
                ourModel5.Draw(ourShader);
            for (int i = 0; i < num_books; ++i)
            {
                if(!(colision_b[i])){
                    ourShader.setMat4("model", books[i]);
                    ourModel2.Draw(ourShader);
                }
            }
            for (int i = 0; i < num_phones; ++i)
            {
                if(!(colision[i])){
                    ourShader.setMat4("model", phones[i]);
                    ourModel3.Draw(ourShader);
                }
            }
        }
      }else{
        glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
         glViewport(0, 0, viewportWidth, viewportHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GLTtext *text4 = gltCreateText();
        GLTtext *text5 = gltCreateText();
        GLTtext *text6 = gltCreateText();
        GLTtext *text7 = gltCreateText();
        GLTtext *text8 = gltCreateText();
        GLTtext *text9 = gltCreateText();
        GLTtext *text10 = gltCreateText();
        GLTtext *text11 = gltCreateText();
         gltSetText(text4,"Instruções de Jogo:" );
         gltSetText(text5,"1- Para entrar no jogo :P");
         gltSetText(text6,"2- Voce pode trocar de personagem antes de começar o jogo aperte: 1 ou 2");
          gltSetText(text7,"3 - para começar o jogo aperte: C");
          gltSetText(text8,"4 - para movimentar o boneco aperte nas setas para o lado do teclado"); 
         gltSetText(text9,"Objetivo"); 
          gltSetText(text10,"Voce deve pegar 10 livros para se formar");
         gltSetText(text11," voce só tem 3 vidas então só pode pegar ate duas cameras " );
           gltBeginDraw();
            gltColor(1.0f, 1.0f, 1.0f, 1.0f);
            gltDrawText2D(text4, 10.0f, 0.0f, 1.0f);
            gltDrawText2D(text5, 10.0f, 30.0f, 1.0f);
            gltDrawText2D(text6, 10.0f, 60.0f, 1.0f);
            gltDrawText2D(text7, 10.0f, 90.0f, 1.0f);
            gltDrawText2D(text8, 10.0f, 120.0f, 1.0f);
            gltDrawText2D(text9, 10.0f, 150.0f, 1.0f);
            gltDrawText2D(text10, 10.0f, 180.0f, 1.0f);
            gltDrawText2D(text11, 10.0f, 210.0f, 1.0f);
            gltEndDraw(); 
          processInput(window);
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        ourShader.use();
       
     glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
      }

         glfwSwapBuffers(window);
        glfwPollEvents();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        
}
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// OPÇÕES ṔARA MEXER A CAMERA PELO SCROLL DO MOUSE

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
