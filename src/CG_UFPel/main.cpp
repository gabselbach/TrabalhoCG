
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <iostream>
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
#include <math.h>  
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
  //divide um pelo outro
  //pega a parte fracionaria e  multiplica pelo divisior
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

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader ourShader(FileSystem::getPath("resources/cg_ufpel.vs").c_str(), FileSystem::getPath("resources/cg_ufpel.fs").c_str());

    // load models
    // -----------
    Model ourModel1(FileSystem::getPath("resources/objects/nanosuit/nanosuit.obj"));
   Model ourModel2(FileSystem::getPath("resources/objects/mo/SS4_Zoom.obj"));
    Model ourModel3(FileSystem::getPath("resources/objects/book2/bookVintage.obj"));
    vector <glm::mat4> books;
    vector <glm::mat4> phones;
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
  srand(time(NULL)); 
    for (int i = 0; i < num_books; ++i)
    {
        delta_books[i]=0.0f;
        first_books[i] =0.0f;
        glm::mat4 m;
        res = min_x + rand() * (max_x - min_x) / RAND_MAX;
        m = glm::translate(m, glm::vec3(res, altura_objetos, 0.0f)); 
        m = glm::scale(m, glm::vec3(0.1f, 0.1f, 0.1f));  
      books.push_back(m);
    }
    for (int i = 0; i < num_phones; ++i)
    {
        delta_phones[i]=0.0f;
         first_phones[i] =0.0f;
      glm::mat4 m;
        res = min_x + rand() * (max_x - min_x) / RAND_MAX;
        m = glm::translate(m, glm::vec3(res, altura_objetos, 0.0f)); 
        m = glm::scale(m, glm::vec3(0.1f, 0.1f, 0.1f));  
      phones.push_back(m);
    }
    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    float firstTime =0.0f;
    /* inicializando a semente do gerador aleatorio*/
 
  //res = min_x + rand() * (max_x - min_x) / RAND_MAX;

      glm::mat4 model1; 
        model1 = glm::translate(model1, glm::vec3(0.0f, -2.5f, 0.0f)); 
        model1 = glm::scale(model1, glm::vec3(0.2f, 0.2f, 0.2f));  
        // std::cout <<"\n\n";
        // std::cout <<"Bem vindo ao jogo tal\n\n";
         //std::cout <<"Instruções de jogo:\n";
        res=2;
       
    float temp_caindo =0.0f;
    i=valido_phones;
    j=valido_books;
     glViewport( 0.0f, 0.0f, SCR_WIDTH, SCR_HEIGHT ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho( 0, SCR_WIDTH, 0, SCR_HEIGHT, 0, 1 ); // essentially set coordinate system
    glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity( ); // same as above comment
    
    GLfloat lineVertices[] =
    {
        200, 100, 0,
        100, 300, 0
    };
    while (!glfwWindowShouldClose(window))
    {

         float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
         if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && play_cai_phone==false && play_cai_book==false){
            play_cai_phone= true;
            play_cai_book= true;
            first_phones[0]=currentFrame;
            first_books[0]=currentFrame+0.2f;
         }
         if(play_cai_phone){
            temp_caindo_phones+=deltaTime;
            std::cout <<"tempo caido phones:"<< temp_caindo_phones <<"\n";
            if(i <liberado_phones)
            {
                
                delta_phones[i] = currentFrame - first_phones[i];
                if(delta_phones[i] >0.0f){
                    if(delta_phones[i]<duracao_caida){
                            float val_y = (delta_phones[i] * 0.03f);
                            phones[i][3][1] -= val_y;
                    }else{
                        ++valido_phones;
                    }
                    if ((temp_caindo_phones>res) && (liberado_phones!= num_phones))  {
                       
                          res+=2;
                        first_phones[liberado_phones] = currentFrame;
                        delta_phones[liberado_phones] =0.0f;
                        if(liberado_phones!= num_phones){
                            ++liberado_phones;
                           
                        }else{
                            play_cai_phone = false;
                            break;
                        }
                    }
                }
                ++i;
            }else{
                i=valido_phones;
            }
        }
        if(play_cai_book){
            if(j <liberado_books)
            {
               
                delta_books[j] = currentFrame - first_books[j];
                if(delta_books[j] >0.0f){
                    if(delta_books[j]<duracao_caida){
                       
                            float val_t = (delta_books[j] * 0.03f);
                            books[j][3][1] -= val_t;
                    }else{
                        ++valido_books;
                    }
                    if ((temp_caindo_phones>res_b) && (liberado_books!= num_books))  {
                       
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
        
            
        
        // per-frame time logic
        
        // --------------------
       
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // view/projection transformations
        //inicialização
      
        //começou a animaçao
       
     glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
            anda = sleep * deltaTime;
            model1 = glm::translate(model1,glm::vec3(-anda,0.0f,0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
            anda = sleep * deltaTime;
            model1 = glm::translate(model1,glm::vec3(anda,0.0f,0.0f));
        }
        
      
        ourShader.setMat4("model", model1);
        ourModel1.Draw(ourShader);
        for (int i = 0; i < num_books; ++i)
        {
            ourShader.setMat4("model", books[i]);
            ourModel3.Draw(ourShader);
        }
        for (int i = 0; i < num_phones; ++i)
        {
            ourShader.setMat4("model", phones[i]);
            ourModel2.Draw(ourShader);
        }
           glEnable( GL_LINE_SMOOTH );
        glEnable( GL_LINE_STIPPLE );
        glPushAttrib( GL_LINE_BIT );
        glLineWidth( 10 );
        glLineStipple( 1, 0x00FF );
        glEnableClientState( GL_VERTEX_ARRAY );
        glVertexPointer( 3, GL_FLOAT, 0, lineVertices );
        glDrawArrays( GL_LINES, 0, 2 );
        glDisableClientState( GL_VERTEX_ARRAY );
        glPopAttrib( );
        glDisable( GL_LINE_STIPPLE );
        glDisable( GL_LINE_SMOOTH );
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
